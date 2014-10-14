//
//  MemExceptions.h
//  CS2106_proj_VM
//
//  Created by Zsw on 14/10/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef __CS2106_proj_VM__MemExceptions__
#define __CS2106_proj_VM__MemExceptions__

#include <exception>
class AddrOutOfBoundException: public std::exception {
    
};
class InvalidReadException: public std::exception {
    
};
class PageNoOutOfBoundException: public std::exception {
    
};
class OccupyAlreadyOccupiedBitException: public std::exception {
    
};
class InsufficientMemoryException: public std::exception {
    
};

#endif /* defined(__CS2106_proj_VM__MemExceptions__) */
