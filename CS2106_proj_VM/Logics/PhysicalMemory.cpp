//
//  PhysicalMemory.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "PhysicalMemory.h"
#include "MemExceptions.h"

PhysicalMemory::PhysicalMemory() {
    this->memSize = (1 << PAGE_LENGTH) << FRAME_LENGTH;
    this->valid = new bool[memSize];
    for (int i = 0; i < memSize; i++) {
        this->valid[i] = false;
    }
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
    if (!valid[addr]) {
        throw InvalidReadException();
    }
    return data[addr];
}

void PhysicalMemory::write(int addr, int data) {
    if (addr < 0 || addr >= memSize) {
        throw AddrOutOfBoundException();
    }
    valid[addr] = true;
    this->data[addr] = data;
}

