## Class Clock

This class is used to handle time in the kitchen.
It is used to know if the kitchen is idle or not, if the stocks need to be
refilled and if it is time to cook food.

### Constructors and Destructors

The default constructor and the copy, move and destructor are default generated.

## Methods

  * `setIdle`
    * This method sets the kitchen as idle or not.
    * If the kitchen is idle, then it sets the start time to the current time.
    * This method takes a boolean as parameter.
  * `isIdle`
    * This method returns true if the kitchen has been idle for more than 5
      seconds.
  * `getIdle`
    * This method returns the idle state of the kitchen.
  * `reset`
    * This method resets the start time to the current time.
  * `resetStocks`
    * This method resets the restock time to the current time.
  * `isNSeconds`
    * This method returns true if a number of seconds passed since the last call.
    * This method takes an unsigned int as parameter.

## Static methods

  * `getSeconds`
    * This method returns the number of seconds passed as parameter.
    * This method takes a template as parameter.

## Usage example

```cpp
#include "Clock.hpp"
#include <chrono>

int main()
{
    Clock clock;

    clock.setIdle(true);
    clock.reset();
    clock.resetStocks();

    if (clock.isIdle())
        return (1);
    if (clock.getIdle())
        return (1);
    if (!clock.isNSeconds(5))
        return (1);

    return (0);
}
```