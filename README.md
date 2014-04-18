Generate an AST
===============

Building
--------

You'll need CMake, Flex, Bison, and your favorite C++ compiler.

Make a build directory. It should work in or out of the source directory, but naming doesn't matter. I like keeping everything packaged under another directory, but they can be anywehre.

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

The binary you're interested in is called `frontend`.

    $ ./frontend
    int x;
    int y;
    x = 5;
    y = 10;
    int z = x * y ^ 7;
    207 Program
    206 Declarations
    203  'int'
    204  'x'
    211 Declarations
    208  'int'
    209  'y'
    213 Assignment
    214  'y'
    212  '5'
    216 Assignment
    217  'y'
    215  '10'

    207 206 211 213 216
    206 203 204
    211 208 209
    213 214 212
    216 217 215


What we're suppose to do
------------------------

- Parse a language like this:

        //language example 0
        const int a = 1;
        int x = 1<<a;
        int y, z = 3;

        y = z - x;
        if ( y <= 0 ) {
           z = (x+2) + z*z ;
        } else {
           z = z / y;
        }
        return z;

- Generate line/column annotated error messages to stderr.

- Print the AST to stdout.

- Return 0 on successful AST creation.
