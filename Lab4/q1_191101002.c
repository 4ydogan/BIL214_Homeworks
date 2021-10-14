/* Mustafa Aydogan 191101002 */

#include <stdio.h>

int main() {

   printf("Welcome,\n");
   char exec = 'Y'; 
   
   while(exec == 'Y'){
   
   	printf("Please enter the array: ");
   		   
	int i=0, j=0; 
	int max=0;
	int min=9999;
	int sum=0;
	int *arr; 
	long product = 1;
	char temp; 
	do { 
		scanf("%d%c", &arr[i], &temp);
		sum += arr[i];
		product *= arr[i];
		if(arr[i] > max) max = arr[i];
		if(min > arr[i]) min = arr[i];
		i++; 
	}
	while(temp != '\n'); 

        float mean =  sum/(float)i;
        int max_diff = max - min;
       
        printf("Number of elements: %d\n", i); 
        printf("Max: %d\n", max);
        printf("Min: %d\n", min);
        printf("Sum: %d\n", sum);
        printf("Mean: %f\n", mean);
        printf("Product: %ld\n", product);
        printf("Max difference: %d\n", max_diff);
        
        printf("Do you want to continue? (Y/N)\n");
        scanf("%c", &exec);
  
   }	   
   
   printf("Exiting program.\n");
   
   return 0;
}

