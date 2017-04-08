#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include<stdbool.h>
#include<math.h>

//Generate random numbers between 0 - 2^16-1
const int max_rand_num = 65535;

struct node {
    int data;
    struct node* next;
};

int member(struct node* head_p ,int value);
int insert(struct node** head_pp,int value) ;
int delete(struct node** head_pp,int value) ;
//int* randomNumber(int howMany) ;

struct node *head = NULL;

pthread_rwlock_t rwlock;

void *using_RW_locks();

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
        printf("\nYou must enter 6 Arguements\n");
        exit(EXIT_FAILURE);
    }

    int thread_count;

    
   thread_count  = (int) strtol(argv[1], NULL, 10);
   

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
        temp_count += insert(&head,tmp_value);
    }

    pthread_t *thread_handles;

    thread_handles = (pthread_t *) malloc(thread_count * sizeof (pthread_t));

     pthread_rwlock_init(&rwlock, NULL);

    int thread;
    clock_t start_time = clock();

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, (void *) using_RW_locks, NULL);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    clock_t end_time = clock();

   pthread_rwlock_destroy(&rwlock);


    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Time taken using Read Write Locks is : %f \n", time_taken);
    return 0;
}

/*int* randomNumber(int howMany){
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
*/
int member(struct node* head_p ,int value) {
    struct node* curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value) {
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }

}

//insert function

int insert(struct node** head_pp,int value) {
    struct node* curr_p = *head_pp;
    struct node* pred_p = NULL;
    struct node* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = malloc(sizeof (struct node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL)
            *head_pp = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    } else {
        return 0;
    }

}


//delete function

int delete(struct node** head_pp,int value) {
    struct node* curr_p = *head_pp;
    struct node* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) {
            *head_pp = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    } else {
        return 0;
    }
}

// run random operations on the link list according to given fractions

void *using_RW_locks() {

    int total_countof_operations = 0;

    int countof_member_oprations_completed = 0;
    int countof_insert_oprations_completed = 0;
    int countof_delete_oprations_completed = 0;

    while (total_countof_operations < m) {

        int opr_type = rand() % 3; //operation type defines which operation should run (0 for member, 1 for insert, 2 for delete)
 
        if (opr_type == 0 && countof_member_oprations_completed == 0) {
            pthread_rwlock_rdlock(&rwlock);

            if (member_operations_count < total_member_ops) {
                int tmp_value = rand() % max_rand_num;
                member(head,tmp_value);
                member_operations_count++;
            } else {
                countof_member_oprations_completed = 1;
            }
             pthread_rwlock_unlock(&rwlock);

        } else if (opr_type == 1 && countof_insert_oprations_completed == 0) {

           pthread_rwlock_rdlock(&rwlock);

            if (insert_operations_count < total_insert_ops) {
                int tmp_value = rand() % max_rand_num;
                insert(&head,tmp_value);
                insert_operations_count++;
            } else {
               countof_insert_oprations_completed= 1;
            }
             pthread_rwlock_unlock(&rwlock);

        } else if (opr_type == 2 && countof_delete_oprations_completed == 0) {
            pthread_rwlock_rdlock(&rwlock);

            if (delete_operations_count < total_delete_ops) {
                int tmp_value = rand() % max_rand_num;
                delete(&head,tmp_value);
                delete_operations_count++;
            } else {
                countof_delete_oprations_completed = 1;
            }
            pthread_rwlock_unlock(&rwlock);

        }
        total_countof_operations = member_operations_count + insert_operations_count + delete_operations_count;
    }
    return NULL;
}

