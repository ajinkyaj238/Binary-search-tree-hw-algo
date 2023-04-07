//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file PrecondViolatedExcep.h */

#ifndef TREEEXCEPTIONS_H
#define TREEEXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcep : public logic_error
{
public:
   PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep 

class NotFoundException : public logic_error
{
public:
   NotFoundException(const string& message = "");
}; // end NotFoundException 

#include "TreeExceptions.cpp"

#endif