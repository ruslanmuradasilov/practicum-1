#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int t, i, p, n, j;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");
		fscanf(in, "%d", &n);
		fclose(in);
		for (i = 0; i < 1 << n; i++)//i < 2^n
		{
			p = n;
			t = i;
			for (j = 0; j < n; j++)//���� ����� ��� ������ ����� �� n ���� � ������ ������
			{
				if ((t & (1 << n - 1)) != 0)//�������� ��� �������� ����� ������������ ����������� ����� ������������, ������� � ��������� ������������ ���� �� 0, �������� 100*100
					fprintf(out, "%d ", p);
				else//����� ������� 0
					fprintf(out, "%d ", 0);
				t = t << 1;//�������� �� 2, ����� �������� �������� ��� �������� ���������, ������ ��� ��������� ��������
				p--;//�������� ��� ����������� ������ �� ������ ������
			}
			fprintf(out, "\n");
	  }
	  fclose(out);
	}
	return 0;
}