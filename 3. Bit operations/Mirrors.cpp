#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int i, n, j, p, n1, n2, t;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");
		fscanf(in, "%d", &n);
		fclose(in);
		for (i = 1, t = 0; t < n; i++)
		{
			p = 1;
			for (j = 0; j < 8; j++)
			{
				n1 = i & (1 << j);//����� ���� �������� �����
				n2 = i & (1 << (15 - j));//����� ���� ���������� �����
				if (!(((n1 == 0) && (n2 == 0)) || ((n1 != 0) && (n2 != 0))))//���������� ��
					p = 0;//��������, ���� ������
			}
			if (p == 1)
			{
				fprintf(out, "%d ", i);
				t++;
			}
			
		}
		fclose(out);
	}
	return 0;
}