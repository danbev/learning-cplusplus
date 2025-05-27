## Empty Base Optimization (EBO)
This is an optimization technique in C++ that allows you to reduce the size of
classes/structs that inherit from empty base classes.

The easist way to understand this I think is to look at an example which can
be found in [ebo.cpp](../src/ebo.cpp).

Notice that we are not just saving 1 byte when we use the base class as a
member/field but with padding this becomes 4 bytes.

And recall that a struct/class is basically a description of the memory
layout for this type. The base class/struct does not have any members so
there is nothing to place on the stack/heap which if the base class/struct
did have members they would be placed before the derived class/struct's members.
So they can both have the same address in memory.

But the base class/struct can have functions and also recall that functions/methods
in c++ are free standing functions and don't take up any space in the struct.
And this is used in the standard library for example to implement deleters for
`unique_ptr`.

* So this only works for inheritance and not for composition.
* The base class must be empty.
* The base class cannot have virtual functions.
