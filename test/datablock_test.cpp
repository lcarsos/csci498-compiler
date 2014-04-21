#include <stdio.h>
#include <string>
#include "datablock.h"

int main() {
    DataBlock db1;
    DataBlock db2(40ul);
    puts("Newly initilized");
    puts("var   | size |  len | store");
    printf("db1   | %4d | %4d | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4d | %4d | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    nameRef hw1 = db1.insert("HelloWorld");
    nameRef hw2 = db2.insert("HelloWorld");
    puts("Added HelloWorld");
    puts("var   | size |  len | store");
    printf("db1   | %4d | %4d | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4d | %4d | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    nameRef fbb1 = db1.insert("foobarbaz");
    nameRef fbb2 = db2.insert("foobarbaz");
    puts("Added foobarbaz");
    puts("var   | size |  len | store");
    printf("db1   | %4d | %4d | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4d | %4d | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    nameRef java1 = db1.insert("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    nameRef java2 = db2.insert("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    puts("Added com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    puts("var   | size |  len | store");
    printf("db1   | %4d | %4d | %s\n", db1.getSize(), db1.getLength(), db1.getDatablock());
    printf("db2   | %4d | %4d | %s\n", db2.getSize(), db2.getLength(), db2.getDatablock());

    puts("");

    std::string test;

    test = db1.get(hw1);
    printf("db1:hw1 - %s\n", test.c_str());
    test = db1.get(fbb1);
    printf("db1:fbb1 - %s\n", test.c_str());
    test = db1.get(java1);
    printf("db1:java1 - %s\n", test.c_str());

    test = db2.get(hw2);
    printf("db2:hw2 - %s\n", test.c_str());
    test = db2.get(fbb2);
    printf("db2:fbb2 - %s\n", test.c_str());
    test = db2.get(java2);
    printf("db2:java2 - %s\n", test.c_str());


}
