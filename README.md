# Stack-hack #

## Intro ##

If you see `"Stack has been Smashed"`,
the stack has been modified, through an unauthorized access as the variables are declared as const.

To avoid compiler optimization, we NEED to use 'volatile' to force the comparison, if we don't the compiler pre-fill the condition and so the condition isn't really evaluated.

## Conditions of testing ##

The hack is limited as they are really a few variables so the variable addresses are easy to predict and there is 'nothing' else to break. If you add a new variable between `one` and `zero`, `foo()` and `foo3()` doesn't work anymore. Same for `foo2()`, if it's placed before the declaration of `g`.

## Solutions ##

Sanitizer COULD help harden the program but you should avoid rely only on it.
Options like `-fsanitize=safe-stack` seems to properly secure for the two first functions. The third as it gives the an access through another scope, the hack works.

Options that CAN'T avoid the smash in this particuliar case :

- `-fPIE` : enables the ASLR (Address space layout randomization), the program uses 'random' addresses for variables and functions BUT here, the variables are stored contiguously so it changes nothing.
- `-D_FORTIFY_SOURCE=3` : detect buffer overflow vulnerabilities and other memory-related issues, but here we are using direct addressing to generate the hack
- `-fsanitize-minimal-runtime` : don't do anything
- `-fstack-protector` : don't protect anything here
