set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -O3 -std=c++11 -DYTMSG_LITE -DESP32 -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -DYTMSG_LITE -DESP32 -fPIC")

set(COMPONENT_SRCS "hello_visionseed.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
