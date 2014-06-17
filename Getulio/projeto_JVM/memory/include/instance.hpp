#ifndef INSTANCE
#define INSTANCE

#include "definition.hpp"
#include "class.hpp"

class Instance {
public:
	Class *classref;
	u4 fields_count;
	field_index *fields_table;
	u4 *fields;
	
	Instance(Class *);
	u2 make_fields_table();
};

#endif

