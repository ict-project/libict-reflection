################################################################
cmake_minimum_required(VERSION 3.25)
################################################################
set(LIBRARY_NAME "reflection")
set(LIBRARY_DESC "Library with pseudo reflection mechanism for C++.")

project(libict-${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)

include(../libict-dev-tools/libs-include.cmake)
include(../libict-dev-tools/info-include.cmake)
include(../libict-dev-tools/test-include.cmake)
include(../libict-dev-tools/git-include.cmake)

file(GLOB CMAKE_HEADER_LIST . *.hpp)

set(CMAKE_SOURCE_FILES 
  info.cpp
  types.cpp
  meta.cpp
  definition.cpp
  meta-vector.cpp
  meta-map.cpp
  process.cpp
  processor.cpp
)

add_library(ict-static-${LIBRARY_NAME} STATIC ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-static-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ict-static-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_library(ict-shared-${LIBRARY_NAME} SHARED ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-shared-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ict-shared-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_executable(${PROJECT_NAME}-test ${CMAKE_HEADER_LIST} test.cpp)
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME}-test ict-static-${LIBRARY_NAME})
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_LINK_LIBS})
target_compile_definitions(${PROJECT_NAME}-test PUBLIC -DENABLE_TESTING)

################################################################
install(TARGETS ict-static-${LIBRARY_NAME} ict-shared-${LIBRARY_NAME} DESTINATION lib COMPONENT libraries)
install(
  FILES ${CMAKE_HEADER_LIST}
  DESTINATION include/libict/${LIBRARY_NAME} COMPONENT headers
)
################################################################
enable_testing()

add_test(NAME ict-definition-tc1 COMMAND ${PROJECT_NAME}-test ict definition tc1)
add_test(NAME ict-meta_vector-tc1 COMMAND ${PROJECT_NAME}-test ict meta_vector tc1)
add_test(NAME ict-meta_map-tc1 COMMAND ${PROJECT_NAME}-test ict meta_map tc1)
add_test(NAME ict-meta_map-tc2 COMMAND ${PROJECT_NAME}-test ict meta_map tc2)
add_test(NAME ict-meta_map-tc3 COMMAND ${PROJECT_NAME}-test ict meta_map tc3)
add_test(NAME ict-process-tc1 COMMAND ${PROJECT_NAME}-test ict process tc1)

################################################################
include(../libict-dev-tools/cpack-include.cmake)
################################################################
