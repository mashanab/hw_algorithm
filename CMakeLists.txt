project(hw)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(SRC
    main_4_task.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
