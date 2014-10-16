//
//  main.cpp
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "VirtualMemory.h"
#include "MemExceptions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

void readInitFile(std::ifstream& initFile, VirtualMemory& vm);
void readInitFileLine0(std::ifstream& initFile, VirtualMemory& vm);
void readInitFileline1(std::ifstream& initFile, VirtualMemory& vm);
void readRunFile(std::ifstream& runFile, bool hasBuffer, VirtualMemory& vm);

std::string& rtrim(std::string& s);

int main(int argc, const char * argv[]) {
    std::ifstream initFile;
    std::ifstream runFile;
    VirtualMemory vm;
    
    if (argc != 4) {
        std::cout << "Missing some arguments" << std::endl;
        return -1;
    }
    
    bool hasBuffer;
    
    if (!strcmp(argv[3], "nobuffer")) {
        hasBuffer = false;
    } else if (!strcmp(argv[3], "buffer")) {
        hasBuffer = true;
    } else {
        std::cout << "Buffer not indicated" << std::endl;
        return -1;
    }
    
    initFile.open(argv[1]);
    if (!initFile.is_open()) {
        std::cout << "Cannot open init file" << std::endl;
        return -1;
    }
    
    runFile.open(argv[2]);
    if (!runFile.is_open()) {
        std::cout << "Cannot open run file" << std::endl;
        return -1;
    }
    
    readInitFile(initFile, vm);
    readRunFile(runFile, hasBuffer, vm);
    
    initFile.close();
    runFile.close();
    
    return 0;
}

void readInitFile(std::ifstream& initFile, VirtualMemory& vm) {
    readInitFileLine0(initFile, vm);
    readInitFileline1(initFile, vm);
}

void readInitFileLine0(std::ifstream& initFile, VirtualMemory& vm) {
    std::string line0;
    std::getline(initFile, line0);
    
    rtrim(line0);
    
    std::stringstream lineStream0(line0);
    
    int segNo;
    int addr;
    while (!lineStream0.eof()) {
        lineStream0 >> segNo >> addr;
        if (lineStream0.fail()) {
            std::cout << "Init file first line format error" << std::endl;
            exit(-1);
        }
        vm.fillSegmentTable(segNo, addr);
    }
}

void readInitFileline1(std::ifstream& initFile, VirtualMemory& vm) {
    std::string line1;
    std::getline(initFile, line1);
    
    rtrim(line1);
    
    std::stringstream lineStream1(line1);
    
    int segNo;
    int pageNo;
    int addr;
    while (!lineStream1.eof()) {
        lineStream1 >> pageNo >> segNo >> addr;
        if (lineStream1.fail()) {
            std::cout << "Init file second line format error" << std::endl;
            exit(-1);
        }
        vm.fillPageTable(pageNo, segNo, addr);
    }
}

void readRunFile(std::ifstream& runFile, bool hasBuffer, VirtualMemory& vm) {
    std::string line;
    std::getline(runFile, line);
    
    rtrim(line);
    
    std::stringstream lineStream(line);
    
    bool write;
    int virtualAddr;
    while (!lineStream.eof()) {
        lineStream >> write >> virtualAddr;
        if (lineStream.fail()) {
            std::cout << "Run file format error" << std::endl;
            exit(-1);
        }
        try {
            int physicalAddr;
            physicalAddr = hasBuffer ? vm.translateWithBuffer(virtualAddr, write, true) : vm.translate(virtualAddr, write);
            std::cout << physicalAddr << ' ';
            std::cout.flush();
        }
        catch (NullPageReadException& nr) {
            std::cout << "error ";
            std::cout.flush();
        }
        catch (PageFaultException& pf) {
            std::cout << "pf ";
            std::cout.flush();
        }
    }
}

std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}