.. default-domain:: cpp
.. namespace:: estl

Stream Reference
================

iostream functions utilizing variadic tempaltes.

.. code-block:: cpp

   #include <string.h>

   #include <iomanip>
   #include <iostream>
   #include <limits>
   #include <locale>
   #include <sstream>
   #include <string>
   #include <type_traits>

.. contents::
   :local:

====  ========================
enum  :cpp:enum:`estl::Format`
void  :cpp:func:`estl::cprint`
void  :cpp:func:`estl::cscan`
void  :cpp:func:`estl::print`
void  :cpp:func:`estl::print`
void  :cpp:func:`estl::scan`
void  :cpp:func:`estl::scan`
====  ========================


Enumeration Type Documentation
------------------------------

.. cpp:enum:: Format

   Enum to specify additional format information for scan.

   .. enumerator:: NONE = 0
   .. enumerator:: OCT = 1
   .. enumerator:: HEX = 2
   .. enumerator:: FLOAT_HEX = 3

Function Documentation
----------------------

.. cpp:function:: template<typename... Args> \
                  void cprint(std::string __format, Args&... args)

   Default `cout` stream interface for :cpp:func:`estl::print`.

   :tparam Args: Packed set of variadic template arguments.
   :param __format: Format stirng defining the format of the output to `cout`.
   :param args: Packed set of additional variables.

.. cpp:function:: template<typename... Args> \
                  void cscan(std::string __format, Args&... args)

   Default `cin` stream interface for :cpp:func:`estl::scan`.

   :tparam Args: Packed set of variadic template arguments.
   :param __format: Format string defining the format of the input to read from
                    `cin`.
   :param args: Packed set of additional variables.

.. cpp:function:: template<typename T, typename... Args> \
                  void print(std::ostream& out, std::string __format, T first, Args... args)

   Varadic template implementation of print.

   This function takes any number of varaibles of any types, where the first
   one must be an `ostream`, ad the second must be a format style string. Then
   every variables after that is printed according to the format string.

   :tparam T: The type of the first additional variable.
   :tparam Args: Packed set of variadic tempalte arguments.
   :param out: `ostream` reference to write output to.
   :param __format: Format string defining the format of the output to `out`.
   :param first: First additional varaible.
   :param args: Packed set of additional variables.

.. cpp:function:: void print(std::ostream& out, std::stirng __format)

   Prints the reset of the formated string, after all varaibles have been used.

   :param out: `ostream` reference to write output to.
   :param __format: Format stirng defining the format of the output to `out`.

.. cpp:function:: template<typename T, typename... Args> \
                  void scan(std::istream& in, std::string __format, T& first, Args&... args)

   Variadic template implementation of scan.

   This function takes any number of variables of any type, where the first one
   must be an `istream`, and the second must be a format stye string. Then
   every varaible after that is read from `in` according to the format string.

   .. warning::

      The reading of hexadecimal floating values is not yet implemented.

   :tparam T: The type of the first additional variable.
   :tparam Args: Packed set of variadic template arguments.
   :param in: `istream` to read input from.
   :param __format: Format string defining the format of the input from `in`.
   :param first: First additional varaible to save read data to.
   :param args: Paked set of additional variables.

.. cpp:function:: void scan(std::istream& in, std::string __format)

   Continues reading the reset of __format string, to clear the remaining
   expected contents of the `in` stream buffer.

   :param in: `istream` to read data from.
   :param __format: Format string defining the text to read from `in`.

