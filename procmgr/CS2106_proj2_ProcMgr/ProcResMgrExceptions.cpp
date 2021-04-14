//
//  ProcResMgrExceptions.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "ProcResMgrExceptions.h"

const char* InvalidCmdTypeException::what() const throw() {
	return "Invalid command type";
}

const char* InvalidCmdArgException::what() const throw() {
	return "Invalid command argument";
}

const char* ProcIDCollisionException::what() const throw() {
	return "Process ID occupied";
}

const char* ProcNotFoundException::what() const throw() {
	return "Target process is not the running process or the child of the running process";
}

const char* ResNotFoundException::what() const throw() {
	return "Target resource is not found";
}

const char* NoProcReadyException::what() const throw() {
	return "No process ready in queue, error";
}

const char* ReqExceedsResCapException::what() const throw() {
	return "Requested more resources than its capacity";
}

const char* RelResExceedsOccuException::what() const throw() {
	return "Tried to release more resources than process actually occupies";
}

const char* RuntimeNotInitException::what() const throw() {
    return "Runtime not initialized";
}