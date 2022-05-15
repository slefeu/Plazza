add_library(
    Kitchen
    Kitchen.cpp
    Threads.cpp
    Clock.cpp
    Fridge.cpp
    Process.cpp
    Pizzas/DefaultPizzas.cpp
    Pizzas/Pizza.cpp
    Pizzas/Factory.cpp
)

target_include_directories(Kitchen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/Pizzas"
    "${PROJECT_SOURCE_DIR}/Error"

)