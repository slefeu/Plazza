# Fridge class

The `Fridge` class is the storage of ingredients for pizzas. 
It contains an `std::array` of `size_t`s which is the stock for each ingredient.
It also contains a `restock_time_` which is the time needed to restock the fridge.

## Constructors and destructor

The `Fridge` constructor takes a `unsigned int` as parameter. It initializes the fridge's stock with the maximum value and sets the restock time.
The default destructor is generated as it does nothing.
The copy/move constructor and operator are generated as well as they are not needed.

## Public methods

  * `restock`
    * This method increases the stock of each ingredient by 1 if it is below the maximum.
  * `getRestockTime`
    * This method returns the restock time of the fridge.
  * `hasEnough`
    * This method takes a `std::vector` of ingredients as parameter. It returns true if the fridge has enough stock for each ingredient in the vector.
  * `takeIngredients`
    * This method takes a `std::vector` of ingredients as parameter. It removes one unit of each ingredient from the fridge's stock.
  * `display`
    * This method displays the stock of each ingredient in the fridge.

## Protected and private methods

  * `remove`
    * This method takes a double as parameter. It removes one unit of the ingredient in the fridge's stock.
  * `contains`
    * This method takes a double as parameter. It returns true if the fridge has enough stock of the ingredient.

## Usage

```cpp
#include <vector>
#include "Fridge.hpp"

int main()
{
    // create a fridge with a restock time of 5 seconds
    plazza::Fridge fridge(5);

    // create a vector of ingredients for a margarita pizza
    std::vector<pizza::Ingredients> list = {pizza::Ingredients::Doe, pizza::Ingredients::Tomato, pizza::Ingredients::Gruyere};

    // check if the fridge has enough ingredients for the margarita pizza
    if (fridge.hasEnough(list)) {
        // take the ingredients from the fridge
        fridge.takeIngredients(list);
        // display the fridge's stock
        fridge.display();
    }

    // restock the fridge
    fridge.restock();

    return (0);
}
```