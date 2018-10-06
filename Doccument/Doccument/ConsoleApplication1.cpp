// sudoku.cpp : Defines the entry point for the console application.
//Chương trình : sudoku
//Họ và Tên: Lê Minh Tiến
//MSSV: 17110236
#include "pch.h"
#include "conio.h"
#include "iostream"
#include "math.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
 typedef struct stack
{
	 int col;
	 int row;
 } Stack;
using namespace std;
#define MAX 100
#define input "sudoku.TXT"
bool search(int a[][MAX], int c, int d, int k)
{
	int dem = 0;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (k == a[d + i][c + j])
				dem++;
		}
	if (dem == 1) return true;
	else return false;
}
bool docfile(const char fname[], int a[][MAX], int &n)
{
	FILE *fp;
	fopen_s(&fp, fname, "rt");
	if (fp == NULL)
	{
		cout << "ko mo dc tap tin!" << endl;
		return false;
	}
	fscanf_s(fp, "%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			fscanf_s(fp, "%d", &a[i][j]);
		}
	fclose(fp);
	return true;
}
void inmt(int a[][MAX], int d, int c)
{
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout.width(4);
			cout << a[i][j];
		}
		cout << endl;
	}
}
bool ktdong(int a[][MAX], int n, int k)
{
	int i = k, j = 0, t;
	for (j = 0; j < n; j++)
		for (int z = j + 1; z < n; z++)
		{
			if (a[k][j] > 0 && a[k][z] > 0 && a[k][j] == a[k][z])
			{
				return false;
			}
		}
	return true;
}
bool ktcot(int a[][MAX], int n, int c)
{
	int i = c, j = 0, t;
	for (j = 0; j < n; j++)
		for (int z = j + 1; z < n; z++)
		{
			if (a[j][c] > 0 && a[z][c] > 0 && a[j][c] == a[z][c])
			{
				return false;
			}
		}
	return true;
}
void chuyenvung(int k, int &c, int &d)
{
	switch (k)
	{
	case 0:
		d = c = 1;
		break;
	case 1:
		d = 1, c = 4;
		break;
	case 2:
		d = 1, c = 7;
		break;
	case 3:
		c = 1, d = 4;
		break;
	case 4:
		c = d = 4;
		break;
	case 5:
		c = 7; d = 4;
	case 6:
		d = 7, c = 1;
		break;
	case 7:
		d = 7, c = 4;
		break;
	case 8:
		d = c = 7;
		break;
	default:
		cout << "xin nhap lai!\n";
		break;
	}
}

bool kt3x3(int a[][MAX], int c, int d)
{
	int k;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (a[d + i][c + j] > 0)
			{
				if (search(a, c, d, a[d + i][c + j]) == false) return false;
			}
		}
	return true;
}
void ktixj(int q, int w, int &k, int &v, int &b)
{
	//d=q,w=c
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (q + i == 1)
			{
				if (w + j == 1)  k = 0;
				else if (w + j == 4)  k = 1;
				else if (w + j == 7)  k = 2;
			}
			else if (q + j == 4)
			{
				if (w + j == 1)  k = 3;
				else if (w + j == 4)  k = 4;
				else if (w + j == 7)  k = 5;
			}
			else if (q + i == 7)
			{
				if (w + j == 1)  k = 6;
				else if (w + j == 4)  k = 7;
				else if (w + j == 7)  k = 8;
			}
		}
	chuyenvung(k, v, b);

}
bool kt9o(int a[][MAX], int n, int d, int c, int hang, int cot)
{
	if (ktcot(a, n, c) == false) return false;
	if (ktdong(a, n, d) == false) return false;
	if (kt3x3(a, hang, cot) == false) return false;
	else return true;
}
int feasible(int S[][MAX], int x, int y, int k)
{
	int i = 0, j = 0;
	for (i = 0; i < 9; i++) {

		if (S[x][i] == k) return 0;
	}
	for (i = 0; i < 9; i++) {
		if (S[i][y] == k) return 0;
	}
	int a = x / 3, b = y / 3;
	for (i = 3 * a; i < 3 * a + 3; i++) {
		for (j = 3 * b; j < 3 * b + 3; j++) {
			if (S[i][j] == k) return 0;
		}
	}
	return 1;

}
void solve_sudoku(int S[][MAX], int x, int y, int n) 
{
	if (y == 9) {
		if (x == 8) {
			inmt(S,n,n);
			exit(0);
		}
		else {
			solve_sudoku(S, x + 1, 0,n);
		}
	}
	else if (S[x][y] == 0)
	{
		for (int k = 1; k <= 9; k++) {
			if (feasible(S, x, y, k)) {
				S[x][y] = k;
				solve_sudoku(S, x, y + 1, n);
				S[x][y] = 0;
			}
		}
	}
	else {
		solve_sudoku(S, x, y + 1,n);
	}
}
void solve_sudoku1(int S[][MAX], int x, int y, int n, Stack)
{
	while (y < 9 && x < 8)
	{
		if (S[x][y] == 0)
		{
			for (int k = 1; k <= 9; k++) {
				if (feasible(S, x, y, k)) {
					S[x][y] = k;
					solve_sudoku1(S, x, y + 1, n, Stack);
					S[x][y] = 0;
				}
			}
		}
		else {
			solve_sudoku1(S, x, y + 1, n,Stack);
		}
		x++;
	}
	inmt(S, x, y);
}
int pop( Stack P[]) {
	Stack m;

	m.col = P->col;
		top = top - 1;

		return d;
}
void push( Stack P[], int top, int col, int row) 
{
		top = top + 1;
		P[top].col = col;
		P[top].row = row;
}


int main()
{
	do {
		int stack[1000];
		int a[MAX][MAX], n, k, c, m, d, b[MAX][MAX];
		int hang, cot;
		if (!docfile(input, a, n))
			return -1;
		Stack S;
		
		inmt(a, n, n);
		cout << "-----------------" << endl;
	solve_sudoku1(a, 0, 0,n);
		//inmt(a, n, n);
		cout << "--------------------------" <<endl;
		/*if (!docfile(input, b, n))
			return -1;
		inmt(b, n, n);
		solve_sudoku(b, 0, 0, n);
		inmt(b, n, n);*/


		cout << "nhap esc de thoat! \n";
	} while (_getch() != 27);
}

