#include <iostream>

#define FOR(n) for (int i = 0; i < n; i++)
#define BUFFSIZE 512

using namespace std;

typedef struct value {
	double x, fx;
}val;

int main() {
	int	n; 
	double x;

	while (cin >> n >> x) {
		val* v = new val[n];
		double* l = new double[n];

		FOR(n) {
			cin >> v[i].x >> v[i].fx;
		}

		double res = 0.0;

		FOR(n) {
			l[i] = 1;
			for (int j = 0; j < n; j++) {
				if (j != i) {
					l[i] *= ((x - v[j].x) / (v[i].x - v[j].x));
				}
			}
			l[i] *= v[i].fx;
			res += l[i];
		}

		cout.setf(ios::fixed);
		cout.precision(6);
		cout << res << endl;
		
		delete[] v;
		delete[] l;
	}

	return 0;
}