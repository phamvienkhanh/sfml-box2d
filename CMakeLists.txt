cmake_minimum_required (VERSION 3.7)

file(GLOB SOURCE ./source/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/libs)

set(CMAKE_CXX_CPPCHECK "cppcheck")

add_executable(sfml_box2d ${SOURCE})
target_link_libraries(sfml_box2d -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lbox2d)
