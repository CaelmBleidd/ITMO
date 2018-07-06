
 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 
using namespace std;
 
int min_distance;
int number;
long length;
double sum_timings;
 
vector<int> timings;
vector<int> speed;
//vector<int> first_train_x;
 
 
double find_cur_location(double time) {
    double result = 0;
    if (time <= 0) {
        result = 0;
    }
    else if (time > sum_timings)
    {
        return length + min_distance;
    }
    else {
        int i = 0; 
        while(time>timings[i]){
            result += speed[i] * timings[i];
            time -= timings[i++];   
        }
        result += time*speed[i];    
    }   
    return result;
}
 
 
double damnAnswer(double l, double r) {
 
    bool isTrue = true;                 
    double left = l, right = r; 
    while (right - left > 0.0001) {          //��������
        isTrue = true;                      //��������� �������� �������
        double mid = (left + right) / 2;            //�������� ��������
        double sum_cur_timings = 0;             //������� ����� ������ � ������
             
        for (int i = 0; i <= number; i++) {
            sum_cur_timings += timings[i];          //������������ ������� ����� ����������� ����������
        //  if (speed[i] == 0) continue;
            double train = find_cur_location(sum_cur_timings), next_train = find_cur_location(sum_cur_timings - mid),  prev_train = find_cur_location(sum_cur_timings + mid);
 
            if (next_train == 0 || train == 0) {
                if (prev_train - train < min_distance) {
                    isTrue = false;
                    break;
                }
            }
            else {
                if (train - next_train < min_distance || prev_train - train < min_distance)
                {
                    isTrue = false;
                    break;
                }
 
 
            }
        }
 
        if (isTrue)
            right = mid;
        else
            left = mid;
    }
 
    return (left + right) / 2;
}
 
int main() {
    freopen("trains.in", "r", stdin);
    freopen("trains.out", "w", stdout);
 
    cin >> min_distance;
    cin >> number;
 
    timings.resize(number+1);
    speed.resize(number+1);
    timings[0] = 0;
    speed[0] = 1;
 
    //first_train_x.resize(number);
 
    for (int i = 1; i <= number; i++) {
        cin >> timings[i] >> speed[i];
        length += timings[i] * speed[i];
        //  first_train_x[i] += timings[i] * speed[i];
        sum_timings += timings[i];
    }
 
    double answer = damnAnswer(0, sum_timings);
    printf("%.3f", answer);
 
 
    fclose(stdin);
    fclose(stdout);
    return 0;
}