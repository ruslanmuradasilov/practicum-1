#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _SPoint
{
	float x;
	float y;
}Point;

int Input(const char *sf, Point **m1, int *n1, Point **m2, int *n2)
{
	int i, rtn = 0;
	float x, y;
	FILE *in = fopen(sf, "r");
	if(fscanf(in, "%d", &(*n1)) != 1) rtn = -1;
	else
	{
		if (*n1 > 0)
		{
			*m1 = (Point*)malloc((*n1)*sizeof(Point));// создаем массив точек 1го многоугольника
			for (i = 0; i < *n1; i++)
			{
				fscanf(in, "%f %f", &x, &y);
				(*m1 + i) -> x = x;
				(*m1 + i) -> y = y;
			}
		}
		else rtn = -2;
	}
	if(fscanf(in, "%d", &(*n2)) != 1) rtn = -3;
	else
	{
		if (*n2 > 0)
		{
			*m2 = (Point*)malloc((*n2)*sizeof(Point));// создаем массив точек 2го многоугольника
			for (i = 0; i < *n2; i++)
			{
				fscanf(in, "%f %f", &x, &y);
				(*m2 + i) -> x = x;
				(*m2 + i) -> y = y;
			}
		}
		else rtn = -4;
	}
	fclose(in);
	return rtn;
}
int Cross(Point a, Point b, Point c, Point d)
{
	int rtn = 0;
	float v1, v2, v3, v4;// x1*y2 - x2*y1;
	if( ( ((a.x != b.x) && (a.x != c.x) && (a.x != d.x)) || ((a.y != b.y) && (a.y != c.y) && (a.y != d.y)) ) == 0 )//если оба отрезка не лежат на одной прямой
	{
		v1 = ((d.x - c.x)*(c.y - a.y)) - ((d.y - c.y)*(c.x - a.x));
		v2 = ((d.x - c.x)*(b.y - c.y)) - ((d.y - c.y)*(b.x - c.x));
		v3 = ((b.x - a.x)*(c.y - a.y)) - ((b.y - a.y)*(c.x - a.x));
		v4 = ((b.x - a.x)*(d.y - a.y)) - ((b.y - a.y)*(d.x - a.x));
		if((v1*v2 <= 0) && (v3*v4 <= 0)) rtn = 1;//отрезки пересеклись или имеют общее начало или конец
	}
	return rtn;
}
int CrossCheck(Point *m1, int n1, Point *m2, int n2)
{
	int i, j, p, q, rtn = 0;
	for(i = 0; i < n1; i++)
	{
		p = i + 1;
		if(i == n1 - 1)
			p = 0;
		for (j = 0; j < n2; j++)
		{
			q = j + 1;
			if(j == n2 - 1)
				q = 0;
			if( (Cross(m1[i], m1[p], m2[j], m2[q]) ) == 1)//отрезки, то есть многоугольники, пересеклись или коснулись => расстояние ровно 0
			{
				rtn = 1;
				break;
			}
		}
	}
	return rtn;
}

float MinDis(Point *m1, int n1, Point *m2, int n2)
{
	float *m, mindis;
	int i, j, k = 0;
	m = (float*)malloc((n1*n2)*sizeof(float));

	for(i = 0; i < n1; i++)
	{
		for(j = 0; j < n2; j++)
		{
			m[k] = sqrt( (m2[j].x - m1[i].x)*(m2[j].x - m1[i].x) + (m2[j].y - m1[i].y)*(m2[j].y - m1[i].y) ); // собираем расстояния между всеми точками
			if((i == 0) && (j == 0))
				mindis = m[0];
			if(m[k] < mindis)// находим минимальное расстояние
				mindis = m[k];
			k++;
		}
	}
	free(m);
	return mindis;
}

float Distance(Point *m1, Point *m2, int curr, int prev, int j)
{
	float x, y;//координаты основания перпендикуляра 
	float d = -1;
	if(m1[curr].x == m1[prev].x)//вертикаль
	{
		x = m1[curr].x;
		y = m2[j].y;
	}
	if(m1[curr].y == m1[prev].y)//горизонталь
	{
		x = m2[j].x;
		y = m1[curr].y;
	}
	if((m1[curr].x != m1[prev].x) && (m1[curr].y != m1[prev].y))//общий случай
	{
		x = ((m1[prev].x - m1[curr].x)*(m1[prev].y - m1[curr].y)*(m2[j].y - m1[curr].y) + m1[curr].x*(m1[prev].y - m1[curr].y)*(m1[prev].y - m1[curr].y) + m2[j].x*(m1[prev].x - m1[curr].x)*(m1[prev].x - m1[curr].x))/((m1[prev].y - m1[curr].y)*(m1[prev].y - m1[curr].y) + (m1[prev].x - m1[curr].x)*(m1[prev].x - m1[curr].x));
		y = ((m1[prev].y - m1[curr].y)*(x - m1[curr].x)) / ((m1[prev].x - m1[curr].x) + m1[curr].y);
	}
	if(((x-m1[curr].x)*(x-m1[prev].x) <= 0) && ((y-m1[curr].y)*(y-m1[prev].y) <= 0))//проверяем принадлежность точки отрезку
		d = sqrt((x - m2[j].x)*(x - m2[j].x) + (y - m2[j].y)*(y - m2[j].y));//находим расстояние
	return d;
}


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		Point *m1, *m2;
		FILE* out = fopen(argv[2], "w");
		float mindis1, mindis2, dis2, dis3, mindis3;
		int rtn, n1, n2, i, j;
		Input(argv[1], &m1, &n1, &m2, &n2);

		rtn = CrossCheck(m1, n1, m2, n2);//проверка на пересечение многоугольников
		if(rtn == 1) fprintf(out, "0");
		else 
		{
			mindis1 = MinDis(m1, n1, m2, n2);//минимальное расстояние по точкам
			mindis2 = mindis1;
			//берем точки 1ого многоугольника и опускаем перпендикуляры на стороны второго
			for(i = 0; i < n2; i++)
			{
				dis2 = Distance(m1, m2, 0, n1-1, i);
				if((dis2 < mindis2) && (dis2 != -1))
					mindis2 = dis2;
			}
			for(i = 0; i < n2; i++)
			{
				for(j = 1; j < n1; j++)
				{
					dis2 = Distance(m1, m2, j, j-1, i);
					if((dis2 < mindis2) && (dis2 != -1))//находим минимальное расстояние
						mindis2 = dis2;
				}
			}
			//берем точки 1ого многоугольника и опускаем перпендикуляры на стороны второго
			mindis3 = mindis2;
			for(i = 0; i < n1; i++)
			{
				dis3 = Distance(m2, m1, 0, n2-1, i);
				if((dis3 < mindis3) && (dis3 != -1))
					mindis3 = dis3;
			}
			for(i = 0; i < n1; i++)
			{
				for(j = 1; j < n2; j++)
				{
					dis3 = Distance(m2, m1, j, j-1, i);
					if((dis3 < mindis3) && (dis3 != -1))//находим минимальное расстояние
						mindis3 = dis3;
				}
			}
			fprintf(out, "%f", mindis3);
		}
		free(m1);
		free(m2);
		fclose(out);
	}
	return 0;
}