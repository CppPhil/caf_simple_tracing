set(NODE_B_HEADERS
   )

set(NODE_B_SOURCES
   )

set(NODE_B_APP_NAME node_b_application)

add_executable(${NODE_B_APP_NAME} ${NODE_B_HEADERS} ${NODE_B_SOURCES})

target_link_libraries(${NODE_B_APP_NAME} PRIVATE lib)

target_include_directories(${NODE_B_APP_NAME} PRIVATE ${caf_simple_tracing_SOURCE_DIR}/node_b/include)

