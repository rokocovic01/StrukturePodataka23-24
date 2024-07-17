#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MALLOC_ERROR (-1)

typedef struct poly* position;

typedef struct poly {
	int coef;
	int exponent;
	position next;
}poly;

int insertFirst(position);
int insertSecond(position);
int printPoly(position);
int sum(position, position, position);
int multiply(position, position, position);

int main() {
	poly Head1 = {
		.coef = 0,
		.exponent = 0,
		.next = NULL
	};
	poly Head2 = {
		.coef = 0,
		.exponent = 0,
		.next = NULL
	};
	poly HeadSum = {
		.coef = 0,
		.exponent = 0,
		.next = NULL
	};
	poly HeadMultiply = {
		.coef = 0,
		.exponent = 0,
		.next = NULL
	};
	insertFirst(&Head1);
	insertSecond(&Head2);
	printf("First polynome: ");
	printPoly(Head1.next);
	printf("\nSecond polynome: ");
	printPoly(Head2.next);
	sum(&Head1, &Head2, &HeadSum);
	printf("\nSum: ");
	printPoly(HeadSum.next);
	multiply(&Head1, &Head2, &HeadMultiply);
	printf("\nMultiple: ");
	printPoly(HeadMultiply.next);
	
	return 0;
}
int insertFirst(position p)
{
	FILE* fp = NULL;
	fp = fopen("pol1.txt", "r");
	if (fp == NULL)
	{
		printf("File didn't open successfully\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp))
	{
		position q = NULL;
		q = (position)malloc(sizeof(struct poly));
		if (q == NULL)
		{
			printf("Unsuccessful memory alocation!\n");
			return MALLOC_ERROR;
		}
		position prev, temp;
		temp = p->next;
		prev = p;
		fscanf(fp, "%d %d", &q->coef, &q->exponent);
		while (temp != NULL && temp->exponent < q->exponent)
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL)
			q->next = temp;
		else
			q->next = NULL;
	}
	fclose(fp);
	return 0;
}
int insertSecond(position p)
{
	FILE* fp = NULL;
	fp = fopen("pol2.txt", "r");
	if (fp == NULL)
	{
		printf("File didn't open successfully\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp))
	{
		position q = NULL;
		q = (position)malloc(sizeof(struct poly));
		if (q == NULL)
		{
			printf("File didn't open successfully!\n");
			return MALLOC_ERROR;
		}
		position prev, temp;
		temp = p->next;
		prev = p;
		fscanf(fp, "%d %d", &q->coef, &q->exponent);
		while (temp != NULL && temp->exponent < q->exponent)
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = q;
		if (temp != NULL)
			q->next = temp;
		else
			q->next = NULL;
	}
	fclose(fp);

	return 0;
}
int printPoly(position p)
{
	while (p != NULL)
	{
		printf("%dx^%d ", p->coef, p->exponent);
		p = p->next;
	}
	return 0;
}

int sum(position p, position q, position r) {
	while (p->next != NULL && q->next != NULL)
	{
		position s = NULL;
		s = (position)malloc(sizeof(struct poly));
		if (s == NULL)
		{
			printf("Unsuccessful memory alocation!\n");
			return FILE_DIDNT_OPEN_ERROR;
		}
		s->next = NULL;

		if (p->next->exponent < q->next->exponent)
		{
			s->exponent = p->next->exponent;
			s->coef = p->next->coef;
			p = p->next;
		}
		else if (p->next->exponent > q->next->exponent)
		{
			s->exponent = q->next->exponent;
			s->coef = q->next->coef;
			q = q->next;
		}
		else
		{
			s->exponent = p->next->exponent;
			s->coef = (p->next->coef + q->next->coef);
			p = p->next;
			q = q->next;
		}
		r->next = s;
		r = s;
	}
	position temp = NULL;
	if (p->next == NULL)
		temp = q->next;
	else
		temp = p->next;
	while (temp != NULL)
	{
		position s = NULL;
		s = (position)malloc(sizeof(poly));
		if (s == NULL)
		{
			printf("Unsuccessful memory alocation!\n");
			return FILE_DIDNT_OPEN_ERROR;
		}
		s->next = NULL;
		s->exponent = temp->exponent;
		s->coef = temp->coef;
		r->next = s;
		r = s;
		temp = temp->next;
	}
	return 0;
}

int multiply(position p, position q, position r) {
	position first = p->next;
	position second = q->next;
	poly x;
	position s = NULL;
	s = (position)malloc(sizeof(poly));
	if (s == NULL)
	{
		printf("Unsuccessful memory alocation!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	s->next = NULL;
	x.next = s;
	while (first != NULL)
	{
		second = q->next;
		while (second != NULL)
		{
			s->coef = first->coef * second->coef;
			s->exponent = first->exponent + second->exponent;

			sum(&x, r, r);
			second = second->next;
		}
		first = first->next;
	}
	return 0;
}
