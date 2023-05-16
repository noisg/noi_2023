#include<bits/stdc++.h>
using namespace std;

#define int long long

const int mxnk=5e6+5,mxn=mxnk,mxk=mxnk;

int R[mxnk],U[mxnk];
int n,k;
#define r(i,j) R[i*k+j]
#define u(i,j) U[i*k+j]

int filled[mxn];//for each task, how many requirements fulfilled
int cur[mxk];//for each topic, current knowledge...

#define f first
#define s second
vector<pair<int,int> > reqs[mxk];//for each topic, store (requirement, task index)
int ind[mxk];//index of next req to hit in reqs...

int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    cin>>n>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            cin>>r(i,j);
            reqs[j].emplace_back(r(i,j),i);
        }
    }
    for(int j=0;j<k;j++)sort(reqs[j].begin(),reqs[j].end());
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++)cin>>u(i,j);
    }
    int ans=0;
    vector<int>nex;
    bool can=1;
    while(can){
        can=0;
        for(int j=0;j<k;j++){
            while(ind[j]<n && reqs[j][ind[j]].f<=cur[j]){
                filled[reqs[j][ind[j]].s]++;
                if(filled[reqs[j][ind[j]].s]==k){
                    // nex.push_back(reqs[j][ind[j]].s);
                    // int x=reqs[j][ind[j]].s;
                    for(int jj=0;jj<k;jj++){
                        cur[jj]+=u(reqs[j][ind[j]].s,jj);
                    }
                    ans++;
                    can=1;
                }
                ind[j]++;
            }
        }
        // if(nex.size()==0)break;
        // while(nex.size()>0){
            
        // }
    }
    cout<<ans;
    return 0;
}