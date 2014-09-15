//
//  CmdUI.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "CmdUI.h"

#include <iostream>
#include <string>
#include "CmdMgr.h"

void CmdUI::setWillAcceptCommand(bool will) {
	this->willAcceptCommand = will;
}

void CmdUI::conectCmdMgr(CmdMgr *cmdMgr) {
	this->cmdMgr = cmdMgr;
}

void CmdUI::acceptCmds() {
	std::string cmd;
	while (willAcceptCommand && std::getline(std::cin, cmd)) {
		cmdMgr->execute(cmd);
	}
}

void CmdUI::echo(std::string str) {
	std::cout << str << std::endl;
}