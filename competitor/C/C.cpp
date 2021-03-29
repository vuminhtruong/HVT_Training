#include <bits/stdc++.h>

using namespace std;
namespace DEBUG {
    void __print(int x) {cerr << x;}
    void __print(long x) {cerr << x;}
    void __print(long long x) {cerr << x;}
    void __print(unsigned x) {cerr << x;}
    void __print(unsigned long x) {cerr << x;}
    void __print(unsigned long long x) {cerr << x;}
    void __print(float x) {cerr << x;}
    void __print(double x) {cerr << x;}
    void __print(long double x) {cerr << x;}
    void __print(char x) {cerr << '\'' << x << '\'';}
    void __print(const char *x) {cerr << '\"' << x << '\"';}
    void __print(const string &x) {cerr << '\"' << x << '\"';}
    void __print(bool x) {cerr << (x ? "true" : "false");}

    template<typename T, typename V>
    void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
    template<typename T>
    void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
    void _print() {cerr << "]\n";}
    template <typename T, typename... V>
    void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define rand __rand
    mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
    template <class T = int>
    T rand(T range = numeric_limits <T> :: max()){
        return (T) (generator() % range);
    }
}
using namespace DEBUG;

template <class T,class U>
void maximize(T &lhs,U rhs){
    if(lhs < rhs)lhs = rhs;
}
template <class T,class U>
void minimize(T &lhs,U rhs){
    if(lhs > rhs)lhs = rhs;
}
template <class T>
T tabs(T x){
    return (x < (T)0 ? -x : x);
}

#define len(c) (int)((c).size())
#define llong int64_t
#define MASK(i) ((1LL) << (i))
#define BIT(x,i) (((x) >> (i)) & 1)
#define file_name "test"    /// FILE NAME HERE!!!

/* ================================= END OF TEMPLATE ================================= */

namespace Task{

    class Solver{
        public:

            static const int BASE = (int)(1e9 + 7);
            static const int N = 54;

            int f(string val){
                vector < int > digits; digits.emplace_back(0);
                for(int i = len(val) - 1;i >= 0;--i){
                    digits.emplace_back(val[i] - '0');
                }
                int L = len(digits);
                int dp[L + 2][(L + 6) / 3][(L + 6) / 3][(L + 6) / 3][2];
                memset(dp,-1,sizeof(dp));
                dp[L - 1][0][0][0][1] = 1;
                for(int pos = L - 1;pos > 0;--pos){
                    for(int th = 0;3 * th <= L;++th){
                        for(int si = 0;3 * si <= L;++si){
                            for(int ni = 0;3 * ni <= L;++ni){
                                for(int flag = 0;flag < 2;++flag){
                                    if(dp[pos][th][si][ni][flag] != -1){
                                        int bound = flag ? digits[pos] : 9;
                                        for(int k = 0;k <= bound;++k){
                                            int new_flag = flag & (digits[pos] == k);
                                            int &cur = dp[pos - 1][th + (k == 3)][si + (k == 6)][ni + (k == 9)][new_flag];
                                            if(cur == -1){
                                                cur = dp[pos][th][si][ni][flag];
                                            } else {
                                                cur += dp[pos][th][si][ni][flag];
                                                if(cur >= BASE){
                                                    cur -= BASE;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                int ans = 0;
                for(int c = 1;3 * c <= L;++c){
                    for(int flag = 0;flag < 2;++flag){
                        if(dp[0][c][c][c][flag] != -1){
                            ans += dp[0][c][c][c][flag];
                            if(ans >= BASE){
                                ans -= BASE;
                            }
                        }
                    }
                }
                return ans;
            }
            
            void solve(){
                string l,r; cin>>l>>r;
                auto cnt = [&](const char &c) -> int{
                    return (int)count_if(l.begin(),l.end(),[c](const char &cur) -> bool{
                            return cur == c;
                    });
                };
                int ans = f(r) - f(l);
                if(ans < 0){
                   ans += BASE;
                }
                ans += (cnt('3') > 0 and cnt('3') == cnt('6') and cnt('6') == cnt('9'));
                if(ans >= BASE){
                    ans -= BASE;
                }
                cout<<ans<<'\n';
            }

            ~Solver(){} 
    };

    void solve(){
        int ntest = 1;
#ifndef  ONLINE_JUDGE
        ntest = 1; // single test to multitest.
#endif
        cin>>ntest;  // multitest
        while(ntest--){
            Solver().solve();
        }
    }
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    Task::solve();
}

