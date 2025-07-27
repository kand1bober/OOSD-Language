#include <stdint.h>

#include "../../proc_project/enum.h"
#include "../../proc_project/decoration.h"

#ifndef PROC_LIBRARY_HEADER
#define PROC_LIBRARY_HEADER

typedef double ProcElem;

const uint32_t SIGNATURE = 0x56564b;
const uint32_t VERSION = 2;

const uint64_t RAM_POISON = 0xBADBABA;


#endif