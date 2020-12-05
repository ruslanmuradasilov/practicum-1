#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Input(const char *sf, float **m, int *n, float *k)
{
	FILE* in = fopen(sf, "r");
	if(in!=NULL)
	{
		int i;
		*m = NULL; *n = 0; *k = 0;
		if(fscanf(in, "%f", k)!=1)
		{
			fclose(in);
			return -2;
		}
		if(fscanf(in, "%d", n)!=1)
		{
			fclose(in);
			return -2;
		}
		if(*n>0)
		{
			*m = (float*)malloc(*n*sizeof(float));
			if(*m == NULL)
			{
				fclose(in);
				return -3;
			}
			for(i = 0; i < *n && fscanf(in, "%f", (*m)+i) == 1; i++);
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

int segment(float *m, int n, float k)
{
	float x1, x2, halfsum;
	int i, j, rtn = 0, t = 0, p;
	if(n != 0)
	{
		i = 0;
		while (t != 1)
		{
			
			while ((m[i] != k) && (i <= n - 1)) i++;//ищем х-отрезок
			if(i > n-1) t = 1;
			else 
			{
				if (i == 0)
				{
					x1 = 0;
					p = i;
				}
				else 
				{
					x1 = m[i-1];
					p = i;
				}//запоминаем элемент до х-отрезка
				while((m[i] == k) && (i <= n-1)) i++;//считаем кол-во элементов х-отрезка
				if(i > n-1)
				{
					x2 = 0;
					t = 1;
				}
				else x2 = m[i];//запоминаем элемент после х-отрезка
				halfsum = (x1 + x2)/2;
				for(j = p; j < i; j++)
					m[j] = halfsum;
			}
			//переходим к следующему х-отрезку
		}
	}
	else rtn = -1;
	return rtn;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		float *m, k;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, i;
		rtn = Input(argv[1], &m, &n, &k);
		if(rtn != 0) fprintf(out, "0");
		else
		{
			rtn = segment(m, n , k);
			if(rtn!=0) fprintf(out, "0");
			else
			{
				fprintf(out, "%d ", n);
				for(i = 0; i < n; i++) fprintf(out, "%f ", m[i]);
			}
			free(m);
		}
		fclose(out);
		return rtn;
	}
}
