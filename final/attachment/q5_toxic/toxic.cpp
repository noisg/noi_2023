#include "toxic.h"

void determine_type(int n){
	std::vector<int> v;
	v.push_back(1);
	int qvalue = query_sample(v);
	answer_type(1,'T');
}