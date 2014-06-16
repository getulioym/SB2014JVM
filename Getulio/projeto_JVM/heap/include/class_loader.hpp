#ifndef CLASS_LOADER
#define CLASS_LOADER

#include <iostream>
#include <string.h>

#include "class.hpp"

class ClassLoader {
public:
	Class *temp;
	
	Class *new_class(u1 *);
	field_info *field_loader(FILE *, u2);
	method_info *method_loader(FILE *, u2);
	attribute_info *attribute_loader(FILE *, u2);
};

#endif

