cmake_minimum_required(VERSION 3.20)


project(vec3)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/vec3ets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/.)


file(GLOB PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB vec3_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/src/etc/*.c ${CMAKE_CURRENT_SOURCE_DIR}/src/obj/*.c)

message(${vec3_files})

add_executable(vec3_e ${vec3_files})
target_compile_options(vec3_e PRIVATE -g -Wall)



list(FILTER vec3_files EXCLUDE REGEX "main.c")

add_library(vec3 SHARED ${vec3_files})
add_library(vec3_static STATIC ${vec3_files})

target_compile_options(vec3 PUBLIC -fPIC)
target_compile_options(vec3_static PUBLIC -fPIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  vec3
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  vec3_static
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  vec3_e
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


    include(FetchContent)


if (NOT TARGET cglm)
FetchContent_Declare(
  cglm
  GIT_REPOSITORY https://github.com/recp/cglm.git
  GIT_TAG "v0.8.4"
  )
FetchContent_MakeAvailable(cglm)
endif()

set(LIBRARIES m cglm)

target_link_libraries(vec3_e PRIVATE ${LIBRARIES})
target_link_libraries(vec3 PRIVATE ${LIBRARIES})
target_link_libraries(vec3_static PRIVATE ${LIBRARIES})
