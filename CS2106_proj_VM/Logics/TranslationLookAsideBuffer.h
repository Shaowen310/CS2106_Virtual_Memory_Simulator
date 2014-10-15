//
//  TranslationLookAsideBuffer.h
//  CS2106_proj_VM
//
//  Created by Zsw on 14/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef __CS2106_proj_VM__TranslationLookAsideBuffer__
#define __CS2106_proj_VM__TranslationLookAsideBuffer__

#define BUFFER_SIZE 4
#define PAGE_ADDR_NOT_BUFFERED -1

struct SegNoPageNo {
    int segNo;
    int pageNo;
    
    SegNoPageNo() {}
    SegNoPageNo(int segNo, int pageNo);
    bool equals(SegNoPageNo& other);
};

struct TLBBlock {
    SegNoPageNo segNoPageNo;
    int pageAddr;
    
    TLBBlock() {}
    TLBBlock(int segNo, int pageNo, int pageAddr);
};

class TranslationLookAsideBuffer {
private:
    int numStored;
    TLBBlock blocks[BUFFER_SIZE];
public:
    TranslationLookAsideBuffer();
    
    int access(int segNo, int pageNo);
    void push(int segNo, int pageNo, int pageAddr);
};

#endif /* defined(__CS2106_proj_VM__TranslationLookAsideBuffer__) */
