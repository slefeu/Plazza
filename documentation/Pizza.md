# Pizza

The Pizza class is the abstract class which contains the basic attributes and methods of a pizza.

## Attributes

Pizza has the following attributes:

* PizzaType, which can be Regina, Margarita, Americana, Fantasia or Custom.
* PizzaSize, which can be S, M, L, XL or XXL.
* Ingredients, which is a vector of Ingredients.
* CookingTime, which is the time to cook the pizza.

## Methods

Pizza has the following methods:

* `getCookingTime()` returns the cooking time of the pizza.
* `getPizzaType()` returns the type of the pizza.
* `getIngredients()` returns the ingredients of the pizza.
* `getPizzaSize()` returns the size of the pizza.
* `setCookingTime(CookingTime&)` sets the cooking time of the pizza.
* `setPizzaType(PizzaType&)` sets the type of the pizza.
* `setSize(PizzaSize)` sets the size of the pizza.
* `addIngredient(Ingredients&)` adds an ingredient to a custom pizza.

## Operators

Pizza has the following operators:

* `operator<<(ostream& output, Ingredients rhs)` overloads operator << to print Ingredients.
* `operator<<(ostream& output, PizzaSize size)` overloads operator << to print PizzaSize.
* `operator<<(ostream& output, PizzaType type)` overloads operator << to print PizzaType.
* `operator<<(ostream& output, Pizza& pizza)` overloads operator << to print Pizza.

## Usage

```cpp
class MyPizza : public Pizza
{
  public:
    MyPizza() noexcept;
    MyPizza(const MyPizza&) noexcept = default;
    MyPizza(MyPizza&&) noexcept = default;
    ~MyPizza() noexcept = default;

    MyPizza& operator=(const MyPizza& rhs) noexcept = default;
    MyPizza& operator=(MyPizza&& rhs) noexcept = default;

  private:
};

MyPizza::MyPizza() noexcept
    : Pizza(PizzaType::Custom, 10.0)
{
    addIngredient(Ingredients::Dough);
    addIngredient(Ingredients::Tomato);
    addIngredient(Ingredients::Gruyere);
}

int main()
{
    MyPizza pizza;
    std::cout << pizza << std::endl;
}
```
```bash
custom S Dough Tomato Gruyere
```