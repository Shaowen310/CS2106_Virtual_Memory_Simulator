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
#include "CmdReceiver.h"

void Command::execute() { }

CmdCreateProc::CmdCreateProc(std::vector<std::string>& args, CmdReceiver* cmdRecv) : Command(cmdRecv){
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
}

void CmdCreateProc::execute() {
	cmdRecv->createProc(pID, procPriority);
}

CmdTimeOut::CmdTimeOut(CmdReceiver* cmdRecv) : Command(cmdRecv){}

void CmdTimeOut::execute() {
	cmdRecv->timeOut();
}

CmdDeleteProc::CmdDeleteProc(std::vector<std::string>& args, CmdReceiver* cmdRecv) : Command(cmdRecv){
	if (args.size() != 1) {
		throw InvalidCmdArgException();
	}
	pID = args[0];
}

void CmdDeleteProc::execute() {
	cmdRecv->destroyProc(pID);
}

CmdRequestRes::CmdRequestRes(std::vector<std::string>& args, CmdReceiver* cmdRecv) : Command(cmdRecv){
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
}

void CmdRequestRes::execute() {
	cmdRecv->requestRes(rID, reqNum);
}

CmdReleaseRes::CmdReleaseRes(std::vector<std::string>& args, CmdReceiver* cmdRecv) : Command(cmdRecv){
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
}

void CmdReleaseRes::execute() {
	cmdRecv->releaseRes(rID, relNum);
}

CmdInit::CmdInit(CmdReceiver* cmdRecv) : Command(cmdRecv){}

void CmdInit::execute() {
	cmdRecv->initRuntime();
}

CmdDeleteRuntime::CmdDeleteRuntime(CmdReceiver* cmdRecv) : Command(cmdRecv) {}

void CmdDeleteRuntime::execute() {
    cmdRecv->deleteRuntime();
}