#ifndef CLASS
#define CLASS

#include <string.h>

#include "definition.hpp"
#include "attribute.hpp"
#include "access_flag.hpp"


typedef struct {
	u1 tag;
	union {
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
	} info;
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
	u2 *static_fields_table;
	u4 *static_fields;
	
	u1 *get_class_name();
	u1 *get_super_name();
	u4 get_field_index(u1 *);
	u1 *get_field_name(u4);
	u1 *get_field_type(u4);
	u4 get_method_index(u1 *);
	u1 *get_method_name(u4);
	u1 *get_method_descriptor(u4);
	u1 *get_utf8(u4);
	
	void initialize();
	u2 count_static_field();
	
	void print_class();
	void print_cp();
};

enum cp_tag { ZERO, TAG_UTF8, DOIS, TAG_INTEGER, TAG_FLOAT, TAG_LONG, 
			  TAG_DOUBLE, TAG_CLASS, TAG_STRING, TAG_FIELD, TAG_METHOD,
			  TAG_IMETHOD, TAG_NAMEANDTYPE};

#endif