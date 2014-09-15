//
//  Runtime.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "Runtime.h"

#include <string>
#include "ResCtrlBlk.h"
#include "ProcResMgrExceptions.h"

void Runtime::initResList() {
	for (int i = 1; i <= 4; i++) {
		std::string rID = "R";
		rID.append(std::to_string(i));
		ResCtrlBlk rcb(rID,i);
		resources.push_back(rcb);
	}
}

ResCtrlBlk* Runtime::getRcb(std::string rID) {
	for (std::vector<ResCtrlBlk>::iterator it = resources.begin(); it != resources.end(); it++) {
		if (!(*it).getRID().compare(rID)) {
			return &(*it);
		}
	}
	return NULL;
}

Runtime::~Runtime() {
	delete init;
}

void Runtime::initialize() {
	// initialize ready list
	readyList.resize(MAX_PROC_PRIOR + 1);
    
	// initialize resource list
	initResList();
    
	// initialize init process
	init = new ProcCtrlBlk("init",ProcPriority::INIT,NULL,ProcStatus::READY,&readyList[ProcPriority::INIT],&readyList);
	
	schedule();
}

void Runtime::create(std::string pID, ProcPriority priority) {
	// check pID
	if (ProcCtrlBlk::findPcb(init, pID) != NULL) {
		throw ProcIDCollisionException();
	}
    
	ProcCtrlBlk* newProc = new ProcCtrlBlk(pID,priority,running,ProcStatus::READY,&readyList[priority],&readyList);
    
	running->getChildList().push_back(newProc);
    
	// schedule
	schedule();
}

void Runtime::request(std::string rID, int numUnits) {
	ResCtrlBlk* rcb = getRcb(rID);
    
	if (rcb == NULL) {
		throw ResNotFoundException();
	}
    
	running->requestRes(rID, numUnits, rcb);
    
	schedule();
}

void Runtime::release(std::string rID, int numUnits) {
	running->releaseRes(rID, numUnits);
	schedule();
}

void Runtime::destroy(std::string pID) {
	// search for the process
	ProcCtrlBlk* targetProc = ProcCtrlBlk::findPcb(running, pID);
    
	// need to check destroy must be triggered by its ancestors or itself
	if (targetProc == NULL) {
		throw ProcNotFoundException();
	}
    
	if (init == targetProc) {
		throw DeleteInitException();
	}
    
	if (running == targetProc) {
		running = NULL;
	}
    
	// delete child from parent
	ProcCtrlBlk* targetProcParent = targetProc->getParent();
	targetProcParent->destroyChild(pID);
    
	schedule();
}

void Runtime::timeOut() {
	running->timeOut();
    
	schedule();
}

void Runtime::schedule() {
	ProcCtrlBlk* highestPriProc = NULL;
	for (int i = MAX_PROC_PRIOR; i >= 0; i--) {
		if (!readyList[i].empty()) {
			highestPriProc = readyList[i].front();
			break;
		}
	}
	if (highestPriProc == NULL) {
		// There is no process in the ready list, error
		throw NoProcReadyException();
	}
	if (running == NULL ||
		running->getPriority() < highestPriProc->getPriority() ||
		running->getStatus() != ProcStatus::RUNNING
		) {
		// preempt
		if (running != NULL) {
			if (running->getStatus() == ProcStatus::RUNNING) {
				running->setStatus(ProcStatus::READY);
			}
		}
		highestPriProc->setStatus(ProcStatus::RUNNING);
		running = highestPriProc;
	}
}

std::string Runtime::getRunningProcID() {
	if (running != NULL) {
		return running->getPID();
	}
	else {
		return "No running process.";
	}
}