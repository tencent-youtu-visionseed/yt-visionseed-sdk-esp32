cmake_minimum_required(VERSION 3.5)

# project(ytvisionseed)

file(GLOB SRCS
    "sdk/src/*.c"
    "sdk/src/*.cpp"
    "src/*.c"
    "src/*.cpp"
)

# include_directories(${PROJECT_SOURCE_DIR}/include)
# add_library(ytvisionseed ${SRCS})
# target_include_directories(ytvisionseed INTERFACE ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -O3 -std=c++11 -DYTMSG_LITE -DESP32 -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -DYTMSG_LITE -DESP32 -fPIC")
#
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(COMPONENT_SRCS ${SRCS})
set(COMPONENT_ADD_INCLUDEDIRS sdk/include src)
register_component()
