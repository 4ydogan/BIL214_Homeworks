/* Mustafa Aydoğan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// create movie struct
struct movie{
	int id;
	char name[100];
	char director[100];
	int year;
	char type[100];
};

struct movie array[100]; // to store the movies


// this function replaces comma with | inside double quotes
void replace(char *array){

	int into = 0;

	for (int i = 0; i < 255; i++)
	{

		if (*array == '"' && into == 0)	{
			into = 1;
		}else if (*array == '"' && into == 1){
			into = 0;
		}

		if(*array == ',' && into == 1){
			*array = '|';
		}

		array++;
	}
}

// this function replace | with comma
void undo(char *array){

	for (int i = 0; i < 255; i++){
		if(*array == '|') *array = ',';
		array++;
	}
}

// this function prints i-nt movie into array
void print_movie(int i){
	printf("%d. %s, %s, %d, %s", 
    	array[i].id, array[i].name, array[i].director, 
    	array[i].year, array[i].type);
}

//this function print all movies
void print(){
	for (int i = 0; i < 256; ++i) {
    	if (array[i].id == 0) break;
    	print_movie(i);
    }
}

// this function controls s1 contains s2 or not
int isExist(char* s1, char* s2){

	char *ret;

    ret = strstr(s1, s2);
    if (ret)
        return 1;
    else
        return 0;
}

// this function update the array with given info
void update(){

	int id;
	char temp;
	char* info = NULL;
	size_t size = 1000;
	ssize_t read = 0;
	FILE * output;

	output = fopen("movies.csv", "w"); // opens the movies.csv

	printf("ID: "); // take id 
	scanf("%d", &id);
	scanf("%c", &temp);

	printf("New info: "); // take info
	read = getline(&info, &size, stdin);

	replace(info);

	char *token;

	array[id-1].id = id; // assign id

	token = strtok(info, ",");
	
	if(strcmp(token, " ") == 0);
	else{
		strcpy(array[id-1].name, token); // assign name
		undo(array[id-1].name);
	}
	token = strtok(NULL, ",");

	if(strcmp(token, " ") == 0);
	else{
		strcpy(array[id-1].director, token); // assign director
		undo(array[id-1].director);
	}
	token = strtok(NULL, ",");

	if(strcmp(token, " ") == 0);
	else array[id-1].year = atoi(token); // assign year
	token = strtok(NULL, "\n");
	
	if(strcmp(token, " ") == 0);
	else{
		strcpy(array[id-1].type, token); // assign type
		undo(array[id-1].type);
	}
	token = strtok(NULL, "\n");


	// this for loop write updated array to output file
	for (int i = 0; i < 100; ++i)
	{	
		if (array[i].id == 0){
    		break;
    	}

		fprintf(output, "%s,%s,%d,%s", 
    	array[i].name, array[i].director, 
    	array[i].year, array[i].type);
	}

	fclose(output);
}

// this function search into array given arguments
void search(){

	char* info = NULL;
	size_t size = 1000;
	ssize_t read = 0;

	printf("Search condition: ");
	read = getline(&info, &size, stdin); // take search condition

	char *token;
	char *comp;
	char *oper;
	char *value; 

	token = strtok(info, " ");
	comp = token;

	token = strtok(NULL, " ");
	oper = token;

	token = strtok(NULL, "\n");
	value = token;

	char str[256];

	strcpy(str, value);


	// if condition is genre
	if (strcmp(comp, "genre") == 0){
		if (strcmp(oper, "==") == 0){
			for (int i = 0; i < 100; ++i){
				if(array[i].id == 0) break;
				if(isExist(array[i].type, value) == 1) 
					print_movie(i);
			}
		}
		else if (strcmp(oper, "!=") == 0){
			for (int i = 0; i < 100; ++i){
				if(array[i].id == 0) break;
				if(isExist(array[i].type, value) != 1) 
					print_movie(i);
			}
		}
		else printf("Wrong input!\n");
	}

	// if condition is year
	else if (strcmp(comp, "year") == 0){

		int year = atoi(value);
		if (strcmp(oper, "==") == 0){
			for (int i = 0; i < 100; ++i) {
				if(array[i].id == 0) break;
				if(array[i].year == year) print_movie(i);
			}
		}
		else if (strcmp(oper, "!=") == 0){
			for (int i = 0; i < 100; ++i) {
				if(array[i].id == 0) break;
				if(array[i].year != year) print_movie(i);
			}
		}
		else if (strcmp(oper, "<" ) == 0){
			for (int i = 0; i < 100; ++i) {
				if(array[i].id == 0) break;
				if(array[i].year  < year) print_movie(i);
			}
		}
		else if (strcmp(oper, ">" ) == 0){
			for (int i = 0; i < 100; ++i) {
				if(array[i].id == 0) break;
				if(array[i].year  > year) print_movie(i);
			}
		}

		// if condition is wrong
		else printf("Wrong input!\n");
	}
}


// main function
int main()
{
	int id = 1;
	FILE *input;
	char line[1000];


	// if there is no movies.csv file
	if ( ( input = fopen("movies.csv", "r") ) == NULL ) {
        printf( "File could not be opened.\n" );
        return 1;
    }

    // reads the lines from file and adds to array
	while( (fgets(line, 1000, input)) != NULL){
		char *token;
		replace(line);
		token = strtok(line, ",");

		array[id-1].id = id;
		
		strcpy(array[id-1].name, token);
		undo(array[id-1].name);
		token = strtok(NULL, ",");

		strcpy(array[id-1].director, token);
		undo(array[id-1].director);
		token = strtok(NULL, ",");

		array[id-1].year = atoi(token);
		token = strtok(NULL, ",");

		strcpy(array[id-1].type, token);
		undo(array[id-1].type);

		id++;
    }

    fclose(input); // close the file

  	char command[20];
  	char* command_print = "print";
  	char* command_update = "update";
  	char* command_search = "search";

  	char temp;

    printf("Please enter a command: ");
    scanf("%s%c", command, &temp); // take the command

    while(strcmp(command, "exit") != 0){ // if command is not exit

    	if (strcmp(command_print, command) == 0) {
    		print();
    		printf("Please enter a command: ");
    		scanf("%s", command);
    	}
    	else if (strcmp(command_update, command) == 0) {
    		update();
    		printf("Please enter a command: ");
    		scanf("%s", command);
    	}
    	else if(strcmp(command_search, command) == 0) {
    		search();
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