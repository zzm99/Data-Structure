#include <iostream>
using namespace std;
#define NUM 50
int Data[NUM];

void Display(int data[], int low, int high)
{
    for (int i = low; i <= high; i++) cout << data[i] << " ";
    cout << endl;
}

void Merge(int data[], int lx, int ly, int hx, int hy){
    int tmp[NUM] = {0};
    int ii = lx, yy = hy;
    int z = 0;
    while(lx <= ly && hx <= hy){
        if(data[lx] <= data[hx]){
            tmp[z++] = data[lx];
            lx++;
        }else{
            tmp[z++] = data[hx];
            hx++;
        }
    }
    while(lx <= ly){
        tmp[z++] = data[lx];
        lx++;
    }
    while(hx <= ly){
        tmp[z++] = data[hx];
        hx++;
    }
    for(int i=ii; i<=yy; i++){
        data[i] = tmp[i-ii];
    }
    Display(data, 0, 49);
}

void MergeSort(int data[], int low, int high){
    if(low >= high) return;
    int mid = low + (high-low)/2;
    MergeSort(data, low, mid);
    MergeSort(data, mid+1, high);
    Merge(data, low, mid, mid+1, high);
}

int main(){
    for(int i=49; i>=0; i--) Data[50-i-1] = i;
    MergeSort(Data, 0, NUM-1);
    return 0;
}
