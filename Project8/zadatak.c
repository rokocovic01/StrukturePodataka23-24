#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS (1)

#include<stdlib.h>
#include<stdio.h>

typedef struct cvor* position;
typedef struct cvor {
	int number;
	position l;
	position d;
}cvor;

position insert(position p, position q);
void inorder(position p);
void preorder(position p);
void postorder(position p);
position delete(position p, int br);
position findmax(position p);
position findmin(position p);
position find(position p, int br);

int main() {
	position root = NULL;
	int choice;
	do {
		printf("\nOdaberi:\n");
		printf("1 - insert\n");
		printf("2 - Ispis preorder\n");
		printf("3 - Ispis inorder\n");
		printf("4 - Ispis postorder \n");
		printf("5 - Brisanje elementa\n");
		printf("6 - Trazenje elementa\n");
		printf("7 - Izlaz\n");
		scanf(" %d", &choice);
		switch (choice) {
		case 1:
			printf("Unesite new element:");
			int new_num;
			scanf(" %d", &new_num);
			position new = (position)malloc(sizeof(cvor));
			new->number = new_num;
			new->l = NULL;
			new->d = NULL;
			root = insert(root, new);
			break;
		case 2:
			printf("Preorder ispis je: \n");
			preorder(root);
			break;
		case 3:
			printf("Inorder ispis je: \n");
			inorder(root);
			break;
		case 4:
			printf("Postorder ispis je: \n");
			postorder(root);
			break;
		case 5:
			printf("Unesite element koji zelite izbrisati: ");
			int delete_number;
			scanf(" %d", &delete_number);
			root = delete(root, delete_number);
			break;
		case 6:
			printf("Unesite element koji zelite pronaci: ");
			int lf_number; position temp;
			scanf(" %d", &lf_number);
			temp = find(root, lf_number);
			if (temp)
				printf("Element %d nalazi se u stablu na adresi %d\n", temp->number, temp);
			else
				printf("Element koji ste unijeli ne postoji u stablu.");
			break;
		case 7:
			break;
		default:
			printf("Pogresan insert!");
		}
	} while (choice != 7);

	return 0;
}

position insert(position p, position q) {
	if (p == NULL)
		return q;
	if (p->number < q->number){
		p->d = insert(p->d, q);
	}
	else if (p->number > q->number){
		p->l = insert(p->l, q);
	}
	else
		free(q);
	return p;
}

void inorder(position p){
	if (p == NULL)
		return NULL;
	else {
		inorder(p->l);
		printf(" %d", p->number);
		inorder(p->d);
	}
}

void preorder(position p){
	if (p == NULL)
		return NULL;
	else {
		printf(" %d", p->number);
		preorder(p->l);
		preorder(p->d);
	}
}

void postorder(position p){
	if (p == NULL)
		return NULL;
	else {
		postorder(p->l);
		postorder(p->d);
		printf(" %d", p->number);
	}
}

position delete(position p, int br){
	if (p == NULL) {
		printf("Element koji zelite izbrisati ne postoji u stablu.");
		return NULL;
	}
	if (p->number < br)
		p->d = delete(p->d, br);
	else if (p->number > br)
		p->l = delete(p->l, br);
	else {
		if (p->l){
			position temp = findmax(p->l);
			p->number = temp->number;
			p->l = delete(p->l, temp->number);
		}
		else if (p->d){
			position temp = findmin(p->d);
			p->number = temp->number;
			p->d = delete(p->d, temp->number);
		}
		else{
			free(p);
			return NULL;
		}
	}
	return p;
}

position findmax(position p){
	while (p->d)
		p = p->d;
	return p;
}

position findmin(position p){
	while (p->l)
		p = p->l;
	return p;
}

position find(position p, int br) {
	while (p != NULL && p->number != br){
		if (p->number < br)
			p = p->d;
		else
			p = p->l;
	}
	return p;
}
