#include <stdio.h>

int powFour(int sayi){
	return sayi*sayi*sayi*sayi;
}

void print(int map[6][7]){

	printf("\nX 0 1 2 3 4 5 6 X\n");

	for (int i = 0; i < 6; i++)
	{
		printf("%d ", i);

		for (int j = 0; j < 7; j++)
		 {
		 	if(map[i][j] == 0) printf("_ ");
		 	else if(map[i][j] == 1) printf("R ");
		 	else if(map[i][j] == 2) printf("Y ");
		 }

		 printf("%d\n", i);
	}

	printf("X 0 1 2 3 4 5 6 X\n");

}

int add(int map[6][7], int player){

	int column;
	int ch;

	if(player == 1) ch = 'R';
	else if(player == 2) ch = 'Y';

	print(map);

	printf("\nPlayer %d's Turn (%c):\n", player, ch);
	printf("Enter a move: ");
	scanf("%d", &column);

	if (column > 6){ 
		printf("\nEntered move is not valid!\n");
		return 0;
	}

	int sol = 5;
	int done = 0;
	while(sol >= 0 && done == 0){
		if (map[sol][column] == 0)
		{
			map[sol][column] = player;
			done = 1;
			return 1;
		}
		sol--;
	}

	if (done == 0)
	{
		printf("\nThe column is full, try again!\n");
		return 0;
	}
}

int isWon(int map[6][7], int player){
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int toplam = 0;
			int carpim = 1;

			for (int k = j; k < j+4; k++)
			{
				toplam += map[i][k];
				carpim *= map[i][k];
			}

			if (toplam == 4*player && carpim == powFour(player))
				return 1;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int toplam = 0;
			int carpim = 1;

			for (int k = j; k < j+4; k++)
			{
				toplam += map[k][i];
				carpim *= map[k][i];
			}

			if (toplam == 4*player && carpim == powFour(player))
				return 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int toplam = 0;
			int carpim = 1;

			for (int k = 0; k < 4; k++)
			{
				toplam += map[i+k][j+k];
				carpim *= map[i+k][j+k];
			}

			if (toplam == 4*player && carpim == powFour(player))
				return 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 6; j > 2; j--)
		{
			int toplam = 0;
			int carpim = 1;

			for (int k = 0; k < 4; k++)
			{
				toplam += map[i+k][j-k];
				carpim *= map[i+k][j-k];
			}

			if (toplam == 4*player && carpim == powFour(player))
				return 1;
		}
	}

	return 0;
}

int main(){

	int map[6][7];
	int count = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			map[i][j] = 0;
		}
	}

	printf("The game has started!\n");

	while(count < 42){

		int done_1 = 0;

		do{
			done_1 = add(map, 1);
		}while(done_1 == 0);

		count++;

		if (isWon(map, 1))
		{
			print(map);
			printf("\nPlayer 1 has won!\n");
			return 1;
		}

		int done_2 = 0;

		do{
			done_2 = add(map, 2);
		}while(done_2 == 0);

		count++;

		if (isWon(map, 2))
		{
			print(map);
			printf("\nPlayer 2 has won!\n");
			return 1;
		}
	}

	return 0;
}