
#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>

struct list {
  struct list *next;
} list;

/*test : min 3 three nodes required due to way I point nodes*/
void create_looped_list(struct list **head) {
  struct list *nodes[50];
  int32_t len = 50;
  for (int i = 0; i < len; ++i) {
    nodes[i] = (struct list *)malloc(sizeof(struct list));
    nodes[i]->next = NULL;
  }
  for (int i = 0; i < len; ++i) {
    nodes[i]->next = nodes[i + 1];
    if ((i + 1) == len - 1)
      break;
  }
  nodes[49]->next = nodes[10];
  *head = nodes[0];
}
void test_create_looped_list() {
  struct list *head = NULL;
  create_looped_list(&head);
  struct list *slow = head, *fast = head;
  uint32_t loop = 0;

  while (fast && fast->next) {
    slow = slow->next;
    if (fast->next == NULL || fast->next->next == NULL)
      break;
    fast = fast->next->next;
    if (slow == fast) {
      loop = 1;
      break;
    }
  }

  /*
  while( fast != slow ) {
          slow = slow->next;
          fast = fast->next->next;
          if (slow == NULL) {
                  loop = 0;
                  break;}
  }*/

  if (loop)
    printf("loop detected %p\n", slow);
  else
    printf("loop not found");
}

int main() { test_create_looped_list(); }

/*you cannot load a array to list by typecasting
compiler will go crazy :)
*/
#if MAKE_BUGGY_LIST
struct list_v1 {
  uint64_t val;
  struct list *next;
} list_v1;

uint64_t arr[100] = {1, 3};
uint64_t arr_v1[100] = {1};
struct list *create_loop_list(struct list *in) {
  struct list *l = (struct list *)arr, *iter = l;
  struct list_v1 *_l = (struct list *)arr_v1, *_iter = _l;

  /*interesting goof up: I typed cast the next to next array but it is
   * actually overwriting the arr with the address of iter->next
   *
   * what it means that compiler interpret array to store pointers, not integers
   * FIX: add data element*/

  for (uint32_t i = 1; i < sizeof(arr) / sizeof(arr[0]); ++i) {
    /*BUG: here we are pointing to next arr but actually writing the arr[0]*/
    iter->next = (struct list *)(arr + i);
    iter = iter->next;
  }

  uint64_t *x = (uint64_t *)l;
  printf("x val %lx arr[0] %lx\n ", *x, arr[0]);
  printf("add %4p %4p\n", l, arr);
  printf("add next %4p %4p\n", l->next, arr + 1);

  printf("orig arr %ld\n", arr_v1[0]);
  for (uint32_t i = 0; i < sizeof(arr_v1) / sizeof(arr_v1[0]); ++i) {
    _iter->val = arr[i];
    _iter->next = (i < 99) ? (struct list_v1 *)(arr_v1 + i) : NULL;
  }
  uint64_t *_x = (uint64_t *)_l;
  printf("x val %lx arr[0] %lx\n ", *_x, arr_v1[0]);
}

/* write way to do it */
/* Loads arr[] into an array of struct list_v1 and links the nodes */
void load_array_to_list_v1(uint64_t *arr, size_t len, struct list_v1 *out) {
  for (size_t i = 0; i < len; ++i) {
    out[i].val = arr[i];
    out[i].next = (i < len - 1) ? &out[i + 1] : NULL;
  }
}

void test_load() {
  struct list_v1 list_nodes[100];
  load_array_to_list_v1(arr, 100, list_nodes);

  /* Now list_nodes[0] is the head of the linked list. */
  /* You can traverse it: */
  struct list_v1 *head = &list_nodes[0];
  while (head) {
    printf("%llu\n", head->val);
    head = head->next;
  }
}

int main() {

  struct list *l;
  create_loop_list(l);

  return 1;
}
#endif
