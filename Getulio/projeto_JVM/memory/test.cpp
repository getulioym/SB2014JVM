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
	i1.make_fields();
	i2.make_fields();
	
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
	data.putfield(p,6,TYPE_LONG,r);
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
	Class *a, *b;
	ClassLoader cl;
	u4 sizes[3] = { 4, 3, 4 };
	const char *types = "[L";
	u4 p, q;
	
	a = cl.load_class((u1 *)"Classe2");
	p = data.new_array(sizes, (u1 *)types, a);
	printf("p: %08X\n",p);
	data.print();
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

	teste_memorydata_array2();
	
	
	return 0;
}
