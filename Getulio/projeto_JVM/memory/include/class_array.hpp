#ifndef CLASS_ARRAY
#define CLASS_ARRAY

#include <stdio.h>
#include <string.h>

#include "class.hpp"
#include "class_loader.hpp"


class ClassArray {
public:
	int max;
	int size;
	Class **classes;
	ClassLoader loader;

	ClassArray(int);
	Class *new_class(u1 *);
	Class *get_classref(u1 *);
	int get_index(u1 *);
};

#endif
