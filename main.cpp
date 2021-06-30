#include "lib.h"
#include "functions.h"

bool flag = 0;
unsigned t0, t1;
double tiempo;

void solve();
void generateAFD(ll opt2, ll &n, ll &qi, ll &nqf, unordered_set<ll> &qf, vector<vector<ll>> &transition);
double timeCalculate(double t0, double t1);

int main(){
    srand (time(NULL));
    do{
        flag = 0;
        solve();
    }while(flag);
    cout << "\n\nPrograma finalizado exitosamente\n\n";
    return 0;
}

void solve(){
    int opt1 = menu1();
    if(opt1 == 4)   
        return;
    int opt2 = menu2();
    if(opt2 == 4){
        flag = 1;   
        return;
    }
    if(opt2 == 5)   
        return;
    
    ll n, qi, nqf; 
    unordered_set<ll> qf;
    vector<vector<ll>> transition;

    switch (opt1){
        case 1:{    //Algoritmo MinSinc
            while(1){
                generateAFD(opt2, n, qi, nqf, qf, transition);
                //Automata leido
                t0 = clock();
                string minCad = shortestString(transition, n);
                t1 = clock();
                if(minCad == ".")   cout << "\nNO\n";                     
                else    cout << "\nMin-Sinc: " << minCad << "\nTamanio: " << minCad.length() << "\n";
                tiempo = timeCalculate(t0, t1);
                cout << "\nExecution Time: " << tiempo << "\n";
                
                string flag2;
                cout << "\n\nProbar Min-Sinc en otro AFD (S/N): ";
                cin >> flag2;
                if(flag2 == "N" || flag2 == "n")
                    break;
            }
            break;
        }
        case 2:{    //Algoritmo Dec-Sinc
            while(1){
                generateAFD(opt2, n, qi, nqf, qf, transition);
                //Automata leído
                t0 = clock();
                if(Dec_Sinc(n, transition))   cout << "SI\n";
                else cout << "NO\n";
                t1 = clock();
                tiempo = timeCalculate(t0, t1);
                cout << "\nExecution Time: " << tiempo << "\n";

                string flag2;
                cout << "\n\nProbar Dec-Sinc en otro AFD (S/N): ";
                cin >> flag2;
                if(flag2 == "N" || flag2 == "n")
                    break;
            }
            break;
        }   
        case 3:{    //Algoritmo Cad-Sinc
            while(1){
                generateAFD(opt2, n, qi, nqf, qf, transition);
                //Automata leído
                if(!Dec_Sinc(n, transition))   
                    cout << "\nNo es sincronizable\n";
                else{
                    t0 = clock();
                    string cadSinc = Cad_Sinc(n, transition);
                    t1 = clock();
                    cout << "\nCadena: " << cadSinc << "\n";
                    cout << "Tamanio: " << cadSinc.length() << "\n";
                    tiempo = timeCalculate(t0, t1);
                    cout << "\nExecution Time: " << tiempo << "\n";
                }
    
                string flag2;
                cout << "\n\nProbar Dec-Sinc en otro AFD (S/N): ";
                cin >> flag2;
                if(flag2 == "N" || flag2 == "n")
                    break;
            }
            break;
        }  
    }
    string flag1;
    cout << "\n\nProbar otro problema (S/N): ";
    cin >> flag1;
    if(flag1 != "N" && flag1 != "n")
        flag = 1;
}

void generateAFD(ll opt2, ll &n, ll &qi, ll &nqf, unordered_set<ll> &qf, vector<vector<ll>> &transition){
    switch (opt2){
        case 1:{    //Lee de consola
            cout << "\nInserta el automata en el formato indicado.\n";
            cin >> n >> qi >> nqf;
            ll tmp1, tmp2;
            for(ll i=0; i<nqf; i++){
                cin >> tmp1;
                qf.insert(tmp1);
            }
            transition.resize(n);
            for(ll i=0; i<n; i++)   transition[i].resize(2);
            for(ll i=0; i<2*n; i++)
                cin >> tmp1 >> tmp2 >> transition[tmp1][tmp2];
            break;
        }
        case 2:{//Aleatorio
            qi = 0;
            nqf = 1;
            qf.insert(1);
            do{
                cout << "\nInserta el tamanio del automata: ";
                cin >> n;
            }while(n < 2);
            transition.resize(n);
            for(ll i=0; i<n; i++)   transition[i].resize(2);
            for(ll i=0; i<n; i++){
                transition[i][0] = rand() % n;
                transition[i][1] = rand() % n;
            }                   
            cout << "\nAutomata generado: \n";
            cout << n << " 0 1 1\n";
            for(ll i=0; i<n; i++){
                cout << i << " 0 " << transition[i][0] << "\n";
                cout << i << " 1 " << transition[i][1] << "\n";
            }
            break;
        }
        case 3:{//Aleatorio Sinc Cerny
            qi = 0;
            nqf = 1;
            qf.insert(1);
            do{
                cout << "\nInserta el tamanio del automata de Cerny: ";
                cin >> n;
            }while(n < 2);
            transition.resize(n);
            for(ll i=0; i<n; i++)   transition[i].resize(2);
            transition[0][0] = 1;
            transition[0][1] = 1;
            for(ll i=1; i<n; i++){
                transition[i][0] = i;
                transition[i][1] = (i+1)%n;
            }                   
            cout << "\n\tAutomata de Cerny generado: \n";
            cout << n << " 0 1 1\n";
            for(ll i=0; i<n; i++){
                cout << i << " 0 " << transition[i][0] << "\n";
                cout << i << " 1 " << transition[i][1] << "\n";
            }
            break;
        }
    }
}

double timeCalculate(double t0, double t1){
    return (double(t1-t0)/(CLOCKS_PER_SEC/1));
}