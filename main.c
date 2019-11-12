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
        printf("\n11. Bubble Sort list ");
        printf("\n12. Insertion Sort list ");
        printf("\n13. Merge Sort list ");
        printf("\n14. Linear Search element ");
        printf("\n15. Binary Search element ");
        printf("\n16. Reverse list ");
        printf("\n17. Delete duplicate elements from list ");
        printf("\n18. Move a node");
        printf("\n19. Exchange first and last node");
        printf("\n20. Count no. of nodes");
        printf("\n21. Split into halves");
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

            case 8: d = delete_at_beginning(d); break;

            case 9: d =  delete_at_end(d);  break;

            case 10: d = delete_at_position(d); break;  

            case 11: d = bubbleSort(d);     break;

            case 12: d = insertionSort(d);  break;

            case 13: d = merge_sort(d);    break;

            case 15: 
                printf("Enter data to search: ");
                scanf("%d", &data);
                if(binary_search(d, data)!=NULL)
                    printf("%d is found in the list!", data);
                else
                    printf("%d is not found in the list!", data);
                break;

            case 16: d = reverse(d);    break;
            
            case 17:    d = deleteduplicates(d);    break;

            case 18:
                int movefrom, moveto;
                printf("Enter index to move from: ");
                scanf("%d", &movefrom);
                printf("Enter index to move to: ");
                scanf("%d", &moveto);
                d = move_node(d, movefrom, moveto);
                break;

            case 19: d = exchangefirstlast(d);  break;

            case 20: printf("%d no. of nodes are present!", count(d));  break;

            case 21: d= split(d);   break;
        }

        printf("\n\n");
    }

    return 0;
    //  end of main = end of program
 }
