#include<bits/stdc++.h>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);cin.tie(0);
  int n;
  cin>>n;
  pair<int,int> swords[n];
  for(int i=0;i<n;i++){//the details of each sword...
    cin>>swords[i].first>>swords[i].second;//the attack, and the defence...
  }
  sort(swords,swords+n);

  int max_defence=0;
  int useful_swords=0;
  for(int i=n-1;i>=0;i--){
    if(swords[i].second>max_defence){
      max_defence=swords[i].second;
      useful_swords++;
    }//else, there is a sword with greater i (and therefore >=attack) and stronger defence (max defence)
    //which makes this sword useless
  }
  cout<<useful_swords;
  return 0;
}
