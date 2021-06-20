#include "../lib/lib.h"

string shortestString(vector<vector<ll>> transition, ll n){
    setType sInit;
    for(ll i=0; i<n; i++)  sInit.insert(i);                             //O(nlg(n))

    //BFS
    map<setType, string> shortString;                                   //max: 2^n
    set<setType> visited;                                               //max: 2^n
    queue<setType> qState;                                             
    qState.push(sInit);                                                 //O(1)
    visited.insert(sInit);                                              //O(1)
    shortString[sInit] = "";                                            //O(1)
    while(!qState.empty()){                                             //O(V + E) | V*(costo de hacer la transición)
        setType sNext0, sNext1;
        for(ll state : qState.front()){                                 //O(n)
            sNext0.insert(transition[state][0]);                        //O(lg(n))
            sNext1.insert(transition[state][1]);                        //O(lg(n))
        }
        if(!visited.count(sNext0)){                                     //O(lg(n))
            visited.insert(sNext0);                                     //O(lg(2^n)) = O(n)
            shortString[sNext0] = shortString[qState.front()] + '0';    //O(1 + lg(2^n)) = O(n)
            qState.push(sNext0);                                        //O(1)
        }
        if(!visited.count(sNext1)){                                     
            visited.insert(sNext1);                                     
            shortString[sNext1] = shortString[qState.front()] + '1';    
            qState.push(sNext1);                                        
        }
        qState.pop();                                                   //O(1)
        if(sNext0.size() == 1)                                          //O(1)
            return shortString[sNext0];                                 //O(1)
        if(sNext1.size() == 1)
            return shortString[sNext1]; 
    }
    return ".";
}

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

    string minCad = shortestString(transition, n);
    
    if(minCad == ".")   cout << "NO\n";                     
    else    cout << minCad << "\n" << minCad.length() << endl;

    return 0;
}