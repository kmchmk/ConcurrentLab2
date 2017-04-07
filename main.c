#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>

static int max = pow(2,16);
int *insertingNumbers;

struct node{
	int data;
	struct node* next;
}node;

struct node* create(){
    struct node* head = NULL;//malloc(sizeof(node));
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

struct node* insert(struct node* head,int value){
    if(head == NULL){
        head = malloc(sizeof(node));
        head->data = value;
        return head;
    }
    else
    {
        struct node* tempNode = head;
        while(tempNode->next != NULL){
            tempNode = tempNode->next;
        }
        tempNode->next = malloc(sizeof(node));
        tempNode->next->data = value;
        return head;
    }

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

int* randomNumber(int howMany, int numberOfInsert){
    int *numberArray = malloc(max * sizeof(int));
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

    int* randomArray = malloc(howMany * sizeof(int));

    for(int i =0; i < howMany; i++){
        randomArray[i] = numberArray[i];
        //printf("%d ", randomArray[i]);
    }

    insertingNumbers = malloc(numberOfInsert * sizeof(int));

    for(int i = 0; i < numberOfInsert; i++){
        insertingNumbers[i] = numberArray[howMany + i];
    }
    free(numberArray);
    return randomArray;

}

int* randomFunction(int m, float m_member, float m_insert, float m_delete){

    int numberOfMember = m * m_member;
    int numberOfInsert = m * m_insert; //this is global
    int numberOfDelete = m * m_delete;

    printf("%d\n",numberOfMember);
    printf("%d\n",numberOfInsert);
    printf("%d\n",numberOfDelete);

    int m_real = numberOfMember + numberOfInsert + numberOfDelete;

    if(1 != (int)(m_member + m_insert + m_delete)){
        printf("\nSum of fractions should be 1.\n");
    }

    //printf("%f\n",m_member + m_insert + m_delete);


    int* functionArray = malloc(m_real);
    for (int i = 0; i < numberOfMember; i++){
        functionArray[i] = 0;// 0 = member
    }
    for (int i = 0; i < numberOfInsert; i++){
        functionArray[numberOfMember + i] = 1;// 1 = insert
    }
    for (int i = 0; i < numberOfDelete; i++){
        functionArray[numberOfMember + numberOfInsert + i] = 2;// 2 = delete
    }
    srand(time(NULL));
    for(int i = 0; i < m_real; i++){
        int randNum = rand()%(m_real);
        int temp = functionArray[i];
        functionArray[i] = functionArray[randNum];
        functionArray[randNum] = temp;
    }

    for(int i =0; i < m_real; i++){
        //printf("%d ", functionArray[i]);
    }

    return functionArray;
}


void main(){
    int n, m;
    printf("Input \"n\": ");
    n = 100;//scanf("%d",&n);
    printf("Input \"m\": ");
    m = 100;//scanf("%d",&m);
    printf("\n");

    float m_member, m_insert, m_delete;
    printf("Enter fractions:\n");
    printf("\tMember: ");
    m_member = 0.4;//scanf("%f",&m_member);
    printf("\tInsert: ");
    m_insert = 0.3;//scanf("%f",&m_insert);
    printf("\tDelete: ");
    m_delete = 0.3;//scanf("%f",&m_delete);

    struct node* head = create();

    //int *restOfRandomNumbers;// = malloc(sizeof(int) * (max-n));
    int *randomNumberArray = randomNumber(n, m * m_insert);

    for(int i = 0; i<10; i++){
        head = insert(head,randomNumberArray[i]); //populate the array
    }

    int *randomFunctionArray = randomFunction(m, m_member, m_insert, m_delete);

    int func;
    int j = 0;
    srand(time(NULL));
    //time starts here
    for(int i = 0; i < m; i++){
        func = randomFunctionArray[i];
        if(func == 0){
            member(head, rand() % max);
        }
        else if(func == 1){
            printf("%d ",insertingNumbers[j]);
            //head = insert(head, 10);//insertingNumbers[j]);
            j++;

        }
        else if(func == 2){
            head = delete(head,randomNumberArray[rand() % n]);
        }
    }
    //insert(head,insertingNumbers[0]);



    //time ends here

    //printf("\nvalue is %d\n", head->data);












    /*int n, m;


    int *numberArray = randomNumber(n);
    //int *functionArray = randomFunction(m);

    struct node* head = create();
    insert(head,12);
    for(int i = 0; i < n-1; i++){
        //insert(head,3);
        //insert(head,numberArray[i]);
    }
    printf("\nLinked List\n");
    //printf("%d",head->next->data);
    //printf("\nnumberArray\n");
    for(int i = 0; i < n; i++){
        //printf("%d ", numberArray[i]);
    }

	//printf("head value is ");
	//printf("%d",head->next->next->data);
	*/
}
