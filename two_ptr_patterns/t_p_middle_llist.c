#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct list {
	struct list *next;
};

/*FUNDAMENTAL CHECK: */

void pointer_basics()
{
	/*array of 20 pointers*/
	int *list_1[20];
	/*pointer to array of 20 ints*/
	/*used for pointing to an array of 20 ints or passing array to function to preserve array size*/
	int(*list_2)[20];

	int array[20] = { 1, 2, 3 };

	/*NOTE: & -> list is pointing to entire array range
     * if you do &array + 1, it will jump 20
     * list_2 = array + 1 -> list_2 pointing to first element of array
     * & make sure list aware of array size*/
	list_2 = &array;

	int(*list_check)[20];
	int test[40] = {};
	for (int i = 0; i < 40; ++i) {
		test[i] = i;
	}
	list_check = (int(*)[20]) & test;
	printf("& -> (*list_check)[] %d\n", (*list_check)[0]);
	//This make list_check to jump 40 + 1 :)
	//list_check = &test + 1;
	//&test become (*test)[40] so &test + 1 is (test + 40) + 1
	++list_check;
	//output: 20
	printf("++  -> (*list_check)[] %d\n", (*list_check)[0]);

	/*note the missing &*/
	list_check = (int(*)[20])test;
	printf("no & -> (*list_check)[] %d\n", (*list_check)[0]);
	list_check = (int(*)[20])(test + 1);
	printf("no & -> (*list_check)[] %d\n", (*list_check)[0]);

	//address check 0x7fff5e9348f0 0x7fff5e9348f0 0x7fff5e9348f4 0x7fff5e934990 0x7fff5e9348f4 0x7fff5e934990
	printf("address check %p %p %p %p %p %p\n", test, &test, test + 1,
	       &test + 1, (int(*)[20])(test + 1), (int(*)[20])(&test + 1));

	/*conclusion: to jump 20, do ++list or typecast (int(*)[20])*/

	/*same as above but look at magic of typecast*/
	list_check = (int(*)[20])test;
	printf("typecast -> (*list_check)[] %d\n", (*list_check)[0]);
	list_check = (int(*)[20])test + 1;
	printf(" typecast -> (int(*)[20])test + 1 %d\n", (*list_check)[0]);
	list_check = test + 1;
	printf(" witout typecast -> test + 1 %d\n", (*list_check)[0]);
}

#define MAX_NODE 2
void llist()
{
	/*array of 20 pointers of type list*/
	/*REM: {list} (*list)[20] -> pointer to array of 20 {types}*/
	struct list *list[MAX_NODE];

	for (int i = 0; i < MAX_NODE; ++i) {
		list[i] = malloc(sizeof(struct list));
		list[i]->next = NULL;
	}

	/*do not overwrite next of last node*/
	for (int i = 0; i < MAX_NODE - 1; ++i) {
		list[i]->next = list[i + 1];
	}

	for (int i = 0; i < MAX_NODE; ++i) {
		printf("list ptr %p next %p\n", list[i], list[i]->next);
	}

	struct list *node = list[0];

	printf("list -> \n");
	while (node != NULL) {
		printf("%p %p\n", node, node->next);
		node = node->next;
	}

	/*find middle and remove the node*/
	int mid = MAX_NODE / 2;

	struct list *head = list[0];
	struct list *s = head, *f = head;

	int i = 1;
	s = head;
	f = head->next;
	while (f != NULL) {
		if (i == mid) {
			s->next = f->next;
			free(f);
			break;
		}
		s = f;
		f = f->next;
		++i;
	}
	node = list[0];

	printf("after delete -->\n");

	while (node != NULL) {
		printf("%p %p\n", node, node->next);
		node = node->next;
	}
}

int main()
{
	pointer_basics();

	llist();

	return 0;
}
