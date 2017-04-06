#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
}node;

void main()
{

	struct node* head = malloc(sizeof(node));
	head->data = 12;
	struct node* temp = malloc(sizeof(node));
	temp->data = 45;
	head->next = temp;

	printf("head is ");
	printf("%d",head->next->data);
	return 0;
}
