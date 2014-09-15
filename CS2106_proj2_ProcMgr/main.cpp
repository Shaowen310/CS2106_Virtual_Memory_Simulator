//
//  main.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "CmdUI.h"
#include "CmdMgr.h"

int main() {
	CmdMgr* cmdMgr = new CmdMgr();
	CmdUI* cmdUI = new CmdUI();
    
	cmdMgr->connectCmdUI(cmdUI);
	cmdUI->conectCmdMgr(cmdMgr);
    
	cmdUI->setWillAcceptCommand(true);
	cmdUI->acceptCmds();
    
	delete cmdMgr;
	delete cmdUI;
    
	return 0;
}
