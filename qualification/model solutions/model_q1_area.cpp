#include<bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin>>n;
  int max_area=0;
  for(int i=0;i<n;i++){
    int height,width;
    cin>>height>>width;
    int area=height*width;
    if(area>max_area)max_area=area;
  }

  cout<<max_area;
  return 0;
}
