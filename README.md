# Estl

[![Version](https://img.shields.io/github/tag/LuxAtrumStudio/estl.svg?style=for-the-badge)](https://github.com/LuxAtrumStudio/estl)
[![Documentation](https://img.shields.io/badge/Documentation-gh--pages-blue.svg?style=for-the-badge)](https://luxatrumstudio.github.io/estl/)

[![Build_Status](https://img.shields.io/travis/LuxAtrumStudio/estl/feature/iostream.svg?style=for-the-badge)](https://travis-ci.org/LuxAtrumStudio/estl)
[![Code_Coverage](https://img.shields.io/codecov/c/github/LuxAtrumStudio/estl/feature/iostream.svg?style=for-the-badge)](https://codecov.io/gh/LuxAtrumStudio/estl)
[![Code Quality](https://img.shields.io/codacy/grade/9dd431f11f53414ab360f1f34e1eef49.svg?style=for-the-badge)](https://www.codacy.com/app/LuxAtrumStudio/estl/dashboard)

[![GitHub commit activity the past week, 4 weeks, year](https://img.shields.io/github/commit-activity/y/LuxAtrumStudio/estl.svg?style=for-the-badge)](<>)
[![GitHub repo size in bytes](https://img.shields.io/github/repo-size/LuxAtrumStudio/estl.svg?style=for-the-badge)](<>)

* * *

## Introduction

Extended standard template library. This library implements a set of new
tools and extends the set of existing tools that are implemented by the
C++ standard template library. There are a number of functionalities that are
added. The basic sections are listed below:

### ArgParse

The _ArgParse_ file is based around the parsing arguments supplied from the
command line. It uses a syntax similar to that of the python class of the same
name. It allows for parsing of arguments to store data in a specified type, or
to set a flag. _ArgParse_ will automatically generate a help display, listing
all of the arguments in an ordered manner. The arguments are returned in a map
with key values as strings referencing the destination for the argument, and
the values being a `estl::Variable` holding the data value. More information
can be found on the documentation for _ArgParse_.

### Matrix ###

The *Matrix* file is primarily to provide a mathematical matrix object. Using
templated arguments, the matrix class provides all classical mathematical matrix
operations, utilizing the templated types commands.

### Stream ###

The *Stream* file is to provide an extended implementation of printf that
utilizes C++ streams. This allows for using the printf notation on any stream
object. This new implementation makes use of variadic templates, so that any
class or struct can be passed as an argument, using its respective `operator<<`
to print it to the stream. There are some default bindings for the default
streams.

### Variable ###

The *Variable* class is a class encapsulating a union of the fundamental types
in C++ as well as vectors of the fundamental types. This includes all of the
following types, and vectors of each of them:

* `bool`
* `char`
* `signed char`
* `unsigned char`
* `signed short int`
* `unsigned short int`
* `signed int`
* `unsigned int`
* `signed long int`
* `unsigned long int`
* `signed long long int`
* `unsigned long long int`
* `float`
* `double`
* `long double`
* `std::string`
* `const char*`

### Variadic ###

The *Variadic* file implements utility functions for handling variadic packed
template arguments. It provides functions for unpacking argument pack into
`vector`, `tuple`, `vector<any>`. Using these functions allows a user to access
all variables in the variadic template without requiring a recursive function.

### Vector ###

The *Vector* file is primarily to provide a mathematical vector object. Using
templated arguments, the vector class provides all classical mathematical vector
operations, utilizing the templated types commands.
