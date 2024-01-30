#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUMBER_OF_CHARACTERS (11)
#define NOT_FOUND_ELEMENT (-1)
#define MEMORY_DIDNT_ALOCATE (-1)
#define DIVISIOR_IS_0 (-1)

typedef struct El* position;
typedef struct El {
	float number;
	position next;
} El;

int postfix(char*);
int Push(float, position);
int Pop(float* , position);
int DeleteAll(position);

int main() {
	char* file = "postfiks.txt";
	postfix(file);

	return EXIT_SUCCESS;
}

int postfix(char* filename) {
	El head = {
	.number = 0.0f,
	.next = NULL
	};
	FILE* fp = NULL;
	int result = 0;
	char buffer[MAX_NUMBER_OF_CHARACTERS] = { 0 };
	float number1 = 0.0f;
	float number2 = 0.0f;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Malloc failed!\n");
		return MEMORY_DIDNT_ALOCATE;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s", buffer);
		int number = 0;
		result = sscanf(buffer, " %d", &number);// sscanf ima dodatnu vrijednost koja kaze jesmo li primili taj number ili nismo, ako jesmo
												// sacuvaj number 1 u varijablu rezultat, ako nismo u varijablu rezultat ide 0
												// Ako rezultat nije 1, gledaj buffer?
		if (result == 1) {
			// push "number" to stack
			Push(number, &head);
		}
		else {
			if (strcmp(buffer, "+") == 0) {
				Pop(&number2, &head); // pop second from stack
				Pop(&number1, &head); // pop first from stack
				Push(number1 + number2, &head); // push first + second to stack
			}
			else if (strcmp(buffer, "-") == 0) {
				Pop(&number2, &head); // pop second from stack
				Pop(&number1, &head); // pop first from stack
				Push(number1 - number2, &head); // push first - second to stack
			}
			else if (strcmp(buffer, "*") == 0) {
				Pop(&number2, &head); // pop second from stack
				Pop(&number1, &head); // pop first from stack
				Push(number1 * number2, &head); // push first * second to stack
			}
			else if (strcmp(buffer, "/") == 0) {
				Pop(&number2, &head); // pop second from stack
				Pop(&number1, &head); // pop first from stack
				if (number2 == 0) {
					printf("Divisior mustn't be 0!");
					return DIVISIOR_IS_0;
				}
				Push(number1 / number2, &head); // push first / second to stack
			}
		}
	}
	if (head.next->next == NULL){
		Pop(&number1, &head);
		printf("Postfix: %lf", number1);
	}
	else {
		printf("Something went wrong!");
	}
	DeleteAll(&head);
	return EXIT_SUCCESS;
}

int Push(float new_element, position p) {
	position q = NULL;
	q = (position)malloc(sizeof(El));
	if (q == NULL)
	{
		printf("Malloc failed\n");
		return MEMORY_DIDNT_ALOCATE;
	}
	q->number = new_element;
	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int Pop(float* element_out, position p) {
	position q = NULL;
	q = (position)malloc(sizeof(El));
	if (q == NULL)
	{
		printf("Malloc failed!\n");
		return MEMORY_DIDNT_ALOCATE;
	}
	q = p->next;
	*element_out = q->number;
	p->next = q->next;
	
	free(q);
	return EXIT_SUCCESS;
}

int DeleteAll(position p) {
	position temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}