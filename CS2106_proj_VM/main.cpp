//
//  main.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "PhysicalMemory.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    PhysicalMemory pm;
    
    pm.allocTable(2);
    pm.printValidDataOfPage(0);
    pm.printValidDataOfPage(2);
    std::cout << pm.read(0) << std::endl;
    pm.printValidDataOfPage(1023);
    pm.printValidDataOfPage(1024);
//    pm.printValidDataOfPage(0);
//    pm.printValidDataOfPage(1);
//    pm.printValidDataOfPage(2);
    
    pm.allocNewPage();
//    pm.read(1024);
    pm.write(1024, 1);
    std::cout << pm.read(1024) << std::endl;
    
    return 0;
}
