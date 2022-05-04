add_library(
    Kitchen
    Kitchen.cpp
    Threads.cpp
)

target_include_directories(Kitchen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})