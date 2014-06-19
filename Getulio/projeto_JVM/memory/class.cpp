#include "class.hpp"

u1 *Class::get_class_name() {
	u4 cp_index = constant_pool[this_class].name_index;
	return get_utf8(cp_index);
}

u1 *Class::get_super_name() {
	u4 cp_index = constant_pool[super_class].name_index;
	return get_utf8(cp_index);
}

u4  Class::get_field_index(u2 cp_index) {
	u4 index = -1;
	u1 *name = get_utf8( get_cp_field_name_index(cp_index) );
	
	for(int i=0; i<fields_count; i++) {
		if(strcmp((char *)name, (char *)get_field_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u4 Class::get_cp_field_name_index(u4 cp_index) {
	printf("cp_index: %d\n",cp_index);
	test_cp("get_cp_field_name_index", TAG_FIELD, cp_index);
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	printf("cp_index: %d\n",cp_index);
	test_cp("get_cp_field_name_index", TAG_NAMEANDTYPE, cp_index);
	return constant_pool[cp_index].NameAndType.name_index;
}


u4  Class::get_method_index(u2 cp_index) {
	u4 index = -1;
	u1 *name = get_utf8( get_cp_method_name_index(cp_index) );
	
	for(int i=0; i<methods_count; i++) {
		if(strcmp((char *)name, (char *)get_method_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u4 Class::get_cp_method_name_index(u4 cp_index) {
	test_cp("get_cp_method_name_index", TAG_METHOD, cp_index);
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	test_cp("get_cp_method_name_index", TAG_NAMEANDTYPE, cp_index);
	return constant_pool[cp_index].NameAndType.name_index;
}

u1 *Class::get_field_name(u4 index) {
	u4 i = fields[index].name_index;
	return get_utf8(i);
}

u1 *Class::get_field_type(u4 index) {
	u4 i = fields[index].descriptor_index;
	return get_utf8(i);
}

u1 *Class::get_method_name(u4 index) {
	u4 i = methods[index].name_index;
	return get_utf8(i);
}

u1 *Class::get_method_descriptor(u4 index) {
	u4 i = methods[index].descriptor_index;
	return get_utf8(i);
}

u1 *Class::get_utf8(u4 cp_index) {
	test_cp("get_utf8", TAG_UTF8, cp_index);
	return constant_pool[cp_index].utf8;
}

void Class::make_static_fields() {
	u2 size = 0;
	
	static_fields_index = new u4[fields_count];
	static_fields_type = new u1[fields_count];
	static_fields_count = 0;
	size = make_field_index();

//#define TEST_STATIC
#ifdef TEST_STATIC
	printf("TEST STATIC:class\n");
	printf("fields: %d\n",fields_count);
	printf("statics: %d size [%d]\n",static_fields_count ,size);
	for(int i=0; i<fields_count; i++) {
		printf("[%d] %c | %d\n",i, static_fields_type[i], (short)static_fields_index[i]);
	}
	printf("\n");
#endif

	static_fields = new u4[size];
}

u2 Class::make_field_index() {
	u2 size = 0;
	
	for(int i=0; i<fields_count; i++) {
		u1 type = *( get_field_type(i) );
		static_fields_type[i] = type;
		if( isStatic(fields[i].access_flags) ) {
			static_fields_count++;
			static_fields_index[i] = size;
			size++;
			if( (type == TYPE_LONG) || (type == TYPE_DOUBLE) )
				size++;
		} else {
			static_fields_index[i] = (u2) -1;
		}
	}
	return size;
}

void Class::test_cp(const char *func, u2 tag, u2 cp_index) {
	if(cp_index<1 || cp_index>cp_count) {
		printf("Error cp index %d: class.%s\n",cp_index,func);
		exit(0);
	}
	if(constant_pool[cp_index].tag != tag) {
		printf("Error cp tag %d != %d: class.%s\n",tag, constant_pool[cp_index].tag,func);
		exit(0);
	}
}

/* Print */
void Class::print() {
	printf("class name: %s\n", get_class_name());
	printf("super name: %s\n", get_super_name());
	printf("fields count: %d\n", fields_count);
	for(int i=0;i<fields_count; i++) {
		printf("   [%d]", i);
		printf("\tname: %s", get_field_name(i));
		printf("\ttype: %s", get_field_type(i));
		printf("\n");
	}
	printf("methods count: %d\n", methods_count);
	for(int i=0;i<methods_count; i++) {
		printf("   [%d]", i);
		printf("\tname: %s", get_method_name(i));
		printf("\tdescr: %s", get_method_descriptor(i));
		printf("\n");
	}
}

void Class::print_cp() {
	const char *tipo[16] = { NULL, "Utf8", NULL, "Integer", "Float", "Long", "Double", "Class",
						"String", "Field", "Method", "Interface", "NameAndType"};
	u2 tag;
	
	for(int i=1; i<cp_count; i++) {
		tag = constant_pool[i].tag;
		printf("  %d.%s\n", i, tipo[tag]);
		if(tag == TAG_CLASS) {
			printf("\tname_index: %d\n", constant_pool[i].name_index);
		} else if( (tag == TAG_FIELD)  ||
				   (tag == TAG_METHOD) ||
				   (tag == TAG_IMETHOD) ) {
			printf("\tclass_index: %d\n",constant_pool[i].Ref.class_index);
			printf("\tname_and_type_index: %d\n", constant_pool[i].Ref.name_and_type_index);
		} else if(tag == TAG_STRING) {
			printf("\tstring_index: %d\n", constant_pool[i].string_index);
		} else if( (tag == TAG_INTEGER) || (tag == TAG_FLOAT) ) {
			printf("\tbytes: %08X\n", constant_pool[i].bytes);
		} else if( (tag == TAG_DOUBLE) || (tag == TAG_LONG) ) {
			printf("\thigh_bytes: %08X\n", constant_pool[i].high_bytes);
			printf("\tlow_bytes: %08X\n", constant_pool[i].low_bytes);
			i++;
		} else if(tag == TAG_NAMEANDTYPE) {
			printf("\tname_index: %d\n", constant_pool[i].NameAndType.name_index);
			printf("\tdescriptor_index: %d\n", constant_pool[i].NameAndType.descriptor_index);
		} else if(tag == TAG_UTF8) {
			printf("\tbytes: %s\n", constant_pool[i].utf8);
		} else {
			printf("tag invalido: %d\n", tag);
		}
	}
}
