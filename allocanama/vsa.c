#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_BLK 128
#define BLK_SIZE 10

/*BUG : overflow 
 *
 * 1 << 32 -> On 64 bit the value will wrap around 
 * 1 is treated as u32 and if we shift more than the width
 * the value become 0x1<<0
 *
 * FIX: 1UL 
 * */

/*very stupid allocator*/

/*linked list is excellent for O(1) but leads to complexities
 * when we have variable allocation BLK_SIZE
 *
 * The best way is to use bitmap for the blocks or use
 * buddy allocator pool (32, 64, 128, 256..)*/
struct block {
  struct block *next;
};
struct mem_pool {
  uint8_t buf[NUM_BLK * BLK_SIZE];
  struct block *free_list;
};

/*bitmap based pool*/
struct mem_pool_bm {
  uint8_t buf[NUM_BLK * BLK_SIZE];
  uint64_t bitmap[NUM_BLK / sizeof(uint64_t)];
};

struct mem_pool ram = {};
struct mem_pool_bm ram_bm = {};

void print() {
  struct block *iter = ram.free_list;

  while (iter->next != NULL) {
    printf("block entry %4p, pointing to %4p\n", iter, iter->next);
    iter = iter->next;
  }
}

void u64_2_binary(uint64_t v)
{
    uint8_t b[64];

    for (uint32_t i = sizeof(uint64_t)*8; i > 0; --i) {
        b[i - 1] = v & (1UL <<(64 - i))  ? 1 : 0;
    }

    printf("64b->binary ");
    for (uint32_t i = 0; i < sizeof(uint64_t)*8; ++i) {
        printf("%d", b[i]);
    }
    printf("\n");
}

void vsa_dump_bitmap() {
  uint64_t bit, index;

  printf("bitmap size %ld\n", sizeof(ram_bm.bitmap));


  for (uint32_t m = 0; m < 2; ++m)
  for (uint64_t i = 0; i < NUM_BLK; ++i) {
    bit = i % 64;
    index = i / 64;
    printf("Bitmap index %ld block bitmap %ld block free/occupied %ld\n",
           index, bit, ram_bm.bitmap[index] & (1UL << bit));
  }
}

uintptr_t vsa_alloc_bm() {
  /*use modulo 64 for find the bit*/

  uint64_t bit, index;

  for (uint32_t i = 0; i < NUM_BLK; ++i) {

    bit = i % 64;
    index = i / 64;
    if (!(ram_bm.bitmap[index] & (1UL << bit))) {
      ram_bm.bitmap[index] = ram_bm.bitmap[index] | (1UL << bit);
      return ram_bm.buf + i;
    }
  }
  return NULL;
}

void vsa_init() {
  for (int i = 0; i < NUM_BLK; ++i) {

    struct block *block = (struct block *)(ram.buf + i * BLK_SIZE);

    block->next = ram.free_list;
    ram.free_list = block;
    printf("block mem %d add %4p next %4p free_list %4p\n", i, block,
           block->next, ram.free_list);
  }
}

uintptr_t vsa_alloc() {
  struct block *block = ram.free_list;

  ram.free_list = block->next;

  return block;
}

void vsa_free(uintptr_t mem) {
  ((struct block *)mem)->next = ram.free_list;
  ram.free_list = mem;
}

int main() {

    u64_2_binary(0xffffffff);

#ifdef VAS_LL
  vsa_init();

  // print();
  printf("alloc\n");
  uintptr_t *t1 = vsa_alloc();
  // print();
  printf("free\n");
  vsa_free(t1);
#else

  //vsa_dump_bitmap();
  vsa_alloc_bm();
  //vsa_dump_bitmap();
  
#endif// print();
  return 0;
}
