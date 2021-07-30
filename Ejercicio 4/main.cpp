#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <array>

using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define ll long long

const ll MOD = 1e9+7;

void solve(){
    ll n, num;   cin >> n;
    vector<vector<ll>> transition(n);
    for(ll i=0; i<n; i++)   transition[i].resize(2);
    for(ll i=0; i<n; i++){
        cin >> num;
        transition[i][0] = num-1;
    }
    for(ll i=0; i<n; i++){
        cin >> num;
        transition[i][1] = num-1;
    }
    
    vector<vector<ll>> invertedTransitions(n);
    for(ll i=0; i<n; i++){
        if(i != transition[i][0])   invertedTransitions[transition[i][0]].push_back(i);
        if(i != transition[i][1])   invertedTransitions[transition[i][1]].push_back(i);
    }

    bool sinkDetec = false;
    for(ll i=0; i<n; i++){
        vector<bool> visited(n, 0);     
        queue<ll> q;
        visited[i] = 1;
        q.push(i);
        while(!q.empty()){
            for(ll e : invertedTransitions[q.front()]){
                if(!visited[e]){
                    visited[e] = 1;
                    q.push(e);
                }
            }
            q.pop();
        }
        for(ll i = 0; i < n; i++){
            if(!visited[i]) break;
            if(i == n - 1 && visited[i]) sinkDetec = true;
        }
        if(sinkDetec)  break;
    }
    if(!sinkDetec){
        cout << "impossible\n"; 
        return;
    }
    ll n_2 = n*(n+1)/2;
    vector<vector<ll>> pairToCode(n);
    for(ll i = 0; i < n; i++)   pairToCode[i].resize(n);
    ll code = n;
    for(ll i=0; i<n; i++){
        for(ll j=i; j<n; j++){
            if(i == j)
                pairToCode[i][i] = i;
            else{
                pairToCode[i][j] = code;
                pairToCode[j][i] = code++;
            }
        }
    }
    
    vector<vector<pair<ll, ll>>> invertedTransitions2(n_2);
    for(ll i=0; i<n; i++){
        for(ll j=i+1; j<n; j++){
            if(pairToCode[ transition[i][0] ][ transition[j][0] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][0] ][ transition[j][0] ]].push_back(make_pair(pairToCode[i][j], 0));
            if(pairToCode[ transition[i][1] ][ transition[j][1] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][1] ][ transition[j][1] ]].push_back(make_pair(pairToCode[i][j], 1));
        }
    }
    queue<ll> qu;
    vector<bool> visited(n_2, 0);
    for(ll i=0; i<n; i++){
        visited[i] = 1;
        qu.push(i);
    }
    while(!qu.empty()){
        for(pair<ll, ll> pcode : invertedTransitions2[qu.front()]){
            if(!visited[pcode.first]){
                visited[pcode.first] = 1;
                qu.push(pcode.first);
            }
        }
        qu.pop();
    }
    for(ll i=0; i<n_2; i++){
        if(!visited[i]){
            cout << "impossible\n";
            return;
        }
    }
    
    vector<vector<ll>> pairState(n_2);                          
    for(ll i = 0; i < n_2; i++) pairState[i].resize(n);         
    vector<string> pairMinString(n_2, "");                      
    vector<bool> visited2(n_2, 0);                              
    queue<ll> q;
    for(ll i = 0; i < n; i++){
        q.push(i);
        for(ll j=0; j < n; j++){
            pairState[i][j] = j;
        }
    }
    while(!q.empty()){
        ll cur = q.front();
        q.pop();
        for(auto pcode : invertedTransitions2[cur]){
            if(visited2[pcode.first])    continue;
            visited2[pcode.first] = 1;
            q.push(pcode.first);
            if(pcode.second)
                pairMinString[pcode.first] = "B" + pairMinString[cur];
            else
                pairMinString[pcode.first] = "W" + pairMinString[cur];
            for(ll i = 0; i < n; i++)                           
                pairState[pcode.first][i] = pairState[cur][ transition[i][pcode.second] ];
        }
    }
    unordered_set<ll> X;
    for(ll i=0; i<n; i++)   X.insert(i);
    string cad = "";
    ll s1, s2, codes1s2;
    while(X.size() > 1){
        auto it = X.begin();
        s1 = *(it++);
        s2 = *it;
        codes1s2 = pairToCode[s1][s2];
        cad += pairMinString[codes1s2];
        unordered_set<ll> Y;
        for(auto state : X)
            Y.insert(pairState[codes1s2][state]);
        X = Y;
    }
    cout << cad << endl;
}
 
int main(){ 
    fastio;
    ll q;
    cin >> q; while(q--)    solve();
    //solve();
    return 0;
}