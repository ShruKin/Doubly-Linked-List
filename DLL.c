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
void swap(int *a, int *b);
struct DLL bubbleSort(struct DLL d);
struct DLL insertionSort(struct DLL d);
struct DLL merge(struct DLL left, struct DLL right);
struct DLL merge_sort(struct DLL d);
struct node* middle(struct node* start, struct node* last);
struct node *binary_search(struct DLL d, int key);
struct DLL delete_at_position(struct DLL d); //  :( change korte hobe
struct DLL delete_at_beginning(struct DLL d);
struct DLL delete_at_end(struct DLL d);
struct DLL exchangefirstlast(struct DLL d);
int count(struct DLL d);
struct DLL split(struct DLL d);
struct DLL deleteduplicates(struct DLL d);
struct DLL reverse(struct DLL d);


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

struct DLL merge(struct DLL left, struct DLL right)
{
    struct DLL merged = {NULL, NULL}; //  a temp LL where the merged list will be stored

    while(left.head != NULL && right.head != NULL){   //  iterating through the sub-lists
        if(left.head->data <= right.head->data){  
            merged = insert_node_end(merged, left.head->data);    //  sort and insert to the list
            left.head = left.head->next;  //  shift the tested list
        }

        else if(left.head->data >= right.head->data){
            merged = insert_node_end(merged, right.head->data);   //  sort and insert to the list
            right.head = right.head->next;    //  shift the tested list
        }
    }

    while(left.head != NULL){    //  if there are extra element(s) in the left LL, insert them too
        merged = insert_node_end(merged, left.head->data);
        left.head = left.head->next;
    }
    
    while(right.head != NULL){   //  if there are extra element(s) in the right LL, insert them too
        merged = insert_node_end(merged, right.head->data);
        right.head = right.head->next;
    }

    // printf("Sorting & Merging: \n");    //  PRINT DEBUGGING
    // traverse(merged);   printf("\n\n"); //  PRINT DEBUGGING
    return merged;
}

struct DLL merge_sort(struct DLL d)
{
    if((d.head == NULL && d.tail == NULL) || (d.head->next == NULL && d.tail->prev == NULL))  //  terminating condition, when the list is empty
        return d;

    struct DLL left = d, right = d;
    while(right.head != NULL && right.head->next != NULL && right.head->next->next != NULL){   //  finding the mid element
        right.head = right.head->next->next;  //  hopping right two at a time
        left.head = left.head->next;  //  while hopping left one at a time
    }
    /*  after the above iteration: left is the middle element   */
    right.tail = right.head;
    right.head = left.head->next; //  setting the head of the right LL to the next of mid
    right.head->prev = NULL;
    while(right.tail->next != NULL)
        right.tail = right.tail->next;

    left.tail = left.head;
    left.tail->next = NULL;  
    left.head = d.head;    //  setting the head of left LL to the head of the list

    // printf("Spliting: \n"); //  PRINT DEBUGGING
    // printf("Left: \n");   print_list(left);     printf("\n");   //  PRINT DEBUGGING
    // printf("Right: \n");   print_list(right);   printf("\n\n"); //  PRINT DEBUGGING
    // printf("\n");

    left = merge_sort(left);    //  keep on dividing the left half
    right  = merge_sort(right);  //  keep on dividing the right half
    return merge(left, right);      //  conquer the left and right halves
}

struct node* middle(struct node *start, struct node* last) 
{ 
    if (start == NULL) 
        return NULL; 
  
    struct node* slow = start; 
    struct node* fast = start -> next; 
  
    while (fast != last) 
    { 
        fast = fast -> next; 
        if (fast != last) 
        { 
            slow = slow -> next; 
            fast = fast -> next; 
        } 
    } 
  
    return slow; 
} 

struct node *binary_search(struct DLL d, int key)
{
	if(d.head == NULL && d.tail == NULL)
        return NULL;

    struct node *first = d.head, *last = NULL;

    do
    { 
        struct node* mid = middle(first, last); 

        if (mid == NULL) 
            return NULL; 

        if (mid -> data == key) 
            return mid; 

        else if (mid -> data < key)
            first = mid -> next; 
        
        else
            last = mid; 
  
    } while (last == NULL || last != first); 
  
    return NULL; 
}

struct DLL delete_at_position(struct DLL d) //  :( change korte hobe
{
	if(d.head==NULL && d.tail==NULL)
	{
		printf("\nLinked list not found ");
	     return d;
	}
	else if(d.head==d.tail)
	{
		d.head=d.tail=NULL;
		return d;
	}
	int i=1,pos;
	struct node *ptr,*ptr2;
	printf("enter the position to be deleted");
	scanf("%d",&pos);
	ptr=d.head;
	while(i<pos-1 && ptr->next!=NULL)
	{
		ptr=ptr->next;
		i++;
	}
	if(pos==1)
	{
		ptr=d.head;
		d.head=d.head->next;
		d.head->prev=NULL;
		free(ptr);
		return d;
	}
     else if(ptr==d.tail)
     {
     	d.tail=d.tail->prev;
     	d.tail->next=NULL;
     	free(ptr);
     	return d;
	}
	else
	{
		ptr2=ptr->next;
		ptr->next=ptr2->next;
		ptr2->next->prev=ptr;
		free(ptr2);
		return d;
	}
}

struct DLL delete_at_beginning(struct DLL d)
{
	if(d.head==NULL && d.tail==NULL)
	{
		printf("\nLinked list not found ");
	     return d;
	}
	else if(d.head==d.tail)
	{
		d.head=d.tail=NULL;
		return d;
	}
	struct node *ptr;
	ptr=d.head;
	d.head=d.head->next;
	d.head->prev=NULL;
	free(ptr);
	return d;
}

struct DLL delete_at_end(struct DLL d)
{
	if(d.head==NULL && d.tail==NULL)
	{
		printf("\nLinked list not found ");
	     return d;
	}
	else if(d.head==d.tail)
	{
		d.head=d.tail=NULL;
		return d;
	}
	struct node *ptr;
	ptr=d.tail;
	d.tail=d.tail->prev;
     	d.tail->next=NULL;
     	free(ptr);
     	return d;
}

struct DLL exchangefirstlast(struct DLL d)
{
	struct node *ptr=d.tail,*qtr=d.head;
	if(d.head==NULL && d.tail==NULL)
	{
	printf("list is empty");
	return d;
    }
	int t=0;
	t=ptr->data;
	ptr->data=qtr->data;
	qtr->data=t;
      return d;
}

int count(struct DLL d)
{
	if(d.head==NULL && d.tail==NULL)
     {
	printf("list is empty");
	return 0;
     }
	struct node *ptr;
	int cnt=0;
	ptr=d.head;
	while(ptr!=d.tail)
	{
		cnt++;
		ptr=ptr->next;
	}
	printf(" \nThe no. of nodes %d",cnt+1);
	return (cnt+1);
}

struct DLL split(struct DLL d)
{
	struct node *temp1,*ptr,*qtr,*temp2,*head1=d.head,**head2=NULL;
	if(d.head==NULL && d.tail==NULL)
	{
		printf("linked list is empty");
		return d;
	}
     temp1=d.head;
     temp2=d.tail;
     printf("dll");
     while(temp1->next!=NULL)
     {
     	if(temp1->next==temp2)
     	break;
     	temp1=temp1->next;
     	temp2=temp2->prev;
	}
	temp1->next=NULL;
	*head2=temp2;
	temp2->prev=NULL;
	ptr=d.head;
	qtr=*head2;
	printf("First list \n");
	while(ptr!=NULL)
	{
		printf("%d",ptr->data);
		ptr=ptr->next;
	}
	printf("Second list \n");
	while(qtr!=NULL)
	{
		printf("%d",qtr->data);
		qtr=qtr->next;
	}
	return d;
}

//  TODO: Fix this
struct DLL deleteduplicates(struct DLL d)
{
	struct node *ptr,*ptr2,*ptr3;
	ptr=d.head;
	if(d.head==NULL && d.tail==NULL)
	{
	printf("list is empty");
	return d;
     }
     while(ptr->next!=NULL && ptr!=NULL)
     {
     	ptr2=ptr;
     	ptr3=ptr->next;
     	printf("dll");
     	while(ptr3!=NULL)
     	{
     		if(ptr3->data==ptr2->data)
     		{
     			struct node* todel = ptr3;
     			ptr2->next=ptr3->next;
     			ptr3->next->prev=ptr2;
     			free(todel);
//     			ptr3=ptr2;//gotcha ig ;(
			}
			else
				ptr3=ptr3->next;
		}
		ptr=ptr->next;
	}
printf("Duplicates deleted");
return d;
}

//  TODO Fix this
struct DLL reverse(struct DLL d)
{
	struct node *current,*temp;
	current=d.head;
	if(d.head==NULL && d.tail==NULL)
	{
	printf("list is empty");
	return d;
     }
     while(current!=NULL)
     {
     	temp=current->prev;
     	current->prev=current->next;
     	current->next=temp;
     	current=current->prev;
     }
	d.head=temp->prev;
	printf("linked list reversed");
	return d;
}

//  TODO: complete this
struct DLL deleteevens(struct DLL d)
{
	struct node *ptr=d.head,*ptr2;
	if(d.head==NULL && d.tail==NULL)
	{
	printf("list is empty");
	return d;
     }
     while(ptr!=NULL)
     {
     	ptr2=ptr;
     	if(ptr2->data%2==0)
     	{
     		printf("even");
     		if(ptr2==d.head)
			{
     			d.head=d.head->next;
     			d.head->prev=NULL;
     			free(ptr2);
     			
			}
			else
			{
				ptr2->prev->next=ptr2->next;
				ptr2->next->prev=ptr2->prev;
				free(ptr2);
			}
		}
		ptr=ptr->next;
	}
	return d;
}