//
//  ResCtrlBlk.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_ResCtrlBlk_h
#define CS2106_proj2_ProcMgr_ResCtrlBlk_h

#include <string>
#include <list>
#include "ProcCtrlBlk.h"

class ProcCtrlBlk;

class ResCtrlBlk {
private:
	// identifier
	std::string rID;
	// capacity
	int maxUnits;
	// status
	int numFreeUnits;
	// waiting list
	std::list<ProcCtrlBlk*> procWaitingList;
public:
	ResCtrlBlk(std::string rID, int capacity);
    
	std::string getRID() { return this->rID; }
	std::list<ProcCtrlBlk*>& getProcWaitingList() { return this->procWaitingList; }
    
	bool hasEnoughUnits(int necessaryUnits) { return necessaryUnits <= this->maxUnits; }
	bool hasEnoughFreeUnits(int numUnits) { return numUnits <= this->numFreeUnits; }
	void alloc(int numUnits) { this->numFreeUnits -= numUnits; }
	void release(int numUnits);
};

#endif
