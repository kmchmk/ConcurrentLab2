#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<pthread.h>


const int max = pow(2,16);
int *insertingNumbers;
pthread_mutex_t mutex;
struct node* head;
int *randomNumberArray;
int *randomFunctionArray;
int numberOfThreads;
int insertingNumberIndex = 0;
int n,m;
pthread_rwlock_t lock;

struct node
{
    int data;
    struct node* next;
} node;

void create()
{
    head = NULL;
}


bool member(int value)
{
    struct node* tempNode = head;
    while(tempNode != NULL)
    {
        if(tempNode->data == value)
        {
            return true;
        }
        else
        {
            tempNode = tempNode->next;
        }
    }
    return false;
}

void insert(int value)
{
    if(head == NULL)
    {
        head = malloc(sizeof(node));
        head->data = value;
        head->next = NULL;
        insertingNumberIndex = insertingNumberIndex + 1;
    }
    else
    {
        struct node* tempNode = head;
        while(tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = malloc(sizeof(node));
        tempNode->next->data = value;
        tempNode->next->next = NULL;
        insertingNumberIndex = insertingNumberIndex + 1;
    }
}

void delete(int value)
{
    if(head->data == value)
    {
        head = head->next;
    }
    else
    {
        struct node* previouseTempNode = head;
        struct node* middleTempNode = previouseTempNode->next;
        while(middleTempNode != NULL)
        {
            struct node* nextTempNode = middleTempNode->next;
            if(middleTempNode->data == value)
            {
                previouseTempNode->next = nextTempNode;
                return;
            }
            if(nextTempNode == NULL)
            {
                return;
            }
            previouseTempNode = previouseTempNode->next;
            middleTempNode = previouseTempNode->next;
            nextTempNode = middleTempNode->next;
        }
    }
    return;
}

int* randomNumber(int howMany, int numberOfInsert)
{
    int *numberArray = malloc(max * sizeof(int));
    for (int i = 0; i < max; i++)
    {
        numberArray[i] = i;
    }
    srand(time(NULL));
    for (int i = 0; i < max; i++)
    {
        int randNum = rand()%(max);
        int temp = numberArray[i];
        numberArray[i] = numberArray[randNum];
        numberArray[randNum] = temp;
    }

    int* randomArray = malloc(howMany * sizeof(int));

    for(int i =0; i < howMany; i++)
    {
        randomArray[i] = numberArray[i];
    }

    insertingNumbers = malloc(numberOfInsert * sizeof(int));

    for(int i = 0; i < numberOfInsert; i++)
    {
        insertingNumbers[i] = numberArray[howMany + i];
    }
    free(numberArray);
    return randomArray;

}

int* randomFunction(int m, float m_member, float m_insert, float m_delete)
{

    int numberOfMember = m * m_member;
    int numberOfInsert = m * m_insert;
    int numberOfDelete = m * m_delete;

    printf("\nNumber of member operations : %d\n",numberOfMember);
    printf("Number of insert operations : %d\n",numberOfInsert);
    printf("Number of delete operations : %d\n",numberOfDelete);

    int m_real = numberOfMember + numberOfInsert + numberOfDelete;

    if(1 != (int)(m_member + m_insert + m_delete))
    {
        printf("\nSum of fractions should be 1.\n");
    }

    int* functionArray = malloc(m_real * sizeof(int));
    for (int i = 0; i < numberOfMember; i++)
    {
        functionArray[i] = 0;// 0 = member
    }
    for (int i = 0; i < numberOfInsert; i++)
    {
        functionArray[numberOfMember + i] = 1;// 1 = insert
    }
    for (int i = 0; i < numberOfDelete; i++)
    {
        functionArray[numberOfMember + numberOfInsert + i] = 2;// 2 = delete
    }
    srand(time(NULL));
    for(int i = 0; i < m_real; i++)
    {
        int randNum = rand()%(m_real);
        int temp = functionArray[i];
        functionArray[i] = functionArray[randNum];
        functionArray[randNum] = temp;
    }

    return functionArray;
}


void* threadFunction(void* arg)
{
    int *threadNumber_ptr = (int*)arg;
    int threadNumber = *threadNumber_ptr;
    int numberOfprocessesPerThread = m/numberOfThreads;
    int func;
    for(int i = 0; i < numberOfprocessesPerThread; i++)
    {
        func = randomFunctionArray[(numberOfprocessesPerThread * threadNumber) + i];
        if(func == 0)
        {
            pthread_rwlock_rdlock(&lock);
            member(rand() % max);
            pthread_rwlock_unlock(&lock);
        }
        else if(func == 1)
        {
            pthread_rwlock_wrlock(&lock);
            insert(insertingNumbers[insertingNumberIndex]);
            pthread_rwlock_unlock(&lock);
        }
        else if(func == 2)
        {
            pthread_rwlock_wrlock(&lock);
            delete(randomNumberArray[rand() % n]);
            pthread_rwlock_unlock(&lock);
        }
    }
    pthread_exit(0);
}

int main()
{
    printf("Input \"n\": ");
    n = 1000;
    printf("%d\n",n);
    //scanf("%d",&n);
    printf("Input \"m\": ");
    m = 10000;
    printf("%d",m);
    //scanf("%d",&m);
    printf("\n");

    float m_member, m_insert, m_delete;
    printf("Enter fractions:\n");
    printf("\tMember: ");
    m_member = 0.99;
    printf("%f\n",m_member);
    //scanf("%f",&m_member);
    printf("\tInsert: ");
    m_insert = 0.005;
    printf("%f\n",m_insert);
    //scanf("%f",&m_insert);
    printf("\tDelete: ");
    m_delete = 0.005;
    printf("%f\n",m_delete);
    //scanf("%f",&m_delete);

    printf("Input \"Number of threads\": ");
    numberOfThreads = 2;
    printf("%d\n",numberOfThreads);
    //scanf("%d",&numberOfThreads);
    create();//create head
    randomNumberArray = randomNumber(n, m * m_insert);

    for(int i = 0; i < n; i++)
    {
        insert(randomNumberArray[i]); //populate the array
    }
    insertingNumberIndex = 0;//set insertingNumberIndex to 0 for "insert operation"
    randomFunctionArray = randomFunction(m, m_member, m_insert, m_delete);

    //create m thread ids
    pthread_t* ids = malloc(numberOfThreads * sizeof(pthread_t));

    srand(time(NULL));
    clock_t start, end;
    double processTime;
    printf("\nProcess started.");
    int tempThreadIdArray[numberOfThreads];
    start = clock();//time starts here
    for(int i = 0; i < numberOfThreads; i++)
    {
        tempThreadIdArray[i] = i;
        pthread_create(&ids[i], NULL, threadFunction, &tempThreadIdArray[i]);
    }
    for(int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(ids[i],NULL);
    }
    end = clock();//time ends here
    printf("\nProcess finished.");
    double elapsedTime = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed time (locks_case_1_thread_2) = %f millisecs.\n\n", elapsedTime);

    FILE *f = fopen("locks_case_1_thread_2.txt", "a");
    //fprintf(f, "n = %d, m = %d, m_member = %f, m_insert = %f, m_delete = %f\n", n, m, m_member, m_insert, m_delete);
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%f\n", elapsedTime);
    fclose(f);

    free(randomNumberArray);
    free(randomFunctionArray);

    return 0;
}
