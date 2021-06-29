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

    bool isSync = false;
    for(ll i=0; i<n; i++){
        vector<bool> visited(n, 0);     
        queue<ll> q;
        visited[i] = 1;
        q.push(i);
        while(!q.empty()){
            ll cur = q.front();
            q.pop();
            for(ll e : invertedTransitions[cur]){
                if(!visited[e]){
                    visited[e] = 1;
                    q.push(e);
                }
            }
        }
        bool flag = true;
        for(bool e : visited)   flag &= e;
        if(flag)    isSync = true;
        if(isSync)  break;
    }
 
    if(!isSync){
        cout << "impossible\n"; 
        return;
    }
    ll n_2 = n*(n+1)/2; //total pares
    vector<vector<ll>> pairToCode(n);   //pairToCode[i][j] = k; if i=j, i=k < n;
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
            //Va de un estado tamaño 2 a otro de tamaño 2 o tamaño 1, aun no sé su nivel. Guardo la invertida. Evito bucles
            if(pairToCode[ transition[i][0] ][ transition[j][0] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][0] ][ transition[j][0] ]].push_back(make_pair(pairToCode[i][j], 0));
            if(pairToCode[ transition[i][1] ][ transition[j][1] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][1] ][ transition[j][1] ]].push_back(make_pair(pairToCode[i][j], 1));
        }
    }
    queue<ll> qu;
    unordered_set<ll> visitedStates;
    for(int i=0; i<n; i++)  visitedStates.insert(i);
    for(ll single = 0; single < n; single++){
        for(auto pcode : invertedTransitions2[single]){
            if(visitedStates.count(pcode.first))   continue;
            visitedStates.insert(pcode.first);
            qu.push(pcode.first);
        }
    }
    
    while(!qu.empty()){
        auto cur = qu.front();
        qu.pop();
        for(auto pcode : invertedTransitions2[cur]){
            //pcode.first = state
            if(!visitedStates.count(pcode.first)){
                visitedStates.insert(pcode.first);
                qu.push(pcode.first);
            }
        }
    }
    if(visitedStates.size() != n_2){
        cout << "impossible\n";
        return;
    }
    
    vector<vector<ll>> pairState(n_2);
    for(ll i = 0; i < n_2; i++) pairState[i].resize(n);
    vector<string> pairMinString(n_2, "");
    vector<ll> visited(n_2, 0);
    queue<ll> q;
    //Iniciamos con los nodos conectados a los nodos simples (0 a n-1)
    for(ll single = 0; single < n; single++){
        for(auto pcode : invertedTransitions2[single]){
            if(visited[pcode.first])   continue;
            visited[pcode.first] = 1;
            q.push(pcode.first);
            if(pcode.second)
                pairMinString[pcode.first] += "B";
            else
                pairMinString[pcode.first] += "W";
            for(ll i = 0; i < n; i++)
                pairState[pcode.first][i] = transition[i][pcode.second];
        }
    }
    while(!q.empty()){
        ll cur = q.front();
        q.pop();
        for(auto pcode : invertedTransitions2[cur]){
            if(visited[pcode.first])    continue;
            visited[pcode.first] = 1;
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