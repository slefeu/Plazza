# Stocks handler : Fridge class

The `Fridge` class handles the storage of ingredients for pizzas. 
It contains an `std::array` of `size_t`s which is the stock for each ingredient.
It also contains a `restock_time_` which is the time needed to restock the fridge.

## Constructors and destructor

The `Fridge` constructor takes a `unsigned int` as parameter. It initializes the fridge's stock with the maximum value and sets the restock time.

## Public methods

```c++
void restock() noexcept
```
- This method allows to increase the stock of each ingredient by 1 if it is below the maximum.
```c++
unsigned int getRestockTime() const noexcept
```
- This method returns the restock time of the fridge, which is defined in the third parameter of the program.
```c++
bool hasEnough(const std::vector<pizza::Ingredients>& list) const noexcept
```
- This method takes all the necessary ingredients to make a pizza as parameter.
- It returns true if the fridge has enough stock to create it.

```c++
void takeIngredients(const std::vector<pizza::Ingredients>& list) noexcept
```
- This method takes a `std::vector` of ingredients as parameter. It removes one unit of each ingredient from the fridge's stock.
 
```c++
void display() const noexcept
```
- This method displays the stock of each ingredient in the fridge.

## Protected and private methods

```c++
void remove(const double ingredient) noexcept
```
- This method takes a double as parameter. It removes one unit of the ingredient in the fridge's stock.

```c++
bool contains(const double ingredient) const noexcept
```
- This method takes a double as parameter.
- It returns true if the fridge has enough stock of the ingredient.

## Usage example

```cpp
#include <vector>
#include "Fridge.hpp"

int main()
{
    plazza::Fridge fridge(5);  // create a fridge with a restock time of 5 seconds

    // create a vector of ingredients for a margarita pizza
    std::vector<pizza::Ingredients> list = {pizza::Ingredients::Doe, pizza::Ingredients::Tomato, pizza::Ingredients::Gruyere};

    if (fridge.hasEnough(list)) {
        fridge.takeIngredients(list);
        fridge.display();
    }
    fridge.restock();
    return (0);
}
```
