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
#include <typeinfo>
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
        cmdUI->echo("error ");
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
	
    if (cmd == NULL) {
        cmdUI->setWillAcceptCommand(false);
        return;
    }
    
	try {
		cmd->execute();
	}
    catch (std::exception& e) {
        delete cmd;
        cmdUI->echo("error ");
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
    
    if (cmdRecv.isRuntimeInitialized()) {
        cmdUI->echo(cmdRecv.getRunningPid() + ' ');
    }
}

Command* CmdMgr::createCmd(std::string cmdText) {
	std::string cmdType, buf;
	std::stringstream ss(cmdText);
	std::vector<std::string> cmdArgs;
    
	ss >> cmdType;
    
	while (ss >> buf) {
		cmdArgs.push_back(buf);
	}
    
    if (!cmdType.compare("quit")) {
        return NULL;
    }
    
    if (cmdRecv.isRuntimeInitialized()) {
        if (cmdType.empty()) {
            cmdUI->echo("\n");
            return new CmdDeleteRuntime(&cmdRecv);
        }
        else if (!cmdType.compare("cr")) {
            return new CmdCreateProc(cmdArgs, &cmdRecv);
        }
        else if (!cmdType.compare("to")) {
            return new CmdTimeOut(&cmdRecv);
        }
        else if (!cmdType.compare("de")) {
            return new CmdDeleteProc(cmdArgs, &cmdRecv);
        }
        else if (!cmdType.compare("req")) {
            return new CmdRequestRes(cmdArgs, &cmdRecv);
        }
        else if (!cmdType.compare("rel")) {
            return new CmdReleaseRes(cmdArgs, &cmdRecv);
        }
        else {
            throw InvalidCmdTypeException();
        }
    } else {
        if (!cmdType.compare("init")) {
            return new CmdInit(&cmdRecv);
        } else {
            throw InvalidCmdTypeException();
        }
    }
}
