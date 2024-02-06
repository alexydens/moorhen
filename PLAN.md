# Plan for Moorhen: My Latest Atempt at a C Codebase

## Specs:
- C Standard: C99.
    - Reason: Adds inline functions.
    - Note: I will still not be using C++ comments, nor will I mix declarations
    and program code.
- Platforms supported: Windows, Linux.
    - Reason: I have a windows laptop running WSL. Anything else would be quite
    a hassle to test.
- OpenGL Version: 3.3
    - Reason: For some reason, thats as high as WSL2 supports without me having
    to spend hours fiddling with drivers. Furthermore, last time I tried to do
    that it _still_ didn't work.
- Vulkan Version: Not sure
    - Reason: I don't know anything about Vulkan versions, I have not even used
    Vulkan before. I can't see this being a pressing matter anytime soon, since
    I will have to have done a lot of prep before even considering writing some
    Vulkan code in this library. After all, it does seem to carry quite the
    reputation for being rather complicated. TL;DR: Problem for future me.

## Things to consider using:
### Libraries:
- GNUlib or APR for POSIX conformity with system functions?
- CGLM or Kazmath for linear algebra and matrix manipulation?
- SDL2 for windowing?
- Xlib for windowing?
- Win32 API.
- libcurses for terminal I/O.
- CImGUI for UI in windowed applications (particularly with any form of graphics
API contexts.
### CRT Functions:
- `getopt_long()` for parsing command line options.
- `select()` and `fd_set` for managing blocking I/O functions.
- `mmap` for allocation and file handling (in certain cases).
- `strerror(errno)` whenever a system functions fails (and whenever a system
functions is called, this should be checked).
- `mprotect()` in allocators to handle ownership.
- `getenv()` to get environment variables.
### Error Handling:
- Check for errors after every system function.
    - Use `strerror(errno)` if this fails.
- Check for a return of `NULL` after every call of `malloc()` and `realloc`.
    - When this happens, and memory is exhausted, it should be considered a
    fatal error. Use an assertion or a conditional statement followed by a fatal
    error (says fatal, calls `exit(EXIT_FAILURE)`) if this happens.
- Try to add protection for low level things with signals, as they act like
a system exception and also can be handled in the program itself.
- Parsing errors: (e.g. shaders, json): GNU Standards say the following:
    - either `sourcefile:lineno: message`
    - or `sourcefile:lineno.column: message`
- Other errors: GNU Standards say the following:
    - either `program:sourcefile:lineno: message`
    - or `program: message`
### Debugging Tools:
- Valgrind (more memory-focused).
- GDB (versatile, from GNU, so standard).
### Other:
- Use the `TMPDIR` env variable rather than `/tmp` if possible.
- Add a `--version` and `--help` in commmand line programs.

## Features:

### Base:
#### Context Cracking:
- Compiler, and with that:
- Architecture.
- Operating system.
#### Hot reloading:
- Might be interesting to try and implement.
#### Simple Types:
- Rust style ux, ix, and fx types.
- A bool type for booleans (`#if !defined(__cplusplus)`)
#### Symbolic consts:
- Max and min for relevant types.
- Float's machine epsilons.
- Euler's number, pi.
#### Optimisations:
- SIMD Optimisations.
- Increase cache hits if possible (not sure I get in practise).
- Register storage for iterators.
- Reference memory only when necessary.
- Use switch statements when possible (put frequent options first).
- Chars will become ints for operations, so avoid using them for operations too
much.
- Pre increment where possible.

### Memory:
#### Allocators:
- __Allocator union and type.__
- Arena.
- Chunk.
#### Structured Data Types:
- Dynamic array.
- Stack (fixed size).
#### Strings:
- Length based strings?

### Maths:
#### Floats:
- Linear interpolation.
- Infinity const.
#### Vectors:
- Add, subtract.
- Dot product, cross product.
- Normalize.
- Scale.
#### Matrices:
- Identity matrix.
- Translation matrix.
- Rotation matrix.
- Matrix multiplication.
- Matrix like `gluLookAt()`.
- Perspective projections matrix.

### Logging:
#### Assertions:
- A new `ASSERT_ONFAIL`.
#### Output:
- Log to file, `stderr` or `stdout` (just pass in a file descriptor).
- Info, success, error, fatal (exits).
- Colours (to use in general, for success, error, etc) (with ANSI escape codes).

### Files/Saved Data:
#### Basic File I/O:
- Read full file.
- Write full file.
- Append to file.
#### Format(s):
- OBJ parser for 3D models.
- JSON parser for general data.
- Some image formats? (.PNG, .PPM, .JPEG)?

### Networking (SUPPORT: Windows, Linux):
#### Basic sockets:
- __Maybe IPv6 as well? - IPv4 at least, only TCP/IP__
- Create and destroy sockets.
- Bind and listen (1 func).
- Connect to server as client.
- Send and receive data (`void* data, u64 size`).
#### Multi-Client Server:
- A multi-client server with the `fd_set`.
- Update & receive data.
- Run on separate thread (`select()` is blocking).
- Send to all.

### Graphics (SUPPORT: Windows, Linux) (USE: OpenGL, Vulkan):
#### Structs:
- Color structs - rgb, rgba for different types.
- Vertex structs - with tex coords, normals, etc.
#### VBO, VAO:
- For data in.
#### RBO, FBO:
- For rendering to texture.
#### Optimisations:
- LOD (Level Of Detail) - custom, generated.
- Frustum culling.
- Occlusion culling.
- Spacial hash grids (not necessarily specific to graphics).
#### Shaders:
- Compute, vertex, fragment, (geometry?).
- Uniforms - support all types in base simple typedefs and maths section.
- Hot reloading.

### Assets:
#### Shaders:
##### Fragment:
- Solid colour.
- Texture.
- Blinn-Phong.
- PBR.
##### Vertex:
- 3D, 2D.
