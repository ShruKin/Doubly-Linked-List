#include <stdio.h>
#include <malloc.h>

struct node{
    int data;
    struct node *prev, *next;
};

struct DLL{
    struct node *head, *tail;
};

void print_list(struct DLL d)
{
    struct node *first = d.head, *last = d.tail;

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return;
    }

    printf("First-to-Last: ");
    while(first->next != NULL){   //  iterating throughout the list(till NULL is reached)
        printf("%d -> ", first->data);  //  printing current node
        first = first->next;    //  shifting the temporary node to the next one
    }
    printf("%d -> ", first->data);  //  printing the last node
    printf("NULL\n");

    printf("Last-to-First: ");
    while(last->prev != NULL){   //  iterating throughout the list(till NULL is reached)
        printf("%d -> ", last->data);  //  printing current node
        last = last->prev;    //  shifting the temporary node to the previous one
    }
    printf("%d -> ", last->data);  //  printing the first node
    printf("NULL\n");
}

struct DLL insert_node_begin(struct DLL d, int data)
{
    // struct node *first = d.head, *last = d.tail;

    if(d.head == NULL && d.tail == NULL){ //  if list is initially empty
        struct node* newNode = (struct node *) malloc(sizeof(struct node));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        d.head = newNode;
        d.tail = newNode;
        return d;
    }

    struct node* newNode = (struct node *) malloc(sizeof(struct node));
    if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }
    else{
        newNode->data = data;
        newNode->next = d.head;
        d.head->prev = newNode;
        d.head = newNode;
        d.head->prev = NULL;
    }

    return d;
} 

struct DLL insert_node_end(struct DLL d, int data)
{
    // struct node *first = d.head, *last = d.tail;

    if(d.head == NULL && d.tail == NULL){ //  if list is initially empty
        struct node* newNode = (struct node *) malloc(sizeof(struct node));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        d.head = newNode;
        d.tail = newNode;
        return d;
    }

    struct node* newNode = (struct node *) malloc(sizeof(struct node));
    if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }
    else{
        newNode->data = data;
        newNode->prev = d.tail;
        d.tail->next = newNode;
        d.tail = newNode;
        d.tail->next = NULL;
    }

    return d;
} 

/*  insert a node at any passed point (as param) in the list */
struct DLL insert_node(struct DLL d, int data, int idx){     //  idx is index of the insertion point, not postion! ;)
    if(d.head == NULL && d.tail == NULL){ //  if list is initially empty
        struct node* newNode = (struct node *) malloc(sizeof(struct node));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        d.head = newNode;
        d.tail = newNode;
        return d;
    }

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    // struct node *ptr = head;

    if(idx < 0){
        printf("<Index Overflow> Index cannot be negative, Insertion Failed\n");
        return d;
    }

    if(idx == 0){    //  if idx is zero, insert at the beginning
        newNode->data = data;
        newNode->next = d.head;
        d.head->prev = newNode;
        d.head = newNode;
        d.head->prev = NULL;
        return d;
    }
    
    if (newNode == NULL) {
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }
    else {
        struct node *ptr = d.head;
        for(int i = 0; i < idx-1; i++)
        {   //  interating till the required position to insert
            ptr = ptr->next;
            if(ptr == NULL){    //  if end of the list is already reached
                printf("<Index Overflow> Index beyond range, Insertion Failed!\n");
                return d;
            }
        }
        newNode->data = data;

        /*  inserting the node in between the current temporary node and the next one   */
        newNode->next = ptr->next; // Connect new node with n+1th node
        newNode->prev = ptr;
        if (newNode->next != NULL) 
            newNode->next->prev = newNode; 
        else if(newNode->next == NULL)
            d.tail = newNode;
        ptr->next = newNode;
    }
    return d;
}