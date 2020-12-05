#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int k = 0, t = 0;
		float x, y;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");

		fscanf(in, "%f", &x);
		while(fscanf(in, "%f", &y) == 1)
		{
			if(x < y)//находим начало возврастающего участка
				t = 1;
			else
			{
				if(t == 1)
				{
					k++;//подсчитываем этот участок
					t = 0;
				}	
			}
			x = y;//сдвигаемся
		}
		if(t == 1) k++;//прибавляем участок, который остался на конце
		fclose(in);
	
		fprintf(out, "%d", k);
		fclose(out);
	}
	return 0;
}