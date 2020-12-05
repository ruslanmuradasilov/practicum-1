#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Input(const char *sf, int **a, int *n)
{
	FILE* in = fopen(sf, "r");
	if(in!=NULL)
	{
		int i;
		*a = NULL; *n = 0;
		if(fscanf(in, "%d", n)!=1)
		{
			fclose(in);
			return -2;
		}
		if(*n>0)
		{
			*a = (int*)malloc(*n*sizeof(int));
			if(*a == NULL)
			{
				fclose(in);
				return -3;
			}
			for(i = 0; i < *n && fscanf(in, "%d", (*a)+i) == 1; i++);
			if(i < *n)
			{
				fclose(in);
				return -4;
			}
		}
		fclose(in);
		return 0;
	}
	else return -1;
}

int CountingSort(int *a, int n, int **c)
{
	int *b = NULL, i, j, max;
	max = a[0];
	for(i = 0; i < n; i++)
		if(a[i] > max)
			max = a[i];//находим максимальный элемент для размерности вспомогательного массива

	b = (int*)malloc(max*sizeof(int));
	for(i = 0; i <= max; i++)
		b[i] = 0;
	for(i = 0; i < n; i++)
		b[a[i]]++;//в соотв индексы записываем соотв элементы
	for(i = 1; i <= max; i++)
		b[i] += b[i - 1];//прибавляем каждый пред элемент
	

	*c = (int*)malloc(n*sizeof(int));
	for(i = n-1; i >= 0; i--)
	{
		b[a[i]]--;//для сохранения устойчивости
		(*c)[b[a[i]]] = a[i];//собираем отсортированный массив
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int *a = NULL, *c = NULL;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, i;
		rtn = Input(argv[1], &a, &n);
		if(rtn != 0) fprintf(out, "0");
		else
		{
			CountingSort(a, n, &c);
			fprintf(out, "%d ", n);
			for(i = 0; i < n; i++)
				fprintf(out, "%d ", c[i]);
			free(a);
			free(c);
		}
		fclose(out);
	}
	return 0;
}