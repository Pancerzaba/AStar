
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<iso646.h>
#include<math.h>
using namespace std;
int i = 0;
int j = 0;
int koszt, minkoszt;


int Size = 20;
double obstacle = 5;

int** licz(float** open, int** closed)
{
	int** koncowa = new int* [Size];
	int** rodzic = new int* [Size];
	int** grid = new int* [Size];
	for (int i = 0; i < Size; i++)
	{
		koncowa[i] = new int[Size];
		rodzic[i] = new int[Size];
		grid[i] = new int[Size];
	}

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			koncowa[i][j] = closed[i][j];
			rodzic[i][j] = 0;
		}
	}

	koncowa[0][0] = 3;
	grid[0][0] = 0;
	grid[0][1] = grid[1][0] = 1;

	if (open[0][1] != 5) open[0][1] = sqrt(pow(1 - 20, 2) + pow(0 - 20, 2)) + grid[0][1];
	if (open[1][0] != 5) open[1][0] = sqrt(pow(0 - 20, 2) + pow(1 - 20, 2)) + grid[1][0];



	while (true)
	{
		int chk = 0;
		for (int i = 0; i < Size; i++)		//zarzadzanie otwartymi i zamknietymi listami
		{
			for (int j = 0; j < Size; j++)
			{
				if ((i > 0 && closed[i][j] == 1 && open[i - 1][j] != -1 && open[i - 1][j] != 5) || (j > 0 && closed[i][j] == 1 && open[i][j - 1] != -1 && open[i][j - 1] != 5) || (i < Size - 1 && closed[i][j] == 1 && open[i + 1][j] != -1 && open[i + 1][j] != 5) || (j < Size - 1 && closed[i][j] == 1 && open[i][j + 1] != -1 && open[i][j + 1] != 5))
				{
					chk++;
					break;
				}

				if ((i > 0 && open[i - 1][j] == 0) || (j > 0 && open[i][j - 1] == 0) || (i < Size - 1 && open[i + 1][j] == 0) || (j < Size - 1 && open[i][j + 1] == 0))
				{
					chk++;
					break;
				}
			}
			if (chk != 0)
				break;
		}

		if (chk == 0)
		{
			koncowa[0][0] = -1;
			return koncowa;
		}

		pair<int, int> min = make_pair(0, 0);		//dodawanie do otwartej listy
		float minf = 19999;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (open[i][j] < minf && open[i][j] > 0 && closed[i][j] != 1 && open[i][j] != 5 && open[i][j] != 3)
				{
					minf = open[i][j];
				}
			}
		}
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (open[i][j] == minf) min = make_pair(i, j);
			}
		}

		closed[min.first][min.second] = 1;		//dodawanie z zamknietej do otwartej listy oraz sprawdzanie sasiednich pol (liczenie ich wartosci)
		open[min.first][min.second] = -1;

		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (closed[i][j] != 1)
				{

					if (i < Size - 1 && closed[i + 1][j] == 1)
					{
						if (open[i][j] != obstacle)
						{
							grid[i][j] = grid[i + 1][j] + 1;
							open[i][j] = sqrt(pow(i - Size, 2) + pow(j - Size, 2)) + grid[i][j];
							rodzic[i][j] = 3;
						}
					}else if (i > 0 && closed[i - 1][j] == 1)
					{
						if (open[i][j] != obstacle)
						{
							grid[i][j] = grid[i - 1][j] + 1;
							open[i][j] = sqrt(pow(i - Size, 2) + pow(j - Size, 2)) + grid[i][j];
							rodzic[i][j] = 1;
						}
					}
					else if (j > 0 && closed[i][j - 1] == 1)
					{
						if (open[i][j] != obstacle)
						{
							grid[i][j] = grid[i][j - 1] + 1;
							open[i][j] = sqrt(pow(i - Size, 2) + pow(j - Size, 2)) + grid[i][j];
							rodzic[i][j] = 4;
						}
					}
					else if (j < Size - 1 && closed[i][j + 1] == 1)
					{
						if (open[i][j] != obstacle)
						{
							grid[i][j] = grid[i][j + 1] + 1;
							open[i][j] = sqrt(pow(i - Size, 2) + pow(j - Size, 2)) + grid[i][j];
							rodzic[i][j] = 2;
						}
					}
				}
				else
				{
					if (i > 0 && open[i - 1][j] != 0 && grid[i][j] < grid[i - 1][j] - 1 && open[i - 1][j] != obstacle)
					{
						grid[i - 1][j] = grid[i][j] + 1;
						rodzic[i - 1][j] = 3;
						open[i - 1][j] = sqrt(pow(i - 1 - Size, 2) + pow(j - Size, 2)) + grid[i - 1][j];
					}else if (j > 0 && open[i][j - 1] != 0 && grid[i][j] < grid[i][j - 1] - 1 && open[i][j - 1] != obstacle)
					{
						grid[i][j - 1] = grid[i][j] + 1;
						rodzic[i][j - 1] = 2;
						open[i][j - 1] = sqrt(pow(i - Size, 2) + pow(j - 1 - Size, 2)) + grid[i][j - 1];
					}
					else if (i < Size - 1 && open[i + 1][j] != 0 && grid[i][j] < grid[i + 1][j] - 1 && open[i + 1][j] != obstacle)
					{
						grid[i + 1][j] = grid[i][j] + 1;
						rodzic[i + 1][j] = 1;
						open[i + 1][j] = sqrt(pow(i + 1 - Size, 2) + pow(j - Size, 2)) + grid[i + 1][j];
					}
					
					else if (j < Size - 1 && open[i][j + 1] != 0 && grid[i][j] < grid[i][j + 1] - 1 && open[i][j + 1] != obstacle)
					{
						grid[i][j + 1] = grid[i][j] + 1;
						rodzic[i][j + 1] = 4;
						open[i][j + 1] = sqrt(pow(i - Size, 2) + pow(j + 1 - Size, 2)) + grid[i][j + 1];
					}
				}
			}
		}



		if ((((min.first + 1 == Size - 1 && min.second == Size - 1) || (min.first == Size - 1 && min.second + 1 == Size - 1))) && (closed[Size - 1][Size - 2] == 1 || closed[Size - 2][Size - 1] == 1))
		{
			if (closed[Size - 1][Size - 2] == 1) rodzic[Size - 1][Size - 1] == 1;
			if (closed[Size - 2][Size - 1] == 1) rodzic[Size - 1][Size - 1] == 4;
			koncowa[Size - 1][Size - 1] = 3;
			break;
		}
	}

	int i = Size - 1, j = i;
	rodzic[1][0] = 1;
	rodzic[0][1] = 4;

	while (rodzic[i][j] != 0)		//wyznaczanie trasy
	{
		if (i == 0 && j == 0) break;

		switch (rodzic[i][j])
		{
		case 1:
		{
			koncowa[i][j] = 3;
			i--;
			break;
		}
		case 2:
		{
			koncowa[i][j] = 3;
			i++;
			break;
		}
		case 3:
		{
			koncowa[i][j] = 3;
			j++;
			break;
		}
		case 4:
		{
			koncowa[i][j] = 3;
			j--;
			break;
		}
		default:
			break;
		}
	}

	return koncowa;
}




/*
double (k, l) {
		double koszt = sqrt(pow(k - 19, 2) + pow(l - 19, 2));
		return koszt;
	}*/
int main()
{


cout << "Wczytywanie danych z pliku\n";

string nazwap = "grid.txt";
int wym2 = 20;
int wym1 = 20;

//teraz deklarujemy dynamicznie tablice do, której wczytamyu nasz plik,
int rows = wym2 + 1;
double** G;
G = new double* [rows];
while (rows--) G[rows] = new double[wym1 + 1];

cout << "\n ENTER aby wczytac"<< nazwap;
getchar();

std::ifstream plik(nazwap.c_str());

for (unsigned int i = 0; i < wym2; i++)
{
	for (unsigned int j = 0; j < wym1; j++)
	{
		plik >> G[i][j];
	}
}
plik.close();

cout << "\nWypisz\n";
for (int i = 0; i < wym2; i++)
{
	for (int j = 0; j < wym1; j++)
	{
		cout << " " << G[i][j];
	}cout << "\n";
}

cout << endl << endl;
/*cout << "open:" << endl;*/

float** open = new float* [Size];
int** closed = new int* [Size];

for (int i = 0; i < Size; i++)
{
	open[i] = new float[Size];
	closed[i] = new int[Size];
	for (int j = 0; j < Size; j++)
	{
		if (i == 0 && j == 0)
		{
			closed[i][j] = 1;
			open[i][j] = i + j + sqrt(pow(i + 1 - 20, 2) + pow(j + 1 - 20, 2));
		}
		else if (G[i][j] == 5)
		{
			open[i][j] = 5;
			closed[i][j] = 5;
		}
		/*else if (closed[i - 1][j] == 1 || closed[i + 1][j] == 1 || closed[i][j - 1] == 1 || closed[i][j + 1] == 1)
		{
			if (open[i][j] != 5) open[i][j] = i + j + sqrt(pow(i+1 - 20, 2) + pow(j+1 - 20, 2));
		}*/
		else
		{
			open[i][j] = 0;
			closed[i][j] = 0;
		}
	}
}

/*for (int i = 0; i < mapSize; i++)
{
	for (int j = 0; j < mapSize; j++)
	{
		cout << open[i][j] << " ";
	}
	cout << endl;
}

cout << "closed:" << endl;

for (int i = 0; i < mapSize; i++)
{
	for (int j = 0; j < mapSize; j++)
	{
		cout << closed[i][j] << " ";
	}
	cout << endl;
}*/


int** path = licz(open, closed);
if (path[0][0] != -1)
{
	cout << endl << "trasa: " << endl << endl;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
}
else
{
	cout << endl << "brak mozliwosci dotarcia do celu" << endl;
	getchar();
	return 0;
}


//na koniec czyścimy pamięć po naszej tablicy
for (int i = 0; i < wym2 + 1; i++)
{
	delete[] G[i];
}//czyscimy wiersze
delete[] G;//zwalniamy tablice wskaznikow do wierszy

cout << "\nENTER aby zakonczyc";
getchar();


return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
