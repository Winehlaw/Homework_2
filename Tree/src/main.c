#include"head.h"

int main()
{
    AVLTree avlRoot = NULL;
    LPTree lpRoot = NULL;
    ElemType data;
    char command;
    int nums[NUM], len;

    while (1) {
        printf("Please choose a command:\n");
        printf("A: AVL Tree\n");
        printf("L: Linked List\n");
        printf("q: Quit\n");

        scanf("%c", &command);
        getchar();  // «Â≥˝ ‰»Îª∫¥Ê

        switch (command) {
        case 'A':
            while (1) {
                printf("Please choose a command:\n");
                printf("i: Insert a node\n");
                printf("d: Delete a node\n");
                printf("s: Search for a node\n");
                printf("h: Heap Sort\n");
                printf("b: Return to the previous menu\n");

                scanf("%c", &command);
                getchar();  // «Â≥˝ ‰»Îª∫¥Ê

                switch (command) {
                case 'i':
                    printf("Please enter a character to insert:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    avlRoot = insertTree(avlRoot, data);
                    printf("Successfully inserted %d.\n", data);
                    break;

                case 'd':
                    printf("Please enter a character to delete:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    avlRoot = AVL_del(avlRoot, data);
                    printf("Successfully deleted %d.\n", data);
                    break;

                case 's':
                    printf("Please enter a character to search:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    AVLTree temp = SearchAVLnode(avlRoot, data);
                    if (temp == NULL) {
                        printf("%d does not exist.\n", data);
                    }
                    else {
                        printf("%d is found.\n", data);
                    }
                    break;

                case 'h':
                    printf("Please enter the length of the array:\n");
                    fflush(stdin);
                    scanf("%d", &len);
                    printf("Please enter the elements of the array:\n");
                    for (int i = 0; i < len; i++) {
                        scanf("%d", &nums[i]);
                    }
                    heap_sort(nums, len);
                    printf("Sorted array: ");
                    for (int i = 0; i < len; i++) {
                        printf("%d ", nums[i]);
                    }
                    printf("\n");
                    break;

                case 'b':
                    break;

                default:
                    printf("Unknown command.\n");
                    break;
                }
                getchar();  // «Â≥˝ ‰»Îª∫¥Ê
                if (command == 'b') {
                    break;
                }
            }
            break;

        case 'L':
            while (1) {
                printf("Please choose a command:\n");
                printf("i: Insert a node\n");
                printf("d: Delete a node\n");
                printf("s: Search for a node\n");
                printf("h: Heap Sort\n");
                printf("b: Return to the previous menu\n");

                scanf("%c", &command);
                getchar();  // «Â≥˝ ‰»Îª∫¥Ê

                switch (command) {
                case 'i':
                    printf("Please enter a character to insert:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    LPTree curNode = createNode(data);
                    if (lpRoot == NULL) {
                        lpRoot = curNode;
                    }
                    else {
                        InsertNode(curNode, &lpRoot);
                    }
                    printf("Successfully inserted %d.\n", data);
                    break;

                case 'd':
                    printf("Please enter a character to delete:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    LPTree curNode1 = searchNode(lpRoot, data);
                    if (curNode1 == NULL) {
                        printf("%d does not exist.\n", data);
                    }
                    else {
                        deleteNode(curNode1, &lpRoot);
                        printf("Successfully deleted %d.\n", data);
                    }
                    break;

                case 's':
                    printf("Please enter a character to search:\n");
                    fflush(stdin);
                    scanf("%d", &data);
                    LPTree curNode2 = searchNode(lpRoot, data);
                    if (curNode2 == NULL) {
                        printf("%d does not exist.\n", data);
                    }
                    else {
                        printf("%d is found.\n", data);
                    }
                    break;

                case 'h':
                    printf("Please enter the length of the array:\n");
                    fflush(stdin);
                    scanf("%d", &len);
                    printf("Please enter the elements of the array:\n");
                    for (int i = 0; i < len; i++) {
                        scanf("%d", &nums[i]);
                    }
                    heap_sort(nums, len);
                    printf("Sorted array: ");
                    for (int i = 0; i < len; i++) {
                        printf("%d ", nums[i]);
                    }
                    printf("\n");
                    break;

                case 'b':
                    break;

                default:
                    printf("Unknown command.\n");
                    break;
                }
                getchar();  // «Â≥˝ ‰»Îª∫¥Ê
                if (command == 'b') {
                    break;
                }
            }
            break;

        case 'q':
            printf("Bye-bye!\n");
            desAVLtree(avlRoot);
            exit(0);

        default:
            printf("Unknown command.\n");
            break;
        }
        getchar();  // «Â≥˝ ‰»Îª∫¥Ê
    }
}