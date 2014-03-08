Generate an AST
===============

Our goals, as listed on the assignment page.

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
