#include "toxic.h"
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;


namespace {
    static void wrong_answer(){
        printf("%d\n",-1);
        exit(0);
    }
    static int tc, current_tc, N, batchsize = 300, qlimit = 600;
    static int q[105];
    static char answer[105][305];
    static char participant_type[105][305];
}

int query_sample(vector<int> species){
    if (species.size() > batchsize){
        wrong_answer();
    }
    q[current_tc]++;
    if (q[current_tc] > qlimit){
        wrong_answer();
    }
    bool has_toxic = false;
    int reg = 0, strong = 0;
    for (int i = 0; i < (int) species.size(); ++i){
        if (species[i] < 1 || species[i] > N){
            wrong_answer();
        }
        char tp = answer[current_tc][species[i]];
        if (tp == 'T'){
            has_toxic = true;
        }
        if (tp == 'R'){
            reg++;
        }
        if (tp == 'S'){
            strong++;
        }
    }
    if (has_toxic) return strong;
    else return reg + strong;
}

void answer_type(int x, char c){
    if (x < 1 || x > N) wrong_answer();
    if (c != 'T' && c != 'R' && c != 'S') wrong_answer(); 
    participant_type[current_tc][x] = c;
    if (participant_type[current_tc][x] != answer[current_tc][x]) wrong_answer();
}

int main(){

    assert(2 == scanf("%d %d\n",&tc,&N));
    for (int t = 1; t <= tc; ++t){
        assert(1 == scanf("%s",answer[t]));
        for (int i = N; i >= 1; --i){
            answer[t][i] = answer[t][i-1];
        }
        answer[t][0] = 'X';
        for (int i = 1; i <= N; ++i){
            participant_type[t][i] = 'X';
        }
    }
    for (int t = 1; t <= tc; ++t){
        current_tc = t;
        q[current_tc] = 0;
        determine_type(N);
        for (int i = 1; i <= N; ++i){
            if (participant_type[current_tc][i] != answer[current_tc][i]) wrong_answer();
        }
    }
    


    for (int t = 1; t <= tc; ++t){
        printf("%d\n",q[t]);
    }
    return 0;
    
}