/* Mustafa Aydogan 191101002 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node{
	int value;
	struct Node *parent1;
	struct Node *parent2;
	struct Node *child1;
	struct Node *child2;
};

int createChild(struct Node *parent1, struct Node *parent2, int height){

	if (height == 0)
		return 1;

	printf("asd\n");

	struct Node *child;

	if (( child = (struct Node*)malloc(sizeof(struct Node))) != NULL);
	else {
		printf("Out of memory!\n");
		exit(0);
	}

	int value1 = 0, value2 = 0;

	if (parent1 != NULL) value1 = parent1->value;
	if (parent2 != NULL) value2 = parent2->value;
	
	child->parent1 = parent1;
	child->parent2 = parent2;
	child->value = value1 + value2;

	if (parent1 != NULL)
	{
		parent1->child2 = child;

		if (parent1->parent2 != NULL)
		{
			parent1->parent2->child2->child1 = child;
		}
	}

	pid_t pr1_id = fork();
	pid_t pr2_id = fork();

	if (getpid() == pr1_id){
		createChild(parent1->child1, child, height-1);
	}

	else if (getpid() == pr2_id){
		createChild(child, parent2->child2, height-1);
	}
}

int print(struct Node *node){

	printf("%d ", node->value);

	print(node->child1);
	print(node->child2);

}

int main(int argc, char const *argv[])
{
	int height;
	printf("Enter the wanted triangle height:\n");
	scanf("%d", &height);

	struct Node root = {1, NULL, NULL, NULL, NULL};
	createChild(NULL, &root, height);

	/*int pr1_id = fork();
	int pr2_id = fork();*/

	pid_t pr1_id = fork();
	pid_t pr2_id = fork();

	if (getpid() == pr1_id){
		createChild(NULL, &root, height);
	}

	else if (getpid() == pr2_id){
		createChild(&root, NULL, height);
		
	}
	

	print(&root);


	return 0;
}