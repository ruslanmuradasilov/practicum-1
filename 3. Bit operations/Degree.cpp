#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[])
{
	if (argc > 1)
	{
		int k, n, res = 1;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");
		fscanf(in, "%d", &k);
		fscanf(in, "%d", &n);
		fclose(in);

		while (n != 0)
			if (n & 1 != 0)//�������� �� ����������, ������ ������ � ������� = 1
			{
				res *= k;//�������� ����� �� ����
				n--;//������� ���� �������
			}
			else
			{
				k *= k;//�������� ���������� ����� �� ���� �� ��� ���, ���� ������ �� ������ 1
				n = n>>1; //����� ������� �������
			}
		fprintf(out, "%d", res);
		fclose(out);
	}
	return 0;
}