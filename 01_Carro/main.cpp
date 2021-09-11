#include <iostream>

using namespace std;

struct Carro{
        float gas;
        float gas_max;
        int pass;
        int pass_max;
        float km;

        bool embarcar(){
            if(pass < pass_max){
                pass += 1;
                cout<<" Done\n";
                return true;
            }
            cout<<"Fail: Limite de pessoas atingido\n";
            return false;
        }

        bool desembarcar(){
            if(pass > 0){
                pass -= 1;
                cout<<" Done\n";
                return true;
            }
            cout<<"Fail: não ha ninguém no carro\n";
            return false;
        }

        void abastecer(float abs){
            gas += abs;
            if(gas > gas_max)
                gas = gas_max;
            cout<<" Done\n";
        }

        bool dirigir(float distancia){
            if(pass > 0){
                if(gas >= distancia/10){
                    gas -= distancia/10;
                    km += distancia;
                    cout<<" Done\n";
                    return true;
                }
                else
                    cout<<"Fail: gasolina insuficiente\n";
                return false;
            }else
                cout<<"Fail: nao ha ninguem no carro\n";
            return false;
        }
        void show(){
           cout<<" pass: "<<pass<<" gas: "<<gas<<" km: "<<km<<endl;
        }

};

int main(){
    Carro car;
    car = {0,10,0,2,0};
    string op;

    while (true) {
        cin>>op;
        if(op == "help")
            cout<<"in; out; fuel; show; drive; clear; fim.\n";
        else if(op == "in"){;
                  car.embarcar();
    }
        else if(op == "out"){
            car.desembarcar();
        }
        else if(op == "fuel"){
            float fuel;
            cin>>fuel;
            car.abastecer(fuel);
        }
        else if(op == "drive"){
            float km;
            cin >> km;
            car.dirigir(km);
        }
        else if(op == "show"){
            car.show();
        }
        else if(op == "clear"){
            system("clear");
        }
        else if(op == "fim"){
            break;
        }
    }

    return 0;
}

