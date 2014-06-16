#ifndef INSTANCE
#define INSTANCE

#include "definition.hpp"
#include "class.hpp"
path

class Instance {
	public:
	void *class_index;
	u2 field_count;
	void **field_index;
	u1 *bytes;
};

#endif

