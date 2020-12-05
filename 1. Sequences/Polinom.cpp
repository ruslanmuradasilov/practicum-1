#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		float x, a1, a2, y, res, respr, c, k = 2;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");
		fscanf(in, "%f", &x);
		c = x;//���������� ����� �
		fscanf(in, "%f", &a1);
		if(fscanf(in, "%f", &a2) != 1)//���� ����� ����� ���� �����������
		{
			res = a1;
			respr = 0;
		}
		else
		{
			res = a1 + (a2*x);//���� ����� ��� ������������
			respr  = a2;
			while(fscanf (in, "%f", &y) == 1)//���� n �������������
			{
				res += (x*x)*y;
				x = x*x*x;//������� ������� ����������
				respr += y*c*k;
				c = c*c;//������� ������� �����������
				k++;//�������� �� ����� ��� ������� ��������� ������� �����������
			}
		}
		fclose(in);
		fprintf(out, "%f %f", res, respr);
		fclose(out);
	}
	return 0;
}
