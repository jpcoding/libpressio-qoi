#include <libpressio.h>
#include <libpressio_ext/io/posix.h>
#include <libpressio_ext/io/pressio_io.h>
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include <sstream>
#include<string>
#include<cassert>
#include <ctime>

// #include<csstream>


void print_all_options(struct pressio_options* options) {
  struct pressio_options_iter* iter = pressio_options_get_iter(options);
  while(pressio_options_iter_has_value(iter)) 
  {
    char const* key = pressio_options_iter_get_key(iter);
    struct pressio_option* option = pressio_options_iter_get_value(iter);

    if(pressio_option_has_value(option)) {
      switch(pressio_option_get_type(option)) {
        case pressio_option_charptr_type:
          printf("%s : \"%s\"\n", key, pressio_option_get_string(option));
          break;
        case pressio_option_userptr_type:
          printf("time %s : %p\n", key, pressio_option_get_userptr(option));
          break;
        case pressio_option_int16_type:
          printf("%s : %hd\n", key, pressio_option_get_integer16(option));
          break;
        case pressio_option_uint16_type:
          printf("%s : %hu\n", key, pressio_option_get_uinteger16(option));
          break;
        case pressio_option_int32_type:
          printf("%s : %d\n", key, pressio_option_get_integer(option));
          break;
        case pressio_option_uint32_type:
          printf("%s : %u\n", key, pressio_option_get_uinteger(option));
          break;
        case pressio_option_int64_type:
          printf("%s : %ld\n", key, pressio_option_get_integer64(option));
          break;
        case pressio_option_uint64_type:
          printf("%s : %lu\n", key, pressio_option_get_uinteger64(option));
          break;
        case pressio_option_double_type:
          printf("%s : %.6G\n", key, pressio_option_get_double(option));
          break;
        case pressio_option_float_type:
          printf("%s : %.6G\n", key, pressio_option_get_float(option));
          break;
        case pressio_option_bool_type:
          printf("%s : %s\n", key, pressio_option_get_bool(option) ? "true":"false");
          break;
        default:
          assert(false && "a cleared option can never have a value");
      } 
    } else {
      switch(pressio_option_get_type(option)) {
        case pressio_option_charptr_type:
          printf("%s <string>: null\n", key);
          break;
        case pressio_option_userptr_type:
          printf("%s <void*>: null\n", key);
          break;
        case pressio_option_int8_type:
          printf("%s <int8_t>: null\n", key);
          break;
        case pressio_option_uint8_type:
          printf("%s <uint8_t>: null\n", key);
          break;
        case pressio_option_int16_type:
          printf("%s <int16_t>: null\n", key);
          break;
        case pressio_option_uint16_type:
          printf("%s <uint16_t>: null\n", key);
          break;
        case pressio_option_int32_type:
            printf("%s <int32_t>: null\n", key);
            break;
        case pressio_option_uint32_type:
          printf("%s <uint32_t>: null\n", key);
          break;
        case pressio_option_int64_type:
          printf("%s <int64_t>: null\n", key);
          break;
        case pressio_option_uint64_type:
          printf("%s <uint64_t>: null\n", key);
          break;
        case pressio_option_double_type:
            printf("%s <double>: null\n", key);
            break;
        case pressio_option_float_type:
          printf("%s <float>: null\n", key);
          break;
        case pressio_option_unset_type:
          printf("%s <unset>: null\n", key);
          break;
        case pressio_option_charptr_array_type:
          printf("%s <char**>: null\n", key);
          break;
        case pressio_option_data_type:
          printf("%s <data>: null\n", key);
          break;
        case pressio_option_bool_type:
          printf("%s <bool>: null\n", key);
          break;
      }
    }

    pressio_option_free(option);
    pressio_options_iter_next(iter);
  }
  pressio_options_iter_free(iter);
}


int main (int argc, char ** argv)
{
    // get sz3 compressor
    struct pressio* library = pressio_instance();
    struct pressio_compressor* sz3 = pressio_get_compressor(library, "sz3");



    // configure the compressor
    struct  pressio_options* config =pressio_compressor_get_options(sz3);
    pressio_options_set_string(config, "sz3:error_bound_mode_str", "REL");
    pressio_options_set_double(config, "sz3:rel_error_bound", atof(argv[1]));

    if( pressio_compressor_set_options( sz3, config) ) 
    {
    printf("%s\n", pressio_compressor_error_msg(sz3));
    exit(pressio_compressor_error_code(sz3));
    }

    pressio_options * avail1 = pressio_compressor_get_options(sz3);
    char * avail_str1 = pressio_options_to_string(avail1);
    // std::cout<<"options \n" <<avail_str1<<std::endl;



    // struct pressio_metrics * avail_metrics = pressio_metrics_get_options(sz3);
    // configure metrics 
    const char* metrics[] = {"size", "time", "error_stat"};
    struct pressio_metrics* metrics_plugin = pressio_new_metrics(library, metrics, 3);
    pressio_compressor_set_metrics(sz3, metrics_plugin);

    // get zfp and configure 


    // struct pressio_options* metrics_results1 = pressio_compressor_get_metrics_results(sz3);
    // print_all_options(metrics_results1);

    // import data
    // std::cout<<"construct data" << std::endl;

    size_t dims[]={500,500,100};
    struct pressio_data* description = pressio_data_new_empty( pressio_float_dtype, 3, dims);

    struct pressio_data* input_data = pressio_io_data_path_read(description, "/home/pjiao/data/hurricane_100x500x100/CLOUDf48.bin.f32");

    // std::cout<< input_data << std::endl;

    // std::cout<<"construct data" << std::endl;

    // create output buffers

    struct pressio_data* compressed_data = pressio_data_new_empty(pressio_byte_dtype, 0, NULL);
    struct pressio_data* decompressed_data = pressio_data_new_owning(pressio_float_dtype,3, dims);



    // compress and decompress the data
        double compress_time_cxx; 
    std::clock_t start;
    start=std::clock();
    int compress_ =pressio_compressor_compress(sz3, input_data, compressed_data);
    compress_time_cxx=(std::clock()-start)/ (double) CLOCKS_PER_SEC;

    int decompress_ = pressio_compressor_decompress(sz3, compressed_data, decompressed_data);
    // std::cout<<"decompress results" << decompress_<< std::endl;

    // write file 
    // pressio_io_data_path_write(compressed_data, "test.sz3");

    // pressio_io_data_path_write(decompressed_data, "test.sz3.out");


    // FILE* outfile = fopen("test.sz3.out", "w");

    // pressio_io_data_fwrite(decompressed_data, outfile);

    // fclose(outfile);

    // metrics 

    // std::cout<< sizeof(decompressed_data)<<std::endl;

    struct pressio_options* metrics_results = pressio_compressor_get_metrics_results(sz3);

    double compression_ratio=0;
    unsigned int compression_time=0;
    // double decompression_time=0;
    double psnr=0;
    double max_x_sq_diff_rel=0;
    pressio_options_get_double(metrics_results, "size:compression_ratio", &compression_ratio);
    pressio_options_get_uinteger(metrics_results, "time:compress", &compression_time);
    pressio_options_get_double(metrics_results, "error_stat:psnr", &psnr);
    pressio_options_get_double(metrics_results, "error_stat:max_x_sq_diff_rel", &max_x_sq_diff_rel);



    // print_all_options(metrics_results);
    std::cout<<"compression ratio = "<<compression_ratio<<std::endl;
    std::cout<<"psnr = "<< psnr <<std::endl;

    std::cout<<"rel max x^2 error = "<< max_x_sq_diff_rel <<std::endl;
    std::cout<<"compression time = " << compression_time <<std::endl;
    std::cout<<"compress time " << compress_time_cxx<<std::endl;
    
    // std::cout<<" end the program" <<std::endl;
    

    // pressio_options * avail = pressio_compressor_get_options(sz3);
    // char * avail_str = pressio_options_to_string(avail);
    // std::cout<<avail_str<<std::endl;


      // free the input, decompressed, and compressed data
  pressio_data_free(decompressed_data);
  pressio_data_free(compressed_data);
  pressio_data_free(input_data);

  // free options and the library
  pressio_options_free(config);
  pressio_options_free(metrics_results);
  pressio_compressor_release(sz3);
  pressio_release(library);
  return 0;
    
}