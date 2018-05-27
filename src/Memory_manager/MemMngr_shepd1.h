#pragma once

#include <cstdlib>
#include <iostream>
#include <inttypes.h>

enum AllocationType {
	Single,
	Array
};

enum Deallocation
{
	Deallocated,
	NotDeallocated,
	TypeMismatch
};

struct Allocation {
	Allocation* next;
	uint32_t number;
	size_t size;
	uint64_t address;
	AllocationType type;
	Deallocation deallocation;
};
