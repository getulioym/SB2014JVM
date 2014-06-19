#ifndef MEMORY_DATA_ARRAY
#define MEMORY_DATA_ARRAY

#include <stdio.h>

#include "definition.hpp"
#include "mem_data.hpp"

class MemoryDataArray {
public:
	int max;
	int size;
	MemoryData **data;
	
	MemoryDataArray(int);
	u4 new_instance(Class *);
	u4 new_array(u4 *, u1 *, Class *);
	
	void putfield(u4, u2, u1, u4 *);
	u1 getfield(u4, u2, u4 *);
	/*
	void iaload();
	void laload();
	void faload();
	void daload();
	void aaload();
	void baload();
	void caload();
	void saload();
	void iastore();
	void lastore();
	void fastore();
	void dastore();
	void aastore();
	void bastore();
	void castore();
	void sastore();
	void newarray();
	void anewarray();
	void multianewarray();
	void arraylength();
	*/
	
	void print();
};

#endif
