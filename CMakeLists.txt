cmake_minimum_required(VERSION 3.6)

project(plazza VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(HEADER_FILES ${PROJECT_SOURCE_DIR}/)

add_executable(${PROJECT_NAME}
    main.cpp
    Reception.cpp
    ${HEADER_FILES}
)

add_subdirectory(Error)

target_link_libraries(${PROJECT_NAME} Error)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Error"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_FLAGS})