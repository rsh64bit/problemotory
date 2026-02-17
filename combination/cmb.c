#include<stdio.h>

/*combination:(n,r) -> number of ways to choose r from n
 *ways = n!/(n-r)!r!
 */



/*create a empty stack and push empty list
 *pop stack 
 *iterate from 0 to nth element
 *if empty
 *create a path list, push element to path and push it to stack
 *if not empty & path.len != number of elements push element not in path p 
 */


/*
 * stack -> 
 *
 * */

/*stack data structure*/

struct list {
	int i;
	struct list *next;
};

struct stack_elem {
	struct list *list;
	struct stack_elem *next;
};

push(stuct stack_elem *root, void *x)
{
	struct stack_elem *elem = malloc(sizeof(struct stack_elem));
	
	elem->list = x;
	elem->next = root;


}
	

int main()
{

	return 0;
}
