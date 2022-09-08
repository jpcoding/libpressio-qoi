#include <iostream>
#include <limits>
#include <libpressio.h>
#include <libpressio_ext/cpp/libpressio.h>
#include <libpressio_ext/io/posix.h>
#include <libpressio_opt/pressio_search_defines.h>
#include "mpi.h"
#include <typeinfo>

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
  if(thread_provided != MPI_THREAD_MULTIPLE) {
    if(rank == 0){
      std::cout << "insufficient thread support from MPI" << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, 3);
  }



 std::cout<<"size = " <<size<<std::endl;


  pressio library;
  std::string metrics_ids[] = {"size", "time", "error_stat"};
  pressio_metrics metrics = library.get_metrics(std::begin(metrics_ids), std::end(metrics_ids));
  pressio_options metric_options = metrics->get_options();

  double target_x2_error=atof(argv[1]); // input search space will be ( 0.1 * target_x2_error, target_x2_error)  

  double target_upper=atof(argv[2]); // input restriction 
  double target_lower=atof(argv[3]);


  std::string string1 = R"lua(
    local cr = metrics['size:compression_ratio'];
    local x2 = metrics['error_stat:max_x_sq_diff_rel'];
    if (x2 < )lua";
  std::string string2(argv[3]);

  std::string string3 = R"lua( or x2 > )lua";

  std::string string4(argv[2]);

  std::string string5 = R"lua( ) then
      objective = -1*(x2-0.1);
    else
      objective = cr;
    end
    return "objective", objective
  )lua";
  
    std::vector<std::string> lua_scripts {string1+string2+string3+string4+string5};

  

    // std::cout<<lua_scripts1<<std::endl;

  //   std::vector<std::string> lua_scripts {R"lua(
  //   local cr = metrics['size:compression_ratio'];
  //   local x2 = metrics['error_stat:max_x_sq_diff_rel'];
  //   if (x2 >0.1) then
  //     objective = -math.huge; // -1*(x2-0.1); 
  //   else
  //     objective = cr;
  //   end
  //   return "objective", objective
  // )lua"};

      // std::cout<<lua_scripts<<std::endl;

      // exit(0);



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
    auto const inputs = std::vector<std::string>{"sz3:rel_error_bound"};
    auto const outputs = std::vector<std::string>{ "composite:objective","error_stat:max_x_sq_diff_rel","size:compression_ratio", "time:compress", "time:decompress"};
  auto const headers = [&]()
  {
    std::vector<std::string> headers;
    headers.insert(headers.end(), inputs.begin(), inputs.end());
    headers.insert(headers.end(), outputs.begin(), outputs.end());
    return headers;
  }();

  pressio_data lower_bound{target_x2_error/10};
  pressio_data upper_bound{target_x2_error};
  pressio_data guess= pressio_data{0.5*target_x2_error}; // will need guess first

  // options.set("opt:search", "binary");
  //   options.set("opt:lower_bound", lower_bound);
  // options.set("opt:upper_bound", upper_bound);
  //   options.set("opt:prediction", guess);

  

  options.set("fraz:nthreads", 1u);
  options.set("opt:search", "dist_gridsearch");
  options.set("dist_gridsearch:search", "fraz");
  options.set("dist_gridsearch:num_bins", pressio_data{(size == 1) ? 1 : (size -1)});  // not for single thread
  options.set("dist_gridsearch:overlap_percentage", pressio_data{0.05}); // not for single thread  
  // options.set("distributed:comm", (void*)MPI_COMM_WORLD);
  options.set("opt:compressor", "sz3");
  options.set("opt:inputs", inputs);
  options.set("opt:lower_bound", lower_bound);
  options.set("opt:upper_bound", upper_bound);
  options.set("opt:target", 0.1); // stop criterion 
  options.set("opt:local_rel_tolerance", 0.01); // used in pressio_search_mode_max 
  options.set("opt:global_rel_tolerance", 0.01); // related to target ,  not used in pressio_search_mode_max
  options.set("opt:max_iterations", 200u);
  options.set("opt:output", outputs);
  options.set("opt:search_metrics", "composite_search");
  options.set("composite_search:search_metrics", std::vector<std::string>{"progress_printer", "record_search"});
  options.set("io:path", "/tmp/trace.csv");
  options.set("csv:headers", headers);
  options.set("opt:prediction", guess);
  options.set("opt:do_decompress", 1);
  options.set("opt:objective_mode", (unsigned int)pressio_search_mode_max); // 
  options.set("sz3:error_bound_mode_str", "REL"); // options.set( "", "pressio:rel");  
  options.set("sz3:metric", "composite");
  options.set("opt:metric", "composite");
  options.set("composite:plugins", std::vector<std::string>{"time", "size", "error_stat"});
  options.set("composite:names", std::vector<std::string>{"time", "size", "error_stat"});


  if(compressor->set_options(options)) {
    std::cout << compressor->error_msg() << std::endl;
    exit(compressor->error_code());
  }
  options = compressor->get_options();
  // if(rank == 0){
  //   std::cout << "options:" << std::endl << options << std::endl;
  // }


  size_t dims[] = {500,500,100};
  auto description = pressio_data_new_empty( pressio_float_dtype, 3, dims);

  auto input_data = pressio_io_data_path_read(description,argv[4]);

  // auto input_data = pressio_data_new_move(pressio_float_dtype, make_data(), 3, dims, pressio_data_libc_free_fn, nullptr);
  auto compressed = pressio_data_new_empty(pressio_byte_dtype, 0, 0);
  auto decompressed = pressio_data_new_owning(pressio_float_dtype, 3, dims);
  
  if(compressor->compress(input_data, compressed)) {
    std::cerr << compressor->error_msg() << std::endl;
    return compressor->error_code();
  }

  if(compressor->decompress(compressed, decompressed)) {
    std::cerr << compressor->error_msg() << std::endl;
    return compressor->error_code();
  }

  auto metrics_results = compressor->get_metrics_results();
  auto finaloptions = compressor->get_options();
  
  if(rank == 0) {
        // std::cout << "time:compress = "<< metrics_results.get("time:compress")<< std::endl;

    std::cout << "time:compress = "<< metrics_results.get("time:compress").get_value<uint32_t>()<< std::endl;
        std::cout << "time:decompress = "<< metrics_results.get("time:decompress").get_value<uint32_t>()<< std::endl;

    std::cout << "sz3:rel_error_bound = "<< finaloptions.get("sz3:rel_error_bound").get_value<double>()<< std::endl;
    std::cout << "size:compression ratio = "<< metrics_results.get("size:compression_ratio").get_value<double>()<< std::endl;
    std::cout << "error_stat:max_x_sq_diff_rel = "<< metrics_results.get("error_stat:max_x_sq_diff_rel").get_value<double>()<< std::endl;
  }

  // auto finaloptions = compressor->get_options();

  // double error_bound=0;

  // pressio_options_get_double(finaloptions, "sz3:rel_error_bound", &error_bound);

  // printf("error bound = %.G \n", error_bound);


  // if(rank == 0){
  //   std::cout << "final options:" << std::endl << finaloptions << std::endl;
  // }

  pressio_data_free(description);
  pressio_data_free(input_data);
  pressio_data_free(compressed);
  pressio_data_free(decompressed);

  MPI_Finalize();
  return 0;
}