#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _SPoint
{
	float x;
	float y;
}Point;

typedef struct _SSegment
{
	Point beg;
	Point end;
}Segment;

int Input (const char *sf, Segment **m, int *n)
{
	int i, rtn = 0;
	Point p;
	FILE *in = fopen(sf, "r");
	if(fscanf(in, "%d", &(*n)) != 1) rtn = -1;
	else
	{
		if (*n > 0)
		{
			*m = (Segment*)malloc((*n)*sizeof(Segment));// создаем массив отрезков
			fscanf(in, "%f %f", &p.x, &p.y);
			(*m + 0) -> beg = p;
			fscanf(in, "%f %f", &p.x, &p.y);
			(*m + 0) -> end = p;
			for (i = 1; i < *n; i++)
			{
				(*m + i) -> beg = p;//началу следующего отрезка присваиваем конец предыдущего
				fscanf(in, "%f %f", &p.x, &p.y);
				(*m + i) -> end = p;
			}
			(*m + (*n-1)) -> end = (*m + 0) -> beg;//замыкаем ломаную в многоугольник
		}
		else rtn = -2;
	}
	fclose(in);
	return rtn;
}

int ComplexCheck(Segment *m, int n)
{
	int i, rtn = 1;
	float vec1, vec2;
	vec1 = (m[0].end.x - m[0].beg.x)*(m[1].end.y - m[1].beg.y) - (m[1].end.x - m[1].beg.x)*(m[0].end.y - m[0].beg.y);//а1*b2 - a2*b1, считаем первое векторное произведение
	i = 1;
	while((rtn == 1) && (i < (n-1)))
	{
		vec2 = (m[i].end.x - m[i].beg.x)*(m[i+1].end.y - m[i+1].beg.y) - (m[i+1].end.x - m[i+1].beg.x)*(m[i].end.y - m[i].beg.y);//считаем остальные векторные произведения
		if(vec2*vec1 < 0) rtn = 0;
		i++;
	}
	if(rtn == 1)
	{
		vec2 = (m[n-1].end.x - m[n-1].beg.x)*(m[0].end.y - m[0].beg.y) - (m[0].end.x - m[0].beg.x)*(m[n-1].end.y - m[n-1].beg.y);//считаем последнее векторное произведение
		if(vec2*vec1 < 0) rtn = 0;
	}
	return rtn;
}


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		Segment *m;
		FILE* out = fopen(argv[2], "w");
		int rtn, n;
		Input(argv[1], &m, &n);
		rtn = ComplexCheck(m, n);
		if(rtn == 1) fprintf(out, "1");//выпуклый
		if(rtn == 0) fprintf(out, "0");//вогнутый
		free(m);
		fclose(out);
	}
	return 0;
}
