# Moorhen
## What is Moorhen?
### The animal
A moorhen is a type of waterfowl, a close relative of the coot. They tend to
have black feathers and are small in size, somewhere between a pigeon and a duck.
#### How do I differentiate moorhens from coots?
Coots have white flesh above their beaks, whereas moorhens have red flesh avove
their yellow beaks, at least in my experience. I wouldn't advise looking for
birdspotting advice on github. Perhaps try [Wikipedia](https://en.wikipedia.org/wiki/Moorhen).
### This project
This is just a small header-only base library, written using the C11 standard,
to hold some basic utilities that I use in my other projects, so I don't end up
re-writing them every single time. I use it for some freestanding projects, so
it should be dependency-free and does not use any of the standard library
headers.
#### Update:
- 1 standard library header has been used, in the file `printf.h`, the header
`<stdarg.h>` has been used. If you can't use any standard library headers, then
simply don't use this file. This shouldn't be a problem for embedded systems
or other freestanding applications because this header doesn't introduce any
depencies to libraries static or dynamic (the header itself is freestanding).
## Usage
1. Set any preferences you may have using `#define` or the `-D` compiler flag:
- `MOORHEN_SIZE_32` for 32-bit pointers, `size_t` and `ssize_t`, along with any
other size-specific things.
- `MOORHEN_SIZE_64` for 64-bit pointers, `size_t` and `ssize_t`, along with any
other size-specific things.
- `MOORHEN_DISABLE_SSE` to prevent any SSE instructions from being used. This
may limit the functionality of some headers, I would recommend trying to avoid
using this and instead just setting up SEE wherever possible. You can check if
your CPU supports this feature in `x86` or `x86_64` assembly with the `cpuid`
instruction.
- NOTE: If neither of the above two are set, 64-bit will be chosen and defined.
- `MOORHEN_INCLUDE_STDLIB` if you plan to include standard library headers, so
don't want a redefinition of `NULL`, `true`, `false`, `bool`, etc.
2. Just include in your project and you should be good to go!
## Testing
To run the tests, do the following:
1. Go to the `test` directory: `cd test`.
2. Run the tests: `make`.
- `gcc` is required.
- `make` is required.
