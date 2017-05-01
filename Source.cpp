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
	int k, i, j, M[200], N, l;
	double A[200][200], Z[200], X[200], Z_data[200][200];
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
	for (j = 0; j < k + 1; j++) {
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
			for (j = 1; j < k + 1; j++) {
				Z[i] = Z[i] + A[j][i] * X[j-1];
			}
			fout << Z[i] << ' ';
		}
		fout << '\n';
		C++;
	}
	fout.close();
	ifstream fin("data.txt");
	for (j = 0; j < N; j++) {
		for (i = 0; i < l; i++) {
			fin >> Z_data[i][j];
		}
	}
	double *Z_Sred = new double[200];
	double *S = new double[200];
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
	fin.close();
	C = 0;
	cout << 'N' << "     ";
	for (i = 0; i < k; i++) {
		cout << fixed << ' ' << "X[" << i + 1 << "]" << '\t';
	}
	cout << '\t';
	for (j = 0; j < l; j++) {
		cout << fixed << ' ' << "Z[" << j + 1 << "]" << '\t';
	}
	cout << '\n';
	while (C < N) {
		cout << C + 1 << ' ';
		for (j = 0; j < k; j++) {
			cout << fixed << ' ' << X[j];
		}
		cout << ' ';
		for (i = 0; i < l; i++) {
			cout << fixed << ' ' << Z_data[i][C];
		}
		Sleep(T * 1000);
		C++;
		cout << '\n';
		}
	cout << '\n';
	for (j = 0; j < k; j++) {
		cout << ' ' << '\t';
	}
	cout << "Srednie:";
	for (i = 0; i < l; i++) {
		cout << ' ' << fixed << Z_Sred[i];
	}	
	cout << '\n';
	for (j = 0; j < k; j++) {
		cout << ' ' << '\t';
	}
	cout << "Dispersia:";
	for (i = 0; i < l; i++) {
		cout << ' ' << fixed << S[i];
	}
	delete[] Z_Sred;
	delete[] S;
	cout << '\n';
	system ("pause");
}