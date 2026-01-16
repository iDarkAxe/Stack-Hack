#include <stdio.h>

static void	foo(void);
static void	foo2(void);
static void	foo3(const volatile int *p);

#define SEE_ADDRESSES 1

// Targets directly the stack variable and modifies it
void	foo(void)
{
	char	i;

	if (SEE_ADDRESSES)
	{
		printf("Address of i: %p\n", &i);
		printf("Address of i: %p\n", &i + 19);
	}
	*(int *)(&i + 19) = 1;
}

// Targets near the stack variable (in the "red zone") and modifies it
void	foo2(void)
{
	char	g;

	if (SEE_ADDRESSES)
	{
		printf("Address of g: %p\n", &g);
		printf("Address of g: %p\n", &g + 25);
	}
	*(int *)(&g + 25) = 1;
}

// Targets a pointer to a stack variable and modifies it
void	foo3(const volatile int *p)
{
	if (SEE_ADDRESSES)
		printf("Address of p: %p\n", p + 1);
	p = p + 1;
	printf("Value of p: %d\n", *p);
	*(int *)p = 1;
	printf("Value of p: %d\n", *p);
}

int	main(void)
{
	const volatile int	zero = 0; // a const should be in read-only memory
	const volatile int	one = 1;

	if (SEE_ADDRESSES)
	{
		printf("Address of z: %p\n", &zero);
		printf("Address of o: %p\n", &one);
	}

	foo();
	// foo2();
	// foo3(&one);

	printf("Value of zero after: %d\n", zero);
	printf("Value of one after: %d\n", one);
	if (zero == one)
		printf("Stack has been smashed!\n");
	else
		printf("Stack is intact.\n");
	return (0);
}
