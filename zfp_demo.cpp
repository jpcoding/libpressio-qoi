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
          printf("%s : %p\n", key, pressio_option_get_userptr(option));
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
          printf("%s : %lf\n", key, pressio_option_get_double(option));
          break;
        case pressio_option_float_type:
          printf("%s : %f\n", key, pressio_option_get_float(option));
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
    // get zfp
    struct pressio* library = pressio_instance();
    struct pressio_compressor* zfp = pressio_get_compressor(library, "zfp");


    // std::cout<<avail_str<<std::endl;

    // configure the compressor
    struct  pressio_options* config =pressio_compressor_get_options(zfp);
    
    pressio_options_set_double(config, "zfp:accuracy", atoi(argv[1]));
    // pressio_options_set_integer(config, "zfp:mode", 8);



    pressio_options * avail = pressio_compressor_get_options(zfp);
    char * avail_str = pressio_options_to_string(avail);
    std::cout<<avail_str<<std::endl;

    if( pressio_compressor_set_options( zfp, config) ) 
    {
    printf("%s\n", pressio_compressor_error_msg(zfp));
    exit(pressio_compressor_error_code(zfp));
    }

    // configure metrics 
    const char* metrics[] = {"size", "time", "error_stat"};
    struct pressio_metrics* metrics_plugin = pressio_new_metrics(library, metrics, 3);
    pressio_compressor_set_metrics(zfp, metrics_plugin);

    // prepare input data
    size_t dims[]={500,500,100};
    struct pressio_data* description = pressio_data_new_empty( pressio_float_dtype, 3, dims);
    struct pressio_data* input_data = pressio_io_data_path_read(description, "/home/pjyh8/data/hurrican100x500x500/Uf48.bin.f32");

    // output buffers 
    struct pressio_data* compressed_data = pressio_data_new_empty(pressio_byte_dtype, 0, NULL);
    struct pressio_data* decompressed_data = pressio_data_new_owning(pressio_float_dtype,3, dims);

    // compress and decompress 
    int compress_ =pressio_compressor_compress(zfp, input_data, compressed_data);
    int decompress_ = pressio_compressor_decompress(zfp, compressed_data, decompressed_data);

    // write files 
    // pressio_io_data_path_write(compressed_data, "test.zfp");
    // pressio_io_data_path_write(decompressed_data, "test.zfp.out");

    // 


    // std::cout<< sizeof(decompressed_data)<<std::endl;

    struct pressio_options* metrics_results = pressio_compressor_get_metrics_results(zfp);

    double compression_ratio=0;
    // double compression_time=0;
    // double decompression_time=0;
    double psnr=0;
    uint32_t dtime=0;
    uint32_t ctime=0;
    pressio_options_get_double(metrics_results, "size:compression_ratio", &compression_ratio);
    // pressio_options_get_double(metrics_results, "time:compress", &compression_time);
    pressio_options_get_double(metrics_results, "error_stat:psnr", &psnr);
    pressio_options_get_uinteger(metrics_results, "time:decompress", &dtime);
    pressio_options_get_uinteger(metrics_results, "time:compress", &ctime);



    // print_all_options(metrics_results);
    std::cout<<"compression ratio "<<compression_ratio<<std::endl;
    std::cout<<"psnr = "<< psnr <<std::endl;
    std::cout<<"time:decompress = "<< dtime <<std::endl;
    std::cout<<"time:compress = "<< ctime <<std::endl;
    // std::cout<<"compression time" << compression_time <<std::endl;
    
    // std::cout<<" end the program" <<std::endl;
    

    // pressio_options * avail = pressio_compressor_get_options(sz3);
    // char * avail_str = pressio_options_to_string(avail);
    // std::cout<<avail_str<<std::endl;


      // free the input, decompressed, and compressed data
  pressio_data_free(decompressed_data);
  pressio_data_free(compressed_data);
  pressio_data_free(input_data);
  pressio_data_free(description);



  // free options and the library
  pressio_options_free(config);
  pressio_options_free(metrics_results);
    free(avail_str);
        pressio_options_free(avail);



  pressio_compressor_release(zfp);
  pressio_release(library);
 
  return 0;
    
}