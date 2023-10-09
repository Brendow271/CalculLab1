#include <cmath>
extern "C" __declspec(dllexport)
double binOper(double a,double b) {
	return pow(b,a);
}