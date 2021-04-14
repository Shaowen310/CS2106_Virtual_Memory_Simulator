//
//  MemArgs.h
//  CS2106_proj_VM
//
//  Created by Zsw on 12/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj_VM_MemArgs_h
#define CS2106_proj_VM_MemArgs_h

// Please make sure that FRAME_LENGTH is greater than or equals to 5 for bit map functionality
// Please make sure that PAGE_TABLE_LENGTH is greater than or equals to PAGE_LENGTH for full use of memory
// Please make sure that SEGMENT_TABLE_LENGTH is greater than or equals to PAGE_LENGTH for full use of memory
// It is recommended that SEGMENT_TABLE_LENGTH is much smaller than sizeof(int)*8
// Please make sure that PAGE_LENGTH + FRAME_LENGTH is strictly less than sizeof(int)*8 for physical memory accecibility
//  If PAGE_LENGTH = 9, and FRAME_LENGTH = 10, then the program cannot run on 16-bit machine
// It is assumed that PAGE_TABLE_LENGTH equals to the FRAME_LENGTH
#define PAGE_LENGTH 9
#define FRAME_LENGTH 10
#define PAGE_TABLE_LENGTH 10
#define SEGMENT_TABLE_LENGTH 9

#define SEGMENT_TABLE_START_ADDR 0

#define PAGE_NOT_IN_MEMORY -1
#define PAGE_NOT_EXIST 0

#endif
