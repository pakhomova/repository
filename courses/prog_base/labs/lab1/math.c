
#include <math.h>

double calc(double x, double y, double z) {
double a;
int m=x+y;
int n=x-y;
if ((z!=0) && (n>=0) && (m!=0) && (sin(y)!=0)){
a = pow(x,y+1)/pow(x-y,1/z) + y/(8*abs(x+y)) + pow(x,abs(1/sin(y)));
return a;
}
else {
    return NAN;
}
}


