# OBJECT LIBRARY
set(LIB_NAME lib)

set(LIB_HEADERS
    include/log.hpp include/test_actor_function.hpp include/test_profiler.hpp
    include/test_tracing_data.hpp include/test_tracing_data_factory.hpp)

set(LIB_SOURCES src/log.cpp src/test_actor_function.cpp src/test_profiler.cpp
                src/test_tracing_data.cpp src/test_tracing_data_factory.cpp)

add_library(${LIB_NAME} OBJECT ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(${LIB_NAME} PUBLIC Threads::Threads jaegertracing
                                         ${CMAKE_DL_LIBS} CAF::core CAF::io)

target_include_directories(
  ${LIB_NAME}
  PUBLIC ${CAF_INCLUDE_DIRS}
         ${caf_simple_tracing_SOURCE_DIR}/lib/include
         ${caf_simple_tracing_SOURCE_DIR}/external/expected/include
         ${caf_simple_tracing_SOURCE_DIR}/external/optional/include
         ${caf_simple_tracing_SOURCE_DIR}/external/fmtlib/include
         ${caf_simple_tracing_SOURCE_DIR}/external/gsl/include
         ${caf_simple_tracing_SOURCE_DIR}/external/philslib/include)

target_compile_definitions(${LIB_NAME} PUBLIC CAF_ENABLE_ACTOR_PROFILER
                                              FMT_HEADER_ONLY __USE_POSIX)
