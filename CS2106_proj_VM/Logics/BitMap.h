//
//  BitMap.h
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef __CS2106_proj_VM__BitMap__
#define __CS2106_proj_VM__BitMap__

#include "MemArgs.h"
// FRAME_LENGTH defined in MemArgs.h

class BitMap {
private:
    int mapSize; // frameSize / (sizeof(int) * 8)
    int* map; 
    int maskSize; // sizeof(int) * 8
    int* masks;
public:
    BitMap();
    ~BitMap();
    
    // find the pageNo of a free page
    // throw exception if cannot find
    int findFreePage();
    // find the starting pageNo of free Pages of length num
    // throw exception if cannot find
    int findFreePages(int numRequired);
    
    void occupyPage(int pageNo);
    void occupyPages(int startPageNo, int numConsecutive);
    void freePage(int pageNo);
    void freePages(int startPageNo, int numConsecutive);
};

#endif /* defined(__CS2106_proj_VM__BitMap__) */
