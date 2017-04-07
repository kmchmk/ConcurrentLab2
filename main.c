#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>

struct node{
	int data;
	struct node* next;
}node;

struct node* create(){
    struct node* head = NULL;
    return head;
}

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


struct node* delete(struct node* head, int value){
    if(head->data == value){
        return head->next;
    }
    else{
        struct node* previouseTempNode = head;
        struct node* middleTempNode = previouseTempNode->next;
        while(middleTempNode != NULL){
            struct node* nextTempNode = middleTempNode->next;
            if(middleTempNode->data == value){
                previouseTempNode->next = nextTempNode;
                return head;
            }
            if(nextTempNode == NULL){
                return head;
            }
            previouseTempNode = previouseTempNode->next;
            middleTempNode = previouseTempNode->next;
            nextTempNode = middleTempNode->next;
        }
    }
    return head;
}

int* randomNumber(int howMany){
    int max = pow(2,16);
    int numberArray[max];
    for (int i = 0; i < max; i++){
        numberArray[i] = i;
    }
    srand(time(NULL));
    for (int i = 0; i < max; i++){
        int randNum = rand()%(max);
        int temp = numberArray[i];
        numberArray[i] = numberArray[randNum];
        numberArray[randNum] = temp;
    }

    int* randomArray = malloc(howMany);

    for(int i =0; i < howMany; i++){
        randomArray[i] = numberArray[i];
        //printf("%d ", randomArray[i]);
    }

    return randomArray;

}

void main(){

    int n, m;
    float m_member, m_insert, m_delete;
    printf("Input \"n\": ");
    scanf("%d",&n);
    printf("Input \"m\": ");
    scanf("%d",&m);
    printf("Enter fractions:\n");
    printf("\tMember: ");
    scanf("%f",&m_member);
    printf("\tInsert: ");
    scanf("%f",&m_insert);
    printf("\tDelete: ");
    scanf("%f",&m_delete);

    int numberOfMember = m * m_member;
    int numberOfInsert = m * m_insert;
    int numberOfDelete = m * m_delete;

    printf("%d\n",numberOfMember);
    printf("%d\n",numberOfInsert);
    printf("%d\n",numberOfDelete);

    if(1 != (int)(m_member + m_insert + m_delete)){
        printf("\nSum of fractions should be 1.\n");
        return;
    }

    //printf("%f\n",m_member + m_insert + m_delete);
    int *randomArray = randomNumber(n);

    int functionArray[m];




    struct node* head = create();
    for(int i = 0; i < n; i++){
        printf("%d ", randomArray[i]);
    }

	//printf("head value is ");
	//printf("%d",head->next->next->data);
}
