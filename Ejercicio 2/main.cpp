#include "../lib/lib.h"

void solve(){
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

    map<ll, setType> invertedTransitions;
    for(ll i=0; i<n; i++){
        if(i != transition[i][0])   invertedTransitions[transition[i][0]].insert(i);
        if(i != transition[i][1])   invertedTransitions[transition[i][1]].insert(i);
    }
    setType endStates;
    for(ll i=0; i<n; i++){  //n BFS's. Cada BFS es B(V+E). V = n, E = 2n. = O(n * (2n+n)) = O(3n^2)
        setType visited = {i};
        queue<ll> q;
        q.push(i);
        //BFS en cada state
        while(!q.empty()){
            ll cur = q.front();
            q.pop();
            for(auto e : invertedTransitions[cur]){
                if(!visited.count(e)){
                    q.push(e);
                    visited.insert(e);
                }
            }
        }
        if(visited.size()==n)   endStates.insert(i);
    }

    cout << "endStates:\n";
    for(auto e : endStates){
        cout << e << " ";
    }cout << "\n\n";

    if(endStates.empty()){
        cout << "NO1\n" << endStates.size(); 
        return;
    }
        
    map<setType, set<setType>> invertedTransitions2; //Guarda transiciones invertidas
    set<setType> statesConnected;   //Guarda los estados tamaño 2 conectados a un estado de tamaño 1
    for(ll i=0; i<n; i++){
        for(ll j=i+1; j<n; j++){    //O(n^2)
            //Estado tamaño 2 va a uno de tamaño 1
            if(transition[i][0] == transition[j][0])    statesConnected.insert({i,j});
            //Va de un estado tamaño 2 a otro de tamaño 2. Guardo la invertida
            else    invertedTransitions2[{transition[i][0], transition[j][0]}].insert({i, j});
            if(transition[i][1] == transition[j][1])    statesConnected.insert({i,j});
            else    invertedTransitions2[{transition[i][1], transition[j][1]}].insert({i, j});
        }
    }
    //En transition2, tengo transiciones invertidas de estados tamaño 2 a otros tamaño 2
    //Hacer BFS en cada estado tamaño 2 conectado a otro tamaño 1.
    //visited = states
    set<setType> states;    //Guarda estados tamaño 2, su tamaño debe ser n*(n-1)/2
    
    cout << "StatesConnected:\n";
    for(auto s : statesConnected){
        for(auto e : s){
            cout << e;
        }cout << endl;
    }cout << endl;

    for(auto s : statesConnected){      //BFS desde los states de tamaño 2 conectados a alguno de tamaño 1. 
                                        //Es un BFS que inicia en varios estados. O(V+E) = O(n^2 + 2*n^2)
        queue<setType> q;
        states.insert(s);
        q.push(s);
        while(!q.empty()){
            setType cur = q.front();
            q.pop();
            if(!invertedTransitions2.count(cur))    continue;
            for(auto s : invertedTransitions2[cur]){
                if(!states.count(s)){
                    states.insert(s);
                    q.push(s);
                }
            }
        }
    }

    if(states.size() != n*(n-1)/2){
        cout << "NO2\n" << states.size();
        return;
    }
    
    cout << "YES\n";
}

int main(){
    while(1){
        solve();
    }
    return 0;
}