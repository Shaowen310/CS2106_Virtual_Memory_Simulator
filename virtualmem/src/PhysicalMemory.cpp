//
//  PhysicalMemory.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "PhysicalMemory.h"
#include "MemExceptions.h"
#include <iostream>

PhysicalMemory::PhysicalMemory() {
    this->pageSize = 1 << PAGE_LENGTH;
    this->memSize = pageSize << FRAME_LENGTH;
    this->valid = new bool[memSize];
    // not going to initialize validity, initialize during allocation step
    this->data = new int[memSize];
}

PhysicalMemory::~PhysicalMemory() {
    delete[] this->valid;
    delete[] this->data;
}

int PhysicalMemory::read(int addr) {
    if (addr < 0 || addr >= memSize) {
        throw AddrOutOfBoundException();
    }
    if (bitMap.isPageFree(addr >> PAGE_LENGTH)) {
        throw InvalidPageAccessException();
    }
    if (!valid[addr]) {
        throw InvalidReadException();
    }
    return data[addr];
}

void PhysicalMemory::write(int addr, int data) {
    if (addr < 0 || addr >= memSize) {
        throw AddrOutOfBoundException();
    }
    if (bitMap.isPageFree(addr >> PAGE_LENGTH)) {
        throw InvalidPageAccessException();
    }
    valid[addr] = true;
    this->data[addr] = data;
}

int PhysicalMemory::allocTable(int num) {
    int freePageStartNo = bitMap.findFreePages(num);
    // occupy
    bitMap.occupyPages(freePageStartNo, num);
    int startAddr = (freePageStartNo << PAGE_LENGTH);
    for (int i = 0; i < pageSize * num; i++) {
        data[startAddr + i] = 0;
        valid[startAddr + i] = true;
    }
    return startAddr;
}

void PhysicalMemory::initTable(int num, int startAddr) {
    // occupy
    if (startAddr % pageSize) {
        throw AddrUnalignedException();
    }
    int startPageNo = (startAddr >> PAGE_LENGTH);
    bitMap.occupyPages(startPageNo, num);
    for (int i = 0; i < pageSize * num; i++) {
        data[startAddr + i] = 0;
        valid[startAddr + i] = true;
    }
}

int PhysicalMemory::allocPage() {
    int freePageNo = bitMap.findFreePage();
    // occupy
    bitMap.occupyPage(freePageNo);
    int startAddr = (freePageNo << PAGE_LENGTH);
    for (int i = 0; i < pageSize; i++) {
        valid[startAddr + i] = false;
    }
    return startAddr;
}

void PhysicalMemory::initPage(int startAddr) {
    // occupy
    if (startAddr % pageSize) {
        throw AddrUnalignedException();
    }
    int pageNo = (startAddr >> PAGE_LENGTH);
    bitMap.occupyPage(pageNo);
    for (int i = 0; i < pageSize; i++) {
        valid[startAddr + i] = false;
    }
}

void PhysicalMemory::printValidDataOfPage(int pageNo) {
    std::cout << "Page number: " << pageNo << std::endl;
    try {
        if (bitMap.isPageFree(pageNo)) {
            std::cout << "Page not initialized" << std::endl;
        }
        else {
            int startAddr = (pageNo << PAGE_LENGTH);
            for (int i = 0; i < pageSize; i++) {
                if (valid[startAddr + i]) {
                    std::cout << i << ' ' << data[startAddr + i] << std::endl;
                }
            }
        }
    }
    catch (PageNoOutOfBoundException& e) {
        std::cout << "Page number out of bound!" << std::endl;
    }

}
