//
//  TranslationLookAsideBuffer.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 14/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "TranslationLookAsideBuffer.h"

SegNoPageNo::SegNoPageNo(int segNo, int pageNo) {
    this->segNo = segNo;
    this->pageNo = pageNo;
}

bool SegNoPageNo::equals(SegNoPageNo &other) {
    return this->segNo == other.segNo && this->pageNo == other.pageNo;
}

TLBBlock::TLBBlock(int segNo, int pageNo, int pageAddr) {
    this->segNoPageNo.segNo = segNo;
    this->segNoPageNo.pageNo = pageNo;
    this->pageAddr = pageAddr;
}

TranslationLookAsideBuffer::TranslationLookAsideBuffer() {
    this->numStored = 0;
}

int TranslationLookAsideBuffer::access(int segNo, int pageNo) {
    SegNoPageNo tempSegNoPageNo(segNo, pageNo);
    for (int i = 0; i < numStored; i++) {
        if (blocks[i].segNoPageNo.equals(tempSegNoPageNo)) {
            // put the recently accessed to front
            TLBBlock tempBlock = blocks[i];
            for (int j = i; j > 0; j--) {
                blocks[j] = blocks[j-1];
            }
            blocks[0] = tempBlock;
            return blocks[0].pageAddr;
        }
    }
    return PAGE_ADDR_NOT_BUFFERED;
}

void TranslationLookAsideBuffer::push(int segNo, int pageNo, int pageAddr) {
    if (numStored != BUFFER_SIZE) {
        numStored++;
    }
    for (int i = numStored - 1; i > 0; i--) {
        blocks[i] = blocks[i-1];
    }
    blocks[0] = TLBBlock(segNo, pageNo, pageAddr);
}