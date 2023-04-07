#include "TreeExceptions.h"
#include <stdexcept>
/**
	Exception class implementations
*/

// Constructor
PrecondViolatedExcep::PrecondViolatedExcep(const string& message) : logic_error("Precondition Violated Exception: " + message){}  // end constructor

// Constructor
NotFoundException::NotFoundException(const string& message) : logic_error("Precondition Violated Exception: " + message){}  // end constructor


