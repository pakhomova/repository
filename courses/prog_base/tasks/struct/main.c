#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct City{
char name[20], country[20];
double population;
};

int count(int size, struct City arr[size]){
int count = 0, i;
for (i = 1; i < size; i++){
    if(arr[i].population > 1000000){
        count++;
    }
}
return count;
}

void change(struct City * pVar, const char * newValue){
strcpy(pVar -> name, newValue);
}

void print(struct City * pVar){
    printf("Name: %s\nCountry: %s\nPopulation: %f\n", (pVar -> name), (pVar -> country), (pVar -> population));
}

int main(void){
struct City Kitty = {"Kitty", "Ukraine", 1}, London = {"London", "UK", 3000000}, Paris = {"Paris", "France", 2800000};
struct City arr[3] = {Kitty, London, Paris};
int i = 0, ind;
char newName[20];
for (i = 0; i < 3; i++){
    printf("%i. \n", i+1);
    print(&arr[i]);
}
printf("There are %i cities with population under million.\n", count(3, arr));
printf("Please, enter the index of city, whose name you want to change:");
scanf("%i", &ind);
printf("Please, enter the new name of city: ");
fflush(stdin);
fgets(newName, sizeof(newName), stdin);
change(&arr[ind-1], newName);
printf("New data:\n");
print(&arr[ind-1]);
return 0;
}
