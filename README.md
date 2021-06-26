# Implementation of pseudo-reflection mechanism in C++

This code implements a pseudo-reflection mechanism on objects. It provides a possibility to store a metadata of the structure (`struct` or `class`) and process each member of that structure separately. This does not happen automatically. Every structure to be processed this way must be completed with metadata definition (thats why it's called only 'pseudo-reflection' mechanism).

## Usage

Source code that uses the pseudo-reflection mechanism must respect following order:
1. A processing context declaration/definition;
2. The Processors declaration/definition;
3. The data structures declaration/definition with reflection metadata.

### Processing context

A processing context can be any struct/class or base type. It should contain all nesseary input, output and temporary data for the processor. The processing context itself determines the right processor selection.

### Processors

A processor is a function (or template of function) that looks like this:

```c
int ict::reflect::processor(Object & object,Context & context);
```

The first argument of that function is a reference to an object to be processed. It can be any struct/class or base type. The second argument is a reference to a processing context. The processor function should return `int` type with following meaning:
* Value grater than zero - there is still data to process (the processing hasn't ended for example due to the lack of input data, or the lack of space for output data);
* Zero - The processing has been finished;
* Value less than zero - The processing has ened with an error.

It must be defined a processor (function or template of function) for each type of object that are to be processed.

### Data structures

The processors for the data strucures (`struct` or `class`) can be defined in two ways:
* As a specific function (or a template of function) for given data structure (than type of first argument is specified);
* As a generic template of function that can process any data structure that have reflection metadata defined.


Example of metadata definition in data structure declaration:
```c
#include "libict/reflection/definition.hpp"

class example {
private:
    int one;
protected:
    float two;
public:
    double three;

// Metadata definition.
REFLECT_BEGIN
    PRIVATE_PROP(one) // Adds 'one' property as private to metadata.
    PROTECTED_PROP(two) // Adds 'two' property as protected to metadata.
    PUBLIC_PROP(three,"trzy") // Adds 'three' property as public to metadata with different name.
REFLECT_END
};
```

The metadata from example above can be retrieved as `std::vector` or `std::map` container.


A `std::vector` metada example:
```c
#include "libict/reflection/meta-vector.hpp"

example e;

std::size s=ict::reflect::meta::getVector(e).size();// 3 (number of properties)
std::string propName=ict::reflect::meta::getVector(e).at(0).propName;// "one" (the property name of first property)
std::size_t index=ict::reflect::meta::getVector(e).at(1).index// a number (index of second property - it is used to execute processing of that property)
std::string givenName=ict::reflect::meta::getVector(e).at(2).givenName;// "trzy" (the given name of third property)
```

A `std::map` metada example:
```c
#include "libict/reflection/meta-map.hpp"

example e;

//Using a property name
std::size s=ict::reflect::meta::getMapByPropName(e).size();// 3 (number of properties)
std::string propName=ict::reflect::meta::getMapByPropName(e).at("one").propName;// "one" (the property name of first property)
std::size_t index=ict::reflect::meta::getMapByPropName(e).at("two").index// a number (index of second property - it is used to execute processing of that property)
std::string givenName=ict::reflect::meta::getMapByPropName(e).at("three").givenName;// "trzy" (the given name of third property)

//Using a given name
std::size s=ict::reflect::meta::getMapByGivenName(e).size();// 3 (number of properties)
std::string propName=ict::reflect::meta::getMapByGivenName(e).at("one").propName;// "one" (the property name of first property)
std::size_t index=ict::reflect::meta::getMapByGivenName(e).at("two").index// a number (index of second property - it is used to execute processing of that property)
std::string givenName=ict::reflect::meta::getMapByGivenName(e).at("trzy").givenName;// "trzy" (the given name of third property)
```

Once index of property is known it can be processed:
```c

#include "libict/reflection/process.hpp"

context c;
example e;

int result=ict::reflect::process(e,c,44);//Process property of 'example' that has index no 44 with 'c' context
``` 

## Building instructions

```sh
make # Build library
make test # Execute all tests
```
