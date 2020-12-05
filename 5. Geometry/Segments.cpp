#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _SPoint
{
	float x;
	float y;
}Point;


int Input(const char *sf, Point **m, int *n)
{
	int i, rtn = 0;
	float x, y;
	FILE *in = fopen(sf, "r");
	if(fscanf(in, "%d", &(*n)) != 1) rtn = -1;
	else
	{
		if (*n > 0)
		{
			*m = (Point*)malloc((*n)*sizeof(Point));// создаем массив отрезков
			for (i = 0; i < *n; i++)
			{
				fscanf(in, "%f %f", &x, &y);
				(*m + i) -> x = x;
				(*m + i) -> y = y;
			}
		}
		else rtn = -2;
	}
	fclose(in);
	return rtn;
}

void sort(Point *m, int n)//сортируем координаты
{
	int i;
	float temp;
	for (i = 0; i < n; i++)
	{
		if(m[i].x > m[i].y)
		{
			temp = m[i].x;
			m[i].x = m[i].y;
			m[i].y = temp;
		}
	}
}

int situation1(Point *m, int n)
{
	int i, rtn = 0;
	for(i = 1; i < n; i++)
	{
		if((m[0].x >= m[i].x) && (m[0].y <= m[i].y))//отрезок [a, b] лежит внутри одного отрезков, например, [0, 4] и отрезок [1, 3]
			rtn = 1;
	}
	return rtn;
}

int situation2(Point *m, int n)
{
	int i, j, rtn = 0;
	for(i = 1; i < n; i++)
	{
		for(j = 2; j < n; j++)
		{
			if((m[i].x <= m[j].y) && (m[i].y >= m[j].x))//отрезок [a, b] лежит внутри пересечения или соприкосновения отрезков, например, [0, 3] и [2, 5]  и отрезок [1, 4]
			{
				if(((m[0].x >= m[i].x) && (m[0].y <= m[j].y)) || ((m[0].x >= m[j].x) && (m[0].y <= m[i].y)))
					rtn = 1;
			}
		}
	}
	return rtn;
}

int SegmentCheck(Point *m, int n)//проверяем обе ситуации
{
	int rtn = 0;
	sort(m, n);
	if((situation1(m, n)) != 0)
			rtn = 1;
	if(rtn == 0)
	{
		if((situation2(m, n)) != 0)
			rtn = 1;
	}
	return rtn;
}


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		Point *m;
		FILE* out = fopen(argv[2], "w");
		int rtn, n;
		Input(argv[1], &m, &n);

		rtn = SegmentCheck(m, n);
		if(rtn == 1) fprintf(out, "1");//отрезок принадлежит объединению данных
		if(rtn == 0) fprintf(out, "0");//отрезок не принадлежит объединению данных
		free(m);
		fclose(out);
	}
	return 0;
}