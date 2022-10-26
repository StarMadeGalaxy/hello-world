#include <stdio.h>

#define SIZE 16
#define True 1
#define False 0			


int is_full(int);
void push(int, int*, int*);
int pop(int*, int*);
int is_empty(int);
void display(int*, int);


void display(int* stack, int stack_pointer)
{
	if (is_empty(stack_pointer) == True)
		printf("Stack is empty.\n");
	else
	{
		for (int i = 0; i <= stack_pointer; ++i)
		{
			printf("(#%d - %d) ", i, stack[i]);
		}
		putchar('\n');
	}
}

int is_full(int stack_pointer)
{
	if (stack_pointer == SIZE - 1)
		return True;
	return False;
}

int is_empty(int stack_pointer)
{
	if (stack_pointer == -1)
		return True;
	return False;
}

int pop(int* stack, int* stack_pointer)
{
	if (is_empty(*stack_pointer) == True)
	{
		printf("Stack is empty.\n");
		return;
	}
	else
	{
		int result = stack[*stack_pointer];
		stack[*stack_pointer] = NULL;
		--stack_pointer;
		printf("Popped successfully: %d\n", result);
		return result;
	}
}

void push(int element, int* stack_pointer, int* stack)
{
	if (is_full(*stack_pointer) == True)
	{
		printf("Stack overflow: %d\n", element);
		return False;
	}
	++*stack_pointer;
	stack[*stack_pointer] = element;
	printf("Pushed successfully: %d\n", element);
}


int main(void)
{
	int stack[SIZE];
	int SP = -1;
	display(stack, SP);
	push(5, &SP, stack);
	display(stack, SP);
	push(6, &SP, stack);
	display(stack, SP);
	pop(stack, &SP);
	display(stack, SP);
	getchar();
	return 0;
}

