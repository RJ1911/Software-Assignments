#include <stdio.h>
#include <stdlib.h>

struct node
{

    int data;
    struct node *link;
};

void print_nodes(struct node *head)
{
    struct node *ptr;
    ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
}

struct node *add_at_end(struct node *ptr, int d)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;
    temp->link = NULL;

    ptr->link = temp;
    return temp;
}

void add_at_position(struct node *head, int d , int position)
{  
    struct node *ptr=head;
    struct node *ptr2 = (struct node *)malloc(sizeof(struct node));
    ptr2->data = d;
    ptr2->link=NULL;

    while(position!=(position-2)){
        ptr=ptr->link;
        position--;

    }
    ptr2->link = ptr->link;
    ptr->link = ptr2;
}
int main()
{

    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->data = 23;
    head->link = NULL;

    struct node *ptr = head;

    ptr = add_at_end(ptr, 12);
    ptr = add_at_end(ptr, 35);
    ptr = add_at_end(ptr, 74);
    ptr = add_at_end(ptr, 59);

    //  struct node *head = (struct node *)malloc(sizeof(struct node));
    // head->data = 10; // 1st node
    // head->link = NULL;

    // struct node *current = (struct node *)malloc(sizeof(struct node));
    // current->data = 20; // 2nd node
    // current->link = NULL;
    // head->link = current;

    // current = (struct node *)malloc(sizeof(struct node));
    // current->data = 30; // 3rd node
    // current->link = NULL;
    // head->link->link = current;

    // current = (struct node *)malloc(sizeof(struct node));
    // current->data = 40; // 4th node
    // current->link = NULL;
    // head->link->link->link = current;

    //printf("Before adding a node at some given position\n");
    //print_nodes(head);
    int data = 10;
    int index = 4;
    add_at_position(head,data,index);
    printf("\nAfter adding node at given poisiton\n");
    print_nodes(head);

    return 0;
}