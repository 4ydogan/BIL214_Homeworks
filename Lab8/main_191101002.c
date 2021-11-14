/* Mustafa Aydogan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    char data;
    int layer;
    struct node *child;
    struct node *next_sibling;
} Node;

struct node tree[200];

Node newNode(int layer, char data){

    int child_count = layer + 2;

    struct node child;
    child.data = '\0';
    child.layer = layer+1;

    struct node newNode;
    newNode.data = data;
    newNode.layer = layer;
    newNode.child = &child;

    struct node *node;
    node = &child;
    for (int i = 0; i < child_count-1; ++i)
    {
        Node sibling;
        sibling.data = '\0';
        sibling.layer = layer+1;

        node->next_sibling = &sibling;
    }

    return newNode;
}

int printNode(Node *node){
    printf("%c", node->data);
    
    if (node->child->data != '\0')
    {
        /*printNode(node->child);
        if (node->child->next_sibling->data != '\0'){
            printNode(node->child->next_sibling);
        }*/
    }

    return 0;

}

void print(){
    if (tree[0].data == '\0')
    {
        printf("The tree is empty.\n");
    }else{

        printNode(&(tree[0]));

        printf("\n");
    }
}

int whichChild(Node node){

    struct node *child;
    child = node.child;
    int i;

    for (i = 0; i < (node.layer)+2; ++i)
    {   
        printf("okk\n");
        if (child->data == '\0')
        {
            return i;
        }
        child = child->next_sibling;
    }

    return -1;
}

int add(char data, int index){

	if (index == 0){
		tree[0] = newNode(0, data);
        printf("ok\n");
        
		return 1;
	}
	else{
		for (int i = 0; i < index; ++i)
        {   
            int layer = log(index+1)/log(2);
            int child_index = whichChild(tree[index-1]);
            printf("%d\n", child_index);
            if(child_index != -1)
            {
                tree[index] = newNode(layer, data);
                Node *child;
                child = tree[i].child;

                if (child_index == 0)
                {
                    tree[i].child = &tree[index];
                }else{

                    for (int j = 0; j < child_index-1; ++j)
                    {
                        child->next_sibling;
                    }
                    child->next_sibling = &tree[index];
                }
                printf("added\n");
                return index+1;
            }
        }
	}

    return -1;
}

int main(int argc, char args[])
{

  	char command[20];
  	char* command_print = "print";
  	char* command_add = "add";

  	char temp;

  	int index = 0;
  	

    printf("Please enter a command: ");
    scanf("%s%c", command, &temp);

    while(strcmp(command, "exit") != 0){

    	if (strcmp(command_print, command) == 0) {
    		print();
    		printf("Please enter a command: ");
    		scanf("%s", command);
    	}

    	else if (strcmp(command_add, command) == 0) {
    		char values[20];
    		printf("Enter node values: ");
    		scanf("%s", values);

    		for (int i = 0; values[i] != '\0'; ++i)
    		{
    			index = add(values[i], index);
    		}

    		printf("Please enter a command: ");
    		scanf("%s", command);
    	}
    	
    	else{
    		printf("Please enter a valid command: ");
    		scanf("%s", command);
    	}

    	scanf("%c", &temp);
    }

    printf("Exiting program.\n");
    
	return 0;
}