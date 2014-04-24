#include "datablock.h"

#include <cstdio>
#include <string>

int main() {
    DataBlock datablock;
    std::string test = "helloWorld";
    const char* fbb = "foobarbaz";

    printf("Newly initilized\n");
    printf("var         | size | store\n");
    printf("datablock   | %4d | %s\n", datablock.getSize(), datablock.getDataBlock().c_str());
	printf("\n");

    NameRef hw1 = datablock.lookup(test);
    printf("lookup (string)HelloWorld\n");
    printf("var         | size | store\n");
    printf("datablock   | %4d | %s\n", datablock.getSize(), datablock.getDataBlock().c_str());
	printf("\n");

    NameRef fbb1 = datablock.lookup(fbb);
    printf("lookup (char*)foobarbaz\n");
    printf("var         | size | store\n");
    printf("datablock   | %4d | %s\n", datablock.getSize(), datablock.getDataBlock().c_str());
	printf("\n");

    NameRef java1 = datablock.lookup("com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState");
    printf("lookup (\"\")com.sun.java.swing.plaf.nimbus.InternalFrameInternalFrameTitlePaneInternalFrameTitlePaneMaximizeButtonWindowNotFocusedState\n");
    printf("var         | size | store\n");
    printf("datablock   | %4d | %s\n", datablock.getSize(), datablock.getDataBlock().c_str());
	printf("\n");

    NameRef fb1 = datablock.lookup("foobar");
    printf("lookup (\"\")foobarbaz\n");
    printf("var         | size | store\n");
    printf("datablock   | %4d | %s\n", datablock.getSize(), datablock.getDataBlock().c_str());
	printf("\n");
	printf("\n");


    test = datablock.getName(hw1);
    printf("datablock:hw1 - %s\n", test.c_str());
    test = datablock.getName(fbb1);
    printf("datablock:fbb1 - %s\n", test.c_str());
    test = datablock.getName(java1);
    printf("datablock:java1 - %s\n", test.c_str());
    test = datablock.getName(fb1);
    printf("datablock:fb1 - %s\n", test.c_str());

}
