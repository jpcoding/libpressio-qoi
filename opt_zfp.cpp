#include <iostream>
#include <limits>
#include <libpressio.h>
#include <libpressio_ext/cpp/libpressio.h>
#include <libpressio_ext/io/posix.h>
#include <libpressio_opt/pressio_search_defines.h>
#include "mpi.h"
#include "utils/FileUtils.h"

float* make_data() {
  size_t idx = 0;
  auto data = static_cast<float*>(malloc(sizeof(float)*500*500*100));
  for (int i = 0; i < 500; ++i) {
    for (int j = 0; j < 500; ++j) {
      for (int k = 0; k < 100; ++k) {
        data[idx] = i*i + 2*j - k;
        idx++;
      }
    }
  }
  return data;
}


int main(int argc, char *argv[])
{
  int rank, size, thread_provided;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &thread_provided);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout<<"szie = " << size <<std::endl;

  if(thread_provided != MPI_THREAD_MULTIPLE) {
    if(rank == 0){
      std::cout << "insufficient thread support from MPI" << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, 3);
  }
size_t num_elements=0;
 float *data=readfile<float>(argv[6], numelements);	
 float data_max =data[0];
 float data_min=data[0];
 for (size_t i=0; i<numelements; i++)
 {
	if(data[i]>data_max) data_max=data[i];
	if (data[i]<data_min) data_min=data[i];
 }
 float data_range = data_max-data_min;

 free(data);

  pressio library;
  std::string metrics_ids[] = {"size", "time", "error_stat"};
  pressio_metrics metrics = library.get_metrics(std::begin(metrics_ids), std::end(metrics_ids));
  pressio_options metric_options = metrics->get_options();

  //   std::vector<std::string> lua_scripts { R"lua(
  //   local cr = metrics['size:compression_ratio'];
  //   local x2 = metrics['error_stat:max_x_sq_diff_rel'];
  //   if (x2 <0.06 or x2 >0.1) then
  //     objective = -math.huge;
  //   else
  //     objective = cr;
  //   end
  //   return "objective", objective
  // )lua"};


  double target_x2_error=atof(argv[1]);
  double target_upper=atof(argv[2]);
  double target_lower=atof(argv[3]);
  
  std::string string1 = R"lua(
    local cr = metrics['size:compression_ratio'];
    local x2 = metrics['error_stat:max_x_sq_diff_rel'];
    if (x2 < )lua";
  std::string string2(argv[3]);

  std::string string3 = R"lua( or x2 > )lua";

  std::string string4(argv[2]);

  std::string string5 = R"lua( ) then
      objective = -math.huge;
    else
      objective = cr;
    end
    return "objective", objective
  )lua";

  std::vector<std::string> lua_scripts {string1+string2+string3+string4+string5};

  auto compressor = library.get_compressor("opt");
  auto configuration = compressor->get_configuration();
  // if(rank == 0) {
  //   std::cout << "configuration:" << std::endl << configuration << std::endl;
  // }

  // auto const inputs = std::vector<std::string>{"sz3:rel_error_bound"};
  //   auto const outputs = std::vector<std::string>{"composite:objective", "size:compression_ratio", "error_stat:max_x_sq_diff_rel"};
  // auto const headers = [&]()
  // {
  //   std::vector<std::string> headers;
  //   headers.insert(headers.end(), inputs.begin(), inputs.end());
  //   headers.insert(headers.end(), outputs.begin(), outputs.end());
  //   return headers;
  // }();

  // std::cout<<headers <<std::endl;

  auto options = compressor->get_options();
  options.set("composite:scripts", lua_scripts);
    auto const inputs = std::vector<std::string>{"zfp:accuracy"};
    // auto const inputs = std::vector<std::string>{"pressio:rel"};
    auto const outputs = std::vector<std::string>{ "composite:objective","error_stat:max_x_sq_diff_rel","size:compression_ratio"};
  auto const headers = [&]()
  {
    std::vector<std::string> headers;
    headers.insert(headers.end(), inputs.begin(), inputs.end());
    headers.insert(headers.end(), outputs.begin(), outputs.end());
    return headers;
  }();
  pressio_data lower_bound{atof(argv[4])*data_range};
  pressio_data upper_bound{atof(argv[5])*data_range};
  pressio_data guess= pressio_data{atof(argv[5])*0.5*data_range};

  // options.set("opt:search", "binary");
  //   options.set("opt:lower_bound", lower_bound);
  // options.set("opt:upper_bound", upper_bound);
  //   options.set("opt:prediction", guess);


  options.set("fraz:nthreads", 1u);
  options.set("opt:search", "dist_gridsearch");
  options.set("dist_gridsearch:search", "fraz");
  options.set("dist_gridsearch:num_bins", pressio_data{1});
  options.set("dist_gridsearch:overlap_percentage", pressio_data{0});
  // options.set("distributed:comm", (void*)MPI_COMM_WORLD);
  options.set("opt:compressor", "zfp");
  options.set("opt:inputs", inputs);
  options.set("opt:lower_bound", lower_bound);
  options.set("opt:upper_bound", upper_bound);
  options.set("opt:target",target_x2_error);
  options.set("opt:local_rel_tolerance", 1);
  // options.set("opt:global_rel_tolerance", 0.1);
  options.set("opt:max_iterations", 100u);
  options.set("opt:output", outputs);
  options.set("opt:search_metrics", "composite_search");
  options.set("composite_search:search_metrics", std::vector<std::string>{"progress_printer", "record_search"});
  options.set("io:path", "trace.csv");
  options.set("csv:headers", headers);
  options.set("opt:prediction", guess);
  options.set("opt:do_decompress", 1);
  options.set("opt:objective_mode", (unsigned int)pressio_search_mode_max);
  options.set("zfp:metric", "composite");
  options.set("opt:metric", "composite");
  options.set("composite:plugins", std::vector<std::string>{"time", "size", "error_stat"});
  options.set("composite:names", std::vector<std::string>{"time", "size", "error_stat"});

  // std::cout<<" end config " <<std::endl;

  if(compressor->set_options(options)) {
    std::cout << compressor->error_msg() << std::endl;
    exit(compressor->error_code());
  }
  options = compressor->get_options();
  // if(rank == 0){
  //   // std::cout << "options2:\n_________________\n" << std::endl << options << std::endl;
  // }


  size_t dims[] = {500,500,100};
  auto description = pressio_data_new_empty( pressio_float_dtype, 3, dims);

  auto input_data = pressio_io_data_path_read(description, argv[6]);

  // auto input_data = pressio_data_new_move(pressio_float_dtype, make_data(), 3, dims, pressio_data_libc_free_fn, nullptr);
  auto compressed = pressio_data_new_empty(pressio_byte_dtype, 0, 0);
  auto decompressed = pressio_data_new_owning(pressio_float_dtype, 3, dims);
  // printf("test afrer data creation\n");
    // std::cout<<" end config " <<std::endl;

  if(compressor->compress(input_data, compressed)) {
    std::cerr << compressor->error_msg() << std::endl;
    return compressor->error_code();
  }
  // std::cout<<"between compress and decompress" <<std::endl;
  if(compressor->decompress(compressed, decompressed)) {
    std::cerr << compressor->error_msg() << std::endl;
    return compressor->error_code();
  }
  // printf("test afrer data creation\n");

  auto metrics_results = compressor->get_metrics_results();
  // if(rank == 0) {
  //   std::cout << "Metrics Results:" << std::endl << metrics_results << std::endl;
  // }

  auto finaloptions = compressor->get_options();
  
  if(rank == 0) {
        // std::cout << "time:compress = "<< metrics_results.get("time:compress")<< std::endl;

    std::cout << "time:compress = "<< metrics_results.get("time:compress").get_value<uint32_t>()<< std::endl;
    std::cout << "time:decompress = "<< metrics_results.get("time:decompress").get_value<uint32_t>()<< std::endl;
    std::cout << "zfp:accuracy = "<< finaloptions.get("zfp:accuracy").get_value<double>()<< std::endl;
    std::cout << "size:compression ratio = "<< metrics_results.get("size:compression_ratio").get_value<double>()<< std::endl;
    std::cout << "error_stat:max_x_sq_diff_rel = "<< metrics_results.get("error_stat:max_x_sq_diff_rel").get_value<double>()<< std::endl;
    std::cout<<"final config "<< finaloptions<<std::endl; 
  }


  // double error_bound=0;

  // pressio_options_get_double(finaloptions, "sz3:rel_error_bound", &error_bound);

  // printf("error bound = %.G \n", error_bound);


  // if(rank == 0){
  //   std::cout << "final options:" << std::endl << finaloptions << std::endl;
  // }

 
  pressio_data_free(input_data);
  pressio_data_free(compressed);
  pressio_data_free(decompressed);
  MPI_Finalize();
  return 0;
}
