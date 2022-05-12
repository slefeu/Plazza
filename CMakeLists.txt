cmake_minimum_required(VERSION 3.6)

project(plazza VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(CXXFLAGS "-pthread")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(HEADER_FILES ${PROJECT_SOURCE_DIR}/)

add_executable(${PROJECT_NAME}
    main.cpp
    Reception.cpp
    ${HEADER_FILES}
)

IF (WIN32)
    target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "C:/mingw64/include")
ENDIF()

add_subdirectory(Error)
add_subdirectory(Kitchen)
add_subdirectory(Communication)

target_link_libraries(${PROJECT_NAME} Error)
target_link_libraries(${PROJECT_NAME} Kitchen)
target_link_libraries(${PROJECT_NAME} Communication)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_FLAGS})