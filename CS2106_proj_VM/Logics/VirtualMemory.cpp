//
//  VirtualMemory.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "VirtualMemory.h"
#include "MemExceptions.h"

VirtualMemory::VirtualMemory() {
    this->segmentTableSize = (1 << SEGMENT_TABLE_LENGTH);
    this->segmentTablePageNum = (1 << (SEGMENT_TABLE_LENGTH - PAGE_LENGTH));
    // initialize segent table
    physicalMem.initTable(segmentTablePageNum, SEGMENT_TABLE_START_ADDR);
    segmentTableAddr = SEGMENT_TABLE_START_ADDR;
    
    this->pageTableSize = (1 << PAGE_TABLE_LENGTH);
    this->pageTablePageNum = (1 << (PAGE_TABLE_LENGTH - PAGE_LENGTH));
}

int VirtualMemory::translate(int virtualAddr, bool write) {
    int segNo = (virtualAddr >> (PAGE_TABLE_LENGTH + PAGE_LENGTH));
    int pageNo = (virtualAddr >> PAGE_LENGTH) % pageTableSize;
    int offset = virtualAddr % (1 << PAGE_LENGTH);
    
    if (segNo < 0 || segNo >= segmentTableSize) {
        throw SegmentNoOutOfBoundException();
    }
    
    int pageTableRefAddr = translateSegNoProtected(segNo);
    int pageTableStartAddr = physicalMem.read(pageTableRefAddr);
    if (pageTableStartAddr == PAGE_NOT_IN_MEMORY) {
        throw PageFaultException();
    }
    if (pageTableStartAddr == PAGE_NOT_EXIST) {
        if (write) {
            // allocate new pageTable and update the segment table
            pageTableStartAddr = physicalMem.allocTable(pageTablePageNum);
            physicalMem.write(pageTableRefAddr, pageTableStartAddr);
        }
        else {
            throw NullPageReadException();
        }
    }
    
    int pageRefAddr = translatePageNoProtected(pageNo, pageTableStartAddr);
    int pageStartAddr = physicalMem.read(pageRefAddr);
    if (pageStartAddr == PAGE_NOT_IN_MEMORY) {
        throw PageFaultException();
    }
    if (pageStartAddr == PAGE_NOT_EXIST) {
        if (write) {
            // allocate new page and update the page table
            pageStartAddr = physicalMem.allocPage();
            physicalMem.write(pageRefAddr, pageStartAddr);
        }
        else {
            throw NullPageReadException();
        }
    }
    
    return pageStartAddr + offset;
}

int VirtualMemory::translateSegNoProtected(int segNo) {
    return segNo + segmentTableAddr;
}

int VirtualMemory::translatePageNoProtected(int pageNo, int pageTableStartAddr) {
    return pageNo + pageTableStartAddr;
}

void VirtualMemory::fillSegmentTable(int segNo, int pageTableStartAddr) {
    if (segNo < 0 || segNo >= segmentTableSize) {
        throw SegmentNoOutOfBoundException();
    }
    if (pageTableStartAddr < PAGE_NOT_IN_MEMORY) {
        throw InvalidInitAddrException();
    }
    int pageTableRefAddr = translateSegNoProtected(segNo);
    if (pageTableStartAddr > 0) {
        physicalMem.initTable(pageTablePageNum, pageTableStartAddr);
    }
    physicalMem.write(pageTableRefAddr, pageTableStartAddr);
}

void VirtualMemory::fillPageTable(int pageNo, int segNo, int pageStartAddr) {
    if (segNo < 0 || segNo >= segmentTableSize) {
        throw SegmentNoOutOfBoundException();
    }
    if (pageNo < 0 || pageNo >= pageTableSize) {
        throw PageTablePageNoOutOfBoundException();
    }
    if (pageStartAddr < PAGE_NOT_IN_MEMORY) {
        throw InvalidInitAddrException();
    }
    int pageTableStartAddr = physicalMem.read(translateSegNoProtected(segNo));
    int pageRefAddr = translatePageNoProtected(pageNo, pageTableStartAddr);
    if (pageStartAddr > 0) {
        physicalMem.initPage(pageStartAddr);
    }
    physicalMem.write(pageRefAddr, pageStartAddr);
}

int VirtualMemory::read(int virtualAddr) {
    return physicalMem.read(translate(virtualAddr, false));
}

void VirtualMemory::write(int virtualAddr, int data) {
    physicalMem.write(translate(virtualAddr, true), data);
}

void VirtualMemory::printSegmentTable() {
    int totalPageNum = 1 << FRAME_LENGTH;
    int pageNo = SEGMENT_TABLE_START_ADDR >> PAGE_LENGTH;
    for (int i = 0; i < segmentTablePageNum; i++) {
        physicalMem.printValidDataOfPage(pageNo);
        pageNo++;
        if (pageNo == totalPageNum) {
            pageNo = 0;
        }
    }
}

void VirtualMemory::printPageTableOfSeg(int segNo) {
    if (segNo < 0 || segNo >= segmentTableSize) {
        throw SegmentNoOutOfBoundException();
    }
    int pageStartAddr = physicalMem.read(translateSegNoProtected(segNo));
    int totalPageNum = 1 << FRAME_LENGTH;
    int pageNo = pageStartAddr >> PAGE_LENGTH;
    for (int i = 0; i < pageTablePageNum; i++) {
        physicalMem.printValidDataOfPage(pageNo);
        pageNo++;
        if (pageNo == totalPageNum) {
            pageNo = 0;
        }
    }
}

void VirtualMemory::printPage(int pageNo) {
    physicalMem.printValidDataOfPage(pageNo);
}