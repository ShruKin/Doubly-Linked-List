#include "DLL.c"

int main(int argc, char const *argv[])
{
    struct DLL d = {NULL, NULL};
    int ch, data, pos;

    while(1)
	{
	    //	most of the menu options dont work for now
		printf("MAIN MENU");
		printf("\n1. Create list");
        printf("\n2. Display ");
        printf("\n3. Insert at beginning ");
        printf("\n4. Insert at end ");
        printf("\n5. Insert at position ");
        printf("\n6. Insert sorted ");
        printf("\n7. Delete at beginning ");
        printf("\n8. Delete at end ");
        printf("\n9. Delete at pos ");
        printf("\n10. Sort list ");
        printf("\n11. Search element ");
        printf("\n12. Reverse list ");
        printf("\n13. Delete duplicate elements from list ");
        printf("\n14. Insert in a sorted list");
        printf("\n0. EXIT\n");

        printf("Enter your choice : ");
		scanf("%d",&ch);
        printf("\n");

		switch(ch)
        {
            case 0: exit(0);    break;

            case 2: print_list(d);   break;

            case 3:	
                printf("Enter data: ");
                scanf("%d", &data);
                d = insert_node_begin(d, data);		break;

			case 4:		
                printf("Enter data: ");
                scanf("%d", &data);
                d = insert_node_end(d, data);		break;

			case 5:		
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                //  using pos-1 as index should be passed in the function
                d = insert_node(d, data, pos-1);  	break;

            case 6:
                printf("Enter data: ");
                scanf("%d", &data);
                d = insert_node_sorted(d, data);		break;
        }

        printf("\n\n");
    }

    return 0;
    //  end of main = end of program
 }
