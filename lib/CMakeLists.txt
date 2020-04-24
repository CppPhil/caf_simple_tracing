# OBJECT LIBRARY
set(LIB_NAME lib)

set(LIB_HEADERS
   )

set(LIB_SOURCES
   )

add_library(${LIB_NAME} OBJECT ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(
  ${LIB_NAME}
  PUBLIC
  Threads::Threads
  jaegertracing
  ${CMAKE_DL_LIBS}
  CAF::core
  CAF::io
)

target_include_directories(
  ${LIB_NAME}
  PUBLIC
  ${CAF_INCLUDE_DIRS}
  ${caf_simple_tracing}/lib/include
  ${caf_simple_tracing}/external/expected/include
  ${caf_simple_tracing}/external/optional/include
  ${caf_simple_tracing}/external/fmtlib/include
  ${caf_simple_tracing}/external/gsl/include
  ${caf_simple_tracing}/external/philslib/include
)

target_compile_definitions(
  ${LIB_NAME}
  PUBLIC
  CAF_ENABLE_ACTOR_PROFILER
  FMT_HEADER_ONLY
  __USE_POSIX
)

