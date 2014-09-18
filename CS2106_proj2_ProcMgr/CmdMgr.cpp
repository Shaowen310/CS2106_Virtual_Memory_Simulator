//
//  CmdMgr.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "CmdMgr.h"

#include <string>
#include <sstream>
#include <vector>
#include "Cmds.h"
#include "ProcResMgrExceptions.h"

void CmdMgr::connectCmdUI(CmdUI *cmdUI) {
	this->cmdUI = cmdUI;
}

void CmdMgr::execute(std::string cmdText) {
	Command* cmd = NULL;
	try {
		cmd = createCmd(cmdText);
	}
    catch (std::exception& e) {
        delete cmd;
        cmdUI->echo("error");
        return;
    }
//	catch (InvalidCmdTypeException& eCmdType) {
//		delete cmd;
//		cmdUI->echo(eCmdType.what());
//		return;
//	}
//	catch (InvalidCmdArgException& eCmdArg) {
//		delete cmd;
//		cmdUI->echo(eCmdArg.what());
//		return;
//	}
	
	try {
		cmd->execute();
	}
    catch (DeleteInitException& eDelInit) {
		delete cmd;
		cmdUI->echo("Delete init process, poweroff.");
		cmdUI->setWillAcceptCommand(false);
		return;
	}
    catch (std::exception& e) {
        delete cmd;
        cmdUI->echo("error");
        return;
    }
//	catch (ProcIDCollisionException& ePIDCol) {
//		delete cmd;
//		cmdUI->echo(ePIDCol.what());
//		return;
//	}
//	catch (ProcNotFoundException& eProcNotFound) {
//		delete cmd;
//		cmdUI->echo(eProcNotFound.what());
//		return;
//	}
//	catch (ResNotFoundException& eResNotFound) {
//		delete cmd;
//		cmdUI->echo(eResNotFound.what());
//		return;
//	}
//	catch (ReqExceedsResCapException& eReqMore) {
//		delete cmd;
//		cmdUI->echo(eReqMore.what());
//		return;
//	}
//	catch (RelResExceedsOccuException& eRelMore) {
//		delete cmd;
//		cmdUI->echo(eRelMore.what());
//		return;
//	}
	
	delete cmd;
    
	cmdUI->echo(runtime.getRunningProcID());
}

Command* CmdMgr::createCmd(std::string cmdText) {
	std::string cmdType, buf;
	std::stringstream ss(cmdText);
	std::vector<std::string> cmdArgs;
    
	ss >> cmdType;
    
	while (ss >> buf) {
		cmdArgs.push_back(buf);
	}
    
	if (notInitialized) {
		if (!cmdType.compare("init")) {
			notInitialized = false;
			return new CmdInit(&runtime);
		}
		else {
			throw InvalidCmdTypeException();
		}
	}
    
	if (!cmdType.compare("cr")) {
		return new CmdCreateProc(cmdArgs, &runtime);
	}
	else if (!cmdType.compare("to")) {
		return new CmdTimeOut(&runtime);
	}
	else if (!cmdType.compare("de")) {
		return new CmdDeleteProc(cmdArgs, &runtime);
	}
	else if (!cmdType.compare("req")) {
		return new CmdRequestRes(cmdArgs, &runtime);
	}
	else if (!cmdType.compare("rel")) {
		return new CmdReleaseRes(cmdArgs, &runtime);
	}
	else {
		throw InvalidCmdTypeException();
	}
}
