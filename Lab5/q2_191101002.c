#include <stdio.h>  
#include <string.h>

void add_index(int *a, int value, int index){
    int temp1 = *(a+index);
    int temp2 = *(a+index+1);
    *(a+index) = value;
    index++;
    
    while(temp1 != -1){
        *(a+index) = temp1;
        temp1 = temp2;
        temp2 = *(a+index+1);
        index++;
    }
    
    *(a+index) = temp1;
}

int main() {  
	int array[100] = {0,1,2,3,4,5,6,7,8,-1};
	int value;
	int index;
	char temp;
	char exec = 'Y';
	int* ptr = array;
	
	printf("Welcome,\n");
	printf("The array: ");
	for(int k=0; k<10; k++)
        	printf("%d ", *(ptr+k));
	printf("\n");
	while (exec == 'Y'){
		
		ptr = array;
			
		printf("Enter a value: ");
		scanf("%d", &value);

		printf("Enter an index: ");
		scanf("%d", &index);
	
		add_index(ptr, value, index);
		
		printf("The new array: ");
		
			
        	for(int k=0; k<100; k++){
        	    if(*(ptr+k-1) == -1) break;
           	    printf("%d ", *(ptr+k));
		}
		
		printf("\nDo you want to continue? (Y/N)\n");
		scanf("%c", &temp);
		scanf("%c", &exec);
	}

	printf("Exiting program.\n");

	return 0;  
}
