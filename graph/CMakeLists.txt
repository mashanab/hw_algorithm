project(hw_graph)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)


set(SOURCES
    src/arcgraph.cpp
    src/listgraph.cpp
    src/setgraph.cpp
    src/matrixgraph.cpp
)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
