cmake_minimum_required(VERSION 3.18)
project(iterate)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include_directories("$HOME/git/libpressio_opt/install/include")
# include_directories("/usr/include/mpich-x86_64")

find_package(LibPressio REQUIRED)
find_package(LibPressioOpt REQUIRED PATHS "/home/pjyh8/git/libpressio_opt/install/lib/cmake/LibPressioOpt")
find_package(LibDistributed REQUIRED)
find_package(std_compat REQUIRED)
find_package(SZ3 REQUIRED )
find_package(ZFP REQUIRED)
find_package(ZLIB REQUIRED)
find_package(SZ REQUIRED)
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
target_link_libraries(opt_demo PUBLIC  LibPressioOpt::libpressio_opt )

add_executable(opt_zfp opt_zfp.cpp)
target_link_libraries(opt_zfp PUBLIC  LibPressioOpt::libpressio_opt)

add_executable(opt_binary opt_binary.cpp)
target_link_libraries(opt_binary PUBLIC LibPressioOpt::libpressio_opt )

add_executable(fraz fraz.cpp)
target_link_libraries(fraz PUBLIC LibPressioOpt::libpressio_opt )