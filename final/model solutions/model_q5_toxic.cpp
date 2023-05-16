#include "toxic.h"
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define show(x) cerr << #x << " is " << x << endl;
#define show2(x,y) cerr << #x << " is " << x << " " << #y << " is " << y << endl;
typedef pair<int, int> ii;

vector<int> toquery;
int query(){
	return query_sample(toquery);
}

deque<int> an;
deque<int> nt;
deque<int> unknown;
int onetoxic = -1;
set<int> antidode;

bool checkunknown(vector<int> elements){
	if(sz(elements) == 0) return false;
		
	toquery.clear();
	
	for(int i = 0;i < sz(elements);i++){
		for(int j = 0;j < (1 << i);j++) toquery.push_back(elements[i]);
	}
	
	int cnt = min(sz(an), 8-sz(elements));
	for(int i = 0;i < cnt;i++){
		for(int j = 0;j < (1 << (i+sz(elements)));j++) toquery.push_back(an[i]);
	}
		
	int res = query_sample(toquery);
	if(res == sz(toquery)){
		return false;
	}
	else{
		for(int i = 0;i < sz(elements);i++){
			if(res & (1 << i)){
				answer_type(elements[i], 'S');
				antidode.insert(elements[i]);
			}
		}
		for(int i = 0;i < cnt;i++){ ///piggybacking
			if(res & (1 << (i+sz(elements)))) answer_type(an[0], 'S');
			else answer_type(an[0], 'R');
			an.pop_front();
		}
		return true;
	}
}

bool checknt(vector<int> elements){
	if(sz(elements) == 0) return false;
		
	toquery.clear();
	
	for(int i = 0;i < sz(elements);i++){
		toquery.push_back(elements[i]);
	}
	
	int cnt = min(sz(an), 8);
	for(int i = 0;i < cnt;i++){
		for(int j = 0;j < (1 << i);j++) toquery.push_back(an[i]);
	}
		
	int res = query_sample(toquery);
	if(res == sz(toquery)){
		return false;
	}
	else{
		for(int i = 0;i < cnt;i++){ ///piggybacking
			if(res & (1 << i)) answer_type(an[0], 'S');
			else answer_type(an[0], 'R');
			an.pop_front();
		}
		return true;
	}
}

void bsta(vector<int> elements){ ///assuming inside this group already got something bad
	if(sz(elements) == 0) return;
	if(sz(elements) == 1){
		onetoxic = elements[0];
		answer_type(elements[0], 'T');
		return;
	}
	
	vector<int> newelements;
	for(int x : elements) if(antidode.find(x) == antidode.end()) newelements.push_back(x);
	
	int mid = sz(newelements) / 2;
	
	vector<int> L, R;
	for(int i = 0;i < mid;i++){
		L.push_back(newelements[i]);
	}
	for(int i = mid;i < sz(newelements);i++){
		R.push_back(newelements[i]);
	}
	
	if(checknt(L)){ ///L have toxic
		for(int x : R) nt.push_back(x);
		bsta(L);
	}
	else{ ///L don't have toxic
		for(int x : L) answer_type(x, 'R');
		bsta(R);
	}
}


void determine_type(int n){
	an.clear(); unknown.clear(); antidode.clear();
	for(int i = 1;i <= n;i++) unknown.push_back(i);
	random_shuffle(all(unknown));
	
	while(sz(unknown) > 0){
		//show(sz(unknown));
		
		int batchsize = min(7, sz(unknown));
		vector<int> totest;
		for(int i = 0;i < batchsize;i++){
			totest.push_back(unknown[0]);
			unknown.pop_front();
		}
		
		if(checkunknown(totest)) bsta(totest);
		else{
			for(int x : totest) an.push_back(x);
		}
	}
	
	while(sz(nt) > 0){
		int batchsize = min(8, sz(nt));
		vector<int> totest;
		for(int i = 0;i < batchsize;i++){
			totest.push_back(nt[0]);
			nt.pop_front();
		}
		
		if(checknt(totest)) bsta(totest);
		else{
			for(int x : totest) answer_type(x, 'R');
		}
	}
	
	//if(current_tc % 100 == 0) show(sz(an));
	while(sz(an) > 0){
		checknt({onetoxic});
	}
}
