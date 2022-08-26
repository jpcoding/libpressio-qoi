cmake_minimum_required(VERSION 3.18)
project(iterate)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("/home/pjiao/git/libpressio_opt/install/include")
# include_directories("/usr/include/mpich-x86_64")

find_package(std_compat REQUIRED)
find_package(LibPressio REQUIRED PATHS "/home/pjiao/git/libpressio/install/lib64/cmake/LibPressio")
find_package(LibPressioOpt REQUIRED PATHS "/home/pjiao/git/libpressio_opt/install/lib64/cmake/LibPressioOpt" )
find_package(LibDistributed REQUIRED PATHS "/home/pjiao/git/spack/opt/spack/linux-fedora36-skylake/gcc-12.1.1/libdistributed-0.4.0-adwrb5d7vc6ilkuxedc76tzsc52n7b3j/lib64/cmake/LibDistributed")
find_package(SZ3 REQUIRED )
find_package(ZFP)
find_package(ZLIB REQUIRED)
find_package(MPI)
pkg_search_module(ZSTD  IMPORTED_TARGET libzstd)
pkg_search_module(FFTW3 IMPORTED_TARGET fftw3)


add_executable(iterate iterate.cpp)
target_link_libraries(iterate LibPressio::libpressio)

add_executable(sz3_demo sz3_demo.cpp)
target_link_libraries(sz3_demo LibPressio::libpressio)

add_executable(zfp_demo zfp_demo.cpp)
target_link_libraries(zfp_demo LibPressio::libpressio)

add_executable(opt_demo opt_demo.cpp)
target_link_libraries(opt_demo LibPressio::libpressio LibPressioOpt::libpressio_opt)

add_executable(opt_zfp opt_zfp.cpp)
target_link_libraries(opt_zfp LibPressio::libpressio LibPressioOpt::libpressio_opt)

add_executable(opt_binary opt_binary.cpp)
target_link_libraries(opt_binary LibPressio::libpressio LibPressioOpt::libpressio_opt)