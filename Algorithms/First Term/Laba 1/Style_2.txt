#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
 
using namespace std;
 
 
int main() {
    freopen("style.in", "r", stdin);
    freopen("style.out", "w", stdout);
 
    int first;
    cin >> first;
    vector<int> first_arr(first);
    for (int i = 0; i < first; i++)
        cin >> first_arr[i];
 
    int second;
    cin >> second;
    vector<int> second_arr(second);
    for (int i = 0; i < second; i++)
        cin >> second_arr[i];
 
    int third;
    cin >> third;
    vector<int> third_arr(third);
    for (int i = 0; i < third; i++)
        cin >> third_arr[i];
 
    int fourth;
    cin >> fourth;
    vector<int> fourth_arr(fourth);
    for (int i = 0; i < fourth; i++)
        cin >> fourth_arr[i];
 
    int min_delta = 200000;
    int cur_delta = 0;
    vector<int> result(4);
    vector<int> cur = { 0,0,0,0 };
 
    sort(first_arr.begin(), first_arr.end());
    sort(second_arr.begin(), second_arr.end());
    sort(third_arr.begin(), third_arr.end());
    sort(fourth_arr.begin(), fourth_arr.end());
 
    while (cur[0] < first && cur[1] < second && cur[2] < third && cur[3] <fourth) {
        vector<int> cur_element = { first_arr[cur[0]], second_arr[cur[1]], third_arr[cur[2]], fourth_arr[cur[3]] };
        sort(cur_element.begin(), cur_element.end());
        cur_delta = abs(cur_element[3] - cur_element[0]);
        if (cur_delta < min_delta) {
             
            result[0] = first_arr[cur[0]], result[1] = second_arr[cur[1]], result[2] = third_arr[cur[2]], result[3] = fourth_arr[cur[3]];
            min_delta = cur_delta;
            if (min_delta == 0) break;
        }
        if (  cur[0] < first && cur_element[0] == first_arr[cur[0]])
            cur[0]++;
        else if (cur[1] < second  && cur_element[0] == second_arr[cur[1]])
            cur[1]++;
        else if ( cur[2] < third  && cur_element[0] == third_arr[cur[2]])
            cur[2]++;
        else if ( cur[3] < fourth  && cur_element[0] == fourth_arr[cur[3]])
            cur[3]++;
        else break;
 
 
    }
 
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}