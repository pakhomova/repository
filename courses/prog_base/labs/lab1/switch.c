
#include <math.h>

int exec(int op, int a, int b) {
   int result;
   int n0 = 7;
   int n1 = 0;
   int c;
   float PI = 3.14159;
    if (op<0){
    op = -op;
    c = a;
    a = b;
    b = c;
    }
    switch (op){
case 0:
    result = -a;
    break;
case 1:
    result = a+b;
    break;
case 2:
    result = a-b;
    break;
case 3:
    result = a*b;
    break;
case 4:
    if (b==0){
    return 0;
    }
    else {
    result = a / b;
    }
    break;
case 5:
    result = abs(a);
    break;
case 6:
    result = pow(a,b);
    break;
case 7:
case 13:
case 77:
    if (b==0){
    return 0;
    }
    else {
    result = a%b;
    }
    break;
case 8:
    result = (a>b) ? a:b;
    break;
case 9:
    result = (a<b) ? a:b;
    break;
case 10:
    switch (abs(b)%8){
        case 0:
        result = abs(a) * sizeof(char);
        break;
        case 1:
        result = abs(a) * sizeof(signed char);
        break;
        case 2:
        result = abs(a) * sizeof(short);
        break;
        case 3:
        result = abs(a) * sizeof(unsigned int);
        break;
        case 4:
        result = abs(a) * sizeof(long);
        break;
        case 5:
        result = abs(a) * sizeof(unsigned long long);
        break;
        case 6:
        result = abs(a) * sizeof(float);
        break;
        case 7:
        result = abs(a) * sizeof(double);
        break;
        }
    break;
case 11:
        if ((cos(a*PI)==0) || (n0-b==0) || (n1+1==0)){
        return 0;
        }
        else{
        result = round((sin(a*PI)/cos(a*PI))/((n0-b)*(n1+1)));
        }
    break;
default:
    if (op<100){
        if ((a+1==0) || (b+1==0)){
        return 0;
        }
        else{
        result = (op%abs(a+1))+(op%abs(b+1));
        }
        }
    else{
        result = -1;
        }
    break;
    }
   return result;
}
