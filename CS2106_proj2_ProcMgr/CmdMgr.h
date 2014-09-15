//
//  CmdMgr.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_CmdMgr_h
#define CS2106_proj2_ProcMgr_CmdMgr_h

#include <string>
#include "CmdUI.h"
#include "Cmds.h"
#include "Runtime.h"

class CmdUI;

// This is the main controller
class CmdMgr{
private:
	bool notInitialized = true;
	Runtime runtime;
	CmdUI* cmdUI;
    
	Command* createCmd(std::string cmdText);
public:
	void connectCmdUI(CmdUI* cmdUI);
	void execute(std::string cmdText);
};

#endif
