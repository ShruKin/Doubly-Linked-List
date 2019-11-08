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
		printf("\n2. Create sorted list");
        printf("\n3. Display ");
        printf("\n4. Insert at beginning ");
        printf("\n5. Insert at end ");
        printf("\n6. Insert at position ");
        printf("\n7. Insert sorted ");
        printf("\n8. Delete at beginning ");
        printf("\n9. Delete at end ");
        printf("\n10. Delete at pos ");
        printf("\n11. Sort list ");
        printf("\n12. Search element ");
        printf("\n13. Reverse list ");
        printf("\n14. Delete duplicate elements from list ");
        printf("\n15. Insert in a sorted list");
        printf("\n16. Move a node");
        printf("\n0. EXIT\n");

        printf("Enter your choice : ");
		scanf("%d",&ch);
        printf("\n");

		switch(ch)
        {
            case 0: exit(0);    break;

            case 1: d = create_DLL(d);  break;

            case 2: d = create_sorted_DLL(d); break;

            case 3: print_list(d);   break;

            case 4:	
                printf("Enter data: ");
                scanf("%d", &data);
                d = insert_node_begin(d, data);		break;

			case 5:		
                printf("Enter data: ");   
                scanf("%d", &data);
                d = insert_node_end(d, data);		break;

			case 6:		
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                //  using pos-1 as index should be passed in the function
                d = insert_node(d, data, pos-1);  	break;

            case 7:
                printf("Enter data: ");
                scanf("%d", &data);
                d = insert_node_sorted(d, data);		break;

            case 16:
                int movefrom, moveto;
                printf("Enter index to move from: ");
                scanf("%d", &movefrom);
                printf("Enter index to move to: ");
                scanf("%d", &moveto);
                d = move_node(d, movefrom, moveto);
        }

        printf("\n\n");
    }

    return 0;
    //  end of main = end of program
 }
