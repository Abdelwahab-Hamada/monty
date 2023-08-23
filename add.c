#include "monty.h"

/**
 * add - add the top two elements of the stack
 * @stack: Double linked list
 * @line_number: File line execution
 */
void add(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n",
			line_number);
		free_all();
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n = (*stack)->next->n + (*stack)->n;
	pop(stack, line_number);
}
