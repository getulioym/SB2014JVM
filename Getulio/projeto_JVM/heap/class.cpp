#include "class.hpp"

u1 *Class::get_class_name() {
	u4 i = constant_pool[this_class].info.name_index;
	return get_utf8(i);
}

u1 *Class::get_super_name() {
	u4 i = constant_pool[super_class].info.name_index;
	return get_utf8(i);
}

u4  Class::get_field_index(u1 *name) {
	u4 index = -1;
	for(int i=1; i<=fields_count; i++) {
		if(strcmp((char *)name, (char *)get_field_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u1 *Class::get_field_name(u4 index) {
	u4 i = fields[index].name_index;
	return get_utf8(i);
}

u1 *Class::get_field_type(u4 index) {
	u4 i = fields[index].descriptor_index;
	return get_utf8(i);
}

u4  Class::get_method_index(u1 *name) {
	u4 index = -1;
	for(int i=1; i<=methods_count; i++) {
		if(strcmp((char *)name, (char *)get_method_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u1 *Class::get_method_name(u4 index) {
	u4 i = methods[index].name_index;
	return get_utf8(i);
}

u1 *Class::get_method_descriptor(u4 index) {
	u4 i = methods[index].descriptor_index;
	return get_utf8(i);
}

u1 *Class::get_utf8(u4 index) {
	return constant_pool[index].info.utf8;
}

void Class::print_class() {
	printf("class name: %s\n", get_class_name());
	printf("super name: %s\n", get_super_name());
	printf("fields count: %d\n", fields_count);
	for(int i=1;i<=fields_count; i++) {
		printf("   [%d]", i);
		printf("\ttype: %s", get_field_type(i));
		printf("\tname: %s\n", get_field_name(i));
	}
	printf("methods count: %d\n", fields_count);
	for(int i=1;i<=methods_count; i++) {
		printf("   [%d]", i);
		printf("\tdescr: %s", get_method_descriptor(i));
		printf("\tname: %s\n", get_method_name(i));
	}
}

void Class::initialize() {
	u2 count = 0;
	
	static_fields_table = new u2[fields_count+1];
	count = count_static_field();
	printf("statics: %d\n",count);
	for(int i=1; i<=fields_count; i++) {
		printf("[%d] %d\n",i,static_fields_table[i]);
	}
	
	static_fields = new u4[count];
	
}

u2 Class::count_static_field() {
	u2 count = 0;
	for(int i=1; i<=fields_count; i++) {
		if( isStatic(fields[i].access_flags) ) {
			static_fields_table[i] = count;
			u1 *type = get_field_type(i);
			count++;
			if( (*type == TYPE_LONG) || (*type == TYPE_DOUBLE) )
				count++;
		} else {
			static_fields_table[i] = 0xFF;
		}
	}
	return count;
}

void Class::print_cp() {
	const char *tipo[16] = { NULL, "Utf8", NULL, "Integer", "Float", "Long", "Double", "Class",
						"String", "Field", "Method", "Interface", "NameAndType"};
	u2 tag;
	
	for(int i=1; i<cp_count; i++) {
		tag = constant_pool[i].tag;
		printf("  %d.%s\n", i, tipo[tag]);
		if(tag == TAG_CLASS) {
			printf("\tname_index: %d\n", constant_pool[i].info.name_index);
		} else if( (tag == TAG_FIELD)  ||
				   (tag == TAG_METHOD) ||
				   (tag == TAG_IMETHOD) ) {
			printf("\tclass_index: %d\n",constant_pool[i].info.Ref.class_index);
			printf("\tname_and_type_index: %d\n", constant_pool[i].info.Ref.name_and_type_index);
		} else if(tag == TAG_STRING) {
			printf("\tstring_index: %d\n", constant_pool[i].info.string_index);
		} else if( (tag == TAG_INTEGER) || (tag == TAG_FLOAT) ) {
			printf("\tbytes: %08X\n", constant_pool[i].info.bytes);
		} else if( (tag == TAG_DOUBLE) || (tag == TAG_LONG) ) {
			printf("\thigh_bytes: %08X\n", constant_pool[i].info.high_bytes);
			printf("\tlow_bytes: %08X\n", constant_pool[i].info.low_bytes);
			i++;
		} else if(tag == TAG_NAMEANDTYPE) {
			printf("\tname_index: %d\n", constant_pool[i].info.NameAndType.name_index);
			printf("\tdescriptor_index: %d\n", constant_pool[i].info.NameAndType.descriptor_index);
		} else if(tag == TAG_UTF8) {
			printf("\tbytes: %s\n", constant_pool[i].info.utf8);
		} else {
			printf("tag invalido: %d\n", tag);
		}
	}
}

