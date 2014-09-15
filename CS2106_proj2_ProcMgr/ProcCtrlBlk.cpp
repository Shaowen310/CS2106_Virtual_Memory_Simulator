//
//  ProcCtrlBlk.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "ProcCtrlBlk.h"

#include <list>
#include <vector>
#include <string>
#include "ProcResMgrExceptions.h"

ResOccupation* ProcCtrlBlk::getRoc(std::string rID) {
	for (std::list<ResOccupation>::iterator it = resList.begin(); it != resList.end(); it++) {
		if (!(*it).getRID().compare(rID)) {
			return &(*it);
		}
	}
	return NULL;
}

// release means examine the waiting list put the code to resource control block
void ProcCtrlBlk::releaseAllOccupiedRes() {
	for (std::list<ResOccupation>::iterator itRoc = this->resList.begin(); itRoc != this->resList.end(); itRoc++) {
		itRoc->getRCB()->release(itRoc->getNumUnits());
	}
}

void ProcCtrlBlk::OccupyAllRes() {
	for (std::list<ResOccupation>::iterator itRoc = this->resList.begin(); itRoc != this->resList.end(); itRoc++) {
		itRoc->getRCB()->alloc(itRoc->getNumUnits());
	}
}

void ProcCtrlBlk::removeFromList(std::list<ProcCtrlBlk*>* list, std::string pID) {
	for (std::list<ProcCtrlBlk*>::iterator it = list->begin(); it != list->end(); it++) {
		if (!((*it)->pID).compare(pID)) {
			list->erase(it);
			return;
		}
	}
	throw ProcNotFoundException();
}

ProcCtrlBlk::ProcCtrlBlk(std::string pID, ProcPriority priority, ProcCtrlBlk* parent,
                         ProcStatus procStatus, std::list<ProcCtrlBlk*>* procStatusList,
                         std::vector<std::list<ProcCtrlBlk*>>* readyList) {
	this->pID = pID;
	this->priority = priority;
	this->parent = parent;
	this->procStatus = procStatus;
	this->statusList = procStatusList;
	this->statusList->push_back(this);
	this->readyList = readyList;
}

ProcCtrlBlk::~ProcCtrlBlk() {
	killProcTree(this);
}

void ProcCtrlBlk::killProcTree(ProcCtrlBlk* pcbRoot) {
	while (!pcbRoot->childList.empty()) {
		ProcCtrlBlk* deletePcb = pcbRoot->childList.front();
		pcbRoot->childList.pop_front();
		delete deletePcb;
	}
    
	// release resources
	if (pcbRoot->procStatus == ProcStatus::RUNNING ||
		pcbRoot->procStatus == ProcStatus::READY) {
		for (std::list<ResOccupation>::iterator itRoc = pcbRoot->resList.begin();
             itRoc != pcbRoot->resList.end(); itRoc++) {
			(*itRoc).getRCB()->release((*itRoc).getNumUnits());
		}
	}
    
	// delete pointer on statuslist
	removeFromList(pcbRoot->statusList, pcbRoot->pID);
}

bool ProcCtrlBlk::requestRes(std::string rID, int numUnits, ResCtrlBlk* rcb) {
	ResOccupation* pRop = getRoc(rID);
	int necessaryNumUnits = numUnits;
    
	if (pRop != NULL) {
		necessaryNumUnits += pRop->getNumUnits();
	}
    
	if (!rcb->hasEnoughUnits(necessaryNumUnits)) {
		throw ReqExceedsResCapException();
	}
    
	// build new resOccupation if necessary
	if (pRop == NULL) {
		ResOccupation rop(rID,0,rcb);
		this->resList.push_back(rop);
		pRop = &this->resList.back();
	}
    
	// determine allocate res or not
	if (pRop->getRCB()->hasEnoughFreeUnits(necessaryNumUnits)) {
		// allocate
		pRop->getRCB()->alloc(numUnits);
		// occupy the res
		pRop->setNumUnits(necessaryNumUnits);
		return true;
	}
	else {
		// block
		this->procStatus = ProcStatus::BLOCKED;
		// release all already occupied resources
		releaseAllOccupiedRes();
		// occupy the res
		pRop->setNumUnits(necessaryNumUnits);
		// move from ready list to waiting list
		this->statusList->pop_front();
		pRop->getRCB()->getProcWaitingList().push_back(this);
		this->statusList = &(rcb->getProcWaitingList());
		return false;
	}
}

void ProcCtrlBlk::releaseRes(std::string rID, int numUnits) {
	// current process is running
	ResOccupation* roc = getRoc(rID);
	if (roc == NULL) {
		throw ResNotFoundException();
	}
    
	if (numUnits > roc->getNumUnits()) {
		throw RelResExceedsOccuException();
	}
    
	roc->setNumUnits(roc->getNumUnits()-numUnits);
    
	roc->getRCB()->release(numUnits);
    
	if (roc->getNumUnits() == 0) {
		// delete the roc
		for (std::list<ResOccupation>::iterator it = resList.begin(); it != resList.end(); it++) {
			if (!it->getRID().compare(rID)) {
				resList.erase(it);
				break;
			}
		}
	}
}

bool ProcCtrlBlk::unBlock() {
	// assume not blocked by other resources
	this->procStatus = ProcStatus::READY;
    
	// examine whether other resources are blocked
	for (std::list<ResOccupation>::iterator itRoc = this->resList.begin();
         itRoc != this->resList.end(); itRoc++) {
		ResCtrlBlk* examineRcb = (*itRoc).getRCB();
		if (!examineRcb->hasEnoughFreeUnits((*itRoc).getNumUnits())) {
			// block
			this->procStatus = ProcStatus::BLOCKED;
			examineRcb->getProcWaitingList().push_back(this);
			this->statusList = &(examineRcb->getProcWaitingList());
			return false;
		}
	}
    
	if (this->procStatus == ProcStatus::READY) {
		// really ready
		// occupy resources and move to ready list
		OccupyAllRes();
		readyList->at(this->priority).push_back(this);
		this->statusList = &(readyList->at(this->priority));
	}
    
	return true;
}

ProcCtrlBlk* ProcCtrlBlk::findPcb(ProcCtrlBlk* pcbRoot, std::string pID) {
	if (!pcbRoot->pID.compare(pID)) {
		return pcbRoot;
	}
	else {
		for (std::list<ProcCtrlBlk*>::iterator it = pcbRoot->childList.begin();
             it != pcbRoot->childList.end(); it++) {
			ProcCtrlBlk* temp = findPcb(*it, pID);
			if (temp != NULL) { return temp; }
		}
		return NULL;
	}
}

void ProcCtrlBlk::destroyChild(std::string pID) {
	for (std::list<ProcCtrlBlk*>::iterator it = childList.begin(); it != childList.end(); it++) {
		if (!(*it)->getPID().compare(pID)) {
			ProcCtrlBlk* deletePcb = (*it);
			childList.erase(it);
			delete deletePcb;
			return;
		}
	}
}

void ProcCtrlBlk::timeOut() {
	std::list<ProcCtrlBlk*>* pList = this->statusList;
	this->procStatus = ProcStatus::READY;
	pList->pop_front();
	pList->push_back(this);
}