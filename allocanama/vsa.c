#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define NUM_BLK 10
#define BLK_SIZE 10



/*very stupid allocator*/
struct block {
	struct block *next;
};
struct mem_pool {
	uint8_t buf[NUM_BLK * BLK_SIZE];
	struct block *free_list;
};

struct mem_pool ram = {};


void print()
{
	struct block *iter = ram.free_list;

	while (iter->next != NULL) {
		printf("block entry %4p, pointing to %4p\n", iter, iter->next);
		iter = iter->next;
	}
}

void vsa_init()
{
	for (int i = 0; i < NUM_BLK; ++i) {

		struct block *block = (struct block *)(ram.buf + i*BLK_SIZE);

		block->next = ram.free_list;
		ram.free_list = block;
		printf("block mem %d add %4p next %4p free_list %4p\n", i, block, block->next, ram.free_list);
	}
}


uintptr_t vsa_alloc()
{
	struct block *block = ram.free_list;

	ram.free_list = block->next;
	return block;
}

void vsa_free(uintptr_t mem)
{
	((struct block*)mem)->next = ram.free_list;
	ram.free_list = mem;
}




int main()
{
	vsa_init();
	print();
	printf("alloc\n");
	uintptr_t *t1 = vsa_alloc();
	print();
	printf("free\n");
	vsa_free(t1);
	print();
	return 0;
}
