/* Mustafa Aydoğan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// create item struct
struct item{
	char title[1000];
	char description[1000];
	char link[1000];
	char pubDate[1000];
};

struct item array[200]; // item array

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

// this function prints i-nt item into array
void print_item(int i){
	printf("%s, %s, %s, %s\n", 
		array[i].title, array[i].description, 
    	array[i].link, array[i].pubDate);
}

//this function print all items
void print(int j){
	for (int i = 0; i < j; ++i) {
    	print_item(i);
    }
    printf("%d\n", j);
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

// this function controls the log is new or not
int isNewLog(char* link, int j){

	for (int i = 0; i < j; ++i) {
		if(strstr(array[i].link, link) != 0)
			return 0;
	}
	return 1;
}

//main function
int main(int argc, char *args[])
{
	char* input;
	char* output;

	FILE *input_file;
	FILE *output_file;

	int i = 0;

	// if arguments is wrong
	if(argc<5){
        printf("Wrong arguments!\n");
        return 1;
	}
    else{
        if(strcmp(args[1], "-i") == 0) input = args[2];
		else if(strcmp(args[1], "-o") == 0) output = args[2];
		
		if(strcmp(args[3], "-i") == 0) input = args[4];
		else if(strcmp(args[3], "-o") == 0) output = args[4];
    }

    // if file is not in repository
    if ( ( input_file = fopen(input, "r") ) == NULL ) {
        printf( "File could not be opened.\n" );
        return 1;
    }
 	
 	// create true first line
    char* csv = "title, description, link, pubDate\n";
    output_file = fopen(output, "r+");
    if ( output_file == NULL){
		output_file = fopen(output, "w+");
    	fprintf(output_file, "%s", csv);
    }else{
    	char first[1000];
    	fgets(first, 1000, output_file);

    	if (strcmp(csv, first) != 0) // if output file is not valid
    	{
    		printf( "Output file is not valid.\n" );
    		return 1;
    	}else{
    		// reads the lines from output file and adds into array
    		while((fgets(first, 1000, output_file)) != NULL){

    			char *token;
				replace(first);
				token = strtok(first, ",");
				
				strcpy(array[i].title, token);
				undo(array[i].title);
				token = strtok(NULL, ",");

				strcpy(array[i].description, token);
				undo(array[i].description);
				token = strtok(NULL, ",");

				strcpy(array[i].link, token);
				token = strtok(NULL, ",");

				strcpy(array[i].pubDate, token);
				undo(array[i].pubDate);

				i++;
    		}
    	}
    }

    char line[1000];
    fgets(line, 1000, input_file);

    // reads the lines until line contains "<ttl>15</ttl>"
    while(isExist(line, "<ttl>15</ttl>") == 0){
		fgets(line, 1000, input_file);
	}

	while((fgets(line, 1000, input_file)) != NULL){

		// reads the lines from input file and parse the lines
		// if the new item is a new log, adds to array
		if (isExist(line, "<item>")){
			fgets(line, 1000, input_file);
			if (isExist(line ,"<title>")) {
				fgets(line, 1000, input_file);
				char *token;
				token = strtok(line, "[");
				token = strtok(NULL, "[");
				token = strtok(NULL, "]");
				strcpy(array[i].title, token);
			}
			fgets(line, 1000, input_file);
			fgets(line, 1000, input_file);

			if (isExist(line, "<description>")) {
				fgets(line, 1000, input_file);
				char *token;
				token = strtok(line, "[");
				token = strtok(NULL, "[");
				token = strtok(NULL, "]");
				strcpy(array[i].description, token);
			}
			fgets(line, 1000, input_file);
			fgets(line, 1000, input_file);

			if (isExist(line, "<link>")) {
				char *token;
				token = strtok(line, ">");
				token = strtok(NULL, "<");
				strcpy(array[i].link, token);
			}
			fgets(line, 1000, input_file);
			fgets(line, 1000, input_file);

			if (isExist(line, "<pubDate>")) {
				char *token;
				token = strtok(line, ">");
				token = strtok(NULL, "<");
				strcpy(array[i].pubDate, token);
			}
			fgets(line, 1000, input_file);
			if(isNewLog(array[i].link, i) != 0){ 
				
				fprintf(output_file, "\"%s\", \"%s\", \"%s\", \"%s\"\n", 
							array[i].title, array[i].description, 
    						array[i].link, array[i].pubDate);
				i++;
			}
			else{
				strcpy(array[i].title, "\0");
				strcpy(array[i].description, "\0"); 
    			strcpy(array[i].link, "\0");
    	 		strcpy(array[i].pubDate, "\0");
			}
		}	
	}
	
	return 0;
}