#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Input(const char *sf, float **m, int *n, int *k)
{
	FILE* in = fopen(sf, "r");
	if(in!=NULL)
	{
		int i;
		*m = NULL; *n = 0; *k = 0;
		if(fscanf(in, "%d", k)!=1)
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

int reverse(float *m, int beg, int end)//функци€ записывающа€ элементы массива с индексами с beg по end наоборот
{
	int rtn = 0;
	float temp;
	if(beg >= end) rtn = -1;
	while(beg < end)
	{
		temp = m[beg];
		m[beg] = m[end];
		m[end] = temp;
		beg++;
		end--;
	}
	return rtn;
}

int displacement(float *m, int n, int k)//функци€, осуществл€юща€ сдвиг
{
	int rtn = 0;
	if(n == 0) rtn = -1;
	if(rtn == 0)
	{
		if(k>=n) k = k%n;//убираем кол-во повторных циклов
		reverse(m, n-k, n);//разворачиваем элементы с к-ого индекса до конца
		reverse(m, 0, n-k);//разворачиваем элементы с начала до к-ого индекса
		reverse(m, 0, n);//разворачиваем весь массив
	}
	return rtn;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		float *m;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, k, i;
		rtn = Input(argv[1], &m, &n, &k);
		if(rtn!=0) fprintf(out, "0");
		else
		{
			rtn = displacement(m, n, k);
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
