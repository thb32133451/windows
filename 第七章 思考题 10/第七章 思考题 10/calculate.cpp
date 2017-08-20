#include <iostream>
using namespace std;

double add(double x, double y);
double point(double x, double y);
double calculate(double x, double y, double(*pf[2])(double, double));

int main() {
	double x, y;
	double (*pf[2])(double, double) = { add,point };

	if ((cin>>x && cin>>y)) {
		double z = calculate(x,y,pf);
		cout << z << endl;
	}
	else {
		cout << "please enter two number next time! now we will exit.\n";
	}
	
	system("pause");
	return 0;
}

double add(double x, double y)
{
	return x+y;
}

double calculate(double x,double y, double(*pf[2])(double, double)) {
	double k =pf[0](x,y)+pf[1](x,y);
	return k;
}

double point(double x, double y) {
	return x / y;
}