Generate an AST
===============

Building
--------

You'll need CMake, Flex, Bison, and your favorite C++ compiler.

Clone or unzip the source somewhere.

    $ mkdir Hellman
    $ cd Hellman
    $ git clone https://github.com/MattWesemann/Compiler.git

Make a build directory. It should work in or out of the source directory, but naming doesn't matter. I like keeping everything packaged under another directory, but they can be anywehre.

    $ mkdir build
    $ cd build

Call CMake, passing in your generator and the path to the source you cloned or unzipped earlier.

    $ cmake -G "Unix Makefiles" ../Compiler/

Make the directory for auto-generated files. CMake doesn't do this and we're working on it.

    $ mkdir flex-bison-autogen

Run `make`

    $ make

The binary you're interested in is called `frontend`.

    $ ./frontend
    int x;
    int y;
    x = 5;
    y = 10;
    int z = x * y ^ 7;
    206 #206 Program
    204 #204 Declaration
    203 #203  'int'
    205 #205  'x'
    208 #208 Declaration
    207 #207  'int'
    209 #209  'y'
    211 #211 Assignment
    212 #212  'x'
    210 #210  '5'
    214 #214 Assignment
    215 #215  'y'
    213 #213  '10'
    224 #224 Declaration
    216 #216  'int'
    222 #222 Assignment
    223 #223  'z'
    221 #221 Expression '*'
    217 #217  'x'
    220 #220 Expression '^'
    218 #218  'y'
    219 #219  '7'

    206 204 208 211 214 224
    204 203 205
    208 207 209
    211 212 210
    214 215 213
    224 216 222
    222 223 221
    221 217 220
    220 218 219


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
