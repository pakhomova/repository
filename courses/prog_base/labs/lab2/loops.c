double calc(int n, int m){
int i, j;
double x = 0, calc = 0;
double pi = 3.1415926;
for(i = 1; i <= n; i++){
    calc = 0;
    for(j = 1; j <= m; j++){
        calc = calc + pow(j, i);
        }
    x = x + sin(2*pi/i)*sqrt(calc);
    }
return x;
}
