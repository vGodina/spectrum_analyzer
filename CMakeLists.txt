cmake_minimum_required(VERSION 3.0) # setting this is required

project(spectrum_analyzer) # this sets the project name

file(GLOB SourceFiles "src/*.cpp")
file(GLOB_RECURSE ExtSourceFiles "external/include/*.cpp")

include_directories(src)
include_directories("external/include")
include_directories( "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/di-cpp14/include")
include_directories("C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/boost_1_69_0")

link_directories(external/libs/fltk)

add_executable(spectrum_analyzer ${SourceFiles} ${ExtSourceFiles}) 
target_compile_features(spectrum_analyzer PRIVATE cxx_std_17)
target_link_libraries(spectrum_analyzer fltkd)

install(TARGETS spectrum_analyzer DESTINATION bin)