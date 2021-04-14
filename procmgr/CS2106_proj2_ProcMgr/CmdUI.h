//
//  CmdUI.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_CmdUI_h
#define CS2106_proj2_ProcMgr_CmdUI_h

#include <string>
#include "CmdMgr.h"

class CmdMgr;

class CmdUI {
private:
	bool willAcceptCommand;
	CmdMgr* cmdMgr;
public:
	void setWillAcceptCommand(bool will);
	void conectCmdMgr(CmdMgr* cmdMgr);
	void acceptCmds();
	void echo(std::string str);
};

#endif
