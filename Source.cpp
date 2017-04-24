#include <iostream>
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
	double A[15][15], Z[15], X[15], Z_Sred[15], Z_data[15][15];
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
			cout << fixed << " " << Z[i];
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
	for (j = 0; j < N; j++) {
		for (i = 0; i < l; i++) {
			cout << ' ' << Z_data[i][j];
		}
		cout << '\n';
	}
	system ("pause");
}