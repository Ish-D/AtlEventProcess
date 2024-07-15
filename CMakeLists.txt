cmake_minimum_required(VERSION 3.26)
project(AtlEventProcess CXX)

set(CMAKE_CXX_STANDARD 20)

find_package( Boost REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} src/AtlCopyBSEvent.cxx)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -std=c++20)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src
                                                   ${CMAKE_SOURCE_DIR}/include
                                                   ${GTest_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${GTest_LIBRARIES} eformat ers DataWriter DataReader eformat_old)

enable_testing()

add_test(
    NAME ClearFiles
    COMMAND "rm" "-f" "../*.data"
)

add_test(
    NAME TestUncompressed
    COMMAND "AtlEventProcess" "-o" "uncompressed.data" "/cvmfs/atlas-nightlies.cern.ch/repo/data/data-art/Tier0ChainTests/data12_8TeV.00209109.physics_JetTauEtmiss.merge.RAW._lb0186._SFO-1._0001.1")

add_test(
    NAME TestCompressed
    COMMAND "AtlEventProcess" "-d" "-o" "compressed.data" "/cvmfs/atlas-nightlies.cern.ch/repo/data/data-art/Tier0ChainTests/data12_8TeV.00209109.physics_JetTauEtmiss.merge.RAW._lb0186._SFO-1._0001.1")