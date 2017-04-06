
 
#include <stdio.h>
#include <stdlib.h>



  typedef struct node

    {
        int num;
        struct node *ptr;

    }node_t;

void main()
{
   
    
int i=0;
node_t *head,*temp =NULL;

for (i=0;i<5;i++){
if(i==0){
createLinkedList(i,head);
temp=head;
}
else{
createLinkedList(i,temp);
temp= temp->ptr; ;
}
}

printf("\nsameera\n");


}

 void createLinkedList(int i, node_t *hd){
if(i==0){
hd=malloc(sizeof(node_t));
hd->num=i ;
}
else{
      hd->ptr=malloc(sizeof(node_t)) ;
      hd->num=i ;
}
}

