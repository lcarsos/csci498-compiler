Generate an AST
===============

Building
--------

You'll need:

1. [CMake](http://www.cmake.org/) **2.8**

2. Flex and Bison **2.5**

3. Your favorite **C++11** compiler. Any up-to-date GCC, Clang, or Intel compiler should work fine.

4. Optionally, [Graphvis](http://www.graphviz.org/) to generate AST diagrams.


    **Notes for Windows users**:

    - Our build files depend on a special Flex and Bison port. Get it [here](http://sourceforge.net/projects/winflexbison/).

    - If you want to use Visual Studio's compiler, you'll need 2013 to ensure C++11 features are available. You may want to consider using Intel's C++ compiler as it is further along the adoption process.

Clone or unzip the source somewhere. Here we'll make a parent directory, `Hellman`, with subdirectories for the source code and one for each build configuration used.

    $ mkdir Hellman
    $ cd Hellman
    $ git clone https://github.com/sgonzalez/csci498-compiler.git Kompiler

Next, make a build directory.

    $ mkdir build-debug
    $ cd build-debug

Call CMake, passing in your prefered generator and the path to the source you cloned or unzipped earlier. You can see a list of CMake generators for your system by running `cmake` with no arguments. You'll also want to define any Debug/Release related flags here, unless you're generating for an IDE. In this example, we assume a Unix-like system.

    $ cmake -G "Unix Makefiles" ../Kompiler/

Then all you need to do is run `make`.

    $ make

For an optimized Makefiles directory, repeat the steps above but add `-DCMAKE_BUILD_TYPE=Release` to the cmake invocation. The default `CMAKE_BUILD_TYPE` changes with compilers.

The binary you're interested in after building is called `frontend`. You can pipe the output from `frontend` to `parse-tree-to-graphvis.py` and that output to the Graphvis program `dot` to generate the AST tree.

From `Hellman` in the previous example:

    $ cat ./Kompiler/examples/standard.lang0 | ./frontend | ./Kompiler/parse-tree-to-graphvis.py | dot -Tpng -o tree.png

In one go:

    $ mkdir Hellman
    $ cd Hellman
    $ git clone https://github.com/sgonzalez/csci498-compiler.git Kompiler
    $ mkdir build-debug
    $ cd build-debug
    $ cmake -G "Unix Makefiles" ../Kompiler/
    $ make
    $ cat ./Kompiler/examples/standard.lang0 | ./frontend | ./Kompiler/parse-tree-to-graphvis.py | dot -Tpng -o tree.png

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

- Print information about scoping and symbols to stdout on a succesful go.
