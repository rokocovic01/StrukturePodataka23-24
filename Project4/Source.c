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
	
	insertFirst(&Head1);
	insertSecond(&Head2);
	printf("First polynome: ");
	printPoly(Head1.next);
	printf("\nSecond polynome: ");
	printPoly(Head2.next);
	
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
