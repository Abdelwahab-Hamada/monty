#include "monty.h"

/**
 * set_gvars - gvars
 * @var: variable
 * Return: 0 Success, 1 Failed
 */
int set_gvars(vars *var)
{
	var->file = NULL;
	var->buff = NULL;
	var->tmp = 0;
	var->dict = create_instructions();
	if (var->dict == NULL)
		return (EXIT_FAILURE);
	var->head = NULL;
	var->line_number = 1;
	var->MODE = 0;

	return (EXIT_SUCCESS);
}

/**
 * create_instructions - commands
 * Return: pointers
 */
instruction_t *create_instructions()
{
	instruction_t *ptr = malloc(sizeof(instruction_t) * 18);

	if (!ptr)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (NULL);
	}
	ptr[0].opcode = "pall", ptr[0].f = pall;
	ptr[1].opcode = "push", ptr[1].f = push;
	ptr[2].opcode = "pint", ptr[2].f = pint;
	ptr[3].opcode = "pop", ptr[3].f = pop;
	ptr[4].opcode = "swap", ptr[4].f = swap;
	ptr[5].opcode = "add", ptr[5].f = add;
	ptr[6].opcode = "nop", ptr[6].f = NULL;
	ptr[7].opcode = NULL, ptr[7].f = NULL;

	return (ptr);
}

/**
 * exec - run methods
 * @var: gvars
 * @opcode: cmd
 * Return: exit code
 */
int exec(vars *var, char *opcode)
{
	int i;

	for (i = 0; var->dict[i].opcode; i++)
		if (strcmp(opcode, var->dict[i].opcode) == 0)
		{
			if (!var->dict[i].f)
				return (EXIT_SUCCESS);
			var->dict[i].f(&var->head, var->line_number);
			return (EXIT_SUCCESS);
		}
	if (strlen(opcode) != 0 && opcode[0] != '#')
	{
		fprintf(stderr, "L%u: unknown instruction %s\n",
			var->line_number, opcode);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}


/**
 * free_all - free memory
 *
 */
void free_all(void)
{
	if (var.buff != NULL)
		free(var.buff);
	if (var.file != NULL)
		fclose(var.file);
	free(var.dict);
	if (var.head != NULL)
	{
		while (var.head->next != NULL)
		{
			var.head = var.head->next;
			free(var.head->prev);
		}
		free(var.head);
	}
}

/**
 * _isdigit - self explained
 * @string: as above
 * Return: 0 Success, 1 Failed
 */
int _isdigit(char *string)
{
	int i;

	for (i = 0; string[i]; i++)
	{
		if (string[i] < 48 || string[i] > 57)
			return (1);
	}
	return (0);
}
