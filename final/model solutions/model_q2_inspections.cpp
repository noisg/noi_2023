#include <bits/stdc++.h>

using namespace std;

#define MAXN 500000
#define MAXM 500000
#define MAXQ 500000

#define DEBUG 0

typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;

struct segment{
    ll left, right;
    ll last_use;

    segment(int _l, int _r, ll _lst){
        left = _l, right = _r, last_use = _lst;
    }

    bool operator<(const segment &other)const{
        return right < other.right;
    }
};

typedef set<segment>::iterator ssi;

set<segment> ranges;

int is_cut(segment cur, segment nex){ 
    // 1 if cur and nex are disjoint
    // 2 if nex is entirely in cur
    // 3 if cur is entirely in nex
    // 4 if nex cuts cur on the left
    // 5 if nex cuts cur on the right
    if (cur.right < nex.left || cur.left > nex.right){
        return 1;
    }
    else if (cur.left <= nex.left && nex.right <= cur.right){
        return 2;
    }
    else if (nex.left <= cur.left && cur.right <= nex.right){
        return 3;
    }
    else if (nex.left <= cur.left && cur.left <= nex.right && nex.right <= cur.right){
        return 4;
    }
    else if (cur.left <= nex.left && nex.left <= cur.right && cur.right <= nex.right){
        return 5;
    }
}

ll N, M, Q;
ll L[MAXM+5], R[MAXM+5];
ll S[MAXQ+5];

map<ll,ll> cnt_dist;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> Q;
    for (int i = 1; i <= M; ++i){
        cin >> L[i] >> R[i];
    }
    for (int i = 1; i <= Q; ++i){
        cin >> S[i];
    }

    vector<pl> v;

    ll tim = 0;

    for (int i = 1; i <= M; ++i){
        
        if (DEBUG){
            cerr << "\nCONSIDERING TASK " << i << "\n";
        }

        segment nex(L[i],R[i],tim);
        vector<segment> cuts;
        vector<segment> ins;
        vector<ssi> del;
        ssi fnd = ranges.lower_bound(segment(L[i],L[i],0));
        while (1){
            if (fnd == ranges.end() || fnd->left > R[i]) break;
            cuts.push_back(*fnd);
            del.push_back(fnd);
            fnd++;
        }

        for (auto it : del){
            if (DEBUG){
                cerr << "DELETING RANGE [" << it->left << "," << it->right << "] WITH TIME " << it->last_use << "\n";
            }
            ranges.erase(it);
        }

        ins.push_back(nex);

        // (nex.last_use - cur.last_use) + (nex.left - cur.left)

        for (auto cur : cuts){
            int cut_dir = is_cut(cur,nex);

            ll time_dist = (nex.last_use - cur.last_use) + (cur.left - nex.left) - 1;
            ll overlap = 0;

            if (cut_dir == 1) continue;
            if (cut_dir == 2){
                ll left_s = cur.left, left_e = nex.left-1, right_s = nex.right+1, right_e = cur.right;
                ll left_time = cur.last_use, right_time = cur.last_use;

                if (left_s <= left_e){
                    ins.push_back(segment(left_s,left_e,left_time));
                }
                if (right_s <= right_e){
                    ins.push_back(segment(right_s,right_e,right_time+right_s-left_s));
                }

                overlap = (nex.right - nex.left + 1);
            }
            if (cut_dir == 3){
                overlap = (cur.right - cur.left + 1);
            }
            if (cut_dir == 4){
                ll right_s = nex.right+1, right_e = cur.right;
                ll right_time = cur.last_use;

                if (right_s <= right_e){
                    ins.push_back(segment(right_s,right_e,right_time+right_s-cur.left));
                }

                overlap = (nex.right - cur.left + 1);
            }
            if (cut_dir == 5){
                ll left_s = cur.left, left_e = nex.left-1;
                ll left_time = cur.last_use;

                if (left_s <= left_e){
                    ins.push_back(segment(left_s,left_e,left_time));
                }

                overlap = (cur.right - nex.left + 1);
            }

            if (cnt_dist.find(time_dist) == cnt_dist.end()){
                cnt_dist[time_dist] = 0;
            }
            cnt_dist[time_dist] += overlap;
        }

        for (auto it : ins){
            if (DEBUG){
                cerr << "INSERTING RANGE [" << it.left << "," << it.right << "] WITH TIME = " << it.last_use << '\n';
            }
            ranges.insert(it);
        } 

        tim += (R[i] - L[i] + 1);
        
    }

    vector<pl> dists, prefdists;
    for (auto it : cnt_dist) dists.push_back(it);
    sort(dists.begin(),dists.end());

    ll sum = 0;
    prefdists.push_back(pl(-1,0));
    for (int i = 0; i < dists.size(); ++i){
        sum += dists[i].second;
        prefdists.push_back(pl(dists[i].first,sum));
        if (DEBUG){
            cerr << "DISTANCE = " << dists[i].first << " , SUM = " << sum << '\n';
        }
    }

    for (int i = 1; i <= Q; ++i){
        cout << sum - (--lower_bound(prefdists.begin(),prefdists.end(),pl(S[i],0)))->second << ' ';
    }
    cout << '\n';


}