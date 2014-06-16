#include <stdio.h>

#include "attribute.hpp"


#include "class.hpp"
#include "class_loader.hpp"

void teste_class() {
	Class *c;
	ClassLoader cl;
	if( (c = cl.new_class((u1 *)"Classe2") ) == NULL) {
		printf("erro\n");
		return;
	}
	//c->initialize();
}

int main() {
	teste_class();
	
	return 0;
}
