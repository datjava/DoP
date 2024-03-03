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
void generate_layer1(int n, int m)
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
void generate_layer2(int n, int m, int*& a)
{
	srand(time(0));
	//n width m height
	//n col m row
	std::ofstream fout("image//map.txt");
	int** map = new int* [m];
	a = new int[n];
	for (int i = 0; i <= m; ++i)
	{
		map[i] = new int[n];
		memset(map[i], 0, n * sizeof(int));
	}
	for (int i = 0; i < 3; ++i)
	{
		a[i] = 0;
	}
	for (int i = 3; i < n; ++i)
	{

		int high = rand() % 5 + 4;
		a[i] = high;
	}

	for (int j = 0; j < n; ++j)
	{
		for (int i = 0; i < m; ++i)
		{
			//std:: cout << j << ' ' << i << ' ' << a[j] << '\n';
			if (i == a[j])
			{
				
				if (rand() % 2 != 0)
				{
					if (j != 0 && j >= 4 && a[j - 2] != 1000000000)
					{
						a[j] = 1000000000;
						map[i][j] = 37;
					}
					else
					{
						map[i][j] = 36;
					}
				}
				else
				{
					map[i][j] = 36;
				}
			}
		}


	}
	for (int i = m - 1; i > 0; --i)
	{
		for (int j = 0; j < n; ++j)
		{

			fout << map[i][j];
			if (map[i][j] < 10)fout << "  ";
			else fout << " ";
		}
		fout << "\n";

	}
}
void generate_layer3(int n, int m, int** map)
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