#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int k = 0, t = 0;
		float x, y;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");

		fscanf(in, "%f", &x);
		while(fscanf(in, "%f", &y) == 1)
		{
			if(x < y)//������� ������ �������������� �������
				t = 1;
			else
			{
				if(t == 1)
				{
					k++;//������������ ���� �������
					t = 0;
				}	
			}
			x = y;//����������
		}
		if(t == 1) k++;//���������� �������, ������� ������� �� �����
		fclose(in);
	
		fprintf(out, "%d", k);
		fclose(out);
	}
	return 0;
}