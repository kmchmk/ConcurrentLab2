#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

struct node{
	int data;
	struct node* next;
}node;

bool member(struct node* head, int value){
    struct node* tempNode = head;
    while(tempNode->next != NULL){
        if(tempNode->data == value){
            return true;
        }
        else{
            tempNode = tempNode->next;
        }
    }
    return false;
}

void insert(struct node* head,int value){
    struct node* tempNode = head;
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
    }
    tempNode->next = malloc(sizeof(node));
    tempNode->next->data = value;
}



void main(){

	struct node* head = malloc(sizeof(node));
	head->data = 11;
    insert(head, 34);
    insert(head,23);

    if(member(head,21)){
        printf("member\n");
    }
    else{
        printf("not member\n");
    }

	printf("head value is ");
	printf("%d",head->next->next->data);
}
