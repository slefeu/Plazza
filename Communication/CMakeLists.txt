add_library(
    Communication
    Serializer.cpp
)

target_include_directories(Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
"${PROJECT_SOURCE_DIR}/Kitchen/Pizzas"
)