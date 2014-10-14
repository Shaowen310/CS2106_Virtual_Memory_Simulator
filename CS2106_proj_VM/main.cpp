//
//  main.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "BitMap.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    BitMap bitMap;
    
    bitMap.occupyPage(30);
    bitMap.occupyPage(1);
    bitMap.occupyPage(32);
    bitMap.occupyPage(1023);
    bitMap.freePages(5,32);
    
    
    
    std::cout << bitMap.findFreePages(2);
    bitMap.occupyPages(100,100);
    bitMap.printMap();
    
    return 0;
}
