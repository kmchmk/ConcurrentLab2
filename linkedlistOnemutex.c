#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include<stdbool.h>

//Generate random numbers between 0 - 2^16-1
const int max_rand_num = 65535;

struct node {
    int data;
    struct node* next;
};

bool member(struct node* head, int value);
int insert(struct node* head,int value);
bool delete(struct node* head, int value);

struct node *head = NULL;

pthread_mutex_t mutex;

void *using_one_mutex();

int member_operations_count = 0;
int insert_operations_count = 0;
int delete_operations_count = 0;

//size of the linklist and operation count
int n;
int m;

int total_member_ops;
int total_insert_ops;
int total_delete_ops;

int main(int argc, char** argv) {

    //user must enter 7 arguements
    if (argc != 7) {
        printf("\nYou must enter 7 Arguements\n");
        exit(EXIT_FAILURE);
    }

    int thread_count = (int) strtol(argv[1], NULL, 10);

    n = (int) strtol(argv[2], NULL, 10);
    m = (int) strtol(argv[3], NULL, 10);

    float m_member = strtof(argv[4], NULL);
    float m_insert = strtof(argv[5], NULL);
    float m_delete = strtof(argv[6], NULL);

    total_member_ops = (int) (m * m_member);
    total_insert_ops = (int) (m * m_insert);
    total_delete_ops = (int) (m * m_delete);

    //creating linked list and assigning random values 
    srand(time(NULL));

    int temp_count = 0;
    while (temp_count < n) {
        int tmp_value = rand() % max_rand_num;
        temp_count += insert(head,tmp_value);
    }

    pthread_t *thread_handles;

    thread_handles = (pthread_t *) malloc(thread_count * sizeof (pthread_t));

    pthread_mutex_init(&mutex, NULL);

    int thread;
    clock_t start_time = clock();

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, (void *) using_one_mutex, NULL);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    clock_t end_time = clock();

    pthread_mutex_destroy(&mutex);


    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Time taken using one mutex is : %f \n", time_taken);
    return 0;
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

int insert(struct node* head,int value){
    struct node* tempNode = head;
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
    }
    tempNode->next = malloc(sizeof(struct node));
    tempNode->next->data = value;
    return 1;
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

// run random operations on the link list according to given fractions

void *using_one_mutex() {

    int total_countof_operations = 0;

    int countof_member_oprations_completed = 0;
    int countof_insert_oprations_completed = 0;
    int countof_delete_oprations_completed = 0;

    while (total_countof_operations < m) {

        int opr_type = rand() % 3; //operation type defines which operation should run (0 for member, 1 for insert, 2 for delete)
 
        if (opr_type == 0 && countof_member_oprations_completed == 0) {
            pthread_mutex_lock(&mutex);

            if (member_operations_count < total_member_ops) {
                int tmp_value = rand() % max_rand_num;
                member(head,tmp_value);
                member_operations_count++;
            } else {
                countof_member_oprations_completed = 1;
            }
            pthread_mutex_unlock(&mutex);

        } else if (opr_type == 1 && countof_insert_oprations_completed == 0) {

            pthread_mutex_lock(&mutex);

            if (insert_operations_count < total_insert_ops) {
                int tmp_value = rand() % max_rand_num;
                insert(head,tmp_value);
                insert_operations_count++;
            } else {
               countof_insert_oprations_completed= 1;
            }
            pthread_mutex_unlock(&mutex);

        } else if (opr_type == 2 && countof_delete_oprations_completed == 0) {
            pthread_mutex_lock(&mutex);

            if (delete_operations_count < total_delete_ops) {
                int tmp_value = rand() % max_rand_num;
                delete(head,tmp_value);
                delete_operations_count++;
            } else {
                countof_delete_oprations_completed = 1;
            }
            pthread_mutex_unlock(&mutex);

        }
        total_countof_operations = member_operations_count + insert_operations_count + delete_operations_count;
    }
    return NULL;
}

