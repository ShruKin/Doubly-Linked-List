#include <stdio.h>
#include <malloc.h>

struct node{
    int data;
    struct node *prev, *next;
};

struct DLL{
    struct node *head, *tail;
};

void print_list(struct DLL d);
struct DLL insert_node_end(struct DLL d, int data);
struct DLL insert_node_begin(struct DLL d, int data);
struct DLL insert_node(struct DLL d, int data, int idx);
struct DLL insert_node_sorted(struct DLL d, int data);
struct DLL create_DLL(struct DLL d);
struct DLL create_sorted_DLL(struct DLL d);
struct DLL move_node(struct DLL d, int movefrom_idx, int moveto_idx);

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
    if (newNode == NULL) {
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }

    if(idx < 0){
        printf("<Index Overflow> Index cannot be negative, Insertion Failed\n");
        return d;
    }

    else if(idx == 0){    //  if idx is zero, insert at the beginning
        newNode->data = data;
        newNode->next = d.head;
        d.head->prev = newNode;
        d.head = newNode;
        d.head->prev = NULL;
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

struct DLL insert_node_sorted(struct DLL d, int data){
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
    if (newNode == NULL) {
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }

    if(data <= d.head->data){
        newNode->data = data;
        newNode->next = d.head;
        d.head->prev = newNode;
        d.head = newNode;
        d.head->prev = NULL;
        return d;
    }

    else {
        struct node *ptr = d.head;
        while(ptr->next != NULL && data >= ptr->next->data)
            ptr = ptr->next;
        
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

struct DLL create_DLL(struct DLL d)
{
	int num;
	printf("Enter -1 to end. \n");
	printf("Enter data : ");
	scanf("%d",&num);
	while(num != -1)
	{
        struct node* newNode = (struct node *) malloc(sizeof(struct node)), *ptr;
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
		// newNode->data=num;
		if(d.head == NULL && d.tail == NULL)
		{
			newNode->data = num;
            newNode->prev = newNode->next = NULL;
            d.head = newNode;
            d.tail = newNode;
		}
		else
		{
			newNode->data = num;
            newNode->prev = d.tail;
            d.tail->next = newNode;
            d.tail = newNode;
            d.tail->next = NULL;
		}

		printf("Enter data : ");
		scanf("%d",&num);		
	}
	return d;	
}

struct DLL create_sorted_DLL(struct DLL d)
{
	int num;
	printf("Enter -1 to end. \n");
	printf("Enter data : ");
	scanf("%d",&num);
	while(num != -1)
	{
        struct node* newNode = (struct node *) malloc(sizeof(struct node)), *ptr;
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
		// newNode->data=num;
		if(d.head == NULL && d.tail == NULL)
		{
			newNode->data = num;
            newNode->prev = newNode->next = NULL;
            d.head = newNode;
            d.tail = newNode;
		}
		else
		{
			if(num <= d.head->data){
                newNode->data = num;
                newNode->next = d.head;
                d.head->prev = newNode;
                d.head = newNode;
                d.head->prev = NULL;
            }

            else {
                struct node *ptr = d.head;
                while(ptr->next != NULL && num >= ptr->next->data)
                    ptr = ptr->next;
                
                newNode->data = num;

                /*  inserting the node in between the current temporary node and the next one   */
                newNode->next = ptr->next; // Connect new node with n+1th node
                newNode->prev = ptr;
                if (newNode->next != NULL) 
                    newNode->next->prev = newNode; 
                else if(newNode->next == NULL)
                    d.tail = newNode;
                ptr->next = newNode;
            }
		}

		printf("Enter data : ");
		scanf("%d",&num);		
	}
	return d;	
}

struct DLL move_node(struct DLL d, int movefrom_idx, int moveto_idx)    //  pass index (0, 1, 2, ... )
{
    if(d.head == NULL && d.tail == NULL)
        return d;

    if(movefrom_idx < 0 || moveto_idx < 0){
        printf("<Index Overflow> Index cannot be negative, Movement Failed\n");
        return d;
    }

    if(movefrom_idx == moveto_idx)  //  no movement needed
        return d;

    if(movefrom_idx <= moveto_idx){ //  move to right
        int move = moveto_idx - movefrom_idx;

        struct node *ptr = d.head;
        for(int i = 0; i < movefrom_idx; i++)
        {   
            ptr = ptr->next;
            if(ptr == NULL){    //  if end of the list is already reached
                printf("<Index Overflow> Index beyond range, Insertion Failed!\n");
                return d;
            }
        }

        int temp = ptr->data;
        for(int i=0; i<move; i++){
            ptr->data = ptr->next->data;
            ptr = ptr->next;
            if(ptr == NULL){    //  if end of the list is already reached
                printf("<Index Overflow> Index beyond range, Insertion Failed!\n");
                return d;
            }
        }
        ptr->data = temp;
    }

    else{   //  move to left
        int move = movefrom_idx - moveto_idx;

        struct node *ptr = d.head;
        for(int i = 0; i < movefrom_idx; i++)
        {   
            ptr = ptr->next;
            if(ptr == NULL){    //  if end of the list is already reached
                printf("<Index Overflow> Index beyond range, Insertion Failed!\n");
                return d;
            }
        }

        int temp = ptr->data;
        for(int i=0; i<move; i++){
            ptr->data = ptr->prev->data;
            ptr = ptr->prev;
            if(ptr == NULL){    //  if end of the list is already reached
                printf("<Index Overflow> Index beyond range, Insertion Failed!\n");
                return d;
            }
        }
        ptr->data = temp;
    }

    return d;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = *a;
}

struct DLL bubbleSort(struct DLL d) 
{ 
    int is_swapped, i; 
    struct node *ptr; 
    struct node *last = NULL; 
   
    if (d.head == NULL && d.tail == NULL) 
        return d; 
   
    do
    { 
        is_swapped = 0; 
        ptr = d.head; 
   
        while (ptr->next != last) 
        { 
            if (ptr->data > ptr->next->data) 
            {  
                swap(&ptr->data, &ptr->next->data); 
                is_swapped = 1; 
            } 
            ptr = ptr->next; 
        } 
        last = ptr; 
    } 
    while (is_swapped); 

    return d;
} 

struct DLL insertionSort(struct DLL d)
{
    if (d.head == NULL && d.tail == NULL) 
        return d; 

    struct DLL sorted = {NULL, NULL};

    struct node *ptr = d.head;
    while (ptr != NULL){
        sorted = insert_node_sorted(sorted, ptr->data);  //  yes! this sorted insert is seperately required for insertion sort
        ptr = ptr->next;
    }
    return sorted;
}