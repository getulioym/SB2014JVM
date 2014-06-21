#include "class_array.hpp"

u4 make_field_index(Class *);
	
ClassArray::ClassArray(int m) {
	max  = m;
	size = 0;
	classes = new Class *[max];
	classes = (Class **)calloc(max,sizeof(Class *));
}

Class *ClassArray::new_class(u1 *name) {
	Class *temp;
	temp = loader.load_class(name);

	temp->static_fields_index = new int[temp->fields_count];
	temp->static_fields_count = 0;
	
	temp->static_fields_length = make_field_index(temp);
	temp->static_fields = (u4 *) calloc(temp->static_fields_length, sizeof(u4));
	
	classes[size] = temp;
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
		if(strcmp((char *)name, (char *)classes[i]->get_cp_this_class()) == 0) {
			i = index;
			break;
		}
	}
	return index;
}

u4 make_field_index(Class *c) {
	u4 length = 0;
	
	for(int i=0; i<c->fields_count; i++) {
		u1 type = *( c->get_field_type(i) );
		if( isStatic(c->fields[i].access_flags) ) {
			c->static_fields_count++;
			c->static_fields_index[i] = length;
			length++;
			if( (type == TYPE_LONG) || (type == TYPE_DOUBLE) )
				length++;
		} else {
			c->static_fields_index[i] = -1;
		}
	}
	return length;
}

