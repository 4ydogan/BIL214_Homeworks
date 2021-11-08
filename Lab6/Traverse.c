#include <stdio.h>
#include <string.h>
#include <math.h>

int path(char* tree, int n, char *last, int k){

	if (n < k)
		return 0;
	else if(n == 0){
		*last = tree[n];
		return 0;
	}else{
		*last = tree[n];
		last++;
		path(tree, (n-1)/2, last, k);
	}
}


int hasChild(char* tree, int n){
	if (tree[n] == '\n')
		return 0;
	return 1;
}

int assignArray(char paths[500][5], int index, char path[5]){
	for (int i = 0; i < index; ++i)	paths[index][i] = path[i];
}

int strrev(char *ptr){

	int count = 0;
	int i = 0;
	while(*(ptr+i) != '\0' && i < 5){
		count++;
		i++;
	}

	char temp = *ptr;
	int x = count;


	for (int i = 1; i <= x/2; i++)
	{
		*(ptr+i-1) = *(ptr+count-1);
		*(ptr+count-1) = temp;
		temp = *(ptr+i);
		count--;
	}
}

int main(){

	char tree[30];
	char paths[500][5];
	int index = 0;

	printf("Enter a binary tree:\n");
	scanf("%s", tree);
	int len = strlen(tree)-1;
	int i = 10;
	char* p;
	int end = 500;


	while(len >= 0 ){
		for (int i = 0; i < 30; i++)
		{
			char string[5] = {};
			p = &string[0];
			path(tree, len, p, i);
			strrev(p);
			assignArray(paths, index, string);
			index++;
		}
		len--; 
	}

	len = strlen(tree);
	int layer = 0;
	int k = 0;
	int l = 0;
	
	printf("\nPaths:\n");

	while (k<len){
		printf("Layer %d | Node %c: ", layer, tree[k]);
		for (int i = 0; i < index; i++)
		{
			if(paths[i][0] == tree[k]) printf("%s, ", paths[i]);
		}
		printf("\n");

		l++;
		k++;

		if(pow(2,layer) == l){
			layer++;
			l = 0;
		}
	}
}