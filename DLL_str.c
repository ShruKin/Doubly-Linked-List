#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

struct node_str{
    char data[MAX_LEN];
    struct node_str *prev, *next;
};

struct DLL_str{
    struct node_str *head, *tail;
};

void print_list_str(struct DLL_str d);
struct DLL_str create_DLL_str(struct DLL_str d);
struct DLL_str insert_node_str(struct DLL_str d, char str[]);
struct DLL_str delete_smallest_str(struct DLL_str d);

void print_list_str(struct DLL_str d)
{
    struct node_str *first = d.head, *last = d.tail;

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return;
    }

    printf("First-to-Last: ");
    while(first != NULL){   //  iterating throughout the list(till NULL is reached)
        // puts(first->data);  //  printing current node
        printf("%s", first->data);  //  printing current node
        printf(" -> ");
        first = first->next;    //  shifting the temporary node to the next one
    }
    // printf("%d -> ", first->data);  //  printing the last node
    printf("NULL\n");

    printf("Last-to-First: ");
    while(last != NULL){   //  iterating throughout the list(till NULL is reached)
        // puts(last->data);  //  printing current node
        printf("%s", last->data);  //  printing current node
        printf(" -> ");
        last = last->prev;    //  shifting the temporary node to the previous one
    }
    // printf("%d -> ", last->data);  //  printing the first node
    printf("NULL\n");
}

struct DLL_str create_DLL_str(struct DLL_str d)
{
    fflush(stdin);
	char str[MAX_LEN];
	printf("Enter \"null\" to end. \n");
	printf("Enter data : ");
	// gets(str);
    scanf("%[^\n]", str);
    fflush(stdin);

	while(strcmp(str, "null") != 0)
	{
        struct node_str* newNode = (struct node_str *) malloc(sizeof(struct node_str));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }

		if(d.head == NULL && d.tail == NULL)
		{
			strcpy(newNode->data, str);
            newNode->prev = newNode->next = NULL;
            d.head = newNode;
            d.tail = newNode;
		}
		else
		{
			strcpy(newNode->data, str);
            newNode->prev = d.tail;
            d.tail->next = newNode;
            d.tail = newNode;
            d.tail->next = NULL;
		}

		printf("Enter data : ");
		// gets(str);		
        scanf("%[^\n]", str);
        fflush(stdin);
	}
	return d;	
}

struct DLL_str insert_node_str(struct DLL_str d, char str[])
{
    // struct node *first = d.head, *last = d.tail;

    if(d.head == NULL && d.tail == NULL){ //  if list is initially empty
        struct node_str* newNode = (struct node_str *) malloc(sizeof(struct node_str));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }
        strcpy(newNode->data, str);
        newNode->prev = newNode->next = NULL;
        d.head = newNode;
        d.tail = newNode;
        return d;
    }

    struct node_str* newNode = (struct node_str *) malloc(sizeof(struct node_str));
    if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
        printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
        return d;
    }
    else{
        strcpy(newNode->data, str);
        newNode->prev = d.tail;
        d.tail->next = newNode;
        d.tail = newNode;
        d.tail->next = NULL;
    }

    return d;
}

struct DLL_str delete_smallest_str(struct DLL_str d)
{
	if(d.head==NULL && d.tail==NULL)
	{
		printf("\nLinked list not found ");
	     return d;
	}

	if(d.head==d.tail)
	{
		d.head=d.tail=NULL;
		return d;
	}

    if(d.head->next == NULL){
        d.head = d.tail = NULL;
        return d;
    }

	int i=1, smallest_len = MAX_LEN;
	struct node_str *ptr = d.head, *toDel;
	
    ptr = d.head;
	while(ptr != NULL){
        if(strlen(ptr->data) <= smallest_len)
            smallest_len = strlen(ptr->data);
        ptr = ptr->next;
    }

    printf("%d", smallest_len);

    ptr = d.head;
    while(ptr != NULL){
        if(strlen(ptr->data) == smallest_len){
            if(ptr == d.head){
                d.head = d.head->next;
                d.head->prev =  NULL;
                free(ptr);
                ptr = d.head;
            }

            else if(ptr == d.tail){
                d.tail = d.tail->prev;
                d.tail->next = NULL;
                free(ptr);
                ptr = d.tail;
            }

            else{
                toDel=ptr;
                ptr->next->prev = toDel->prev;
                ptr->prev->next = toDel->next;
                free(toDel);
            }
        }
        ptr = ptr->next;
    }

    return d;
}

int main(int argc, char const *argv[])
{
    struct DLL_str d = {NULL, NULL};
    int ch;
    char str[MAX_LEN];

    while(1){
        printf("MAIN MENU");
		printf("\n1. Create list");
        printf("\n2. Display ");
        printf("\n3. Insert node ");
        printf("\n4. Delete smallest string ");
        printf("\n0. EXIT\n");

        printf("Enter your choice : ");
		scanf("%d",&ch);
        printf("\n");

        switch(ch){
            case 0: exit(0);    break;

            case 1: d = create_DLL_str(d);  break;

            case 2: print_list_str(d);  break;

            case 3:
                fflush(stdin);
                printf("Enter data: ");
                scanf("%[^\n]", str);
                d = insert_node_str(d, str);    break;

            case 4: d = delete_smallest_str(d); break;
        }

        printf("\n\n");
    }


    return 0;
}

