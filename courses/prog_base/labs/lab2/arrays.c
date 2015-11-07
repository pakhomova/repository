void fillRand2(int arr[], int size){
int i;
for(i = 0; i < size; i++){
    arr[i] = rand()%511 - 255;
    }
}

int checkRand2(int arr[], int size){
int x = 0, i;
for(i = 0; i < size; i++){
    if(arr[i] <= 255 && arr[i] >= -255){
        x++;
        }
    }
if(x == size){
    return 1;
    }
else
    return 0;
}

float meanValue(int arr[], int size){
int i;
float x = 0;
for(i = 0; i < size; i++){
    x = x + arr[i];
    }
x = x/size;
return x;
}

int minValue(int arr[], int size){
int i, min = arr[0];
for(i = 1; i < size; i++){
    if(arr[i]<min){
        min = arr[i];
        }
    }
return min;
}

int meanIndex(int arr[], int size){
int i, ind = 0;
float mean = 0, x;
for(i = 0; i < size; i++){
    mean = mean + arr[i];
    }
mean = mean/(float)size;
x = abs(mean - arr[0]);
for(i = size - 1; i >=0; i--){
    if(abs(mean - arr[i]) <= x){
    x = abs(mean - arr[i]);
    ind = i;
        }
    }
return ind;
}

int minIndex(int arr[], int size){
int i, ind = size - 1, min = arr[size-1];
for(i = size - 2; i >=0; i--){
    if(arr[i] <= min){
        min = arr[i];
        ind = i;
        }
    }
return ind;
}

int maxOccurance(int arr[], int size){
int i, j, max = arr[0], k = 1, k1 = 0;
for(i = 0; i < size; i++){
    k1 = 0;
    for(j = 0; j < size; j++){
        if(arr[i] == arr[j]){
            k1++;
                }
            }
    if((k1 > k) || (k1 == k && arr[i] > max)){
    k = k1;
    max = arr[i];
        }
    }
return max;
}

int diff(int arr1[], int arr2[], int res[], int size){
int i, sum = 0;
for(i = 0; i < size; i++){
    res[i] = arr1[i] - arr2[i];
    sum = sum + res[i];
    }
if(sum == 0){
    return 1;
    }
return  0;
}

void divine(int arr1[], int arr2[], int res[], int size){
int i;
for(i = 0; i < size; i++){
    res[i] = arr1[i] / arr2[i];
    }
}

int gt(int arr1[], int arr2[], int size){
int i, x = 0;
for(i = 0; i < size; i++){
    if(arr1[i] > arr2[i]){
    x++;
        }
    }
if(x == size){
    return 1;
    }
return 0;
}

void land(int arr1[], int arr2[], int res[], int size){
int i, x = 0;
for(i = 0; i < size; i++){
    res[i] = (arr1[i]&&arr2[i]);
    }
}

