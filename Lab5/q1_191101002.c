/* Mustafa Aydoğan 191101002 */

#include <stdio.h>
#include <string.h>

int main()
{
    char exec[20];
    char array[10][20];
    int index = 0;
    
    printf("Welcome,\nEnter a string: ");
    scanf("%s", exec);
    
    while(strcmp(exec,"sort") != 0){
        for(int i=0; i<20; i++){
            array[index][i] = exec[i];
        }
        
        index++;
        
        printf("Enter a string: ");
        scanf("%s", exec);
    }
    
    char temp[30];

    for(int i=0; i<index; i++){
        for(int j=0; j<index-1-i; j++){
          if(strcmp(array[j], array[j+1]) > 0){
            strcpy(temp, array[j]);
            strcpy(array[j], array[j+1]);
            strcpy(array[j+1], temp);
          }
        }
    }
    
    printf("The sorted strings:\n");
    for(int i=0; i<index; i++)
        printf("%s\n", array[i]);
    
    printf("Exiting program.");

    return 0;
}