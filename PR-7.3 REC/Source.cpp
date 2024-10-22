#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

void Delete(int** a, int rowCount);
void Print(int** a, const int rowCount, const int colCount, int i, int j);
void rowmem(int** a, const int rowCount, const int colCount, int i);
void Input(int** a, const int rowCount, const int colCount, int i, int j);
void deleteROW(int** a, int& rowCount, const int colCount, int i, int j);
void deleteCOL(int** a, const int rowCount, int& colCount, int j);
void zsuv(int** a, int i, int colCount, int rowCount, int k);
void zsuv1(int** a, int colrowCount, int k);
int firstrowpos(int** a, int rowCount, int colCount, int rowmin, int i, int j);
void ISZEROrow(int** a, int colCount, int j, int i, int& check);
void ISZEROcol(int** a, int colrowCount, int j, int i, int& check);
int main()
{
	int rc;
	int cc;
	int rowmin = -1;

	cout << "input RowCount:";
	cin >> rc;
	cout << "input ColCount:";
	cin >> cc;

	int** a = new int* [rc];

	rowmem(a, rc, cc,0);
	Input(a, rc, cc,0,0);
	Print(a, rc, cc,0,0);
	deleteROW(a, rc, cc,0,0);
	deleteCOL(a, rc, cc,0);
	Print(a, rc, cc,0,0);
	if (firstrowpos(a, rc, cc,rowmin,0,0) == -1)
		cout << "No positive elements!" << endl;
	else
		cout << "First row with positive element: " << firstrowpos(a, rc, cc,rowmin,0,0) << endl;

	Delete(a, rc );
	return 0;
}
void rowmem(int** a, const int rowCount, const int colCount, int i)
{
	a[i] = new int[colCount];
	if (i < rowCount - 1)
		rowmem(a, rowCount, colCount, i + 1);
}
void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl << endl;
}
int firstrowpos(int** a, int rowCount, int colCount ,int rowmin ,int i, int j)
{
	if (a[i][j] > 0)
		return i;

	if (j < colCount - 1)
		return firstrowpos(a, rowCount, colCount, rowmin, i, j + 1);

	if (i < rowCount - 1)
		return firstrowpos(a, rowCount, colCount, rowmin, i + 1, 0);

	return -1;
}
void deleteROW(int** a, int& rowCount, const int colCount ,int i , int j)
{
	int check = 1;
	ISZEROrow(a,colCount,j,i,check);
	if (check == 1)
	{
		delete[] a[i];
		zsuv1(a, rowCount,i);
		rowCount--;  // Зменшуємо кількість рядків
		deleteROW(a, rowCount, colCount, i,0);
	}
	if( i < rowCount-1)
		deleteROW(a, rowCount,colCount, i + 1, 0);
}
void ISZEROrow(int** a,int colCount,int j,int i,int& check)
{
	if(a[i][j] != 0)
	{
		check = 0;
		return;
	}
	if (j < colCount - 1)
		ISZEROrow(a, colCount, j + 1, i, check);
}
void ISZEROcol(int** a, int rowCount, int j, int i, int& check)
{
	if (a[i][j] != 0)
	{
		check = 0;
		return;
	}
	if (j < rowCount - 1)
		ISZEROcol(a, rowCount, j, i + 1, check);

}
void deleteCOL(int** a, const int rowCount, int& colCount ,int j)
{
	int check = 1;
	ISZEROcol(a,rowCount , j, 0,check);
	if (check == 1)
	{
		zsuv(a, 0, colCount, rowCount, j);
		colCount--;
		deleteCOL(a,rowCount,colCount,j);
	} else if (j < colCount - 1)
		deleteCOL(a, rowCount, colCount, j + 1);
}
void zsuv(int** a, int i, int colCount, int rowCount, int k) {
	if (k < colCount - 1) {
		a[i][k] = a[i][k + 1];
		zsuv(a, i, colCount, rowCount, k + 1);
	}
	else if (i < rowCount - 1) {
		a[i][k] = a[i + 1][0];
		zsuv(a, i + 1, colCount, rowCount, 0);
	}
}
void zsuv1(int** a,int colrowCount,int k)
{
	if (k < colrowCount - 2)
	{
		a[k] = a[k + 1];
		zsuv1(a, colrowCount, k + 1);
	}
}
void Input(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << "a[" << i << "][" << j << "] = ";
	cin >> a[i][j];
	if (j < colCount - 1)
		Input(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Input(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl;
}
void Delete(int** a, int rowCount)
{
	if (rowCount == 0)
		return;
	delete[] a[rowCount - 1];  // Видаляємо останній рядок
	Delete(a, rowCount - 1);    // Рекурсивно видаляємо решту рядків
}