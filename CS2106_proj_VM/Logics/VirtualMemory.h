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
    PhysicalMemory physicalMemory();
public:
    
};

#endif /* defined(__CS2106_proj_VM__VirtualMemory__) */
