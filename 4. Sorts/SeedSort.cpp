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

int SeedSort(int *a, int n)
{
	int i, j, l, temp;
	for(i = 0; i < n ; i++)
		{
			for(j = 1 ; j < n; j++)
			{
				if(a[j-1] > a[j])
				{
					temp = a[j-1];
					a[j-1] = a[j];
					a[j] = temp;
				}
				if(j > 1)//не крайний элемент
				{
					for(l = j - 1; l > 0; l--)
						if(a[l] < a[l-1])
						{
							temp = a[l];
							a[l] = a[l - 1];
							a[l-1] = temp;
						}//делаем мини-пузырек влево
				}
			}
		}
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int *a;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, i;
		rtn = Input(argv[1], &a, &n);
		if(rtn != 0) fprintf(out, "0");
		else
		{
			SeedSort(a, n);
			fprintf(out, "%d ", n);
			for(i = 0; i < n; i++)
				fprintf(out, "%d ", a[i]);
			free(a);
		}
		fclose(out);
	}
	return 0;
}