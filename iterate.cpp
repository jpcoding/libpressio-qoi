#include <libpressio.h>
#include<iostream>
#include"utils/FileUtils.hpp"
#include"utils/MemoryUtil.hpp"

int main()
{
    std::cout<<pressio_version()<<std::endl;
    // std::cout<<pressio_supported_compressors() <<std::endl;

    pressio * library = pressio_instance();


    pressio_compressor * comp = pressio_get_compressor(library, "sz3");

    if(!comp)
    {
        std::cout<<pressio_error_msg(library)<<std::endl;
        exit(1);
    }

    pressio_options* options = pressio_options_new();

    // SZ3 configs using the default settings
    double rel_error;
    pressio_options_set_double(options, "pressio:rel",rel_error ); 

    // std::vector<float> from_application_vec(500*500*100);
    // std::unique_ptr<float[]> from_application = std::make_unique<float[]>(500*500*100);
    // std::iota(from_application.get(), from_application.get()+25000000,0);
    // std::iota(from_application_vec.begin(), from_application_vec.end(),0);

    // std::array<std::size_t,3> dims {500,500,100};
    // pressio_data* from_application_vec_data = pressio_data_new_nonowning(
    //     pressio_float_dtype,
    //     from_application_vec.data(),
    //     dims.size(),
    //     dims.data()
    // );





    if (pressio_compressor_set_options(comp, options) != 0) {
        std::cout<<pressio_compressor_error_msg(comp)<<std::endl;
        exit(1);

    }


    pressio_options * avail = pressio_compressor_get_options(comp);
    char * avail_str = pressio_options_to_string(avail);
    std::cout<<avail_str<<std::endl;



    return 0;
}