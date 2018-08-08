#include <vector> 
#include <iostream>
#include <string>
#include <fstream> 
 
using namespace std;
 
vector<pair<long, long>> queue(1000000);
long heapsize = 0;
long number = 0;
 
void siftUp(int i) {
    while (queue[i].first<queue[(i-1)/2].first)
    {
        swap(queue[i], queue[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
 
void siftDown(int i) {
    while (2 * i + 1 < heapsize) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < heapsize && queue[right].first<queue[left].first)
            j = right;
        if (queue[i].first <=queue[j].first)
            break;
        swap(queue[i], queue[j]);
        i = j;
    }
}
 
long extractMin() {
    long min = queue[0].first;
    queue[0] = queue[heapsize - 1];
    heapsize--;
    siftDown(0);
    return min;
}
 
void push(long key) {
    heapsize++;
    queue[heapsize - 1].first = key;
    queue[heapsize - 1].second = number;
    siftUp(heapsize-1);
 
}
 
void decreaseKey(long operation, long count) {
    for (int i = 0; i < heapsize; i++) {
        if (queue[i].second == operation) {
            queue[i].first = count; 
            siftUp(i);
        }
    }
}
 
 
int main() {
    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);
    string str;
    while (cin >> str)
    {          
         
        number++;
        if (str == "push")
        {
            long a;
            cin >> a;
            push(a);
        }
        else if (str == "extract-min")
        {
            if (heapsize != 0) {
                long min = extractMin();
                cout << min << "\n";
            }
            else {
                cout << "*\n";
            }
        }
        else if(str == "decrease-key") {
            long operation, count;
            cin >> operation >> count;
            decreaseKey(operation, count);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
 
     
 
 
}