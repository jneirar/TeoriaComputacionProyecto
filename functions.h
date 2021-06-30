#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "lib.h"
//n = 23
//v = 1110100000... 64 bits
/*vector<bool> ullToVector(ull n){        //O(n)
    vector<bool> v(64);
    for(ull i = 0; i < 64; i++)
        v[i] = (n >> i) & 1;
    return v;
}
ull vectorToUll(vector<bool> v){        //O(n)
    ull n = 0;
    for(ull i = 0; i < 64; i++)
        if(v[i])
            n += 1ULL << i;
    return n;
}*/

string shortestString(vector<vector<ll>> transition, ll n){             //O(n*2^n)
    /*
    set<ll> sInit;
    for(ll i=0; i<n; i++)  sInit.insert(i);                             //O(nlg(n))
    //BFS
    map<set<ll>, string> shortString;                                   //max: 2^n
    set<set<ll>> visited;                                               //max: 2^n
    queue<set<ll>> qState;                                             
    qState.push(sInit);                                                 //O(1)
    visited.insert(sInit);                                              //O(1)
    shortString[sInit] = "";                                            //O(1)
    while(!qState.empty()){                                             //O(V + E) | O(2^n + (costo de hacer la transición))
        set<ll> sNext0, sNext1;
        for(ll state : qState.front()){                                 //O(n lgn)
            sNext0.insert(transition[state][0]);                        //O(lgn)
            sNext1.insert(transition[state][1]);                        
        }
        if(!visited.count(sNext0)){                                     //O(lg(2^n)) = O(n)
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
            return shortString[sNext0];                                 //O(lg(2^n)) = O(n)
        if(sNext1.size() == 1)
            return shortString[sNext1]; 
    }*/

    /*
    ull sInit = 0; //64 bits, por lo que puedo usarlo para 64 estados como máximo
    for(ull i=0; i<n; i++)  sInit += 1ULL << i;                         //O(n)

    //BFS
    unordered_map<ull, string> shortString;                             //max: 2^n
    unordered_set<ull> visited;                                         //max: 2^n
    queue<ull> qState;                                             
    qState.push(sInit);                                                 //O(1)
    visited.insert(sInit);                                              //O(1)
    shortString[sInit] = "";                                            //O(1)
    
    while(!qState.empty()){                                             //O(V + E) | O(2^n + (costo de hacer la transición))
        vector<bool> vCur = ullToVector(qState.front());                //O(n)
        vector<bool> sNext0(64, 0), sNext1(64, 0);                      //O(n)
        for(ull i = 0; i < 64; i++){                                    //O(n)
            if(vCur[i]){
                sNext0[transition[i][0]] = 1;
                sNext1[transition[i][1]] = 1;
            }
        }
        ull uNext0 = vectorToUll(sNext0);                               //O(n)
        ull uNext1 = vectorToUll(sNext1);                               //O(n)
        if(!visited.count(uNext0)){                                     //O(1)
            visited.insert(uNext0);                                     //O(1)
            shortString[uNext0] = shortString[qState.front()] + '0';    //O(1 + 1) = O(1)
            qState.push(uNext0);                                        //O(1)
        }
        if(!visited.count(uNext1)){                                     
            visited.insert(uNext1);                                     
            shortString[uNext1] = shortString[qState.front()] + '1';    
            qState.push(uNext1);                                        
        }
        qState.pop();                                                   //O(1)
        int sum = 0;
        for(int i = 0; i < 64; i++) sum += sNext0[i];                   //O(n)
        if(sum == 1)                                                    //O(1)
            return shortString[uNext0];                                 //O(1) = O(1)
        sum = 0;                                                        //O(1)
        for(int i = 0; i < 64; i++) sum += sNext1[i];                   //O(n)
        if(sum == 1)                                                    //O(1)
            return shortString[uNext1];                                 //O(1)
    }*/
    
    vbool sInit(n, 1); //O(n)
    
    //BFS
    unordered_map<vbool, string> shortString;                           //max: 2^n
    unordered_set<vbool> visited;                                       //max: 2^n
    queue<vbool> qState;                                             
    qState.push(sInit);                                                 //O(1)
    visited.insert(sInit);                                              //O(1)
    shortString[sInit] = "";                                            //O(1)
    
    while(!qState.empty()){                                             //O(V + E) | O(2^n + (costo de hacer la transición))
        vbool vCur = qState.front();                                    //O(n)
        vbool sNext0(n, 0), sNext1(n, 0);                               //O(n)
        for(ll i = 0; i < n; i++){                                      //O(n)
            if(vCur[i]){
                sNext0[transition[i][0]] = 1;
                sNext1[transition[i][1]] = 1;
            }
        }
        if(!visited.count(sNext0)){                                     //O(n)
            visited.insert(sNext0);                                     //O(n)
            shortString[sNext0] = shortString[qState.front()] + '0';    //O(n + 1) = O(n)
            qState.push(sNext0);                                        //O(1)
        }
        if(!visited.count(sNext1)){                                     
            visited.insert(sNext1);                                     
            shortString[sNext1] = shortString[qState.front()] + '1';    
            qState.push(sNext1);                                        
        }
        qState.pop();                                                   //O(1)
        int sum = 0;
        for(int i = 0; i < n; i++) sum += sNext0[i];                    //O(n)
        if(sum == 1)                                                    //O(1)
            return shortString[sNext0];                                 //O(n)
        sum = 0;                                                        
        for(int i = 0; i < n; i++) sum += sNext1[i];                    
        if(sum == 1)                                                    
            return shortString[sNext1];                                 
    }
    return ".";
}

vector<vector<ll>> pairCodification(ll n){                          //O(n^2)
    vector<vector<ll>> pairToCode(n);
    for(ll i = 0; i < n; i++)   pairToCode[i].resize(n);            //O(n)
    ll code = n;
    for(ll i=0; i<n; i++){                                          //O(n^2), son n(n+1)/2, n single y n(n-1)/2 pares distintos
        for(ll j=i; j<n; j++){                                      //O(n)
            if(i == j)
                pairToCode[i][i] = i;
            else{
                pairToCode[i][j] = code;
                pairToCode[j][i] = code++;
            }
        }
    }
    return pairToCode;
}

vector<vector<pair<ll, ll>>> pairInvertedTransition(ll n, vector<vector<ll>> transition, vector<vector<ll>> pairToCode){
    vector<vector<pair<ll, ll>>> invertedTransitions2(n*(n+1)/2);   
    for(ll i=0; i<n; i++){                          //O(n * n) = O(n^2)
        for(ll j=i+1; j<n; j++){                    //O(n)
            //Evito bucles
            if(pairToCode[ transition[i][0] ][ transition[j][0] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][0] ][ transition[j][0] ]].push_back(make_pair(pairToCode[i][j], 0));
            if(pairToCode[ transition[i][1] ][ transition[j][1] ] != pairToCode[i][j])
                invertedTransitions2[pairToCode[ transition[i][1] ][ transition[j][1] ]].push_back(make_pair(pairToCode[i][j], 1));
        }
    }
    return invertedTransitions2;
}


bool Dec_Sinc(ll n, vector<vector<ll>> transition){         //O(n^2)
    vector<vector<ll>> invertedTransitions(n);
    for(ll i=0; i<n; i++){                                  //O(n)
        if(i != transition[i][0])   invertedTransitions[transition[i][0]].push_back(i);
        if(i != transition[i][1])   invertedTransitions[transition[i][1]].push_back(i);
    }
    bool isIt = false;
    for(ll i=0; i<n; i++){                                  //O(n * n) = O (n^2)
        vector<bool> visited(n, 0);     
        queue<ll> q;
        visited[i] = 1;
        q.push(i);
        while(!q.empty()){                                  //V = O(n), E = O(n)
            ll cur = q.front();
            q.pop();
            for(ll e : invertedTransitions[cur]){
                if(!visited[e]){
                    visited[e] = 1;
                    q.push(e);
                }
            }
        }
        bool visited_true = true;
        for(bool e : visited)   visited_true &= e;          //O(n)
        if(visited_true)    isIt = true;
        if(isIt)  break;
    }
    if(!isIt) return false;
   
    ll n_2 = n*(n+1)/2; //total pares
    vector<vector<ll>> pairToCode = pairCodification(n);    //O(n^2)
    
    vector<vector<pair<ll, ll>>> invertedTransitions2 = pairInvertedTransition(n, transition, pairToCode);  //O(n^2)
    //pairInvertedTransition[i] = nodos que llegan al estado codificado con i con su caracter de transición
    //BFS en invertedTransitions2   //O(n^2)
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
    if(visitedStates.size() != n_2) return false;
    return true;
}

string Cad_Sinc(ll n, vector<vector<ll>> transition){           //O(n^3)
    ll n_2 = n*(n+1)/2; //total pares
    vector<vector<ll>> pairToCode = pairCodification(n);        //O(n^2)
    
    vector<vector<pair<ll, ll>>> invertedTransitions2 = pairInvertedTransition(n, transition, pairToCode);  //O(n^2)

    //BFS from level 0
    vector<vector<ll>> pairState(n_2);                          //O(n^2), guarda la transición {0, ..., n} -> minString
    for(ll i = 0; i < n_2; i++) pairState[i].resize(n);         //O(n^2)
    vector<string> pairMinString(n_2, "");                      //O(n^2), pair with string
    vector<ll> visited(n_2, 0);                                 //O(n^2)
    queue<ll> q;
    //Iniciamos con los nodos conectados a los nodos simples (0 a n-1)
    //BFS es parecido al Dec-Sinc, pero realiza un O(n) para calcular la transición de cada estado con la min-cad del par
    //O(n^3)
    for(ll single = 0; single < n; single++){                   
        for(auto pcode : invertedTransitions2[single]){         
            //pcode: par(code, cadena) -> single
            if(visited[pcode.first])   continue;
            visited[pcode.first] = 1;
            q.push(pcode.first);
            if(pcode.second)
                pairMinString[pcode.first] += "1";
            else
                pairMinString[pcode.first] += "0";
            for(ll i = 0; i < n; i++)                           //O(n)
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
                pairMinString[pcode.first] = "1" + pairMinString[cur];
            else
                pairMinString[pcode.first] = "0" + pairMinString[cur];
            for(ll i = 0; i < n; i++)                           //O(n)
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