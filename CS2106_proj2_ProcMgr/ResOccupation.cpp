//
//  ResOccupation.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "ResOccupation.h"

ResOccupation::ResOccupation(std::string rID, int numUnits, ResCtrlBlk* rcb) {
	this->rID = rID;
	this->numUnits = numUnits;
	this->rcb = rcb;
}