#include "mem_data_array.hpp"

MemoryDataArray::MemoryDataArray(int m) {
	max  = m;
	size = 0;
	data = new MemoryData *[max];
	for(int i=0;i<max;i++)
		data[i] = NULL;
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
	m->make_fields();
	
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
	m->classref = NULL;
	
	
	m->data_count = a_size[0];
	m->data_index = new u4[ a_size[0] ];
	m->data_type = new u1[ a_size[0] ];
	
	int inc;
	if( (a_type[0] != TYPE_LONG) || (a_type[0] != TYPE_DOUBLE) ) {
		inc = 0;
		m->data_length = m->data_count;
	} else {
		inc = 1;
		m->data_length = m->data_count * 2;
	}
	
	for(u4 i=0; i<m->data_count; i++) {
		m->data_index[i] = i + inc;
		m->data_type[i] = a_type[1];	
	}
	
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

void MemoryDataArray::putfield(u4 instance, u2 cp_index, u1 in_type, u4 *data) {
	MemoryData *temp = (MemoryData *)instance;
	u2 index = temp->classref->get_field_index(cp_index);
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
	u2 index = temp->classref->get_field_index(cp_index);
	u1 type = *temp->classref->get_field_type(index);

	temp->get_data(index, type, data);
	return type;
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

