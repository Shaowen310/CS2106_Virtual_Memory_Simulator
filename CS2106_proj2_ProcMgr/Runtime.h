//
//  Runtime.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_Runtime_h
#define CS2106_proj2_ProcMgr_Runtime_h

#include <string>
#include <vector>
#include <list>
#include "ProcCtrlBlk.h"
#include "ResCtrlBlk.h"

class Runtime{
private:
	ProcCtrlBlk* init = NULL;
	ProcCtrlBlk* running = NULL;
	std::vector<std::list<ProcCtrlBlk*> > readyList;
	std::vector<ResCtrlBlk> resources;
    
	void initResList();
	ResCtrlBlk* getRcb(std::string rID);
	void schedule();
public:
	~Runtime();
	
	void initialize();
	void create(std::string pID, ProcPriority priority);
	void destroy(std::string pID);
	void request(std::string rID, int numUnits);
	void release(std::string rID, int numUnits);
	void timeOut();
	
	std::string getRunningProcID();
};

#endif
