//
//  CmdReceiver.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 19/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_CmdReceiver_h
#define CS2106_proj2_ProcMgr_CmdReceiver_h

#include <string>
#include "Runtime.h"

class CmdReceiver {
private:
    Runtime* runtime = NULL;
public:
    ~CmdReceiver() { delete runtime; }
    
    void initRuntime();
    void deleteRuntime();
    
    void createProc(std::string pID, ProcPriority priority);
    void destroyProc(std::string pID);
    void requestRes(std::string rID, int reqNum);
    void releaseRes(std::string rID, int relNum);
    void timeOut();
    
    bool isRuntimeInitialized() { return runtime != NULL; }
    
    std::string getRunningPid();
};

#endif
