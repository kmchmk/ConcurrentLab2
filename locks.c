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
    head = NULL;//malloc(sizeof(node));
}


bool member(int value)
{
    //printf("member\n");
    struct node* tempNode = head;
    while(tempNode != NULL)
    {
        if(tempNode->data == value)
        {
            //printf("\n%d is a member\n",value);
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
    //printf("insert\n");
    //printf("start-b-%d\n",value);
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
            //printf("-%d\n",tempNode);
        }
        //printf("x");
        tempNode->next = malloc(sizeof(node));
        //printf("y");
        tempNode->next->data = value;
        tempNode->next->next = NULL;
        //printf("z");
        insertingNumberIndex = insertingNumberIndex + 1;
    }

}


void delete(int value)
{
    //printf("delete\n");
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
        //printf("%d ", randomArray[i]);
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
    int numberOfInsert = m * m_insert; //this is global
    int numberOfDelete = m * m_delete;

    printf("\nNumber of member : %d\n",numberOfMember);
    printf("Number of insert : %d\n",numberOfInsert);
    printf("Number of delete : %d\n",numberOfDelete);

    int m_real = numberOfMember + numberOfInsert + numberOfDelete;

    if(1 != (int)(m_member + m_insert + m_delete))
    {
        printf("\nSum of fractions should be 1.\n");
    }

    //printf("%f\n",m_member + m_insert + m_delete);


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

    for(int i =0; i < m_real; i++)
    {
        //printf("%d ", functionArray[i]);
    }

    return functionArray;
}


void* threadFunction(void* arg)
{
    int *threadNumber_ptr = (int*)arg;
    int threadNumber = *threadNumber_ptr;
    //printf("\nthreadNumber is - %d.\n",threadNumber);
    int numberOfprocessesPerThread = m/numberOfThreads;
    //printf("\nprocesses per thread - %d\n", numberOfprocessesPerThread);
    int func;
    for(int i = 0; i < numberOfprocessesPerThread; i++)
    {
        func = randomFunctionArray[(numberOfprocessesPerThread * threadNumber) + i];
        if(func == 0)
        {
            //pthread_mutex_lock(&lock);
            pthread_rwlock_rdlock(&lock);
            //printf("tid - %d member\n",threadNumber);
            member(rand() % max);
            pthread_rwlock_unlock(&lock);
            //pthread_mutex_unlock(&lock);
        }
        else if(func == 1)
        {
            pthread_rwlock_wrlock(&lock);
            ///printf("tid - %d insert\n",threadNumber);
            insert(insertingNumbers[insertingNumberIndex]);
            pthread_rwlock_unlock(&lock);
        }
        else if(func == 2)
        {
            pthread_rwlock_wrlock(&lock);
            //printf("tid - %d delete\n",threadNumber);
            delete(randomNumberArray[rand() % n]);
            pthread_rwlock_unlock(&lock);
        }
    }
    //printf("\nthread %d finished\n", threadNumber);
    pthread_exit(0);
}
















int main()
{
    /*long long limit = 1000000;
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, sum_runner1, &limit);
    pthread_create(&tid2, NULL, sum_runner2, &limit);
    for(long long i = 1; i <= limit; i++)
    {
        sum2 = sum2  + i;
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("sum is %lld\n", sum1);
    printf("sum is %lld\n", 2 * sum2);
    printf("sum is %lld\n", sum3);
    */









    printf("Input \"n\": ");
    n = 10000;//scanf("%d",&n);
    printf("Input \"m\": ");
    m = 100000;//scanf("%d",&m);
    printf("\n");

    float m_member, m_insert, m_delete;
    printf("Enter fractions:\n");
    printf("\tMember: ");
    m_member = 1;//scanf("%f",&m_member);
    printf("\tInsert: ");
    m_insert = 0;//scanf("%f",&m_insert);
    printf("\tDelete: ");
    m_delete = 0;//scanf("%f",&m_delete);

    printf("Input \"Number of threads\": ");
    scanf("%d",&numberOfThreads);

    printf("\n%d",numberOfThreads);

    create();//create head
    randomNumberArray = randomNumber(n, m * m_insert);

    for(int i = 0; i < n; i++)
    {
        insert(randomNumberArray[i]); //populate the array
    }
    insertingNumberIndex = 0;//set insertingNumberIndex to 0 for "insert operation"
    randomFunctionArray = randomFunction(m, m_member, m_insert, m_delete);

    /*printf("\nrandomFunctionArray is - ");
    for(int i = 0; i < m; i++)
    {
        printf("%d ", randomFunctionArray[i]);
    }
    printf("\n");
    */

    //create m thread ids
    pthread_t* ids = malloc(numberOfThreads * sizeof(pthread_t));

    srand(time(NULL));
    clock_t start, end;
    double processTime;
    printf("\nProcess started.\n");
    int tempThreadIdArray[numberOfThreads];//= malloc(numberOfThreads * sizeof(int));
    start = clock();//time starts here
    for(int i = 0; i < numberOfThreads; i++)
    {
        tempThreadIdArray[i] = i;
        pthread_create(&ids[i], NULL, threadFunction, &tempThreadIdArray[i]);
        //member(rand() % max);

    }
    for(int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(ids[i],NULL);
    }
    end = clock();//time ends here
    printf("\nProcess finished.");
    printf("\nElapsed time (rw locks) = %f millisecs.", 1000 * ((double) (end - start)) / CLOCKS_PER_SEC);


    return 0;
}

