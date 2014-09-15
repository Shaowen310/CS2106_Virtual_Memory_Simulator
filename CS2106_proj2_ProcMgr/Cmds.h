//
//  Cmds.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_Cmds_h
#define CS2106_proj2_ProcMgr_Cmds_h

#include <vector>
#include <string>
#include "ProcCtrlBlk.h"
#include "Runtime.h"

class Command {
public:
	virtual void execute();
};

class CmdCreateProc : public Command {
private:
	std::string pID;
	ProcPriority procPriority;
	Runtime* runtime;
    
public:
	CmdCreateProc(std::vector<std::string>& args, Runtime* runtime);
	void execute();
};

class CmdTimeOut : public Command {
private:
	Runtime* runtime;
public:
	CmdTimeOut(Runtime* runtime);
	void execute();
};

class CmdDeleteProc : public Command {
private:
	std::string pID;
	Runtime* runtime;
public:
	CmdDeleteProc(std::vector<std::string>& args, Runtime* runtime);
	void execute();
};

class CmdRequestRes : public Command {
private:
	std::string rID;
	int reqNum;
	Runtime* runtime;
public:
	CmdRequestRes(std::vector<std::string>& args, Runtime* runtime);
	void execute();
};

class CmdReleaseRes : public Command {
private:
	std::string rID;
	int relNum;
	Runtime* runtime;
public:
	CmdReleaseRes(std::vector<std::string>& args, Runtime* runtime);
	void execute();
};

class CmdInit : public Command {
private:
	Runtime* runtime;
public:
	CmdInit(Runtime* runtime);
	void execute();
};

#endif
