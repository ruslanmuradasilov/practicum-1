#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		float x, res = 0, k = 0;
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");
		
		while(fscanf(in, "%f", &x) == 1)
		{
			res += x;//������� ����� ����� ������������������
			k++;//������� �� ����������
		}
		fclose(in);
		res = res/k;//������� ��������������
	
		fprintf(out, "%f", res);
		fclose(out);
	}
	return 0;
}
