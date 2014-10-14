//
//  BitMap.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "BitMap.h"

BitMap::BitMap() {
    int frameSize = 1 << FRAME_LENGTH;
    this->maskSize = sizeof(int) * 8;
    
    this->masks = new int[maskSize];
    this->masks[0] = 1;
    for (int i = 1; i < maskSize; i++) {
        this->masks[i] = this->masks[i-1] << 1;
    }
    
    this->mapSize = frameSize / maskSize;
    this->map = new int[mapSize];
    for (int i = 0; i < mapSize; i++) {
        this->map[i] = 0;
    }
}