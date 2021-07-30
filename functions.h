#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "lib.h"

string Min_Sinc(vector<vector<ll>> transition, ll n){       //O(n*2^n)
    //vbool = vector<bool>
    vbool sInit(n, 1);                                      //n
    //BFS
    unordered_map<vbool, string> shortString;               //max 2^n
    unordered_set<vbool> visited;                           //max 2^n
    queue<vbool> qState;                                                
    qState.push(sInit);                                     //O(1)
    visited.insert(sInit);                                  //O(1)
    shortString[sInit] = "";                                //O(1)
    
    while(!qState.empty()){                                 //O(V + E) = O(2^n * transición)
        vbool vCur = qState.front();                        //max n
        vbool sNext0(n, 0), sNext1(n, 0);                   //max n
        for(ll i = 0; i < n; i++){                          //O(n)
            if(vCur[i]){                                    //O(1)
                sNext0[transition[i][0]] = 1;               //O(1)
                sNext1[transition[i][1]] = 1;               //O(1)
            }
        }
        if(!visited.count(sNext0)){                         //O(n)
            visited.insert(sNext0);                         //O(n)
            shortString[sNext0] = shortString[qState.front()] + '0';//O(n)
            qState.push(sNext0);                            //O(1)
        }
        if(!visited.count(sNext1)){                                     
            visited.insert(sNext1);                                     
            shortString[sNext1] = shortString[qState.front()] + '1';    
            qState.push(sNext1);                                        
        }
        qState.pop();                                       //O(1)           
        int sum = 0;                                        //O(1)
        for(int i = 0; i < n; i++) sum += sNext0[i];        //O(n)
        if(sum == 1)                                        //O(1)          
            return shortString[sNext0];                     //O(1)           
        sum = 0;                                            //O(1)            
        for(int i = 0; i < n; i++) sum += sNext1[i];        //O(n)            
        if(sum == 1)                                        //O(1)            
            return shortString[sNext1];                     //O(1)            
    }
    return ".";
}

vector<vector<ll>> pairCodification(ll n){                 //O(n^2)
    vector<vector<ll>> pairToCode(n);                      
    for(ll i = 0; i < n; i++)   pairToCode[i].resize(n);   //O(n)
    ll code = n;                                           //O(1)
    for(ll i=0; i<n; i++){                                 //O(n^2)
        for(ll j=i; j<n; j++){                             //O(n)
            if(i == j)                                     //O(1)
                pairToCode[i][i] = i;                      //O(1)
            else{                                          //O(1)
                pairToCode[i][j] = code;                   //O(1)
                pairToCode[j][i] = code++;                 //O(1)
            }
        }
    }
    return pairToCode;
}

vector<vector<pair<ll, ll>>> pairInvertedTransition(ll n, vector<vector<ll>> transition, vector<vector<ll>> pairToCode){//O(n^2)
    vector<vector<pair<ll, ll>>> invertedTransitions(n*(n+1)/2);   
    for(ll i=0; i<n; i++){                                                              //O(n * n) = O(n^2)
        for(ll j=i+1; j<n; j++){                                                        //O(n)
            //Evito bucles, operaciones O(1)
            if(pairToCode[ transition[i][0] ][ transition[j][0] ] != pairToCode[i][j])
                invertedTransitions[pairToCode[ transition[i][0] ][ transition[j][0] ]].push_back(make_pair(pairToCode[i][j], 0));
            if(pairToCode[ transition[i][1] ][ transition[j][1] ] != pairToCode[i][j])
                invertedTransitions[pairToCode[ transition[i][1] ][ transition[j][1] ]].push_back(make_pair(pairToCode[i][j], 1));
        }
    }
    return invertedTransitions;
}

bool Dec_Sinc(ll n, vector<vector<ll>> transition){         //O(n^2)
    vector<vector<ll>> invertedTransitions(n);
    for(ll i=0; i<n; i++){                                  //O(n)
        if(i != transition[i][0])   invertedTransitions[transition[i][0]].push_back(i);
        if(i != transition[i][1])   invertedTransitions[transition[i][1]].push_back(i);
    }
    bool sinkDetec = false;
    for(ll i=0; i<n; i++){                                  //O(n^2)
        vector<bool> visited(n, 0);                         
        queue<ll> q;
        visited[i] = 1;
        q.push(i);
        while(!q.empty()){                                  //BFS = O(n)
            for(ll e : invertedTransitions[q.front()]){
                if(!visited[e]){
                    visited[e] = 1;
                    q.push(e);
                }
            }
            q.pop();
        }
        for(ll i = 0; i < n; i++){                          //O(n)
            if(!visited[i]) break;
            if(i == n - 1 && visited[i]) sinkDetec = true;
        }
        if(sinkDetec)  break;
    }
    if(!sinkDetec) return false;
    
    ll n_2 = n*(n+1)/2;
    vector<vector<ll>> pairToCode = pairCodification(n);    //O(n^2)
    vector<vector<pair<ll, ll>>> invertedTransitions2 = pairInvertedTransition(n, transition, pairToCode);  //O(n^2)
    queue<ll> q;
    vector<bool> visited(n_2, 0);
    for(ll i=0; i<n; i++){                                  //O(n)
        visited[i] = 1;
        q.push(i);
    }
    while(!q.empty()){                                      //BFS = O(n^2)
        for(pair<ll, ll> pcode : invertedTransitions2[q.front()]){
            //pcode.first = state codificado
            if(!visited[pcode.first]){
                visited[pcode.first] = 1;
                q.push(pcode.first);
            }
        }
        q.pop();
    }
    for(ll i=0; i<n_2; i++)                                 //BFS = O(n^2)
        if(!visited[i]) return false;
    return true;
}

string Cad_Sinc(ll n, vector<vector<ll>> transition){    //O(n^3)
    ll n_2 = n*(n+1)/2; //total pares
    vector<vector<ll>> pairToCode = pairCodification(n); //O(n^2)
    vector<vector<pair<ll, ll>>> invertedTransitions2 = pairInvertedTransition(n, transition, pairToCode);  //O(n^2)

    vector<vector<ll>> pairState(n_2);                          
    for(ll i = 0; i < n_2; i++) pairState[i].resize(n);  //O(n^2)
    vector<string> pairMinString(n_2, "");                      
    vector<ll> visited(n_2, 0);                                 
    queue<ll> q;
    for(ll i = 0; i < n; i++){                           //O(n^2)
        q.push(i);
        for(ll j=0; j < n; j++){                         //O(n)
            pairState[i][j] = j;
        }
    }
    while(!q.empty()){                                   //BFS + O(pairState) = O(n^3)
        ll cur = q.front();
        q.pop();
        for(auto pcode : invertedTransitions2[cur]){
            if(visited[pcode.first])    continue;
            visited[pcode.first] = 1;
            q.push(pcode.first);
            if(pcode.second)
                pairMinString[pcode.first] = "1" + pairMinString[cur];
            else
                pairMinString[pcode.first] = "0" + pairMinString[cur];
            for(ll i = 0; i < n; i++)                    //O(n)
                pairState[pcode.first][i] = pairState[cur][ transition[i][pcode.second] ];
        }
    }
    unordered_set<ll> X;
    for(ll i=0; i<n; i++)   X.insert(i);            //O(n)
    string cad = "";
    ll s1, s2, codes1s2;
    while(X.size() > 1){                            //Se realiza n veces como máximo. O(n^2)
        auto it = X.begin();
        s1 = *(it++);
        s2 = *it;
        codes1s2 = pairToCode[s1][s2];              //O(1)
        cad += pairMinString[codes1s2];             //O(1)
        unordered_set<ll> Y;
        for(auto state : X)                         //O(n)
            Y.insert(pairState[codes1s2][state]);
        X = Y;
    }
    return cad;
}

int menu1(){
    int opt = 0, optMax = 4;
    do{
        cout << "\n\n--------------------Proyecto de Teoria de la Computacion--------------------\n";
        cout << "1. Problema Min-Sinc O(2^n).\n";
        cout << "2. Problema Dec-Sinc O(n^2).\n";
        cout << "3. Problema Cad-Sinc O(n^3).\n";
        cout << "4. Salir del programa.\n";
        cout << "Ingrese una opcion: ";
        cin >> opt;
    }while(!isdigit(opt) && (opt < 1 || opt > optMax));
    return opt;
}

int menu2(){
    int opt = 0, optMax = 5;
    do{
        cout << "\n\n--------------------Eleccion de automata--------------------\n";
        cout << "1. Ingresar AFD por consola.\n";
        cout << "2. Generar AFD aleatorio.\n";
        cout << "3. Generar AFD sincronizable de Cerny.\n";
        cout << "4. Regresar al menu anterior.\n";
        cout << "5. Salir del programa.\n";
        cout << "Ingrese una opcion: ";
        cin >> opt;
    }while(!isdigit(opt) && (opt < 1 || opt > optMax));
    return opt;
}

#endif //FUNCTIONS_H