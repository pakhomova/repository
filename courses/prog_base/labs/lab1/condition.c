
#include <math.h>

int isPowerOfTwo (int number) {
double power = log2(number);
if (floor(power) == power) {
    return 1;
}
else {
    return 0;
}
}
int satisfies(int a, int b, int c) {
    int n1=0;
    int n0=7;
   int result;
if ((a<0) && (b<0) && (c<0)) {
int modmin, sum2;
if ((a<b) && (a<c)){
    modmin=abs(a);
    sum2=b+c;
    }
if ((b<a) && (b<c)){
    modmin=abs(b);
    sum2=a+c;
}
if ((c<a) && (c<b)){
    modmin=abs(c);
    sum2=a+b;
}
if ((sum2<256) && (isPowerOfTwo(modmin)==1) && (modmin<256)){
    return 1;
}
            else {
                if ((abs(sum2)>modmin) && (sum2>-256)){
                    return 1;
                }
                else {
                    return 0;
                }
            }

}
else {
    if ((a<0) || (b<0) || (c<0)){
        if ((a<0) && (b>=0) && (c>=0) || (b<0) && (a>=0) && (c>=0) || (c<0) && (a>=0) || (b>=0)) {
            if (a<0) {
                return (a>-256);
            }
           if (b<0) {
                return (b>-256);
            }
            if (c<0) {
                return (c>-256);
            }
        }
    else {
        if (a>=0) {
            return (b+c)*(n0+n1)>-256;
        }
        if (b>=0) {
            return (a+c)*(n0+n1)>-256;
        }
        if (c>=0) {
            return (b+a)*(n0+n1)>-256;
        }
    }
  }
 else {
    int max;
    max = (a>b) ? a:b;
    max = (max>c) ? max:c;
    int min;
    min = (a<b) ? a:b;
    min = (min<c) ? min:c;
    return (max*min<256);
 }
 return 0;
}
   return result;
}

