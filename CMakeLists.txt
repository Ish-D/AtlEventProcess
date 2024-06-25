cmake_minimum_required(VERSION 3.26)
project(AtlEventProcess CXX)

set(CMAKE_CXX_STANDARD 20)

find_package( Boost REQUIRED)

add_executable(${PROJECT_NAME} src/AtlCopyBSEvent.cxx)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -std=c++20)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src
                                                   ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} eformat ers DataWriter DataReader eformat_old)