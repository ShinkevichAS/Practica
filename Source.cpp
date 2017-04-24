#include <iostream>
#include <cmath>
#include "plant.h"
#include <windows.h>
#include <fstream>
#include <cstdio>
#include <errno.h>
#pragma warning(disable : 4996)
using namespace std;
int main() {
	FILE *f;
	time_t T;
	int k, i, j, M[15], N, l;
	double A[15][15], Z[15], X[15], Z_data[15][15];
	Plant plant;
	plant_init(plant);
	cout << "Vvedite kolichestvo datchikov k: ";
	cin >> k;
	cout << "\nVvedite nomera datchikov M:\n";
	for (j = 0; j < k; j++)
		cin >> M[j];
	cout << "\nVvedite neobhodimii interval T: ";
	cin >> T;
	cout << "\nVvedite kolichestvo povtorenii N: ";
	cin >> N;
	cout << "\nVvedite kolichestvo preobrazovanii l: ";
	cin >> l;
	cout << "\nVvedite matricu koefficientov A: \n";
	for (j = 0; j < k; j++) {
		for (i = 0; i < l; i++) {
			cin >> A[j][i];
		}
	}
	int C = 0;
	ofstream fout("data.txt");
	cout << "Izmerennie znacheniya:\n";
	while (C < N) {
		for (j = 0; j < k; j++) {
			X[j] = plant_measure(M[j], plant);
		}
		for (i = 0; i < l; i++) {
			Z[i] = A[0][i];
			for (j = 1; j < k; j++) {
				Z[i] = Z[i] + A[j][i] * X[j];
			}
			fout << Z[i] << ' ';
			cout << fixed << ' ' << Z[i];
		}
		fout << '\n';
		cout << '\n';
		Sleep(T*1000);
		C++;
	}
	fout.close();
	ifstream fin("data.txt");
	for (j = 0; j < N; j++) {
		for (i = 0; i < l; i++) {
			fin >> Z_data[i][j];
		}
	}
	double *Z_Sred = new double[15];
	double *S = new double[15];
	for (i = 0; i < l; i++) {
		Z_Sred[i] = 0;
		S[i] = 0;
		for (j = 0; j < N; j++) {
			Z_Sred[i] = Z_Sred[i] + Z_data[i][j];
			S[i] = S[i] + pow(Z_data[i][j], 2);
		}
		Z_Sred[i] = Z_Sred[i] / N;
		S[i] = (S[i] - N * pow(Z_Sred[i], 2)) / N;
	}
	cout << "\nSrednie:\n";
	for (i = 0; i < l; i++) {
		cout << ' ' << fixed << Z_Sred[i];
	}
	cout << "\nDispersia:\n";
	for (i = 0; i < l; i++) {
		cout << ' ' << fixed << S[i];
	}
	delete[] Z_Sred;
	delete[] S;
	cout << '\n';
	system ("pause");
}