## Handling time in kitchens : Clock class

This class is used to handle time in our kitchens. It is used to know if the kitchen is idle or not, if the stocks needs to be refilled and if it is time to cook the orders.

### Constructors and Destructors

The default, copy, move constructors as well as the destructor are default generated.

## In-depth explanation of the methods:

```c++
void setIdle(bool value) noexcept
```
- This method sets the kitchen's attribute `idle_` to the boolean value passed in parameters.
- If the kitchen is idle, then it sets the start time to the current time.

```c++
bool isIdle() const noexcept
```
- This method returns `true` if the kitchen has been idle for more than 5 seconds.

```c++
bool getIdle() const noexcept
```
- This method returns the state of the kitchen : idle or not.

```c++
void reset() noexcept
```
- This method resets the start time to the current time.

```c++
bool isNSeconds(unsigned int seconds) noexcept
```
- This method returns true if the number of seconds passed as parameters has passed.

## Static methods

```c++
    static auto getSeconds(T seconds) noexcept
```
- This method returns the number of seconds passed as parameter.
- This method takes a template as parameter.

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
