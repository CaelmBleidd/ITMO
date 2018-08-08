#include <iostream>
#include <fstream> 
#include <algorithm>
#include<cstdlib>
#include <time.h>
#include <stdint.h>
#include <vector>
 
using namespace std;
 
vector<int> arr;
 
int size_array, k, A, B, C;
 
 
int partition(int begin, int end) {
    int index = (begin + end) / 2;
    long pivot = arr[index];
    int i = begin;
    int j = end;
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i++], arr[j--]);
        }
    }
    return max(j, begin);
}
 
 
int kth (int left, int right) {
    if (left == right)
        return arr[left];
    int val = partition(left, right);
    if (k <=val)
        return kth(left, val);
    else return kth(val + 1, right);
 
}
 
 
int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
     
     
 
    cin >> size_array >> k;
 
    k--;
    arr.resize(size_array);
 
 
    cin >> A >> B >> C;
    cin >> arr[0] >> arr[1];
 
 
 
 
 
    for (int i = 2; i < size_array; i++) {
        arr[i]=(A*arr[i - 2] + B*arr[i - 1] + C);
    }
 
 
    if (size_array == 1)
    {
        cout << arr[0]; 
        fclose(stdin);
        fclose(stdout);
        return 0;
    }
    int result = kth(0, size_array -1);
    cout << result;
    fclose(stdin);
    fclose(stdout);
 
    return 0;
}