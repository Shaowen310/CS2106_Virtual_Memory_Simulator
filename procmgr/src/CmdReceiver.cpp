//
//  CmdReceiver.cpp
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 19/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#include "CmdReceiver.h"
#include "ProcResMgrExceptions.h"

void CmdReceiver::initRuntime() {
    if (runtime == NULL) {
        runtime = new Runtime();
    }
}

void CmdReceiver::createProc(std::string pID, ProcPriority priority) {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    runtime->create(pID, priority);
}

void CmdReceiver::destroyProc(std::string pID) {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    try {
        runtime->destroy(pID);
    }
    catch (DeleteInitException& eDelInit) {
        deleteRuntime();
        return;
    }
}

void CmdReceiver::requestRes(std::string rID, int reqNum) {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    runtime->request(rID, reqNum);
}

void CmdReceiver::releaseRes(std::string rID, int relNum) {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    runtime->release(rID, relNum);
}

void CmdReceiver::timeOut() {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    runtime->timeOut();
}

std::string CmdReceiver::getRunningPid() {
    if (runtime == NULL) {
        throw RuntimeNotInitException();
    }
    return runtime->getRunningProcID();
}

void CmdReceiver::deleteRuntime() {
    delete runtime;
    runtime = NULL;
}