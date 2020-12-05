#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Input(const char *sf, float **m, int *n1, int *n2)
{
	int rtn;
	FILE* in = fopen(sf, "r");
	if(in!=NULL)
	{
		int i;
		*m = NULL; *n1 = 0; *n2 = 0;
		if(fscanf(in, "%d", n1)!=1)
		{
			fclose(in);
			rtn = -2;
		}
		if(*n1>0)
		{
			*m = (float*)malloc(*n1*sizeof(float));//считываем один массив
			if(*m == NULL)
			{
				fclose(in);
				rtn = -3;
			}
			for(i = 0; i < *n1 && fscanf(in, "%f", (*m)+i) == 1; i++);
			if(fscanf(in, "%d", n2)!=1)
			{
				fclose(in);
				rtn = -4;
			}
			if(*n2>0)
			{
				*m = (float*)realloc(*m, ((*n1)+(*n2))*sizeof(float));//считываем второй массив в один общий
				for(i = *n1; i < ((*n1) + (*n2)) && fscanf(in, "%f", (*m)+i) == 1; i++);
			}

		}
		fclose(in);
		rtn = 0;
	}
	else rtn = -1;
	return rtn;
}

void Union(float *m, int n)//сортируем по неубыванию
{
	float temp;
	int i, j;
	for(i = 0; i < n ; i++)
		for(j = 1 ; j < n; j++)
				if(m[j-1] > m[j])
				{
					temp = m[j-1];
					m[j-1] = m[j];
					m[j] = temp;
				}
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		float *m = NULL;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, n1, n2, i;
		rtn = Input(argv[1], &m, &n1, &n2);
		if(rtn != 0) fprintf(out, "0");
		else
		{
			n = n1+n2;
			Union(m, n);
			fprintf(out, "%d ", n);
			for(i = 0; i < n; i++) fprintf(out, "%f ", m[i]);
			free(m);
		}
		fclose(out);
	}
	return 0;
}