add_library(
    Communication
    Serializer.cpp
    NamedPipe.cpp
)

target_include_directories(Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
"${PROJECT_SOURCE_DIR}/Kitchen/Pizzas"
"${PROJECT_SOURCE_DIR}/Error"
)