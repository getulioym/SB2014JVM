#include "class_array.hpp"

ClassArray::ClassArray(int m) {
	max  = m;
	size = 0;
	classes = new Class *[max];
	for(int i=0;i<max;i++)
		classes[i] = NULL;
	for(int i=0;i<max;i++)
		printf("%p\n",classes[i]);
}

Class *ClassArray::new_class(u1 *name) {
	Class *temp;
	classes[size] = loader.load_class(name);
	temp = classes[size];
	size++;
	return temp;
}

Class *ClassArray::get_classref(u1 *name) {
	Class *temp = NULL;
	int index = get_index(name);
	
	if(index > -1) {
		temp = classes[index];
	} else {
		temp = new_class(name);
	}
	return temp;
}

int ClassArray::get_index(u1 *name) {
	int index = -1;
	for(int i=0; i<size; i++) {
		if(strcmp((char *)name, (char *)classes[i]->get_class_name()) == 0) {
			i = index;
			break;
		}
	}
	return index;
}

