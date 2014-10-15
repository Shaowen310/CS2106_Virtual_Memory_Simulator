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

// use big-endian system, 0001 for 0, 1000 for 3
// use first-fit algorithm to allocate memory
class BitMap {
private:
    int mapSize; // frameSize / (sizeof(int) * 8)
    int* map; 
    int maskSize; // sizeof(int) * 8
    int* masks;
    // always search from zero
    const int searchStartPageNo = 0;
    int totalPageNum;
protected:
    void occupyPageProtected(int pageNo);
    void freePageProtected(int pageNo);
    bool isPageFreeProtected(int pageNo);
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
    
    bool isPageFree(int pageNo);
    
    void printMap();
    void printMask();
};

#endif /* defined(__CS2106_proj_VM__BitMap__) */
