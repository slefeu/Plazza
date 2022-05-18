# PizzaSerializer

This class is used to serialize and deserialize a pizza.

## Constructors and Destructors

The class is deleted because it's not supposed to be instanciated.

## Methods

### serializePizza

This method is used to serialize a pizza. It takes a `pizza` as parameter and return an array of `bitset`. Each `bitset` contains 64 bits. The first `bitset` contains the type of the pizza, the second one contains the size of the pizza, the third one contains the ingredients of the pizza, the fourth one contains the integral part of the cooking time and the fifth one contains the fractional part of the cooking time. The integral part is stored in an `unsigned int`, so it can only store numbers between 0 and 4294967295. The fractional part is stored in a `double`, so it can only store numbers between 0 and 1. To store numbers bigger than 1, we multiply them by 10000000 and we store them in an `unsigned int`. This way we can store numbers between 0 and 4294967295. We then divide them by 10 until they are smaller than 1. This way we can store numbers between 0 and 1 with 7 decimals precision.

### serializeCommand

This method is used to serialize a command. It takes a `char` as parameter and return a `bitset` containing 8 bits. The `char` is converted into an `unsigned int` which is then converted into a `bitset` containing 8 bits. This way we can send commands through sockets using only 8 bits instead of 8 bytes (64 bits).

### deserializePizza

This method is used to deserialize a pizza. It takes an array of `bitset` as parameter and return a `pizza` object. The first `bitset` contains the type of the pizza, the second one contains the size of the pizza, the third one contains the ingredients of the pizza, the fourth one contains the integral part of the cooking time and the fifth one contains the fractional part of the cooking time. The integral part is stored in an `unsigned int`, so it can only store numbers between 0 and 4294967295. The fractional part is stored in a `double`, so it can only store numbers between 0 and 1. To store numbers bigger than 1, we multiply them by 10000000 and we store them in an `unsigned int`. This way we can store numbers between 0 and 4294967295. We then divide them by 10 until they are smaller than 1. This way we can store numbers between 0 and 1 with 7 decimals precision.

### enumToBitset

This method is used to convert an enum into a bitset. It takes an `unsigned int` and a `bitset` as parameter and return a `bitset`. The `unsigned int` is converted into a `bitset` using the constructor of the `bitset` class. The two `bitsets` are then ORed together and the result is returned.

### enumlistToBitset

This method is used to convert a list of enum into a bitset. It takes a list of enum as parameter and return a `bitset`. The list of enum is converted into a list of `unsigned int` using the `static_cast` operator. Each `unsigned int` is converted into a `bitset` using the constructor of the `bitset` class. The two `bitsets` are then ORed together and the result is returned.

### getDoubleFractional

This method is used to get the fractional part of a double. It takes a `double` as parameter and return an `unsigned int`. The `double` is multiplied by 10000000 and it's converted into an `unsigned int` using the `static_cast` operator. We then divide it by 10 until it's smaller than 1. This way we can store numbers between 0 and 1 with 7 decimals precision. The result is returned.

### findCookingTime

This method is used to find the cooking time of a pizza from its integral part and its fractional part stored in two bitsets. It takes two bitsets as parameter and return a double containing the cooking time of the pizza. The integral part is converted into an unsigned int using the `to_ulong()` method of the `bitset` class. The fractional part is converted into an unsigned int using the `to_ulong()` method of the `bitset` class, then it's converted into a double using the `static_cast` operator, then it's divided by 10 until it's smaller than 1. This way we can store numbers between 0 and 1 with 7 decimals precision. The integral part and the fractional part are added together and the result is returned.

### bitsetToIngredients

This method is used to convert a bitset containing ingredients into a list of ingredients. It takes a `bitset` as parameter and return a list of ingredients. We loop through each bit in the bitset, if it's set to 1, we add its corresponding ingredient to our list of ingredients using the `emplace_back()` method of the `vector` class, otherwise we do nothing. The list of ingredients is returned at the end of our loop.

### bitsetToInt

This method is used to convert a bitset into an unsigned int. It takes a `bitset` as parameter and return an `unsigned int`. The `bitset` is converted into an `unsigned int` using the `to_ulong()` method of the `bitset` class. The result is returned.

### getRequestType

This method is used to get the type of a request from a bitset. It takes a `bitset` as parameter and return a `RequestType` enum. We loop through each possible value of the `RequestType` enum, if the value of our `bitset` is equal to the value of our enum, we return it, otherwise we do nothing. If we reach the end of our loop without finding a match, we return `RequestType::Empty`.

### createRequestType

This method is used to create a bitset containing the type of a request. It takes a `RequestType` enum as parameter and return a bitset. The `RequestType` enum is converted into an unsigned int using the `static_cast` operator, then it's converted into a bitset using the constructor of the `bitset` class. The result is returned.

## Usage

The class can be used to serialize and deserialize a pizza.

## Exemple

Let's say we want to serialize a pizza. We can do the following :

```cpp
pizza::Pizza my_pizza(pizza::PizzaType::Regina, 5);
my_pizza.addIngredient(pizza::Ingredients::Cheese);
my_pizza.addIngredient(pizza::Ingredients::GoatCheese);
auto serialized_pizza = PizzaSerializer::serializePizza(my_pizza);
```

The serialized_pizza variable will contain an array of 5 bitsets. The result of this exemple is :

```cpp
serialized_pizza[0] = 0000000000000100;
serialized_pizza[1] = 0000000000000000;
serialized_pizza[2] = 0000000000000010;
serialized_pizza[3] = 0000000000000101;
serialized_pizza[4] = 0000000000000001;
```

We can now send this array over the network and deserialize it on the other side. We can do the following :

```cpp
auto deserialized_pizza = PizzaSerializer::deserializePizza(serialized_pizza);
```