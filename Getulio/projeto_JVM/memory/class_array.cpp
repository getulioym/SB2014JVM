#include "class_array.hpp"

ClassArray::ClassArray(int s) {
	size = s;
	classes = new Class[size];
}

Class *ClassArray::get_classref(u1 *name) {
	Class *temp = NULL;
	int index = get_index(name);
	
	if(index > -1)
		temp = &(classes[index]);
	return temp;
}

int ClassArray::get_index(u1 *name) {
	int index = -1;
	for(int i=0; i<size; i++) {
		if(strcmp((char *)name, (char *)classes[i].get_class_name()) == 0) {
			i = index;
			break;
		}
	}
	return index;
}
