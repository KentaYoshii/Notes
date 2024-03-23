# Classes

## Concrete Types
- Concrete Classes
    - Behave just like "built-in" types, and its representation is part of its definitions
        - Allow us to place object of this type on the stack, heap, and in other objects
        - Init objects immediately and completely
        - Cp and Mv
    - If a representation changes in any way, we need to recompile (price we need to pay!)
- For performance, simple functions should be _inlined_
    - Functions defined _in a class_ are inlined by default. You could use `inline` keyword to achieve the same thing
- Cp assignment and Cp initialization are defined implicitly.
- _Default Constructor_
    - Constructor that can be invoked without any argument. 
    - Helps you avoid non-init variables of that type.
- Declare a member function that does not modify the state of its object `const`
- User-defined operators should be used cautiously and conventionally
- ___Resource Acquisition Is Initialization(RAII)___
    - The technique of acquiring resources in a constructor and releasing them in a destructor.
    - Eliminates "naked `new` and `delete` operations".
- When making a container, it is often advantageous for it to be able to be created from a list
    - use `std::initializer_list`
    ```cpp
    Vector::Vector(std::initializer_list<double> lst): elem{new double[lst.size()]}, sz{std::static_cast<int>(lst.size())}
    {
        copy(lst.begin(), lst.end(), elem);
    }

    Vector v1 = {1, 2, 3, 4};
    ```
    - When we use a `{}`-list, the compiler will create an object of type `std::initializer_list`.

## Abstract Types
- Abstract Type
    - Type that completely insulates a user from implementation details.
    - Decouple the interface from the representation and give up local variables
        - Since we will not know anything about it (size, etc.), we need allocate objects on the free store and access them through _references_ and _pointers_.
- `virtual`
    - Means "may be re-defined later in a class derived from this one".
    - __Virtual Function__ is a function declared with the `virtual` keyword
        - `=0` means __virtual function__ and some class derived from the base class MUST define the function.
    - A class with virtual function should have a virtual destructor
- Abstract Class
    - a class with pure virtual function
- Abstract Class does not commonly have a constructor
    - No data to initialize!
- Abstract Class _does_ have a destructor 
    - Someone destroying an object through a pointer has no idea what subtype is being used!
    - Since destructor is virtual `delete` invokes the destructor for the most derived class. Then it calls the parent's destructor and so on 
    - Objects are therefore destroyed in derived-first manner
        - Objects are constructed in base-first manner.
- To derive from a class
    - Use `:public`
        - Vector_container is _derived_ from class Container and class Container is _base_ of class Vector_container
    - Use `override` to override virtual functions in the base class

## Virtual Functions
- When a Container has two derived classes (Vector and List), how will it know which correct function to use?
- __Virtual Table(vtbl)__
    - Each class with virtual functions has its own vtbl identifying its virtual functions
        - The compiler convert the name of a virtual function into an index into this table
        - The functions in here allow the object to be used correctly!
    - Each object of a class with virtual functions will then store a pointer to its class' vtbl
    - Overhead 
        - one vtbl for each class with virtual functions 
        - one pointer for each object of such class

## Class Hierarchies
- Class Hierarchy 
    - Set of classes ordered in a lattice created by derivation    
- Hierarchy Navigation
    - What if we want to use a method defined only on a concrete class?
    - `dynamic_cast`
    ```cpp
    Shape *ps {read_shape(cin)};
    if (Smiley* p = std::dynamic_cast<Smiley*>(ps)) // does ps point to Smiley?

    // p == nullptr if ps is not expected type or class derived from expected type

    Smiley& p {std::dynamic_cast<Smiley&>(*ps)};
    // if we use reference type, if cast fails, exception is thrown 
    ```
- Avoiding Resource Leak
    - We have to use reference or pointer for abstract class
        - But using naked pointers are not good!
            - forgetting to `delete`, etc. 
    - When deletion is required, use `std::unique_ptr` which will call delete automatically when it goes out of scope
    ```cpp
    std::unique_ptr<Shape> p {new Circle{p,r}};
    ```
      