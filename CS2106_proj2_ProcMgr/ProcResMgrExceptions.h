//
//  ProcResMgrExceptions.h
//  CS2106_proj2_ProcMgr
//
//  Created by Zsw on 15/9/14.
//  Copyright (c) 2014 Zsw. All rights reserved.
//

#ifndef CS2106_proj2_ProcMgr_ProcResMgrExceptions_h
#define CS2106_proj2_ProcMgr_ProcResMgrExceptions_h

#include <exception>

class InvalidCmdTypeException : public std::exception {
public:
	const char* what() const throw();
};

class InvalidCmdArgException : public std::exception {
public:
	const char* what() const throw();
};

class ProcIDCollisionException : public std::exception {
public:
	const char* what() const throw();
};

class ProcNotFoundException : public std::exception {
public:
	const char* what() const throw();
};

class ResNotFoundException : public std::exception {
public:
	const char* what() const throw();
};

class NoProcReadyException : public std::exception {
public:
	const char* what() const throw();
};

class DeleteInitException : public std::exception {};

class ReqExceedsResCapException : public std::exception{
public:
	const char* what() const throw();
};

class RelResExceedsOccuException : public std::exception{
public:
	const char* what() const throw();
};

#endif
