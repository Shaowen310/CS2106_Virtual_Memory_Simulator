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
#include "CmdReceiver.h"

class Command {
protected:
    CmdReceiver* cmdRecv;
public:
    Command(CmdReceiver* cmdRecv) { this->cmdRecv = cmdRecv; }
	virtual void execute();
};

class CmdCreateProc : public Command {
private:
	std::string pID;
	ProcPriority procPriority;
public:
    CmdCreateProc(std::vector<std::string>& args, CmdReceiver* cmdRecv);
	void execute();
};

class CmdTimeOut : public Command {
public:
	CmdTimeOut(CmdReceiver* cmdRecv);
	void execute();
};

class CmdDeleteProc : public Command {
private:
	std::string pID;
public:
	CmdDeleteProc(std::vector<std::string>& args, CmdReceiver* cmdRecv);
	void execute();
};

class CmdRequestRes : public Command {
private:
	std::string rID;
	int reqNum;
public:
	CmdRequestRes(std::vector<std::string>& args, CmdReceiver* cmdRecv);
	void execute();
};

class CmdReleaseRes : public Command {
private:
	std::string rID;
	int relNum;
public:
	CmdReleaseRes(std::vector<std::string>& args, CmdReceiver* cmdRecv);
	void execute();
};

class CmdInit : public Command {
public:
	CmdInit(CmdReceiver* cmdRecv);
	void execute();
};

class CmdDeleteRuntime : public Command {
public:
    CmdDeleteRuntime(CmdReceiver* cmdRecv);
    void execute();
};

#endif
