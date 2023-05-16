#include <bits/stdc++.h>
using namespace std;

#define int long long

int X[100005];
int A[100005];
int B[100005];

signed main(){
	ios_base::sync_with_stdio(false); cin.tie(0); //fast input/output
	
	//reading input
	int n; cin >> n;
	for(int i = 1;i <= n;i++) cin >> X[i];
	for(int i = 1;i <= n;i++) cin >> A[i];
	for(int i = 1;i <= n;i++) cin >> B[i];
	
	
	int low = 0, high =  1e9+1; //binary search the number of burgers we can make
	while(low != high-1){
		int minA = 0, maxA = 1e9; //bound the possible range of values of A
		int mid = (low+high)/2; //suppose we want to make mid burgers
		
		bool can = true;
		
		for(int i = 1;i <= n;i++){ //consider ingredient by ingredient
			if(A[i] == B[i]){
				if(A[i]*mid > X[i]) can = false;
			}
			else if(A[i] < B[i]){ 
				if(A[i]*mid > X[i]) can = false;
				if(B[i]*mid <= X[i]) continue;
				
				//assume all mid burgers are A first
				//(X[i] - A[i]*mid) / (B[i] - A[i]) is max number of A that can be converted to B
				minA = max(minA, mid - (X[i] - A[i]*mid) / (B[i] - A[i]));
			}
			else{
				if(B[i]*mid > X[i]) can = false;
				if(A[i]*mid <= X[i]) continue;
				
				//assume all mid burgers are B first
				//(X[i] - A[i]*mid) / (B[i] - A[i]) is max number of B that can be converted to A
				maxA = min(maxA, (X[i] - B[i]*mid) / (A[i] - B[i]));
			}
		}
		
		if(can and minA <= maxA) low = mid; //mid burgers is achieveble
		else high = mid; //mid burgers is not achievable
	}
	
	cout << low;
}
