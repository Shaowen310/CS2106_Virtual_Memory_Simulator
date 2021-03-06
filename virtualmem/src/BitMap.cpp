//
//  BitMap.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "BitMap.h"
#include "MemExceptions.h"
#include <iostream>

BitMap::BitMap() {
    this->totalPageNum = 1 << FRAME_LENGTH;
    
    this->maskSize = sizeof(int) * 8;
    this->masks = new int[maskSize];
    this->masks[0] = 1;
    for (int i = 1; i < maskSize; i++) {
        this->masks[i] = this->masks[i-1] << 1;
    }
    
    this->mapSize = totalPageNum / maskSize;
    this->map = new int[mapSize];
    for (int i = 0; i < mapSize; i++) {
        this->map[i] = 0;
    }
}

BitMap::~BitMap() {
    delete[] map;
    delete[] masks;
}

void BitMap::occupyPageProtected(int pageNo) {
    int mapNo = pageNo / maskSize;
    int offset = pageNo % maskSize;
    if (map[mapNo] & masks[offset]) {
        throw OccupyAlreadyOccupiedBitException();
    }
    map[mapNo] |= masks[offset];
}

void BitMap::occupyPage(int pageNo) {
    if (pageNo < 0 || pageNo >= totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    occupyPageProtected(pageNo);
}

void BitMap::occupyPages(int startPageNo, int numConsecutive) {
    if (startPageNo < 0 || startPageNo >= totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    if (numConsecutive < 0 || numConsecutive > totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    int tempPageNo = startPageNo;
    for (int i = numConsecutive; i > 0; i--) {
        occupyPageProtected(tempPageNo);
        tempPageNo++;
        if (tempPageNo == totalPageNum) {
            tempPageNo = 0;
        }
    }
}

void BitMap::freePageProtected(int pageNo) {
    int mapNo = pageNo / maskSize;
    int offset = pageNo % maskSize;
    map[mapNo] &= (~ masks[offset]);
}

void BitMap::freePage(int pageNo) {
    if (pageNo < 0 || pageNo >= totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    freePageProtected(pageNo);
}

void BitMap::freePages(int startPageNo, int numConsecutive) {
    if (startPageNo < 0 || startPageNo >= totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    if (numConsecutive < 0 || numConsecutive > totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    int tempPageNo = startPageNo;
    for (int i = numConsecutive; i > 0; i--) {
        freePageProtected(tempPageNo);
        tempPageNo++;
        if (tempPageNo == totalPageNum) {
            tempPageNo = 0;
        }
    }
}

bool BitMap::isPageFreeProtected(int pageNo) {
    int mapNo = pageNo / maskSize;
    int offset = pageNo % maskSize;
    return (map[mapNo] & masks[offset]) ? false : true;
}

int BitMap::findFreePage() {
    int tempPageNo = searchStartPageNo;
    do {
        if (isPageFreeProtected(tempPageNo)) {
            return tempPageNo;
        }
        tempPageNo++;
        if (tempPageNo == totalPageNum) {
            tempPageNo = 0;
        }
    }
    while (tempPageNo != searchStartPageNo);
    throw InsufficientMemoryException();
}

int BitMap::findFreePages(int numRequired) {
    if (numRequired > totalPageNum) {
        throw InsufficientMemoryException();
    }
    int tempPageNo = searchStartPageNo;
    int traversed = 0;
    do {
        traversed++;
        if (isPageFreeProtected(tempPageNo)) {
            int i;
            int possibleStartPageNo = tempPageNo;
            for (i = 1; i < numRequired; i++) {
                tempPageNo++;
                if (tempPageNo == totalPageNum) {
                    tempPageNo = 0;
                }
                traversed++;
                if (!isPageFreeProtected(tempPageNo)) break;
            }
            if (i == numRequired) {
                return possibleStartPageNo;
            }
        }
        tempPageNo++;
        if (tempPageNo == totalPageNum) {
            tempPageNo = 0;
        }
    }
    while (traversed <= totalPageNum);
    throw InsufficientMemoryException();
}

bool BitMap::isPageFree(int pageNo) {
    if (pageNo < 0 || pageNo >= totalPageNum) {
        throw PageNoOutOfBoundException();
    }
    return isPageFreeProtected(pageNo);
}

void BitMap::printMask() {
    for (int i = 0; i < maskSize; i++) {
        std::cout << i << ' ' << masks[i] << std::endl;
    }
}

void BitMap::printMap() {
    for (int i = 0; i < mapSize; i++) {
        std::cout << i << ' ' << map[i] << std::endl;
    }
}

