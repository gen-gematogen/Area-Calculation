#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS1 0.00001
#define EPS2 0.01

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

extern double df1(double x);
extern double df2(double x);
extern double df3(double x);

extern double d2f1(double x);
extern double d2f2(double x);
extern double d2f3(double x);

double root(double (*f)(double), double (*g)(double),
            double (*df)(double), double (*dg)(double),
            double (*d2f)(double), double (*d2g)(double),
            double a, double b, double eps1, int* comp) {

	double valfa, valga, valfb, valgb;       // переменные, для подсчета значиней фунцций f и g в точках a и b
	double fa, fb, dfa, dfb;                 // переменные для подсчета значений функции f - g
	double newa, newb;                       // новые границы отрезка
	double valdfa, valdga, vald2fa, vald2ga; // производные на концах отрезка
	
	*comp = 0;

	valdfa = df(a);
	valdga = dg(a);
	vald2fa = d2f(a);
	vald2ga = d2g(a);

	while (b - a > eps1) {
		(*comp)++;
		valfa = f(a);
		valfb = f(b);
		valga = g(a);
		valgb = g(b);

		fa = valfa - valga;
		fb = valfb - valgb;

		if ((valdfa - valdga) * (vald2fa - vald2ga) >= 0) {
			dfb = df(b) - dg(b);

			newa = a - fa * (b - a) / (fb - fa);
			newb = b - fb / dfb;
		} else {
			dfa = df(a) - dg(a);

			newa = a - fa / dfa;
			newb = b - fb * (b - a) / (fb - fa);
		}
		a = newa;
		b = newb;
	}

	return a;
}

double integral(double (*f)(double), double a, double b, double eps2) {
	int n = (int) ((b - a) / eps2); // колличество подотрезков на отрезке a b

	double area = 0;
	double l = a;
	double r = a + eps2;

	for (int i = 0; i < n; ++i) {
		area += eps2 * (f(l) + 4 * f((l + r) / 2) + f(r)) / 6;
		l += eps2;
		r += eps2;
	}

	return area;
}

void key_detect(int argc, char **argv, double (*func[])(double)){
	char keys[10][20] = {"-h", "--help", "-pri", "--print_iterations", "-tr", "--test_root", "-ti", "--test_integral"};
	int keys_amt = 8;
	char* end = NULL;
	int comp;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			for (int j = 0; j < keys_amt; ++j) {
				printf("%s\n", keys[j]);
			}

		} else if (strcmp(argv[i], "-tr") == 0 || strcmp(argv[i], "--test_root") == 0) {
			double arg_arr[5];
			char* pntr;

			for (int k = 0; k < 5; ++k){
				pntr = argv[i + k + 1];
				arg_arr[k] = strtod(pntr, &end);
			}

			double test_root = root(func[(int)arg_arr[0] - 1], func[(int)arg_arr[1] - 1],
									func[(int)arg_arr[0] + 2], func[(int)arg_arr[1] + 2],
									func[(int)arg_arr[0] + 5], func[(int)arg_arr[1] + 5],
									arg_arr[2], arg_arr[3], arg_arr[4], &comp);
									
			printf("Абсцисса точки пересечения выбранных функций = %0.4lf\n", test_root);

		} else if (strcmp(argv[i], "-ti") == 0 || strcmp(argv[i], "--test_integral") == 0) {
			double arg_arr[4];
			char* pntr;

			for (int k = 0; k < 4; ++k){
				pntr = argv[i + k + 1];
				arg_arr[k] = strtod(pntr, &end);
			}
			
			double test_integral = integral(func[(int)arg_arr[0] - 1], arg_arr[1], arg_arr[2], arg_arr[3]);

			printf("Интеграл от выбранной функции на отрезке [%0.4lf, %0.4lf] = %0.4lf\n", arg_arr[1], arg_arr[2], test_integral);
		
		} if (strcmp(argv[i], "-pri") == 0 || strcmp(argv[i], "--print_iterations") == 0){
			double arg_arr[5];
			char* pntr;

			for (int k = 0; k < 5; ++k){
				pntr = argv[i + k + 1];
				arg_arr[k] = strtod(pntr, &end);
			}

			double tmp = root(func[(int)arg_arr[0] - 1], func[(int)arg_arr[1] - 1],
									func[(int)arg_arr[0] + 2], func[(int)arg_arr[1] + 2],
									func[(int)arg_arr[0] + 5], func[(int)arg_arr[1] + 5],
									arg_arr[2], arg_arr[3], arg_arr[4], &comp);


			printf("Число итераций для поиска точки пересечения функций %d и %d = %d\n", (int)arg_arr[0], (int)arg_arr[1], comp);
		}
	}
}

int main(int argc, char **argv) {
	double (*func[9])(double) = {f1, f2, f3, df1, df2, df3, d2f1, d2f2, d2f3};
	double left_bound[3] = {0, -3.0, -2.0};
	double right_bound[3] = {2.0 , -1.0, -0.5};
	int comp;

	if (argc > 1){
		key_detect(argc, argv, func);

		return 0;
	}

	double root1 = root(f1, f2, df1, df2, d2f1, d2f2, left_bound[0], right_bound[0], EPS1, &comp);    // абсцисса пересечения функций 1 и 2
	double root2 = root(f1, f3, df1, df3, d2f1, d2f3, left_bound[1], right_bound[1], EPS1, &comp);  // -//- 1 и 3
	double root3 = root(f2, f3, df2, df3, d2f2, d2f3, left_bound[2], right_bound[2], EPS1, &comp);  // -//- 2 и 3

	double total_area = 0;

	total_area += integral(f3, root2, root3, EPS2);
	total_area += integral(f2, root3, root1, EPS2);
	total_area -= integral(f1, root2, root1, EPS2);

	printf("Площадь фигуры, ограниченной данными кривыми = %0.4lf\n", total_area);

	return 0;
}