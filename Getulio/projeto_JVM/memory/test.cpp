#include <stdio.h>

#include "attribute.hpp"


#include "class_array.hpp"
#include "class.hpp"
#include "class_loader.hpp"
#include "mem_data.hpp"
#include "mem_data_array.hpp"

void teste_classes() {
	ClassArray ca(100);
	Class *c;
	c =  ca.get_classref((u1 *)"Classe2");
	c->print();
	c =  ca.get_classref((u1 *)"Classe1");
	c->print();
}

void teste_memorydata() {

	Class *c, *d;
	ClassLoader cl;
	MemoryData i1, i2;
	
	c = cl.load_class((u1 *)"Classe2");
	d = cl.load_class((u1 *)"Classe1");
	i1.type = TYPE_CLASS;
	i2.type = TYPE_CLASS;
	i1.classref = c;
	i2.classref = d;
	//i1.make_fields();
	//i2.make_fields();
	
	u4 data[2] = {0xADC, 0xFED};
	i1.put_data(4, TYPE_LONG, data);
	i1.put_data(1, TYPE_FLOAT, data+1);
	i1.print();
	i2.print();
	
}

void teste_memorydata_array1() {
	Class *a, *b;
	ClassLoader cl;
	MemoryDataArray data(10);
	u4 p, q;
	
	a = cl.load_class((u1 *)"Classe2");
	b = cl.load_class((u1 *)"Classe1");
	//a->print_cp();
	p = data.new_instance(a);
	u4 r[5] = {0xABC, 0xFED, 0x54312}; 
	u4 s[5] = {0};
	data.putfield(p,6,r,TYPE_LONG);
	//data.putfield(p,4,TYPE_INT,r+1);
	//data.putfield(p,5,TYPE_FLOAT,r+2);

	
	q = data.new_instance(b);
	
	
	u1 t;
	data.print();
	t = data.getfield(p,6,s);
	printf("%c %08X%08X",t,s[0],s[1]);
	
}

void teste_memorydata_array2() {
	MemoryDataArray data(100);
	ClassArray classes(100);
	Class *a, *b;
	u4 sizes[3] = { 4, 3, 4 };
	const char *types = "[L";
	u4 p, q;
	
	a = classes.get_classref((u1 *)"Classe2");
	p = data.new_array(sizes, (u1 *)types, a);
	printf("p: %08X\n",p);
	data.print();
}

void teste_class_array1() {
	ClassArray classes(100);
	Class *a, *b;
	a = classes.get_classref((u1 *)"Classe1");
	b = classes.get_classref((u1 *)"Classe2");
	a->print();
	a->print_cp();
	//b->print();
	//b->print_cp();
	printf("\n");
	printf("%s\n", a->get_cp_this_class());
	printf("%s\n", a->get_cp_super_class());
	printf("%s\n", a->get_cp_class_name(3));
	printf("%s\n", a->get_cp_field_class(7));
	printf("%s\n", a->get_cp_field_name(7));
	printf("%s\n", a->get_cp_field_type(7));
	printf("%s\n", a->get_cp_method_class(2));
	printf("%s\n", a->get_cp_method_name(2));
	printf("%s\n", a->get_cp_method_descriptor(2));

	/*
	u1 *get_cp_this_class();
	u1 *get_cp_super_class();
	u1 *get_cp_class_name(u2);
	u1 *get_cp_field_class(u2);
	u1 *get_cp_field_name(u2);
	u1 *get_cp_field_type(u2);
	u1 *get_cp_method_class(u2);
	u1 *get_cp_method_name(u2);
	u1 *get_cp_method_descriptor(u2);
	u1 *get_cp_ref_class(u2);
	u1 *get_cp_ref_name(u2);
	u1 *get_cp_ref_descriptor(u2);
	u1 *get_cp_utf8(u2);
	*/
}

void teste_class_array2() {
	ClassArray classes(100);
	Class *a, *b;
	
	a = classes.get_classref((u1 *)"Classe1");
	b = classes.get_classref((u1 *)"Classe2");
	
	//a->putstatic();
}

void teste_conv() {
	u4 *i;
	float f1 = 1.4, *f2;
	
	i = (u4 *)&f1;
	printf("i: %X f1: %X\n", *i, *((u4 *)&f1));
	f2 = (float *)i;
	printf("f2: %f\n", *f2);
}

int main() {

	teste_class_array1();
	
	
	return 0;
}
