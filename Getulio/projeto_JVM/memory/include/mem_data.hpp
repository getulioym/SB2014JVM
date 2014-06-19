#ifndef MEMORY_DATA
#define MEMORY_DATA

#include <stdio.h>
#include <stdlib.h>

#include "definition.hpp"
#include "class.hpp"

class MemoryData {
public:
	u4 type;
	Class *classref;
	u4 data_count;
	u4 *data_index;
	u1 *data_type;
	u4	data_length;
	u4 *data;
	
	void put_data(u2, u1, u4 *);
	void get_data(u2, u1, u4 *);
	void make_fields();
	u2 make_fields_index();
	void print();
};

#endif

