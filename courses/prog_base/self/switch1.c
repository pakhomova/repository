#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
int m=17;
int h=2;
int min = h*60;
int code=697;
float money;
int time = min + m;

if ((code>=10) && (code<=999)){
    switch (code){
    case 44:
    money = time*0.77;
    printf ("%f",money);
    break;
    case 62:
    money = time*0.8;
    printf ("%f",money);
    break;
    case 32:
    money = time*0.95;
    printf ("%f",money);
    break;
    case 692:
    money = time*1.5;
    printf ("%f",money);
    break;
    case 697:
    money = time*1.5;
    printf ("%f",money);
    break;
    default:
    money = time;
    printf ("%f",money);
    break;
    }

  }
  else {
    printf ("Error");
  }
  return 0;
}
