//
//  ResOccupation.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_ResOccupation_h
#define CS2106_proj2_ProcMgr_ResOccupation_h

#include <string>
#include "ResCtrlBlk.h"

class ResCtrlBlk;

class ResOccupation{
private:
	std::string rID;
	int numUnits;
	ResCtrlBlk* rcb;
public:
	ResOccupation(std::string rID, int numUnits, ResCtrlBlk* rcb);
    
	std::string getRID() { return this->rID; }
	int getNumUnits() { return this->numUnits; }
	void setNumUnits(int newNumUnits) { this->numUnits = newNumUnits; }
	ResCtrlBlk* getRCB() { return this->rcb; }
};

#endif
