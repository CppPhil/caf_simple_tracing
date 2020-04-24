set(NODE_A_HEADERS)

set(NODE_A_SOURCES src/main.cpp)

set(NODE_A_APP_NAME node_a_application)

add_executable(${NODE_A_APP_NAME} ${NODE_A_HEADERS} ${NODE_A_SOURCES})

target_link_libraries(${NODE_A_APP_NAME} PRIVATE lib)

target_include_directories(
  ${NODE_A_APP_NAME} PRIVATE ${caf_simple_tracing_SOURCE_DIR}/node_a/include)
