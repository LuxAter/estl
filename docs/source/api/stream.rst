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

===============  ========================
Enumerations
-----------------------------------------
enum             :cpp:enum:`estl::Format`
Functions
-----------------------------------------
``void``         :cpp:func:`estl::cprint`
``void``         :cpp:func:`estl::cscan`
``void``         :cpp:func:`estl::print`
``void``         :cpp:func:`estl::print`
``void``         :cpp:func:`estl::scan`
``void``         :cpp:func:`estl::scan`
``std::string``  :cpp:func:`estl::sprint`
``void``         :cpp:func:`estl::sscan`
===============  ========================

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

.. cpp:function:: template<typename T> \
                  T scan_delim(std::istream& in, std::string __delim, bool__width = false, unsigned int __scan_width = 0, unsigned int num_fmt = estl::Format::NONE)

   Reads from `istream` untill stopped.

   Reads characterfs from istream untill ther are no more characters to read,
   or untill one of the the characters in `__delim` is read. Then reads data
   from set of characters using `>>` operators for type `T`.

   :tparam T: Type to read from stream.
   :param in: `istream` to read input from.
   :param __delim: String of characters that will stop the reading.
   :param __width: Boolean flag to enable scan width.
   :param __scan_width: Number of characters to stop reading at if `__width` is
                        true.
   :param num_fmt: Additional format information for reading numeric values.

   :return: ``T`` Value read from `in`.

.. cpp:function:: template<typename... Args>\
                  std::string sprint(std::string __format, Args... args)

   String interface for stream formatted print.

   :tparam Args: Packed set of variadic template arguments.
   :param __format: Format stirng defining the format of the output to
                    resulting string.
   :param args: Packed set of additional variables.
   :return: String containing formated values.

.. cpp:function:: template<typename... Args>\
                  void sscan(std::string __str, std::string __format, Args&... args)

   String interface to stream formatted scan.

   :tparam Args: Packed set of variadic template arguments.
   :param __str: String containing formated input data.
   :param __format: Format string defining the format of the input to read from
                    **__str**.
   :param args: Paked set of additional variables.
