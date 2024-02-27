#include "generate_map.h"
bool isPrime(int n)
{
	if (n < 2)
		return false;
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
void generate_layer2(int n, int m)
{
	std::ofstream fout("image//layer2.txt");
	int i = 0;
	for (; i <= n / 2; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fout << 0 << "  ";
		}
		fout << "\n";
	}

	for (int j = 0; j < m; ++j)
	{
		if (j % 10 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 68 << " ";
			}
			j += 4;
		}
		else
			fout << 0 << "  ";
	}

	fout << "\n";

	for (int j = 0; j < m; ++j)
	{
		if (j % 10 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 4 << "  ";
			}
			j += 4;
		}
		else
			fout << 0 << "  ";
	}

	fout << "\n";

	for (int j = 0; j < m; ++j)
	{
		if (j % 7 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 68 << " ";
			}
			j += 4;
		}
		else if (j % 10 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 4 << "  ";
			}
			j += 4;
		}
		else
			fout << 0 << "  ";
	}
	fout << "\n";
	for (int j = 0; j < m; ++j)
	{
		if (j % 7 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 4 << "  ";
			}
			j += 4;
		}
		else if (j % 10 == 0)
		{
			for (int k = 0; k < 5; ++k)
			{
				fout << 4 << "  ";
			}
			j += 4;
		}
		else
			fout << 68 << " ";
	}

	i += 4;
	fout << "\n";
	for (; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (j % 4 == 0)
				fout << 4 << "  ";
			else
				fout << 5 << "  ";
		}
		fout << "\n";
	}
}
void generate_map(int n, int m)
{
	std::ofstream fout("image//map.txt");
	int i = 0;
	for (; i < n / 2; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fout << 06 << "  ";
		}
		fout << "\n";
	}
	// for(int j = 0; j < m; ++j)
	// {
	//    fout << 14 << " ";
	// }
	// fout << "\n";
	for (int j = 0; j < m; ++j)
	{
		if (j % 5 == 0)
		{
			fout << 15 << " ";
		}
		else
			fout << 14 << " ";
	}
	fout << "\n";
	i += 1;
	for (; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fout << 06 << "  ";
		}
		fout << "\n";
	}
}

void generate_layer3(int n, int m,int **map)
{
	srand(time(0));
	std::ofstream fout("image//layer3.txt");
	//int** map = new int* [n];
	for (int i = 0; i <= n; ++i)
	{
		memset(map[i], 0, m * sizeof(int));
	}
	const int r = n / 3 + 1;
	for (int j = 0; j + 2 < m; j += rand() % 3 + 5)

	{
		int k = rand() % 3;
		for (int i = 0; i < 3; ++i)
		{
			if (i == k)
			{
				if (isPrime(j + 1) || j % 59 == 0)
				{
					map[r + i][j] = 68;
					map[r + i][j + 1] = 68;
					map[r + i][j + 2] = 68;
				}
				else {
					map[r + i][j] = 1;
					map[r + i][j + 1] = 2;
					map[r + i][j + 2] = 3;
				}
			}
		}
	}
	map[r][0] = 1;
	map[r][1] = 2;
	map[r][2] = 3;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fout << map[i][j] << " ";
		}
		fout << "\n";
	}
}