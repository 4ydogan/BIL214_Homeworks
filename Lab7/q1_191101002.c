/* Mustafa Aydoğan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int nothing(FILE *inp, FILE *out){

	char ch;
	while((ch = fgetc(inp)) != EOF){
		fprintf(out, "%c", ch);
	}

	return 0;
}

int reverse(FILE* inp, FILE *out) {

    char line[10000];
    if( fgets(line, 10000, inp) == NULL )
        return 0;
    else {
        reverse(inp, out);
        fprintf(out, "%s", line);
    }
    return 0;
}

int sort(FILE* inp, FILE *out) {

	char lines[1000][1000];
	int count = 0;
	char temp[1000];

	for (int i = 0; i<1000 ; i++)
	{
		if (fgets(lines[i], 1000, inp) == NULL)
		{
			break;
		}
		count++;
	}

	for(int i=0; i<count; i++){
	    for(int j=0; j<count-1-i; j++){
			if(strcmp(lines[j], lines[j+1]) > 0){
				strcpy(temp, lines[j]);
				strcpy(lines[j], lines[j+1]);
				strcpy(lines[j+1], temp);
			}
	    }
   }

   for (int i = 0; i < count; i++)
	   	fprintf(out, "%s", lines[i]);
}

int switch_even(FILE* inp, FILE *out) {

	char line1[10000], line2[10000];
	int k = 1;

    while(fgets(line1, 10000, inp) != NULL ){
    	if (fgets(line2, 10000, inp) != NULL){
    		fprintf(out, "%s", line2);
        	fprintf(out, "%s", line1);
    	}else fprintf(out, "%s", line1);
    }

    return 0;
}

int main(int argc, char *argv[]){

	char* input;
	char* output;
	char* operation;
	int c;

	if (argc<7){
		printf("Wrong arguments!\n");
        return 0;
	}else{
		while ((c = getopt(argc, argv, "i:o:s:")) != -1)
	    switch (c){
			case 'i':
			input = optarg;
			break;
			case 'o':
			output = optarg;
			break;
			case 's':
			operation = optarg;
			break;
		}
    }

    FILE *input_file;
    input_file = fopen(input, "r");

    FILE *output_file;
    output_file = fopen(output, "w");

    if (strcmp(operation, "0") == 0) nothing(input_file, output_file);
    if (strcmp(operation, "1") == 0) sort(input_file, output_file);
    if (strcmp(operation, "2") == 0) reverse(input_file, output_file);
    if (strcmp(operation, "3") == 0) switch_even(input_file, output_file);

    fclose(input_file);
    fclose(output_file);
    
	return 0;
}