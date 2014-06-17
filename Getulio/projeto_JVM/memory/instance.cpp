#include "instance.hpp"

Instance::Instance(Class *ref) {
	u2 size;
	classref = ref;
	fields_table = new field_index[classref->fields_count];
	fields_count = classref->fields_count - classref->static_fields_count;
	
	size = make_fields_table();
	
#define TEST_NONSTATIC
#ifdef TEST_NONSTATIC
	printf("fields: %d\n",classref->fields_count);
	printf("non statics: %d size [%d]\n",fields_count ,size);
	for(u2 i=0; i<classref->fields_count; i++) {
		printf("[%d] %c | %d\n",i, fields_table[i].type,(short)fields_table[i].index);
	}
	printf("\n");
#endif

	fields = new u4[size];
}

u2 Instance::make_fields_table() {
	u2 size = 0;
	
	for(u2 i=0; i<classref->fields_count; i++) {
		fields_table[i] = classref->static_fields_table[i];
		if (fields_table[i].index == (u2) -1) {
			fields_table[i].index = size++;
			if( (fields_table[i].type == TYPE_LONG) || 
				(fields_table[i].type == TYPE_DOUBLE) )
				size++;
		} else {
			fields_table[i].index = (u2) -1;
		}
	}
	return size;
}
