double calc(int n, int m){
int i, j;
double x = 0, calc = 0;
for(i = 1; i <= n; i++){
    calc = 0;
    for(j = 1; j <= m; j++){
        calc = calc + pow(j, i);
        }
    x = x + sin(2*M_PI/i)*sqrt(calc);
    }
return x;
}
