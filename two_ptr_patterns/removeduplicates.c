#include <stdint.h>

#include <stdio.h>

struct ops {
	void (*print_cb)(uint32_t *nums, int size);
	int (*remove_duplicates)(uint32_t *nums, int size);
};

void print(uint32_t *nums, int size)
{
	printf("[");
	for (uint32_t i = 0; i < size; ++i) {
		printf(" %d ", nums[i]);
	}
	printf("]\n");
}

int remove_duplicates_non_ptr(uint32_t *nums, int size)
{
	int slow = 0;

	for (int fast = 1; fast < size; ++fast) {
		if (nums[fast] != nums[slow]) {
			++slow;
			nums[slow] = nums[fast];
		}
	}

	return slow + 1;
}

/*BUGGY*/
int remove_duplicates_fast(uint32_t *nums, int size)
{
	uint32_t *s = nums, *f = nums + 1;


	uint32_t new_len = 0;

	for (uint32_t i = 1; i < size; ++i) { //while (len  > 0) {
		/*unique values*/
		if (*f != *s) {
            ++s;
			*s = *f;
		    ++new_len;
		}
		++f;
	}

	return new_len + 1;
}

int remove_duplicates(uint32_t *nums, int size)
{
	uint32_t *s = nums, *f = nums + 1;

	uint32_t len = size - 1;

	uint32_t new_len = 1;

	len -= 1;
	for (uint32_t i = 1; i < len; ++i) { //while (len  > 0) {
		if (*s == *f) {
			/*duplicate, move s to next*/
			++s;
			++f;
		}
		/*unique values*/
		if (*f != *s) {
			*s = *f;
			++f;
			++s;
		}
		++new_len;
	}

	return new_len;
}
struct ops ops = {
	.print_cb = print,
	.remove_duplicates = remove_duplicates_fast,
};

int main()
{
	uint32_t nums[] = { 1, 1, 2, 3, 4 }, l;
	//uint32_t nums[] = { 1, 1, 2, 2 }, l;
	//uint32_t len = remove_duplicates(nums, l = sizeof(nums) / sizeof(nums[0]));
	uint32_t len =
		ops.remove_duplicates(nums, l = sizeof(nums) / sizeof(nums[0]));
	//
	ops.print_cb(nums, l);
	printf("new len %d\n", len);
	return 0;
}
