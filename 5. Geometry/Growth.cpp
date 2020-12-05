#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _SPoint
{
	float x;
	float y;
}Point;

typedef struct _SLine
{
	float a;
	float b;
	float c;
}Line;

int Input(const char *sf, Point **m, int *n, float *h)
{
	int i, rtn = 0;
	float x, y;
	FILE *in = fopen(sf, "r");
	fscanf(in, "%f", &(*h));
	if(fscanf(in, "%d", &(*n)) != 1) rtn = -1;
	else
	{
		if (*n > 0)
		{
			*m = (Point*)malloc((*n)*sizeof(Point));// ������� ������ ������
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

void Equation(Point *m, Line *p, float h, int current, int prev)//�������, ������������ ��������� ����� ������ �� ���������� h �� ������
{
	p[prev].a = m[prev].y - m[current].y;//a1 = y2 - y1 (�� ������� ������, ���������� ����� ��� �����)
	p[prev].b = m[current].x - m[prev].x;//b1 = -(x2 - x1) (�� ������� ������, ���������� ����� ��� �����)
	p[prev].c = h*sqrt(p[prev].a * p[prev].a + p[prev].b*p[prev].b) + (m[current].x*m[prev].y - m[prev].x*m[current].y);//c1 = h*sqrt(a^2 + b^2) + c2, ��� c2 - ��������� ���� �������� ������ � c2 = x1*y2 - x2*y1
}

void Cross(Point *m, Line *p, int current, int prev)//�������, ��������� ���������� ����� ����������� ���� ������
{
	//������� ������� ��� ����������� ������, ���� �� ����� ���������
	m[current].x = -(p[prev].b*p[current].c - p[current].b*p[prev].c) / (p[prev].a*p[current].b - p[current].a*p[prev].b);//x = -(c1*b2 - c2*b1)/(a1*b2 - a2*b1)
	m[current].y = -(p[current].a*p[prev].c - p[prev].a*p[current].c) / (p[prev].a*p[current].b - p[current].a*p[prev].b);//y = -(a1*c2 - a2*c1)/(a1*b2 - a2*b1)
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		Point *m;
		Line *p;
		FILE* out = fopen(argv[2], "w");
		int rtn, n, i;
		float h;
		Input(argv[1], &m, &n, &h);
		p = (Line*)malloc(n*sizeof(Line));
		Equation(m, p, h, 0, n-1);//������ ��a������ ������ ������������ ��������������
		for(i = 1; i < n; i++)
			Equation(m, p, h, i, i-1);

		Cross(m, p, 0, n-1);//������� �� ����� �����������, �� ���� ���������� ����� ������
		for(i = 1; i < n; i++)
			Cross(m, p, i, i-1);
		
		for(i = 0; i < n; i++)
			fprintf(out, "%f %f ", m[i].x, m[i].y);
		fclose(out);
		free(m);
		free(p);
	}
	return 0;
}
