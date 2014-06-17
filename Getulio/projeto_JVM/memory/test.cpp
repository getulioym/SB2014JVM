#include <stdio.h>

#include "attribute.hpp"


#include "class.hpp"
#include "class_loader.hpp"
#include "instance.hpp"

void teste_class() {
	Class c;
	ClassLoader cl;
	
	c = cl.load_class((u1 *)"Classe2");
	Instance i1(&c);
	c = cl.load_class((u1 *)"Classe1");
	Instance i2(&c);
	
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
	teste_class();
	
	
	
	
	return 0;
}
