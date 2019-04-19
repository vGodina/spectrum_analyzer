cmake_minimum_required(VERSION 3.0) # setting this is required

project(spectrum_analyzer) # this sets the project name

# adding source files
file(GLOB SourceFiles "src/*.cpp")
file(GLOB_RECURSE ExtSourceFiles "external/include/*.cpp")

add_executable(spectrum_analyzer ${SourceFiles} ${ExtSourceFiles})

target_compile_features(spectrum_analyzer PRIVATE cxx_std_17)

# adding external headers
target_include_directories(spectrum_analyzer PUBLIC
	"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/boost_1_69_0")
target_include_directories(spectrum_analyzer PUBLIC
	"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/include/di-cpp14/include")
target_include_directories(spectrum_analyzer PUBLIC external/include)

#adding fltk library
target_include_directories(spectrum_analyzer PUBLIC external/libs/fltkd)
target_link_libraries(spectrum_analyzer fltkd)

install(TARGETS spectrum_analyzer DESTINATION bin)

#### package connection example
# find_package(BOOST REQUIRED)
# include_directories(${BOOST_INCLUDE_DIRS} )
# target_link_libraries(spectrum_analyzer ${BOOST_LIBRARY} )