#include "generate_map.h"
void generate_layer3(int n, int m)
{
	srand(time(0));
	std::ofstream fout("image/map.txt");
	int v = 10;
	std::vector<std::pair<int, int>>g[10];
	int** arr = new int* [n];
	int** node = new int* [n];
	for (int i = 0; i < n; ++i)
	{
		node[i] = new int[m];
		arr[i] = new int[m];
		//memset(arr[i], 0,sizeof(arr[i]));
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			arr[i][j] = 0;
			node[i][j] = 0;
		}
	}
	int cur_x = 8, cur_y = 2;
	const int sz = 10;
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < sz + 1; ++j)
		{
			for (int k = 0; k < sz + 1; ++k)
			{
				if ((j == 0 && k == 0))
				{
					arr[cur_x + j][cur_y + k] = 1;
				}
				else if ((j == 0 && k == sz))
				{
					arr[cur_x + j][cur_y + k] = 3;
				}
				else if ((j == sz && k == 0))
				{
					arr[cur_x + j][cur_y + k] = 7;
				}
				else if (j == sz && k == sz)
				{
					arr[cur_x + j][cur_y + k] = 9;
				}
				else if (j == 0 || j == sz)
				{
					arr[cur_x + j][cur_y + k] = 2;
				}
				else if (k == 0 || k == sz)
				{
					arr[cur_x + j][cur_y + k] = 6;

				}
				else
				{
					arr[cur_x + j][cur_y + k] = 5;
				}
				//node[cur_x + j][cur_y + k] = i;
				g[i].push_back({ cur_x + j,cur_y + k });
			}
		}
		cur_y += 15;
		if ((i + 1) % 5 == 0)cur_x += 16, cur_y = 2;

	}
	for (int i = 12; i < m - 16; i += 15)
	{
		for (int st = 11; st < n - 4; st += 16)
		{
			for (int r = st; r <= st + 4; ++r)
			{
				for (int j = i; j <= i + 5; ++j)
				{
					if (r == st || r == st + 4)arr[r][j] = 2;
					else arr[r][j] = 5;
				}
				if (r == st )
				{
					arr[r][i] = 7;
					arr[r][i + 5] = 9;

				}
				if (r == st + 4)
				{
					arr[r][i] = 1;
					arr[r][i + 5] = 3;
				}

			}
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