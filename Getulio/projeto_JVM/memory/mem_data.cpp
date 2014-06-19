#include "mem_data.hpp"

void MemoryData::put_data(u2 index, u1 type, u4 *in) {
	if(data_type[index] != type) {
		printf("Data type error %c != %c: mem_data.put_data\n",data_type[index],type);
		exit(0);
	}
	if(data_index[index] == (u2)-1) {
		printf("Index value error %d: mem_data.put_data\n" ,(short)data_index[index]);
		exit(0);
	}
	

	data[ data_index[index] ] = in[0];
	if( (data_type[index] == TYPE_LONG) || (data_type[index] == TYPE_DOUBLE) )
		data[ data_index[index]+1 ] = in[1];
}

void MemoryData::get_data(u2 index, u1 type, u4 *out) {
	if(data_type[index] != type) {
		printf("Data type error %c != %c: mem_data.get_data\n",data_type[index],type);
		exit(0);
	}
	if(data_index[index] == (u2)-1) {
		printf("Index value error %d: mem_data.get_data\n" ,(short)data_index[index]);
		exit(0);
	}
	
	out[0] = data[ data_index[index] ];
	if( (data_type[index] == TYPE_LONG) || (data_type[index] == TYPE_DOUBLE) )
		out[1] = data[ data_index[index]+1 ];
	
}

void MemoryData::make_fields() {
	data_index = new u4[classref->fields_count];
	data_type = new u1[classref->fields_count];
	data_count = (classref->fields_count) - (classref->static_fields_count);
	
	data_length = make_fields_index();
	data = new u4[data_length];
	
//#define TEST_NONSTATIC
#ifdef TEST_NONSTATIC
	printf("TEST NON STATIC:mem_data\n");
	printf("fields: %d\n",classref->fields_count);
	printf("non statics: %d size [%d]\n",data_count ,data_length);
	for(u2 i=0; i<classref->fields_count; i++) {
		printf("[%d] %c | %d\n",i, data_type[i],(short)data_index[i]);
	}
	printf("\n");
#endif
}

u2 MemoryData::make_fields_index() {
	u2 size = 0;
	
	for(u2 i=0; i<classref->fields_count; i++) {
		data_index[i] = classref->static_fields_index[i];
		data_type[i] = classref->static_fields_type[i];
		if (data_index[i] == (u2) -1) {
			data_index[i] = size++;
			if( (data_type[i] == TYPE_LONG) || 
				(data_type[i] == TYPE_DOUBLE) )
				size++;
		} else {
			data_index[i] = (u2) -1;
		}
	}
	return size;
}

void MemoryData::print() {
	printf("MemoryData\n");
	printf("type: %c\n", type);
	u2 max= data_count;
	if(type == TYPE_CLASS){
		printf("class: %s\n", classref->get_class_name());
		max = classref->fields_count;
	}
	printf("data: %d\n", data_count);
	for(u2 i=0;i<max; i++) {
		if(data_index[i] != (u2)-1) {
			printf("[%d]->[%d] %c| ",i,data_index[i],data_type[i]);
			if(type == TYPE_CLASS)
				printf("%s\t", classref->get_field_name(i));
			printf("%08X", data[ data_index[i] ]);
			if( (data_type[i] == TYPE_LONG) || 
				(data_type[i] == TYPE_DOUBLE) ) {
				printf("%08X\n", data[ data_index[i]+1 ]);
			}
			printf("\n");
		}
	}
		
}
