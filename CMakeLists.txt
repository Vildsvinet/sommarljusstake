cmake_minimum_required(VERSION 3.22)
project(sommarljusstake C)

set(CMAKE_C_STANDARD 99)
add_subdirectory("unitTest/Unity-master")
add_executable(sommarljusstake main.c)
target_link_libraries(sommarljusstake PRIVATE unity)

add_executable(testingFILE "unitTest/Unity-master/src/testing.c")
target_link_libraries(testingFILE PRIVATE unity)

add_executable(helloWorld "unitTest/Unity-master/src/helloWorld.c")
target_link_libraries(helloWorld PRIVATE unity)

add_executable(ranLig "unitTest/Unity-master/src/ranLig.c")
target_link_libraries(ranLig PRIVATE unity)