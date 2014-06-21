#include "mem_data_array.hpp"

u4 make_fields_index(MemoryData *);
u4 make_array_index(MemoryData *);
	

MemoryDataArray::MemoryDataArray(int m) {
	max  = m;
	size = 0;
	data = new MemoryData *[max];
	for(int i=0;i<max;i++)
		data[i] = NULL;
}

void MemoryDataArray::putfield(u4 instance, u2 cp_index, u4 *data, u1 in_type) {
	MemoryData *temp = (MemoryData *)instance;
	int index = temp->classref->get_field_index(cp_index);
	u1 type = *temp->classref->get_field_type(index);
	
	if(in_type != type) {
		printf("Error type %c != %c: mem_data_array\n", type, in_type);
		exit(0);
	}
	temp->put_data(index, type, data);

//#define TEST_PUTFIELD
#ifdef TEST_PUTFIELD
	printf("TEST_PUTFIELD\n")
	printf("addr %p, value %08X\n",temp, instance);
	printf("field index %d\n",index);
	printf("field type %c\n",type);
#endif

}

u1 MemoryDataArray::getfield(u4 instance, u2 cp_index, u4 *data) {
	MemoryData *temp = (MemoryData *)instance;
	int index = temp->classref->get_field_index(cp_index);
	u1 type = *temp->classref->get_field_type(index);

	temp->get_data(index, type, data);
	return type;
}

u4 MemoryDataArray::new_instance(Class *ref) {
	MemoryData *m ;
	
	if( ref->magic != 0xCAFEBABE )  {
		printf("Error invalid class format: mem_data_array.new_instance\n");
		exit(0);
	}
	m = new MemoryData;
	data[size] = m;
	size++;
	
	m->type = TYPE_CLASS;
	m->classref = ref;
	
	m->data_index = new int[ref->fields_count];
	m->data_count = (ref->fields_count) - (ref->static_fields_count);
	
	m->data_length = make_fields_index(m);
	m->data = (u4 *) calloc(m->data_length, sizeof(u4));

	
//#define TEST_NEW_INSTANCE
#ifdef TEST_NEW_INSTANCE
	printf("TEST_NEW_INSTANCE: mem_data_array\n");
	printf("instance addr %p\n", m);
#endif

	return (u4)m;
}

u4 MemoryDataArray::new_array(u4 *a_size, u1 *a_type, Class *ref) {
	MemoryData *m ;
	
	if(a_type[0] != TYPE_ARRAY) {
		printf("Error not array type %c: mem_data_array.new_array",a_type[0]);
		exit(0);
	}
	m = new MemoryData;
	data[size] = m;
	size++;
	
	m->type = TYPE_ARRAY;
	m->data_type = a_type[1];
	
	m->data_index = new int[ a_size[0] ];
	m->data_count = a_size[0];
	
	m->data_length = make_array_index(m);
	m->data = new u4[m->data_length];
	
	if(a_type[1] == TYPE_CLASS) {
		if(ref == NULL) {
			printf("Error class ref null: mem_data_array.new_array\n");
			exit(0);
		}
		for(u4 i=0; i<m->data_count; i++) {
			m->data[i] = new_instance(ref);
		}
	}
	
//#define TEST_NEW_ARRAY
#ifdef TEST_NEW_ARRAY
	printf("TEST_NEW_ARRAY: mem_data_array\n");
	printf("instance addr %p\n", m);
	printf("count %d\n",m->data_count);
	printf("size %d type %c\n", a_size[0], a_type[1]);
	printf("\n");
#endif

	if(a_type[1] == TYPE_ARRAY) {
		for(u4 i=0;i<m->data_count; i++) {
			m->data[i] = new_array(a_size+1, a_type+1, ref);
			
#ifdef TEST_NEW_ARRAY
			printf("add get [%d] %08X",i,m->data[i]);
#endif

		}
	}
	return (u4)m;
}

void MemoryDataArray::print() {
	printf("MemoryDataArray\n");
	printf("max: %d\tsize:%d\n",max,size);
	for(int i=0; i<size; i++) {
		printf("%d.[%p]\n",i,data[i]);
		data[i]->print();
		printf("\n");
	}
}

u4 make_fields_index(MemoryData *d) {
	u4 length = 0;
	
	for(u2 i=0; i<d->classref->fields_count; i++) {
		d->data_index[i] = d->classref->static_fields_index[i];
		u1 d_type = *( d->classref->get_field_type(i) );
		if (d->data_index[i] == -1) {
			d->data_index[i] = length++;
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
				length++;
		} else {
			d->data_index[i] = -1;
		}
	}
	return length;
}

u4 make_array_index(MemoryData *d) {
	u4 length = 0;
	int inc;
	
	if( (d->data_type != TYPE_LONG) || (d->data_type != TYPE_DOUBLE) ) {
		inc = 0;
		length = d->data_count;
	} else {
		inc = 1;
		length = d->data_count * 2;
	}	
	for(u4 i=0; i<d->data_count; i++) {
		d->data_index[i] = i + inc;
	}
	return length;
}
