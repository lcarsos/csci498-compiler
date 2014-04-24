#include <stdio.h>
#include <string>

#include "datablock.h"

int main() {
    DataBlock db1;
    DataBlock db2(40ul);
    std::string test = "helloWorld";
    const char* fbb = "foobarbaz";

    puts("Newly initilized");
    puts("var   | size |  len | store");
    printf("db1   | %4lud | %4lud | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4lud | %4lud | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    NameRef hw1 = db1.lookup(test);
    NameRef hw2 = db2.lookup(test);
    puts("lookup (string)HelloWorld");
    puts("var   | size |  len | store");
    printf("db1   | %4lu | %4lu | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4lu | %4lu | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    NameRef fbb1 = db1.lookup(fbb);
    NameRef fbb2 = db2.lookup(fbb);
    puts("lookup (char*)foobarbaz");
    puts("var   | size |  len | store");
    printf("db1   | %4lu | %4lu | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4lu | %4lu | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    NameRef java1 = db1.lookup("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    NameRef java2 = db2.lookup("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    puts("lookup (\"\")com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    puts("var   | size |  len | store");
    printf("db1   | %4lu | %4lu | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4lu | %4lu | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    NameRef fb1 = db1.lookup("foobar");
    NameRef fb2 = db2.lookup("foobar");
    puts("lookup (\"\")foobarbaz");
    puts("var   | size |  len | store");
    printf("db1   | %4lu | %4lu | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4lu | %4lu | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    puts("");


    test = db1.getName(hw1);
    printf("db1:hw1 - %s\n", test.c_str());
    test = db1.getName(fbb1);
    printf("db1:fbb1 - %s\n", test.c_str());
    test = db1.getName(java1);
    printf("db1:java1 - %s\n", test.c_str());
    test = db1.getName(fb1);
    printf("db1:fb1 - %s\n", test.c_str());


    test = db2.getName(hw2);
    printf("db2:hw2 - %s\n", test.c_str());
    test = db2.getName(fbb2);
    printf("db2:fbb2 - %s\n", test.c_str());
    test = db2.getName(java2);
    printf("db2:java2 - %s\n", test.c_str());
    test = db2.getName(fb2);
    printf("db2:fb2 - %s\n", test.c_str());

    return 0;
}
