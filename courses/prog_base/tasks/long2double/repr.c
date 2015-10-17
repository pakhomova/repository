
double long2double (long long number) {
double E=0, F=0, result=0;
short S, n, k;
S=(number>>63)&1;
for (n=52;n<63;n++){
    E=E+(((number>>n)&1)*pow(2,n-52));
    }
for (k=51; k>=0; --k){
    F=F+(((number>>k)&1)*pow(2,k-52));
    }
if ((E>0)&&(E<2047)){
    result=pow(-1,S)*pow(2,E-1023)*(F+1);
    return result;
}
if ((E==0)&&(F!=0)){
    result=pow(-1,S)*pow(2,-1022)*F;
    return result;
}
if ((E==0)&&(F==0)&&(S==1)){
    return -0;
}
if ((E==0)&&(F==0)&&(S==0)){
    return 0;
}
if ((E==2047)&&(F==0)&&(S==0)){
    return INFINITY;
}
if ((E==2047)&&(F==0)&&(S==1)){
    return -INFINITY;
}
if((E==2047)&&(F!=0)){
    return NAN;
}
}
