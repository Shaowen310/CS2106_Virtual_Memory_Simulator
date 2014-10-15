//
//  VirtualMemory.h
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef __CS2106_proj_VM__VirtualMemory__
#define __CS2106_proj_VM__VirtualMemory__

#include "MemArgs.h"
// PAGE_LENGTH defined in MemArgs.h
// PAGE_TABLE_LENGTH defined in MemArgs.h
// SEGMENT_TABLE_LENGTH defined in MemArgs.h
#include "PhysicalMemory.h"

class VirtualMemory {
private:
    int segmentTableSize;
    int segmentTablePageNum;
    int segmentTableAddr;
    
    int pageTableSize;
    int pageTablePageNum;
    
    PhysicalMemory physicalMem;
protected:
    int translateSegNoProtected(int segNo); // returns pageTableRefAddr
    int translatePageNoProtected(int pageNo, int pageTableStartAddr); // returns pageRefAddr
public:
    VirtualMemory();
    
    void fillSegmentTable(int segNo, int pageTableStartAddr);
    void fillPageTable(int pageNo, int segNo, int pageStartAddr);
    
    int translate(int virtualAddr, bool write);
    
    int read(int virtualAddr);
    void write(int virtualAddr, int data);
    
    void printSegmentTable();
    void printPageTableOfSeg(int segNo);
    void printPage(int pageNo);
};

#endif /* defined(__CS2106_proj_VM__VirtualMemory__) */
