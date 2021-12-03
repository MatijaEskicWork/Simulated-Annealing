#include <iostream>
#include <set>
#include <cmath>
#include <fstream>
using namespace std;

int values[] = { 173669, 275487, 1197613, 1549805, 502334, 217684,
					1796841, 274708, 631252, 148665, 150254, 4784408,
					344759, 440109, 4198037, 329673, 28602, 144173,
					1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997,
					254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203,
					8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991,
					421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919,
					56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422,
					414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571 };

int maxx = 33554432;
int maxx2 = 67108864;

int optimize(int bits[], bool ok = false) {
	int f1 = 0, f2 = 0;
	int res = 0;
	for (int i = 0; i < 64; i++) {
		if (bits[i] == 1) {
			f1 += values[i];
		}
		if (bits[i] == 2) {
			f2 += values[i];
		}
		if (ok) cout << bits[i];
	}
	if (ok) cout << endl;
	f1 = maxx - f1;
	f2 = maxx - f2;
	if (f1 < 0 || f2 < 0) {
		res = maxx2;
	}
	else {
		res = f1 + f2;
	}

	return res;
}

double probability(int delta, double T) {
	if (T < 0.000001) return 0.0;
	if (T > 1000000) return 1.0;
	double tmp = (double)-1.0 * (1.0 * delta / T);
	return exp(tmp);
}


int main() {

	double T0 = 64.0 * 1024.0 * 1024.0;
	int maxIter = 99999;
	double a = 0.95;
	int hmax = 32;
	srand(time(0));
	int bits[64] = { 0 };
	int bitsGlobal[64] = { 0 };
	set<int> s;
	int h = hmax;
	int hmin = 1;
	int delta;
	double p;
	double T;
	int fmin;
	int fminGlobal = 1000000000;
	ofstream out;
	out.open("data1.txt");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 64; j++) {
			bits[j] = rand() % 3;
		}
		fmin = optimize(bits);
		out << fmin << endl;
		for (int j = 0; j < 10; j++) {
			T = T0;
			h = hmax;
			for (int k = 0; k < 100000; k++) {
				bool acc = false;
				int bitsTmp[64];
				for (int l = 0; l < 64; l++) {
					bitsTmp[l] = bits[l];
				}
				while (s.size() < h) {
					s.insert(rand() % 64);
				}
				for (int val : s) {
					bitsTmp[val] = rand() % 3;
				}
				s.clear();
				int fcurr = optimize(bits);
				int fnext = optimize(bitsTmp);
				delta = fnext - fcurr;
				if (delta < 0) {
					acc = true;
					fmin = fnext;
				}
				else {
					fmin = fcurr;
					p = probability(delta, T);
					double r = ((double)rand() / (RAND_MAX));
					if (p >= r) {
						acc = true;
						fmin = fnext;
					}
				}
				T = a * T;
				if (acc) {
					for (int l = 0; l < 64; l++) {
						bits[l] = bitsTmp[l];
					}
				}
				h = ((double)(1.0 * ((double)hmin - hmax) / maxIter) * k) + hmax;
				out << fnext << endl;
			}
		}
		out << -1 << endl;
		cout << fmin << endl;
		if (fminGlobal > fmin) {
			fminGlobal = fmin;
			for (int l = 0; l < 64; l++) {
				bitsGlobal[l] = bits[l];
			}
		}
	}
	out.close();
	ofstream sol;
	sol.open("sol.txt");
	sol << "Optimal function is: " << fminGlobal << endl;
	sol << "Variables are: (";
	for (int i = 0; i < 64; i++) {
		if (i < 63) {
			sol << bitsGlobal[i] << ", ";
		}
		else {
			sol << bitsGlobal[i] << ")";
		}
	}
	sol.close();

	return 0;
}