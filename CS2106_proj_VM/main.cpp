//
//  main.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "VirtualMemory.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    VirtualMemory vm;
    
    vm.fillSegmentTable(2, 2048);
    vm.fillPageTable(0, 2, 512);
    vm.fillPageTable(1, 2, -1);
    
    //    vm.printSegmentTable();
    //    vm.printPageTableOfSeg(2);
    
    //    vm.printPage(0);
    //    vm.read(0);
    std::cout << vm.translateWithBuffer(1048576, false, true) << std::endl;
    std::cout << vm.translateWithBuffer(1048586, true, true) << std::endl;
    std::cout << vm.translateWithBuffer(1049088, true, true) << std::endl;
    
    return 0;
}