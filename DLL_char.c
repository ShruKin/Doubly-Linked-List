#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

struct node_char{
    char data;
    struct node_char *prev, *next;
};

struct DLL_char{
    struct node_char *head, *tail;
};

void print_list_char(struct DLL_char d);
struct DLL_char create_DLL_char(struct DLL_char d, char str[]);
int ispalindrome(struct DLL_char d);
char first_recurring(struct DLL_char d);

void print_list_char(struct DLL_char d)
{
    struct node_char *first = d.head, *last = d.tail;

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return;
    }

    printf("First-to-Last: ");
    while(first != NULL){   //  iterating throughout the list(till NULL is reached)
        // puts(first->data);  //  printing current node
        printf("%c", first->data);  //  printing current node
        printf(" -> ");
        first = first->next;    //  shifting the temporary node to the next one
    }
    // printf("%d -> ", first->data);  //  printing the last node
    printf("NULL\n");

    printf("Last-to-First: ");
    while(last != NULL){   //  iterating throughout the list(till NULL is reached)
        // puts(last->data);  //  printing current node
        printf("%c", last->data);  //  printing current node
        printf(" -> ");
        last = last->prev;    //  shifting the temporary node to the previous one
    }
    // printf("%d -> ", last->data);  //  printing the first node
    printf("NULL\n");
}

struct DLL_char create_DLL_char(struct DLL_char d, char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        struct node_char* newNode = (struct node_char *) malloc(sizeof(struct node_char));
        if (newNode == NULL) { //  if newNode couldnt be allocated: insufficient memory :(
            printf("<Memory Overflow> Insufficient Memory, Insertion Failed!\n");
            return d;
        }

		if(d.head == NULL && d.tail == NULL)
		{
			newNode->data = str[i];
            newNode->prev = newNode->next = NULL;
            d.head = newNode;
            d.tail = newNode;
		}
		else
		{
			newNode->data = str[i];
            newNode->prev = d.tail;
            d.tail->next = newNode;
            d.tail = newNode;
            d.tail->next = NULL;
		}
    }
    return d;
}

int ispalindrome(struct DLL_char d)
{
	if(d.head == NULL && d.tail == NULL)
    {
        printf("linked list empty");
        return 0;
    }
	struct node_char *left=d.head;
	struct node_char *right=d.tail;
    while(left!=right)
    {
        if(left->data!=right->data)
            return 0;
        left=left->next;
        right=right->prev;
    }
	return 1;
}

char first_recurring(struct DLL_char d)
{
    struct node_char *first = d.head, *last = d.tail;

    if(first == NULL && last == NULL){  //  no nodes in the list
        printf("<List Underflow> No Nodes in the list, Unable to print!\n");
        return '\0';
    }

    while(first != NULL){
        while(last != first){
            if(last->data == first->data)
                return first->data;
            last = last->prev;
        }
        first = first->next;
        last = d.tail;
    }

    return '\0';
}

int main(int argc, char const *argv[])
{
    struct DLL_char d = {NULL, NULL};
    char str[MAX_LEN];
    int ch;

    while(1){
        printf("MAIN MENU");
        printf("\n1. Create char based DLL from string");
        printf("\n2. Display ");
        printf("\n3. Check Palindrome ");
        printf("\n4. Find first recurring character ");
        printf("\n0. EXIT\n");

        printf("Enter your choice : ");
		scanf("%d",&ch);
        printf("\n");

        switch(ch){
            case 0: exit(0);

            case 1:
                fflush(stdin);
                printf("Enter string: ");
                scanf("%[^\n]", str);

                d = create_DLL_char(d, str);
                break;

            case 2: print_list_char(d); break;

            case 3: 
                if(ispalindrome(d))
                    printf("The string is palindrome");
                else
                    printf("The string is not palindrome");
                break;

            case 4:
                char rep = first_recurring(d);
                if(rep == '\0')
                    printf("No recurring character found!");
                else
                    printf("First recurring character is: %c", rep);
                break;
        }

        printf("\n\n");
    }

    return 0;
}
