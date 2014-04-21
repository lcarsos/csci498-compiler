Building a Compiler
===================

Building
--------

You'll need:

1. [CMake](http://www.cmake.org/) **2.8**

2. Flex and Bison **>=2.5**

3. Your favorite **C++11** compiler. Any up-to-date GCC, Clang, or Intel compiler should work fine.

4. Optionally, [Graphvis](http://www.graphviz.org/) to generate AST diagrams.


    **Notes for Windows users**:

    - Our build files depend on a special Flex and Bison port. Get it [here](http://sourceforge.net/projects/winflexbison/).

    - If you want to use Visual Studio's compiler, you'll need 2013 to ensure C++11 features are available. You may want to consider using Intel's C++ compiler as it is further along the adoption process.

Clone or unzip the source somewhere. There are many tutorials on the Internet to help with this step.

This project uses CMake as its build tool. The canonical commands for CMake look like
    mkdir build
    cd build
    cmake ..
    make

This method presumes you create the build directory at the root directory of the repository. If you want to deviate from the canonical form,

    <make a build directery>
    <change into the build directory>
    cmake [options] <path-to-source>
    make

For a list of cmake options, please review the cmake man file or [online documentation](http://www.cmake.org/cmake/help/v2.8.8/cmake.html#section_Usage).

Running
-------

The binary you're interested in after building is called `frontend`. You can pipe the output from `frontend` to `parse-tree-to-graphvis.py` and that output to the Graphvis program `dot` to generate the AST tree.

    ./frontend < /path/to/repo/examples/standard.lang0 | python /path/to/repo/parse-tree-to-graphvis.py | dot -Tpng tree.png

What we're suppose to do: AST Component
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
