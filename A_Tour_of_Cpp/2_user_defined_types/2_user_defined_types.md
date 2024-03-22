# User-Defined Types

## Introduction
- __Built-in Types__
    - Types that can be built from the fundamental types, const modifier, and the declarator operators (*, [], etc.)
- __User-Defined Types__
    - Types that are built out of other types using C++'s abstraction mechanisms
    - Often referred as __Classes__ or __Enumerations__

## Structures and Classes
- No fundamental difference between the two 
    - __Struct__ is simply a __Class__ with members _public_ by default.
- The interface of a class is defined by its __public__ members and its __private__ members are accessible only through that interface
- Constructor
    - A member function with the same name as its class
    - Used to construct objects of a class (guaranteed to be used to initialize objects of its class)

## Enumerations
- Simple form of User-Defined types that we can use to enumerate the values
- Enumerators (i.e., the different values) are in the scope of their enum class
```cpp
enum class Traffic_Light {
    green, // starts at 0
    yellow, 
    red
}

// ok
Traffic_Light a = Traffic_Light::red;
Traffic_Light a = Traffic_Light{2};
Traffic_Light a{2};
```
- `enum` vs `enum class`
    - `enum class` specifies that an enumeration is strongly typed and that its enumerators are scoped
        - Cannot mix two enumrations' values
    - `enum` 
        - Enum values can be used as ints without the need for explicit conversions.
- Enumerations are user-defined type, so we can define operations for it!
```cpp
Traffic_Light& operator++(Traffic_Light& t)
{
    switch (t) 
    {
        case Traffic_Light::red:
            return t = Traffic_Light::green;
        ...
    }
}
```
## Unions
- A __Union__ is a struct in which all members are allocated at the same address so that the union occupies only as much space as its largest member.
    - Therefore, a __union__ can only hold a value for one member at a time.
- Used to optimize for space when you know that no two members can exist at the same time
```cpp
union Value {
    // Value::p and Value::i are in same memory location!
    Node* p;
    int i;
}
```
- The language does NOT keep track of which kind of value is currently held.
    - Programmer needs to keep track of this using a _tag_.
```cpp
struct Entry {
    string name;
    Type t; //use a tag! i.e, t == Type::i then use v.i
    Value v;
};
```
- To be safe, we can use `std::variant`
    - Stores a value of one of a set of alternative types
```cpp
struct Entry {
    string name;
    std::variant<Node*, int> v;
};
Entry pe;
...
std::holds_alternative<int>(pe.v) // does pe hold an int?
std::cout << std::get<int>(pe.v);
```