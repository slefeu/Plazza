add_library(
    Kitchen
    Kitchen.cpp
    Threads.cpp
    Clock.cpp
    Fridge.cpp
    Pizzas/DefaultPizzas.cpp
    Pizzas/APizza.cpp
)

target_include_directories(Kitchen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/Pizzas"
)