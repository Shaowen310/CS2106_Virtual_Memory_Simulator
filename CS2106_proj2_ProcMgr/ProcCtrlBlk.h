//
//  ProcCtrlBlk.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_ProcCtrlBlk_h
#define CS2106_proj2_ProcMgr_ProcCtrlBlk_h

#include <string>
#include <list>
#include <vector>
#include "ResCtrlBlk.h"
#include "ResOccupation.h"

#define MAX_PROC_PRIOR 2

class ResCtrlBlk;
class ResOccupation;

enum ProcStatus { READY, RUNNING, BLOCKED };

enum ProcPriority { INIT, USER, SYSTEM};

class ProcCtrlBlk {
private:
	// identifier
	std::string pID;
    
	// processors
    
	// resources
	std::list<ResOccupation> resList;
    
	// status
	ProcStatus procStatus;
	std::list<ProcCtrlBlk*>* statusList = NULL;
    
	// creation tree
	ProcCtrlBlk* parent = NULL;
	std::list<ProcCtrlBlk*> childList;
    
	// priority
	ProcPriority priority;
    
	// ready list
	std::vector<std::list<ProcCtrlBlk*> >* readyList;
	
	void releaseAllOccupiedRes();
	void OccupyAllRes();
	void killProcTree(ProcCtrlBlk* pcbRoot);
	void removeFromList(std::list<ProcCtrlBlk*>* list, std::string pID);
public:
	ProcCtrlBlk(std::string pID, ProcPriority priority, ProcCtrlBlk* parent,
                ProcStatus procStatus, std::list<ProcCtrlBlk*>* procStatusList,
                std::vector<std::list<ProcCtrlBlk*> >* readyList);
	~ProcCtrlBlk();
	
	ResOccupation* getRoc(std::string rID);
    
	bool requestRes(std::string rID, int numUnits, ResCtrlBlk* rcb);
	void releaseRes(std::string rID, int numUnits);
	bool unBlock();
	void destroyChild(std::string pID);
	void timeOut();
    
	static ProcCtrlBlk* findPcb(ProcCtrlBlk* pcbRoot, std::string pID);
    
	std::string getPID() { return this->pID; }
	ProcPriority getPriority() { return this->priority; }
	ProcStatus getStatus() { return this->procStatus; }
	void setStatus(ProcStatus newStatus) { this->procStatus = newStatus; }
	std::list<ProcCtrlBlk*>& getChildList() { return this->childList; }
	ProcCtrlBlk* getParent() { return this->parent; }
};

#endif
