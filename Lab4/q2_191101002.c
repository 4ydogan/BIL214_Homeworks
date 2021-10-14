/* Mustafa Aydogan 191101002 */

#include <stdio.h>
#include <ctype.h>

int main() {

   printf("Welcome,\n");
   char exec = 'Y'; 
   
   while(exec == 'Y'){
   
   	printf("Please enter a string: ");
   	
   	char temp;
	char *str; 
	scanf("%s", str);
	scanf("%c", &temp);
	printf("Original: %s\n", str);
	printf("Lowercase: ");
	for(int i = 0; str[i]; i++){
 	    printf("%c", tolower((unsigned char) str[i]));
	}
	printf("\nUppercase: ");
	for(int i = 0; str[i]; i++){
 	    printf("%c", toupper((unsigned char) str[i]));
	}
	printf("\nAlternated case: ");
	for(int i = 0; str[i]; i++){
	    if(toupper((unsigned char) str[i]) == (unsigned char) str[i])
	    	printf("%c", tolower((unsigned char) str[i]));
	    	
	    if(tolower((unsigned char) str[i]) == (unsigned char) str[i])
	    	printf("%c", toupper((unsigned char) str[i]));
	}
	printf("\nDuplicated: ");
	for(int i = 0; str[i]; i++){
	    printf("%c", str[i]);
	    if(toupper((unsigned char) str[i]) == (unsigned char) str[i])
	    	printf("%c", str[i]);
	}
	printf("\nASCII: ");
	for(int i = 0; str[i]; i++){
	    int c = (char)str[i];
	    if(c<100) printf("0%d ", c);
	    else printf("%d ", c);
		
	}

        printf("\nDo you want to continue? (Y/N)\n");
        scanf("%c", &exec);
   }	   
   
   printf("Exiting program.\n");
   
   return 0;
}

