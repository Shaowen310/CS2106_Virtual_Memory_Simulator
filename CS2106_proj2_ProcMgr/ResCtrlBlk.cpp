//
//  ResCtrlBlk.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "ResCtrlBlk.h"

#include <string>

ResCtrlBlk::ResCtrlBlk(std::string rID, int capacity) {
	this->rID = rID;
	this->maxUnits = capacity;
	this->numFreeUnits = capacity;
}

void ResCtrlBlk::release(int numUnits) {
	this->numFreeUnits += numUnits;
    
	// examine the waiting list
	std::list<ProcCtrlBlk*>::iterator itPcb = this->procWaitingList.begin();
	for (int i = 0; i < (int)this->procWaitingList.size(); i++) {
		ResOccupation* roc = (*itPcb)->getRoc(this->rID);
		if (hasEnoughFreeUnits(roc->getBlockNum())) {
			itPcb++;
			ProcCtrlBlk* examinePcb = this->procWaitingList.front();
			this->procWaitingList.pop_front();
            
            // alloc res
            this->alloc(roc->getBlockNum());
            roc->setBlockNum(0);
            
			examinePcb->unBlock();
		}
		// still blocked
		else { break; }
	}
}