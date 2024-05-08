#include "generate_map.h"
void generate_layer3(int n, int m)
{
	srand(time(0));
	std::ofstream fout("image/map.txt");
	int **arr = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = new int[m];
		for (int j = 0; j < m; ++j)
		{
			arr[i][j] = 0;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (i == 0 && j == 0)
			{
				arr[i][j] = 1;
			}
			else if (i == 0 && j == m - 1)
			{
				arr[i][j] = 3;
			}
			else if (i == n - 1 && j == 0)
			{
				arr[i][j] = 7;
			}
			else  if (i == n - 1 && j == m - 1)
			{
				arr[i][j] = 9;
			}
			else if (i == 0)
			{
				arr[i][j] = 2;
			}
			else if (i == n - 1)
			{
				arr[i][j] = 2;
			}
			else if (j == 0)
			{
				arr[i][j] = 4;
			}
			else if (j == m - 1)
			{
				arr[i][j] = 4;
			}
			else arr[i][j] = 0;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fout << arr[i][j];
			if (arr[i][j] < 10 && arr[i][j] >= 0)fout << "  ";
			else fout << " ";
		}
		fout << "\n";
	}
	//fout << "fff";
}