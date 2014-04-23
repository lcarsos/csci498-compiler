#include <stdio.h>
#include <string>
#include "datablock.h"

int main() {
    DataBlock db1;
    DataBlock db2;
    std::string test = "helloWorld";
    const char* fbb = "foobarbaz";

    printf("Newly initilized\n");
    printf("var   | size | store\n");
    printf("db1   | %4d | %s\n", db1.getSize(), db1.getDataBlock().c_str());
    printf("db2   | %4d | %s\n", db2.getSize(), db2.getDataBlock().c_str());
	printf("\n");

    NameRef hw1 = db1.lookup(test);
    NameRef hw2 = db2.lookup(test);
    printf("lookup (string)HelloWorld\n");
    printf("var   | size | store\n");
    printf("db1   | %4d | %s\n", db1.getSize(), db1.getDataBlock().c_str());
    printf("db2   | %4d | %s\n", db2.getSize(), db2.getDataBlock().c_str());
	printf("\n");

    NameRef fbb1 = db1.lookup(fbb);
    NameRef fbb2 = db2.lookup(fbb);
    printf("lookup (char*)foobarbaz\n");
    printf("var   | size | store\n");
    printf("db1   | %4d | %s\n", db1.getSize(), db1.getDataBlock().c_str());
    printf("db2   | %4d | %s\n", db2.getSize(), db2.getDataBlock().c_str());
	printf("\n");

    NameRef java1 = db1.lookup("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    NameRef java2 = db2.lookup("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    printf("lookup (\"\")com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState\n");
    printf("var   | size | store\n");
    printf("db1   | %4d | %s\n", db1.getSize(), db1.getDataBlock().c_str());
    printf("db2   | %4d | %s\n", db2.getSize(), db2.getDataBlock().c_str());
	printf("\n");

    NameRef fb1 = db1.lookup("foobar");
    NameRef fb2 = db2.lookup("foobar");
    printf("lookup (\"\")foobarbaz\n");
    printf("var   | size | store\n");
    printf("db1   | %4d | %s\n", db1.getSize(), db1.getDataBlock().c_str());
    printf("db2   | %4d | %s\n", db2.getSize(), db2.getDataBlock().c_str());
	printf("\n");
	printf("\n");


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


}
