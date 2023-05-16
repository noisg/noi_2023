#include <bits/stdc++.h>

using namespace std;

#define MAXN 500000
#define MAXM 500000
#define MAXQ 500000

#define DEBUG 0

typedef pair<int,int> pi;

bool endpoint_cmp(pi A, pi B){
    return A.second < B.second;
}

int N, M, Q;
int L[MAXM+5], R[MAXM+5], S[MAXQ+5], E[MAXQ+5];
int ans[MAXQ+5]; 

struct node{
    node *left = nullptr, *right = nullptr;
    int s, e, rend, act = 0;
    
    int lazy_left = -1, lazy_right = -1;

    node (int _s, int _e){
        s = _s;
        e = _e;
        if (s != e){
            left = new node(s,(s+e)/2);
            right = new node((s+e)/2+1,e);
        }
        else rend = s-1;
    }

    void update_lazy(int ul, int ur){
        if (lazy_left == -1 || ul <= lazy_left){
            lazy_left = ul;
            lazy_right = ur;
        }
        else if (ul <= lazy_right){
            lazy_right = ur;
        }
    }

    void propagate(){
        if (lazy_left == -1) return;
        left->update_lazy(lazy_left,lazy_right);
        right->update_lazy(lazy_left,lazy_right);
        lazy_left = lazy_right = -1;
    }

    void update(int l, int r, int ul, int ur){
        if (DEBUG) cerr << "UPDATING NODE [" << s << "," << e << "] WITH UPDATE LEFT = " << l << ", RIGHT = " << r << ", U-LEFT = " << ul << ", U-RIGHT = " << ur << '\n';
        if (l > e || r < s){
            if (DEBUG) cerr << "OUT OF RANGE\n";
            return;
        }
        if (l <= s && e <= r){
            if (DEBUG) cerr << "IN RANGE, UPDATING CURRENT L-LEFT = " << lazy_left << ", L-RIGHT = " << lazy_right << "\n";
            update_lazy(ul,ur);
            if (DEBUG) cerr << "NEW L-LEFT = " << lazy_left << ", L-RIGHT = " << lazy_right << "\n";
            return;
        }
        propagate();
        left->update(l,r,ul,ur);
        right->update(l,r,ul,ur);
    }

    pi query(int x){
        if (DEBUG){
            cerr << "QUERYING NODE [" << s << "," << e << "] AT INDEX X = " << x << "\n";
        }
        if (s == e){
            if (lazy_left != -1){
                if (rend >= lazy_left){
                    rend = max(rend,lazy_right);
                    act = 1;
                }
                lazy_left = lazy_right = -1;
            }
            if (DEBUG){
                cerr << "END QUERYING NODE [" << s << "," << e << "] AT INDEX X = " << x << "\n";
                cerr << "RETURNING FROM BASE NODE (REND = " << rend << ", ACTIVE = " << act << "}\n"; 
            }
            return pi(rend,act);
        }
        else{
            pi a;
            if (x <= (s+e)/2) a = left->query(x);
            else a = right->query(x);
            if (lazy_left != -1){
                if (a.first >= lazy_left){
                    a.first = max(a.first,lazy_right);
                    a.second = 1;
                }
            }
            if (DEBUG){
                cerr << "END QUERYING NODE [" << s << "," << e << "] AT INDEX X = " << x << "\n";
                cerr << "RETURNING FROM INTERMEDIATE NODE (REND = " << a.first << ", ACTIVE = " << a.second << "}\n";
            }
            
            return a;
        }
    }



} *root = nullptr;

struct op{
    int typ; // update = 0, query = 1
    int l, r;
    int idx; // for queries

    op(int _t, int _l, int _r, int _i){
        typ = _t, l = _l, r = _r, idx = _i;
    }

    bool operator<(const op &other)const{
        return r < other.r || (r == other.r && typ < other.typ);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> M >> Q;

    vector<op> v;

    for (int i = 1; i <= M; ++i){
        cin >> L[i] >> R[i];
        v.push_back(op(0,L[i],R[i],i));
    }

    for (int i = 1; i <= Q; ++i){
        cin >> S[i] >> E[i];
        v.push_back(op(1,S[i],E[i],i));
    }

    sort(v.begin(),v.end());

    root = new node(1,N);

    for (auto it : v){
        if (DEBUG){
            cerr << "PROCESSING OP WITH PARAMS {TYPE = " << it.typ << ", LEFT = " << it.l << ", RIGHT = " << it.r << ", INDEX = " << it.idx << "}\n";
        }
        if (it.typ == 0){
            if (DEBUG) cerr << "UPDATING\n";
            root->update(1,it.l,it.l-1,it.r);
        }
        else{
            pi far = root->query(it.l);
            if (far.first == it.r && far.second == 1) ans[it.idx] = 1;
            else ans[it.idx] = 0;
        }
    }

    for (int i = 1; i <= Q; ++i){
        if (ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }

}