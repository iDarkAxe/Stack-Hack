#include <stdio.h>

void end_of_the_world()
{
	char i;

	printf("i: %p\n", &i);
	printf("i: %p\n", &i + 19);
	*(int *)(&i + 19) = 1;
}

void end_of_the_world2()
{
	char i;

	printf("i: %p\n", &i);
	printf("i: %p\n", &i + 25);
	*(int *)(&i + 25) = 1;
}

void end_of_the_world3(const int *p)
{
	printf ("p: %p\n", p + 1);
	p = p + 1;
	printf("p v: %d\n", *p);
	*(int *)p = 1;
	printf("p v: %d\n", *p);
}

int main(void)
{
	const volatile int zero = 0;
	const volatile int one = 1;

	printf("z: %p\n", &zero);
	printf("o: %p\n", &one);
	// end_of_the_world();
	end_of_the_world2();
	// end_of_the_world3(&one);
	printf("z v: %d\n", zero);
	printf("o v: %d\n", one);
	if (zero == one)
		printf("feur");
	else
		printf("four");
	return (0);
}
