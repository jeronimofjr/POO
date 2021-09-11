#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class Operacao{
   public:
    string descricao;
    int valor;
    int saldo;

    Operacao(string descricao = "", int valor = 0, int saldo = 0){
        this->descricao = descricao;
        this->saldo = saldo;
        this->valor = valor;
    }
};

class Conta{
public:
    int numero_Conta;
    int saldo;
    vector<Operacao> extrato;

    Conta(int numero = 0, int saldo = 0): numero_Conta(numero),saldo(saldo)
    {
         extrato.push_back(Operacao("abertura",0,0));
    }

    bool depositar(int valor){
        if(valor > 0){
            saldo += valor;
            extrato.push_back(Operacao("depositar",valor,saldo));
            return true;
        }
        return false;
    }

    bool sacar(int valor){
     if(valor > saldo){
         cout << "Saldo insuficiente\n";
         return false;
     }
        saldo -= valor;
        extrato.push_back(Operacao("sacar",-valor,saldo));
        return true;
    }

    bool tarifa(int valor){
        saldo -= valor;
        extrato.push_back(Operacao("tarifa",-valor,saldo));
        return true;
    }

    bool extornar(int indice){
        for(int i = 0; i < (int) extrato.size(); i++){
            if(indice == i){
                if(extrato[i].descricao == "tarifa"){
                    saldo += (-1)*extrato[i].valor;
                    extrato.push_back(Operacao("extornar",extrato[i].valor,saldo));
                    cout << "Sucess: indice " << indice <<" extornado\n";
                    return true;
                }else{
                    cout <<"failure: indice "<< indice << " nao e tarifa\n";
                    return false;
                }
            }
        }
        cout << "Failure: indice " << indice << " invalido\n";
        return false;
    }

    string historico(){
        stringstream ss;
        for(int i = 0; i < (int) extrato.size(); i++){
            ss << setw(2) << i << ": ";
            ss << setw(9) << extrato[i].descricao << ":";
            ss<< setw(5) << extrato[i].valor << ":";
            ss << setw(5) << extrato[i].saldo<<endl;

        }
        return ss.str();
    }

    string n_historico(int valor){
        stringstream ss;
        for(int i = extrato.size()-1; valor != 0; i--, valor--){
            ss << setw(2) << i << ": ";
            ss << setw(9) << extrato[i].descricao << ":";
            ss << setw(5) << extrato[i].valor << ":";
            ss << setw(5) << extrato[i].saldo << endl;
        }
        return ss.str();
    }

    string toString(){
        stringstream ss;
        ss << "Conta: " << numero_Conta <<" "<<"Saldo: "<< saldo <<endl;
        return ss.str();
    }
};

struct Controller{
    Conta conta;

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;

        in >> op;
        if(op == "init"){
            int numero;
            in >> numero;
            conta = Conta(numero,0);
        }else if(op == "dep"){
            int valor;
            in >> valor;
            if(conta.depositar(valor))
                out<<"Sucess\n";
            else
                out << "Valor inválido\n";
        }else if(op == "saque"){
            int valor;
            in >> valor;
            if(conta.sacar(valor))
                out << "Sucess\n";
        }else if(op == "tarifa"){
            int valor;
            in >> valor;
            conta.tarifa(valor);
            out << "Sucess\n";
        }else if(op == "extrato"){
            out << conta.historico();
        }else if(op == "extraton"){
            int valor;
            in >> valor;
            out << conta.n_historico(valor);
        }else if(op == "ext"){
            int valor;
            while(in >> valor)
             conta.extornar(valor);
        }else if(op == "show"){
            out<< conta.toString();
        }else if(op == "clear"){
            system("clear");
        }
        else if(op == "help"){
            out << "init; dep; saque; tarifa; extrato; extraton; ext; show; end; help"<<endl;
        }
        return out.str();
    }

    void exec(){
        string line;

        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            cout << shell(line) <<endl;
        }
    }
};

int main(){
    Controller controller;
    controller.exec();

    return 0;
}

