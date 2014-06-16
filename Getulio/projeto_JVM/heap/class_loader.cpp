#include "class_loader.hpp"

//#define CLASSFILE "Test1.class"
//#define DEV

#define JAVA6VER 50

cp_info *cp_loader(FILE *, u2);
u2 *interface_loader(FILE *, u2);
field_info *field_loader(FILE *, u2);
method_info *method_loader(FILE *, u2);
attribute_info *attribute_loader(FILE *, u2);

u1 read_u1(FILE *);
u2 read_u2(FILE *);
u4 read_u4(FILE *);
u1 *read_n(FILE *, u4);

Class *ClassLoader::new_class(u1 *name) {
	FILE *fp;
	char name_buff[100];
	temp = NULL;
	
	strcpy(name_buff, (char *)name);
	strcat(name_buff, ".class");
	
	if( (fp = fopen(name_buff, "rb")) == NULL)
		return NULL;
	
	if( (temp = new Class) == NULL) {
		fclose(fp);
		return NULL;
	}
	
	temp->magic = read_u4(fp);
	if(temp->magic != 0xCAFEBABE) {
		delete temp;
		fclose(fp);
		return NULL;
	}
	
	temp->major_version = read_u2(fp);
	temp->minor_version = read_u2(fp);
	int version = temp->major_version + temp->minor_version;
	if(version > JAVA6VER) {
		delete temp;
		fclose(fp);
		return NULL;
	}
	
	temp->cp_count = read_u2(fp);
	temp->constant_pool = cp_loader(fp, temp->cp_count);
	temp->access_flags = read_u2(fp);
	temp->this_class = read_u2(fp);
	temp->super_class = read_u2(fp);
	temp->interfaces_count = read_u2(fp);
	temp->interfaces = interface_loader(fp, temp->interfaces_count);
	temp->fields_count = read_u2(fp);
	temp->fields = field_loader(fp, temp->fields_count);
	temp->methods_count = read_u2(fp);
	temp->methods = method_loader(fp, temp->methods_count);
	temp->attributes_count = read_u2(fp);
	temp->attributes = attribute_loader(fp, temp->attributes_count);
	
	fclose(fp);
	
	return temp;
}

cp_info *cp_loader(FILE *fp, u2 n) {
	cp_info *cp = NULL;
	u1 tag;
	cp = new cp_info[n];
	
	for(int i=1; i<n; i++) {
		tag = read_u1(fp);
		cp[i].tag = tag;
		if( tag == TAG_CLASS) {
			cp[i].info.name_index = read_u2(fp);
		} else if( tag == TAG_STRING) {
			cp[i].info.string_index = read_u2(fp);
		} else if( (tag == TAG_LONG) || (tag == TAG_DOUBLE) ) {
			cp[i].info.high_bytes = read_u4(fp);
			i++;
			cp[i].tag = tag;
			cp[i].info.low_bytes = read_u4(fp);
		} else if(tag == TAG_UTF8) {
			u2 length = read_u2(fp);
			cp[i].info.utf8 = new u1[length+1];
			for(int j=0; j<length; j++)
				cp[i].info.utf8[j] = read_u1(fp);
			cp[i].info.utf8[length] = '\0';
		} else {
			cp[i].info.bytes = read_u4(fp);
		}
	}
	
	return cp;
}

u2 *interface_loader(FILE *fp, u2 n) {
	if(n<=0) 
		return NULL;

	u2 *interfaces = NULL;
	
	n++;
	interfaces = new u2[n];
	for(int i=0; i<n; i++)
		interfaces[i] = read_u2(fp);
		
	return interfaces;
}

field_info *ClassLoader::field_loader(FILE *fp, u2 n) {
	if(n<=0) 
		return NULL;
		
	field_info *f = NULL;
	
	n++;
	f = new field_info[n];
	for(int i=1; i<n; i++) {
		f[i].access_flags = read_u2(fp);
		f[i].name_index = read_u2(fp);
		f[i].descriptor_index = read_u2(fp);
		f[i].attributes_count = read_u2(fp);
		f[i].attributes = new attribute_info[f[i].attributes_count];
		f[i].attributes = attribute_loader(fp, f[i].attributes_count);
	}
	return f;
}

method_info *ClassLoader::method_loader(FILE *fp, u2 n) {
	if(n<=0) 
		return NULL;
	
	method_info *m = NULL;
	
	n++;
	m = new method_info[n];
	for(int i=1; i<n; i++) {
		m[i].access_flags = read_u2(fp);
		m[i].name_index = read_u2(fp);
		m[i].descriptor_index = read_u2(fp);
		m[i].attributes_count = read_u2(fp);
 		m[i].attributes = new attribute_info[m[i].attributes_count];
		m[i].attributes = attribute_loader(fp, m[i].attributes_count);
	}
	return m;
}

#define ATTRIBUTE_TEST
attribute_info *ClassLoader::attribute_loader(FILE *fp, u2 n) {
	if(n<=0) 
		return NULL;
	
	attribute_info *a = NULL;
	
	a = new attribute_info[n];
	for(int i=0; i<n; i++) {
		u1 *name;
		u4 length;
		
		a[i].name_index = read_u2(fp);
		name = temp->get_utf8(a[i].name_index);
		length = read_u4(fp);
#ifdef ATTRIBUTE_TEST
		printf("\nget %s\n",name);
#endif

		if(name == NULL)
			return NULL;
		
		
		if( strcmp((char *)name, "Code") == 0 ) {
			a[i].code = new Code;
			a[i].code->max_stack = read_u2(fp);
			a[i].code->max_locals = read_u2(fp);
			a[i].code->code_length = read_u4(fp);
			a[i].code->code = read_n(fp, a[i].code->code_length);
			a[i].code->exception_table_length = read_u2(fp);
			for(u2 j=0; j<a[i].code->exception_table_length; j++)
				a[i].code->exception_table = (exception_table_t *)read_n(fp, sizeof(exception_table_t));
			a[i].code->attributes_count = read_u2(fp);
			

#ifdef ATTRIBUTE_TEST			
			printf("CODE\n");
			printf("stack %d\n",a[i].code->max_stack);
			printf("locals %d\n",a[i].code->max_locals);
			printf("code len %d\n",a[i].code->code_length);
			for(u2 j=0; j<a[i].code->code_length; j++)
				printf("%02X ", a[i].code->code[j]);
			printf("\n");
			printf("exp len %d\n",a[i].code->exception_table_length);
			for(u2 j=0; j<a[i].code->exception_table_length; j++)
				printf("%d %d %d %X\n", a[i].code->exception_table[j].start_pc, 
										a[i].code->exception_table[j].end_pc, 
										a[i].code->exception_table[j].handler_pc, 
										a[i].code->exception_table[j].catch_type);
			printf("att count %d\n",a[i].code->attributes_count);
#endif			

			a[i].code->attributes = attribute_loader(fp, a[i].code->attributes_count);
		} else if( strcmp((char *)name, "Exceptions") == 0 ) {
			a[i].exceptions = new Exceptions;
			a[i].exceptions->number_of_exceptions = read_u2(fp);
			a[i].exceptions->exception_index_table = new u2[a[i].exceptions->number_of_exceptions];
			for(u2 j=0; j<a[i].exceptions->number_of_exceptions; j++)
				a[i].exceptions->exception_index_table[j] = read_u2(fp);
			
#ifdef ATTRIBUTE_TEST			
			printf("EXCEPTIONS\n");
			printf("number of excep %d\n",a[i].exceptions->number_of_exceptions);
			for(u2 j=0; j<a[i].exceptions->number_of_exceptions; j++)
				printf("%X ",a[i].exceptions->exception_index_table[j]);
			printf("\n");
#endif		
		} else {
			a[i].info = new a_info;
			a[i].info->length = length;
			a[i].info->bytes = new u1[a[i].info->length];
			for(u4 j=0; j<a[i].info->length; j++)
				a[i].info->bytes[j] = read_u1(fp);

#ifdef ATTRIBUTE_TEST					
			printf("INFO\n");
			printf("info len %d\n",a[i].info->length);
			for(u2 j=0; j<a[i].info->length; j++)
				printf("%02X ",a[i].info->bytes[j]);
			printf("\n");
#endif		
		}
	}
	return a;
}

u1 read_u1(FILE* fp) {
	u1 temp = 0;
	
	fread(&temp, sizeof(u1), 1, fp);
	return temp;
}

u2 read_u2(FILE* fp) {
	u2 temp = 0;
	
	for(int i=0; i<2; i++) {
		temp <<= 8;
		fread(&temp, sizeof(u1), 1, fp);
	}
	return temp;
}

u4 read_u4(FILE* fp) {
	u4 temp = 0;
	
	for(int i=0; i<4; i++) {
		temp <<= 8;
		fread(&temp, sizeof(u1), 1, fp);
	}
	return temp;
}

u1 * read_n(FILE* fp, u4 n) {
	u1 *temp;
	temp = new u1[n];
	fread(temp, sizeof(u1), n, fp);
	return temp;
}
