/* Mustafa Aydogan 191101002 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max_index(int* array, int length){
	int max = 0;
	int index = 0;
	int i = 0;

	while(i<length){
		if(max<array[i]){
			max = array[i];
			index = i;
		} 
		i++;
	}
	return index;
}

int min_index(int* array, int length){
	int min = array[0];
	int index = 0;
	int i = 1;

	while(i<length){
		if(min > array[i]){
			min = array[i];
			index = i;
		}
		i++;
	} 

	return index;
}

int exists(char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int worth(char ch){
	if (ch <= 90 && ch >= 65)
		return ch-65;

	else if(ch <= 122 && ch >= 97)
		return ch-97;

	else
		return 26;
}

int main(int argc, char *args[]){

	char* reference;
	char* input;
	char* output;

	if(argc<7){
        printf("Wrong arguments!\n");
        exit(0);
	}
    else{
        if(strcmp(args[1], "-r") == 0) reference = args[2];
		else if(strcmp(args[1], "-c") == 0) input = args[2];
		else if(strcmp(args[1], "-p") == 0) output = args[2];
		
		if(strcmp(args[3], "-r") == 0) reference = args[4];
		else if(strcmp(args[3], "-c") == 0) input = args[4];
		else if(strcmp(args[3], "-p") == 0) output = args[4];

		if(strcmp(args[5], "-r") == 0) reference = args[6];
		else if(strcmp(args[5], "-c") == 0) input = args[6];
		else if(strcmp(args[5], "-p") == 0) output = args[6];
    }

	/*printf("%s\n", reference);
	printf("%s\n", input);
	printf("%s\n", output);*/

	if (exists(reference) == 0)
	{
		printf("%s dosyası bulunamadı.\n", reference);
		exit(0);
	}

	if (exists(input) == 0)
	{
		printf("%s dosyası bulunamadı.\n", input);
		exit(0);
	}

	int ref_count[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int inp_count[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	char ch;
	int index;

	FILE *ref_file;
	ref_file = fopen(reference, "r");
	
	while((ch = fgetc(ref_file)) != EOF){
		index = worth(ch);
		ref_count[index]++;
	}

	fclose(ref_file);

	FILE *input_file;
	input_file = fopen(input, "r");
	
	while((ch = fgetc(input_file)) != EOF){
		index = worth(ch);
		inp_count[index]++;
	}

	fclose(input_file);

	int ref_max = max_index(ref_count, 26);
	int inp_max = max_index(inp_count, 26)+26;

	int ref_min = min_index(ref_count, 26);
	int inp_min = min_index(inp_count, 26)+26;

	int fark_max = abs(ref_max - inp_max)%26;
	int fark_min = abs(ref_min - inp_min)%26;

	input_file = fopen(input, "r");

	if (fark_max == fark_min)
	{
		FILE *output_file;
		output_file = fopen(output, "w+");

		while((ch = fgetc(input_file)) != EOF){
			int a = worth(ch);
			char x = (a-fark_min+26)%26;

			fprintf(output_file, "%c", x+97);
		}

		fclose(output_file);

		printf("Kayırma miktarı %d olarak tespit edilmiştir.\n", fark_min);
		printf("Çözümlenmiş metin %s dosyasına yazılmıştır\n", output);
	}else{
		
		int len = 0;
		len = strlen(output);

		char output1[50] = "";
		char output2[50] = "";
		int i = len-4; 

		strncat(output1, output, i);
		strncat(output2, output, i);

		strcat(output1, "_0.txt");
		strcat(output2, "_1.txt");

		FILE *output_file1, *output_file2;

		output_file1 = fopen(output1, "w+");
		output_file2 = fopen(output2, "w+");

		while((ch = fgetc(input_file)) != EOF){
			int a = worth(ch);
			char x = (a-fark_min+26)%26;
			char y = (a-fark_max+26)%26;
			fprintf(output_file1, "%c", x+97);
			fprintf(output_file2, "%c", y+97);
		}

		fclose(output_file1);
		fclose(output_file2);

		printf("Kayırma miktarı %d (en sık harf) ve %d (en seyrek harf) olarak tespit edilmiştir.\n", fark_max, fark_min);
		printf("Çözümlenmiş metin %s  ve %s dosyalarına yazılmıştır\n", output1, output2);

	}

	fclose(input_file);

	return 0;
}