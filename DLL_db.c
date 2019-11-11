#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

struct node_db{
    char name[MAX_LEN], mob[11];
    struct node_db *prev, *next;
};

struct DLL_db{
    struct node_db *head, *tail;
};

void print_db(struct DLL_db d);
struct DLL_db create_db(struct DLL_db d, int n);
char *ret_mob(struct DLL_db d, char name[]);

void print_db(struct DLL_db d)
{
    struct node_db *first = d.head, *last = d.tail;

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return;
    }

    printf("***Start of the DATABASE***\n");
    while(first != NULL){   //  iterating throughout the list(till NULL is reached)
        // puts(first->data);  //  printing current node
        printf("%s\t", first->name);  //  printing current node
        printf("%s\n", first->mob);
        first = first->next;    //  shifting the temporary node to the next one
    }
    // printf("%d -> ", first->data);  //  printing the last node
    printf("***End of the DATABASE***\n");
}

struct DLL_db create_db(struct DLL_db d, int n)
{
    char name[MAX_LEN], mob[11];

    for(int i=0; i<n; i++){
        fflush(stdin);
        printf("\nEnter name: ");
        scanf("%[^\n]", name);
        fflush(stdin);
        printf("Enter mobile no.: ");
        scanf("%[^\n]", mob);

        struct node_db* newNode = (struct node_db *) malloc(sizeof(struct node_db));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }

		if(d.head == NULL && d.tail == NULL)
		{
			strcpy(newNode->name, name);
			strcpy(newNode->mob, mob);
            newNode->prev = newNode->next = NULL;
            d.head = newNode;
            d.tail = newNode;
		}

        else
		{
			strcpy(newNode->name, name);
			strcpy(newNode->mob, mob);
            newNode->prev = d.tail;
            d.tail->next = newNode;
            d.tail = newNode;
            d.tail->next = NULL;
		}
    }

    return d;
}

char *ret_mob(struct DLL_db d, char name[])
{
    struct node_db *first = d.head, *last = d.tail;
    char n[] = "null";

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return NULL;
    }

    while(first != NULL){
        if(strcmp(first->name, name) == 0)
            return first->mob;
        first=first->next;
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    struct DLL_db d = {NULL, NULL};

    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    d = create_db(d, n);
    printf("\n\n");
    print_db(d);

    char name[MAX_LEN];
    fflush(stdin);
    printf("\n\nEnter name to search mobile no. of: ");
    scanf("%[^\n]", name);

    char *mob = ret_mob(d, name);
    if(mob == NULL)
        printf("Not found!\n");
    else
        printf("Mobile No. found: %s\n", mob);

    return 0;
}
