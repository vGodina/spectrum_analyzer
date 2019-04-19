cmake_minimum_required(VERSION 3.0) # setting this is required

project(spectrum_analyzer) # this sets the project name

# adding source files
file(GLOB SourceFiles "src/*.cpp")
file(GLOB_RECURSE ExtSourceFiles "external/include/*.cpp")

# adding headers
include_directories(src)

# adding external headers
include_directories("external/include")

# adding libraries
include_directories( "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/di-cpp14/include")
include_directories("C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/boost_1_69_0")

#adding fltk library
link_directories(external/libs/fltk)

add_executable(spectrum_analyzer ${SourceFiles} ${ExtSourceFiles}) 
target_compile_features(spectrum_analyzer PRIVATE cxx_std_17)
target_link_libraries(spectrum_analyzer fltkd)

install(TARGETS spectrum_analyzer DESTINATION bin)