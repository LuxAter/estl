# ESTL FORMAT #

## Introduction ##

```cpp
#include<estl/format.hpp>
```

This section is an extremely powerful string formatter. The only accessible
function in the module has a very simple declaration.

```cpp
template <typename... Args>
inline std::string Format(std::string_view fmt, const Args&... args);
```

Here `fmt` is the format specification, and `args` are the additional variables
that are formatted into a string according to the format specification. The
additional argument can be of any type, standard or user defined. `Format` will
intelligently use the most optimal method of converting the argument to the
associated format specification.

## Format Specification ##

The format specification can be written as a string that contains "replacement
fields" that are surrounded by curly braces `{}`. Anything that is not
contained within braces is literal text that will be copied unchanged to the
output. The grammar for a replacement field is shown here

```
replacement ::= "{" argument_index [ "[" index "]" ] [":" format_spec] "}"
format_spec ::= [[fill]align][sign][0][width][.precision][type]
fill        ::= <>any character<>
align       ::= "<" | ">" | "=" | "^"
sign        ::= "+" | "-" | " "
width       ::= <>integer<>
precision   ::= <>integer<>
type        ::= "b" | "c" | "d" | "e" | "E" | "f" | "g" | "G" | "n" | "o" |
                "s" | "x" | "X" | "%"
```
