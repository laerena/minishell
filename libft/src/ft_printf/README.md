*This project has been created as part of the 42 curriculum by vabisco.*

# ft_printf

## Description

'ft_printf' is a custom implementation of the standard C 'printf' function.  
It handles formatted output with a variable number of arguments, supporting most commonly used format specifiers and flags.  
The project is designed to deepen understanding of variadic functions, string formatting, and robust C programming.

**Undefined Behavior Handling**

For undefined or invalid format strings, this implementation:
- Returns '-1'
- Prints nothing
- Stops processing the function

This is a design choice and may differ from the original 'printf', which has undefined behavior in such cases.

## Features

- Supported conversions: '%c', '%s', '%p', '%d', '%i', '%u', '%x', '%X', '%%'
- Bonus: Formats handled: '-', '0', '#', ' ', '+', width and precision
- Extra: Handles length: 'l', 'll', 'z'
- Fully norm-compliant and leak-free

## Instructions

### Compilation

Clone the repository and run:
```bash
make
```
This will produce 'libftprintf.a' at the root of the project.

Create a 'main.c', here is an exemple:
```c
#include "ft_printf.h"

int main(void)
{
	ft_printf("Hello, %s! Number: %d\n", "world", 42);
	return 0;
}
```

To compile and exec, run:
```bash
gcc main.c libftprintf.a -o test_ft_printf && ./test_ft_printf
```
*Compiling with flags (-Wall -Wextra -Werror) is not recommanded to mimic original printf behavior*

### Testing

You can compare the output and return value of 'ft_printf' with the original 'printf' for all supported specifiers and flags.

## Resources

- [42 subject PDF](https://intra.42.fr)
- AI was used for: clarifying subject requirements, generating README structure, and reviewing edge-case behaviors. All code and algorithms were written and reasoned by the author.

## Algorithm and Data Structure

The implementation parses the format string, identifies format specifiers, and dispatches to handler functions for each type.  
A context structure is used to store flags, width, precision, and length modifiers.  
For each argument, the appropriate conversion and formatting is applied, and the result is written using 'write()'.  
Memory management is carefully handled to avoid leaks.

## Bonus

- Flags: '-', '0', '#', '+', space
- Field width and precision for all conversions

## Author

vabisco
