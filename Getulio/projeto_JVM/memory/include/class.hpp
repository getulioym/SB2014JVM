#ifndef CLASS
#define CLASS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definition.hpp"
#include "attribute.hpp"
#include "access_flag.hpp"


typedef struct {
	u4 tag;
	union {	// todos os membros tem tamanho 4 bytes
		u2 name_index;	// Class
		struct {		// Fieldref, Methodref, IMethodref
			u2 class_index;
			u2 name_and_type_index;
		} Ref;
		u2 string_index;// String
		u4 bytes;		// Integer, Float
		u4 high_bytes;	// Long, Double
		u4 low_bytes;
		struct {		// Name and Type
			u2 name_index;
			u2 descriptor_index;
		} NameAndType;
		u1 *utf8;		// Utf8
	};
} cp_info;

typedef struct {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
} field_info;

typedef struct {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
} method_info;


class Class {
public:
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 cp_count;
	cp_info *constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	field_info *fields;
	u2 methods_count;
	method_info *methods;
	u2 attributes_count;
	attribute_info *attributes;
	u2 static_fields_count;
	u4 *static_fields_index;
	u1 *static_fields_type;
	u4 *static_fields;
	
	u1 *get_class_name();
	u1 *get_super_name();
	u4 get_field_index(u2);
	u4 get_cp_field_name_index(u4);
	u4 get_method_index(u2);
	u4 get_cp_method_name_index(u4);
	u1 *get_field_name(u4);
	u1 *get_field_type(u4);
	u1 *get_method_name(u4);
	u1 *get_method_descriptor(u4);
	u1 *get_code(u4);
	u1 *get_utf8(u4);
	
	void make_static_fields();
	u2 make_field_index();
	void test_cp(const char *, u2 , u2);
	
	void print();
	void print_cp();
};

enum cp_tag { 	ZERO, 
				TAG_UTF8,	//1
				DOIS, 		
				TAG_INTEGER,//3 
				TAG_FLOAT, 	//4
				TAG_LONG, 	//5
				TAG_DOUBLE, //6
				TAG_CLASS, 	//7
				TAG_STRING, //8
				TAG_FIELD, 	//9
				TAG_METHOD,	//10
				TAG_IMETHOD, //11
				TAG_NAMEANDTYPE	//12
			};

#endif