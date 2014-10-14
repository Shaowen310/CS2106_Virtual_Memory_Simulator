//
//  PhysicalMemory.h
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef __CS2106_proj_VM__PhysicalMemory__
#define __CS2106_proj_VM__PhysicalMemory__

#include "MemArgs.h"
// PAGE_LENGTH defined in MemArgs.h
// FRAME_LENGTH defined in MemArgs.h
#include "BitMap.h"

class PhysicalMemory{
private:
    int memSize;
    int pageSize;
    bool* valid; // memSize
    int* data; // memSize
    BitMap bitMap;
public:
    PhysicalMemory();
    ~PhysicalMemory();
    
    // create segment table with num of pages and give the starting address
    // all data are initialized to 0, and data are valid
    // error checking required
    int allocTable(int num);
    
    // create a new page and give the starting address
    // all data are not initialized and are invalid
    // error checking required
    int allocNewPage();
    
    // addr must >=0 and <memSize, and addr corresponds pageNum + offset
    // error checking required
    int read(int addr);
    // error checking required
    void write(int addr, int data);
    
    void printValidDataOfPage(int pageNo);
};

#endif /* defined(__CS2106_proj_VM__PhysicalMemory__) */
