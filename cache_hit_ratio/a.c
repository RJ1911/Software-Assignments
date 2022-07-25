#include<stdio.h>
#include<math.h>
#include<stdlib.h>
struct Node{
int ref;
struct Node *next;
};

struct Node* CreateLLNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->ref=data;
    node->next=NULL;
    return node;
}
struct Node* insertAtfront(struct Node *head,int data){
    struct Node *tmp=head;
    head=CreateLLNode(data);
    head->next=tmp;
    return head;
}
struct Node* deleteNode(struct Node* head,int data){

struct Node *tmp=head, *targetnode;
if(head->ref==data){
   targetnode=head;
   head=head->next;
   free(targetnode);
   return head; 
}
while(tmp){
    if(tmp->next->ref==data){
targetnode=tmp->next;
tmp->next=targetnode->next;
free(targetnode);
return head;
    }
    else
    tmp=tmp->next;
}
}
struct Node* insertAtend(struct Node *head,int data){
    if(!head){
        head=CreateLLNode(data);
        return head;
    }
    struct Node *tmp=head;
    while(tmp->next)
    tmp=tmp->next;
    tmp->next=CreateLLNode(data);
    return head;
}
struct Node* deleteAtfront(struct Node *head){
    struct Node *tmp=head;
    head=head->next;
    free(tmp);
    return head;
}
void showLL(struct Node *head){
    while(head){
    printf("%d ",head->ref);
head=head->next;
    }
    printf("\n");
}
struct Node* replaceAtIndex(struct Node *head,int data,int index){
    struct Node *tmp=head;
    while(index--)
    tmp=tmp->next;
    tmp->ref=data;
    return head;
}
int searchItem(struct Node *head,int data){
    while(head){
        if(head->ref==data)
        return 1;
        else
        head=head->next;
    }
    return 0;
}

void FIFO(int arr[],int number_of_block,int number_of_ref){
    int curr_LLsize=0,hit_count=0,oldRefIndex=0;
    struct Node *head=NULL;
for(int i=0;i<number_of_ref;i++){
     showLL(head);
    //ref is already present
if(searchItem(head,arr[i])){
    printf("%d -Hit\n",arr[i]);
    hit_count++;
}
//ref not found and cache is full
else if(curr_LLsize==number_of_block){
head=replaceAtIndex(head,arr[i],oldRefIndex);
printf("%d -Miss\n",arr[i]);
//set the index to next oldest ref
oldRefIndex = (oldRefIndex + 1)%number_of_block;
}
//ref is not found and cache is not full
else{
head=insertAtend(head,arr[i]);
printf("%d -Miss\n",arr[i]);
curr_LLsize++;
}
}
showLL(head);
printf("Total miss: %d\n", number_of_ref-hit_count);
printf("Total hit: %d\n",hit_count);
printf("Hit ratio: %.1f\n",(hit_count*1.0)/(number_of_ref*1.0));
}
void LRU(int arr[],int number_of_block,int number_of_ref){
  /* for(int i=0;i<number_of_ref;i++)
   printf("%d ",arr[i]);*/
int currentLLsize=0,hit_count=0;
struct Node *head=NULL;
for(int i=0;i<number_of_ref;i++){
    showLL(head);
//ref found and cache is full
if(searchItem(head,arr[i])){
    printf("%d -Hit\n",arr[i]);
    head=deleteNode(head,arr[i]);
    head=insertAtend(head,arr[i]);
    hit_count++;
}
//ref not found and cache is full
else if(currentLLsize==number_of_block){
head=deleteAtfront(head);
head=insertAtend(head,arr[i]);
printf("%d -Miss\n",arr[i]);
}
//ref not found and cache is not full
else{
head=insertAtend(head,arr[i]);
currentLLsize++;
printf("%d -Miss\n",arr[i]);
}
}
 showLL(head);
printf("Total hit: %d\n",hit_count);
printf("Total Miss: %d\n",number_of_ref-hit_count);
printf("Hit ratio: %.1f",(hit_count*1.0)/(number_of_ref*1.0));
}
int stringToInt(char *str){
    int length=0,num=0,x=0;
    for(int i=0;str[i]!='\0';i++)
    length++;
    for(int i=length-1;i>=0;i--){
    num += (str[i] -48)*pow(10,x);
    x++;
    }
    return num;
}
int main(int argc,char *argv[]){
int NumOfCacheBlock=stringToInt(argv[1]);
const int NumOfRef=argc-4;
int ref[NumOfRef];
char algorithm=argv[3][0];
for(int i=0;i<NumOfRef;i++)
ref[i]=stringToInt(argv[i+4]);
if(algorithm=='L')
LRU(ref,NumOfCacheBlock,NumOfRef);
else
FIFO(ref,NumOfCacheBlock,NumOfRef);
return 0;
}
