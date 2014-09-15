//
//  Cmds.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "Cmds.h"

#include <vector>
#include <string>
#include "Runtime.h"
#include "ProcCtrlBlk.h"
#include "ProcResMgrExceptions.h"

void Command::execute() { }

CmdCreateProc::CmdCreateProc(std::vector<std::string>& args, Runtime* runtime) {
	if (args.size() != 2) {
		throw InvalidCmdArgException();
	}
	pID = args[0];
    
	int priority;
	try {
		priority = std::stoi(args[1]);
	}
	catch (std::invalid_argument) {
		throw InvalidCmdArgException();
	}
    
	if (priority == 0) {
		procPriority = ProcPriority::INIT;
	}
	else if (priority == 1) {
		procPriority = ProcPriority::USER;
	}
	else if (priority == 2) {
		procPriority = ProcPriority::SYSTEM;
	}
	else {
		throw InvalidCmdArgException();
	}
    
	this->runtime = runtime;
}

void CmdCreateProc::execute() {
	runtime->create(pID, procPriority);
}

CmdTimeOut::CmdTimeOut(Runtime* runtime) {
	this->runtime = runtime;
}

void CmdTimeOut::execute() {
	runtime->timeOut();
}

CmdDeleteProc::CmdDeleteProc(std::vector<std::string>& args, Runtime* runtime) {
	if (args.size() != 1) {
		throw InvalidCmdArgException();
	}
	pID = args[0];
    
	this->runtime = runtime;
}

void CmdDeleteProc::execute() {
	runtime->destroy(pID);
}

CmdRequestRes::CmdRequestRes(std::vector<std::string>& args, Runtime* runtime) {
	if (args.size() != 2) {
		throw InvalidCmdArgException();
	}
	this->rID = args[0];
    
	try{
		this->reqNum = std::stoi(args[1]);
	}
	catch (std::invalid_argument) {
		throw InvalidCmdArgException();
	}
    
	if (this->reqNum < 1) {
		throw InvalidCmdArgException();
	}
    
	this->runtime = runtime;
}

void CmdRequestRes::execute() {
	runtime->request(rID, reqNum);
}

CmdReleaseRes::CmdReleaseRes(std::vector<std::string>& args, Runtime* runtime) {
	if (args.size() != 2) {
		throw InvalidCmdArgException();
	}
	this->rID = args[0];
    
	try{
		this->relNum = std::stoi(args[1]);
	}
	catch (std::invalid_argument) {
		throw InvalidCmdArgException();
	}
    
	if (this->relNum < 1) {
		throw InvalidCmdArgException();
	}
    
	this->runtime = runtime;
}

void CmdReleaseRes::execute() {
	runtime->release(rID, relNum);
}

CmdInit::CmdInit(Runtime* runtime) {
	this->runtime = runtime;
}

void CmdInit::execute() {
	runtime->initialize();
}