#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

struct node{
	int data;
	struct node* next;
}node;

bool member(struct node* head, int value){
    struct node* tempNode = head;
    while(tempNode != NULL){
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


bool delete(struct node* head, int value){
    struct node* previouseTempNode = head;
    struct node* middleTempNode = previouseTempNode->next;
    struct node* nextTempNode = middleTempNode->next;
    while(middleTempNode != NULL){
        previouseTempNode = previouseTempNode->next;
        middleTempNode = previouseTempNode->next;
        nextTempNode = middleTempNode->next;
        if(middleTempNode->data == value){
            previouseTempNode->next = nextTempNode;
            return true;
        }
    }
    return false;
}


void main(){

	struct node* head = malloc(sizeof(node));
	head->data = 11;
    insert(head,22);
    insert(head,33);
    insert(head,44);
    insert(head,55);
    insert(head,66);
    insert(head,77);
    insert(head,88);
    insert(head,99);
    if(member(head,66)){
        printf("member\n");
    }
    else{
        printf("not member\n");
    }

    delete(head,64);

    if(member(head,66)){
        printf("member\n");
    }
    else{
        printf("not member\n");
    }

	//printf("head value is ");
	//printf("%d",head->next->next->data);
}
