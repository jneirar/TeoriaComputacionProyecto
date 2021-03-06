#include "../lib.h"
#include "../functions.h"

int main(){
    ll n, qi, nqf; 
    cin >> n >> qi >> nqf;
    unordered_set<ll> qf;
    ll tmp1, tmp2;
    for(ll i=0; i<nqf; i++){
        cin >> tmp1;
        qf.insert(tmp1);
    }
    vector<vector<ll>> transition(n);
    for(ll i=0; i<n; i++)   transition[i].resize(2);
    for(ll i=0; i<2*n; i++)
        cin >> tmp1 >> tmp2 >> transition[tmp1][tmp2];

    if(Dec_Sinc(n, transition))   cout << "SI\n";
    else cout << "NO\n";
    
    return 0;
}