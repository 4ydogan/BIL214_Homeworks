/* Mustafa Aydogan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// create Star struct
struct Star{
	char name[100];
	struct Movie *movies[15];
};

// create StarNode struct
struct StarNode{
	int id;
	struct Star *own;
	struct StarNode *next;
} starRoot = {0, NULL, NULL};

// create Movie struct
struct Movie{
	char name[100];
	struct Star *stars[15];
};

// create StarNode struct
struct MovieNode{
	int id;
	struct Movie *own;
	struct MovieNode *next;
} movieRoot = {0, NULL, NULL};

// this function replaces comma with | inside double quotes
int replace(char *str){

	int into = 0;

	for (int i = 0; i < 1000; i++)
	{
		if (*str == '"' && into == 0) into = 1;
		else if (*str == '"' && into == 1) into = 0;

		if(*str == ',' && into == 1) *str = '|';
		if(*str == '\n') *str = '\0';

		if (*str == '\0')
			break;

		str++;
	}
}

// delete '\n' from given char pointer
int deleteN(char *str){
	for (int i = 0; i < 1000; i++)
	{
		if(*str == '\n') *str = '\0';
		if (*str == '\0')
			break;
		str++;
	}	
}

// this function replace | with comma
void undo(char *str){
	for (int i = 0; i < 100; i++){
		if(*str == '|') *str = ',';
		str++;
	}
}

// create a new Star struct and return it
struct Star* makeStar(char *name){
	
	struct Star *new;

	if (( new = (struct Star*)malloc(sizeof(struct Star))) != NULL) {
		strcpy(new->name, name);
		undo(new->name);	
	}
	else {
		printf("Out of memory!\n");
		exit(0);
	}

	return new;
}

// create a new StarNodes struct and return it
struct StarNode* makeStarNode(int id, struct Star *node, struct StarNode *next){

	struct StarNode *new;

	if (( new = (struct StarNode*)malloc(sizeof(struct StarNode))) != NULL) {
		new->id = id;
		new->own = node;
		new->next = next;
	}
	else {
		printf("Out of memory!\n");
		exit(0);
	}

	return new;
}


// create a new Star struct and return it
struct Movie* makeMovie(char *name){
	
	struct Movie *new;

	if (( new = (struct Movie*)malloc(sizeof(struct Movie))) != NULL) {
		strcpy(new->name, name);
		undo(new->name);	
	}
	else {
		printf("Out of memory!\n");
		exit(0);
	}

	return new;
}

// create a new StarNodes struct and return it
struct MovieNode* makeMovieNode(int id, struct Movie *node, struct MovieNode *next){

	struct MovieNode *new;

	if (( new = (struct MovieNode*)malloc(sizeof(struct MovieNode))) != NULL) {
		new->id = id;
		new->own = node;
		new->next = next;
	}
	else {
		printf("Out of memory!\n");
		exit(0);
	}

	return new;
}

// adds the given node into linkedlist 
int appendStar(struct Star *node){
	int id = 1;
	struct StarNode *temp;
	struct StarNode *prev;
	temp = &starRoot;

	if (starRoot.own == NULL) // if root is empty
	{
		// if doesn't conclude the star, adds the star into list 
		starRoot.id = 1;
		starRoot.own = node;
		starRoot.next = NULL;
	}else{

		// control the list what it is conclude the star or not
		while(temp != NULL){

			if (strcmp(temp->own->name, node->name) == 0) {
				return 0;
			}

			prev = temp;
			temp = temp->next;
			id++;
		}

		// if doesn't conclude the star, adds the star into list
		prev->next = makeStarNode(id, node, NULL);
	}
}

// creates a Star node and adds the node to linkedlist 
int addStar(char *name){	
	struct Star *new;
	new = makeStar(name);
	appendStar(new);	
}

// adds the given node into linkedlist 
int appendMovie(struct Movie *node){
	int id = 1;
	struct MovieNode *temp;
	struct MovieNode *prev;
	temp = &movieRoot;

	if (movieRoot.own == NULL) // if root is empty
	{
		// if doesn't conclude the star, adds the star into list 
		movieRoot.id = 1;
		movieRoot.own = node;
		movieRoot.next = NULL;
	}else{

		// control the list what it is conclude the star or not
		while(temp != NULL){

			if (strcmp(temp->own->name, node->name) == 0) {
				return 0;
			}

			prev = temp;
			temp = temp->next;
			id++;
		}

		// if doesn't conclude the star, adds the star into list
		prev->next = makeMovieNode(id, node, NULL);
	}
}

// creates a Movie node and adds the node to linkedlist 
int addMovie(char name[100]){
	struct Movie *new;
	new = makeMovie(name);
	appendMovie(new);	
}

// to link the star and the movie given names
int link(char *star_name, char *movie_name) {

	struct MovieNode *movie;
	struct StarNode *star;

	movie = &movieRoot;
	star = &starRoot;

	// control the list what it is conclude the star or not
	while(movie != NULL){

		if (strcmp(movie->own->name, movie_name) == 0) {
			while(star != NULL){
				if (strcmp(star->own->name, star_name) == 0) {	
					for (int i = 0; i < 15; ++i) {
						
						if (star->own->movies[i] != NULL) {
							if(strcmp(star->own->movies[i]->name, movie->own->name) == 0)
							break; 
							star->own->movies[i] = movie->own;
							break;
						}
					}

					for (int i = 0; i < 15; ++i) {
						if (movie->own->stars[i] != NULL) {
							if(strcmp(movie->own->stars[i]->name, star->own->name) == 0)
							break;
							movie->own->stars[i] = star->own;
							break;
						}
					}
					return 1;
				}
				star = star->next;
			}
			return 0;
		}
		movie = movie->next;
	}
	return 0;
}

// controls the stars is valid
int isValidStar(char *line){

	struct StarNode *star;
	star = &starRoot;

	int isExist = 0;

	replace(line);

	char *token;
	token = strtok(line, ",");

	while(token != NULL){

		star = &starRoot;
		isExist = 0;

		undo(token);

		while(star != NULL && star->id != 0){

			if (strcmp(star->own->name, token) == 0) {		
				isExist = 1;
			}

			star = star->next;
		}

		if(isExist == 0) return 0;
		
		token = strtok(NULL, ",");
		if(token == NULL) break;
		token++;
	}

	token = line;

	return 1;
}

// controls the movies is valid
int isValidMovie(char* line){

	struct MovieNode *movie;
	movie = &movieRoot;

	int isExist = 0;

	replace(line);

	char *token;
	token = strtok(line, ",");

	while(token != NULL){

		movie = &movieRoot;
		isExist = 0;

		undo(token);

		while(movie != NULL && movie->id != 0){

			if (strcmp(movie->own->name, token) == 0) {		
				isExist = 1;
			}

			movie = movie->next;
		}

		if(isExist == 0) return 0;
		
		token = strtok(NULL, ",");
		if(token == NULL) break;
		token++;
	}

	token = line;

	return 1;
}

// the add method
int add(){
	char add_type, temp;
  	size_t size = 1000;
  	char* line = NULL;

    printf("Enter add type(s/m/r): ");
    scanf("%c%c", &add_type, &temp); // takes the add type

	// if the add type is 's'
    if (add_type == 's') {

		printf("Enter star names: ");
		getline(&line, &size, stdin); // takes the star names

		char *token;
		replace(&line[0]);
		token = strtok(line, ",");

		while(token != NULL){
			addStar(token);			// adds the star
			token = strtok(NULL, ",");
			if(token == NULL) break;
			token++;
		}
	}

	// if the add type is 'm'
	else if (add_type == 'm') {
		
		printf("Enter movie names: ");
		getline(&line, &size, stdin); // takes the movie names

		char *token;
		replace(line);
		token = strtok(line, ",");

		while(token != NULL){
			addMovie(token);		// adds the movie
			token = strtok(NULL, ",");
			if(token == NULL) break;
			token++;
		}
	}

	// if the add type is 'r'
	else if(add_type == 'r') {

		char* star = NULL;
		char* movie = NULL;
		char temp[1000];

		char *token_star;
		char *token_movie;
		
		char star_array[15][100];
		char movie_array[15][100];

		int i = 0;
		int j = 0;
		
		printf("Enter star names: ");
		getline(&star, &size, stdin); // takes the star names
		strcpy(temp, star);

		while(isValidStar(temp) == 0){
			printf("Enter valid star names: ");
			getline(&star, &size, stdin); // takes the star names
			strcpy(temp, star);
		}

		replace(star);

		token_star = strtok(star, ",");
		while(token_star != NULL){
			
			strcpy(star_array[i], token_star);
			i++;

			token_star = strtok(NULL, ",");
			if(token_star == NULL) break;
			token_star++;
		}

		printf("Enter movie names: ");
		getline(&movie, &size, stdin); // takes the movie names
		strcpy(temp, movie);

		while(isValidMovie(temp) == 0){
			printf("Enter valid movie names: ");
			getline(&movie, &size, stdin); // takes the star names
			strcpy(temp, movie);
		}

		replace(movie);

		token_movie = strtok(movie, ",");
		while(token_movie != NULL){

			strcpy(movie_array[j], token_movie);
			j++;

			token_movie = strtok(NULL, ",");
			if(token_movie == NULL) break;
			token_movie++;
		}

		for(int k=0; k<i; k++){
			for(int l=0; l<j; l++){
				// links the star with the movie
				link(star_array[k], movie_array[l]);
			}
		}
	}

	// if the add type is invalid
	else{
		printf("Invalid add type!\n");
		exit(0);
	} 	
}

// the print method
int print(){
	char print_type, temp;

    printf("Enter print type(s/m): ");
    scanf("%c%c", &print_type, &temp); // take the print type

    while(print_type != 's' && print_type != 'm'){
    	printf("Enter valid print type(s/m): ");
   		scanf("%c%c", &print_type, &temp); // take the print type
	}

    // if the print type is 's'
    if (print_type == 's') {
    	struct StarNode *temp;
    	temp = &starRoot;

    	if (starRoot.id == 0) {
    		printf("No star found.\n");
    		return 1;
    	}

    	while(temp != NULL){
    		printf("%d- %s\n", temp->id, temp->own->name);
    		temp = temp->next;
    	}		
	}

	// if the print type is 'm'
	else if (print_type == 'm') {
		struct MovieNode *temp;
    	temp = &movieRoot;

    	if (movieRoot.id == 0) {
    		printf("No movie found.\n");
    		return 1;
    	}

    	while(temp != NULL){
    		printf("%d- %s\n", temp->id, temp->own->name);
    		temp = temp->next;
    	}	
	}
}

// the search method
int search(){
	char search_type, temp;
	size_t size = 1000;
  	char* line = NULL;
  	char temp_line[1000];

    printf("Enter search type(s/m): ");
    scanf("%c%c", &search_type, &temp); // take the search type

    while(search_type != 's' && search_type != 'm'){
    	printf("Enter valid search type(s/m): ");
   		scanf("%c%c", &search_type, &temp); // take the search type
	}

	// if the search type is 's'
    if (search_type == 's') {
		struct StarNode *star;
		star = &starRoot;

    	printf("Enter movie names: ");
		getline(&line, &size, stdin); // takes the movie names
		strcpy(temp_line, line);

    	while(star != NULL){

			char *movie_name;
			movie_name = strtok(temp_line, ",");
			int isOK = 1;

			while(movie_name != NULL){
				int isExist = 0;

				for (int i = 0; i < 15; ++i) {	
					if (star->own->movies[i] == NULL) break;

					if (strcmp(star->own->movies[i]->name, movie_name) == 0) {
						isExist = 1;
					}
				}

				if (isExist == 0) 
					isOK = 0;
			
				movie_name = strtok(NULL, ",");
				if(movie_name == NULL) break;
				movie_name++;
			}

			if (isOK == 1){
				printf("%d- %s\n", star->id, star->own->name);			
			}

			strcpy(temp_line, line);
			star = star->next;
		}		
	}

	// if the search type is 'm'
	else if (search_type == 'm') {
		struct MovieNode *movie;
    	movie = &movieRoot;

		printf("Enter star names: ");
		getline(&line, &size, stdin); // takes the star names

    	while(movie != NULL){

			char *star_name;
			star_name = strtok(line, ",");

			int isOK = 1;

			while(star_name != NULL){

				int isExist = 0;
				
				for (int i = 0; i < 15; ++i)
				{	
					if (movie->own->stars[i] == NULL) break;

					if (strcmp(movie->own->stars[i]->name, star_name) == 0) {
						isExist = 1;
					}
				}

				if (isExist == 0) {
					isOK = 0;
				}
				
				star_name = strtok(NULL, ",");
				if(star_name == NULL) break;
				star_name++;
			}

			if (isOK == 1){
				printf("%d- %s\n", movie->id, movie->own->name);			
			}

			movie = movie->next;
		}		
	}
}

/***** end of the methods *****/ 

// the main method
int main(){
	
	char command[20];
  	char* command_print = "print";
  	char* command_add = "add";
  	char* command_search = "search";

  	char temp;

    printf("Enter a command: ");
    scanf("%s%c", command, &temp); // take the command

    while(strcmp(command, "exit") != 0){ // if command is not exit

    	if (strcmp(command_print, command) == 0) {
    		print();
    		printf("Enter a command: ");
    		scanf("%s", command);
    	}
    	else if (strcmp(command_add, command) == 0) {
    		add();
    		printf("Enter a command: ");
    		scanf("%s", command);
    	}
    	else if(strcmp(command_search, command) == 0) {
    		search();
    		printf("Enter a command: ");
    		scanf("%s", command);
    	} 	
    	else{
    		printf("Enter a valid command: ");
    		scanf("%s", command);
    	}

    	scanf("%c", &temp);
    }

    printf("Exiting program.\n");

	return 0;
}