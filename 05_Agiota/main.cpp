#include <iostream>
#include<vector>
#include<sstream>
using namespace std;

class Cliente{
public:
    string name;
    string chave;
    int saldo;
    // Construtor
    Cliente(string name = "", string chave = "", int saldo = 0):
        name(name), saldo(saldo), chave(chave)
    {
    }
    // toString
    string toString(){
        stringstream ss;
        ss << this->chave << ":" << this->name << " : " << "saldo: "<< this->saldo;
        return ss.str();
    }
};

class Transacao{
public:
    string id;
    int value;

    Transacao(string id = "", int value = 0):
        id(id),value(value)
    {

    }
};

class Agiota{
public:
    vector<Cliente> clientes;
    vector<Transacao> transacao;
    int capacidade;

    // Construtor
    Agiota(int capacidade = 0):
        capacidade(capacidade)
    {
    }

    string saldo(){
        stringstream ss;
        ss << "Saldo agiota: " << capacidade <<endl;
        return ss.str();
    }

    // toString
    string toString(){
        stringstream ss;
        for(int i = 0; i < clientes.size(); i++){
            ss << clientes[i].toString();
            ss << endl;
        }
        return ss.str();
    }

    // Adicionar cliente
    bool inserir(string nome, string chave){
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].chave == chave){
                cout << "Failure: esse caba já existe \n";
                return false;
            }
        }
        clientes.push_back(Cliente(nome,chave,0));
        return true;
    }

    // Emprestar dinheiro
    bool transf(string chave, int value){
        if((this->capacidade < (-1)*value)){
            cout << "Dinheiro em caixa insuficiente\n";
            return false;
        }
         if(value >= 0){
             cout << "Operação inválida"<<endl;
             return false;
         }
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].chave == chave){
                clientes[i].saldo += value;
                capacidade += value;
                transacao.push_back(Transacao(chave,value));
                return true;
            }
        }
        cout << "fail: cliente nao existe" << endl;
        return false;
    }

    bool pagar(string name, int value){
        for(int i = 0; i < clientes.size(); i++){
            if(name == clientes[i].chave){
                if(value > (-1) * clientes[i].saldo){
                    cout << "Valor maior que a divida\n";
                    return false;
                }else if(value <= (-1)* clientes[i].saldo){
                    clientes[i].saldo += value;
                    transacao.push_back(Transacao(name,value));
                    capacidade += value;
                    return true;
                }
            }
        }
        cout << "Cliente não encotrado\n";
        return false;
    }
    bool matar(string name){
        for(int i = 0; i < clientes.size(); i++){
            if(name == clientes[i].chave){
                clientes.erase(clientes.begin() + i);
                cout << "Morreu otário\n";
                for(int j = 0; j < transacao.size(); j++){
                    if(name == transacao[j].id)
                        transacao.erase(transacao.begin() + j);
                }
                return true;
            }
        }
        cout <<"Esse caba não tá na lista negra\n";
        return false;
    }

    void historico(){
        for(int i = 0; i < (int) transacao.size(); i++)
            cout << "id:"<< i <<"[ "<<transacao[i].id << " "<<transacao[i].value <<" ]\n";
    }
    void historico_individual(string name){
        int saldo = 0;
        for(int i = 0; i < (int) transacao.size(); i++){
            if( name == transacao[i].id){
                cout << "id:"<< i <<" [ "<<transacao[i].id <<" "<< transacao[i].value <<" ]\n";
                saldo += transacao[i].value;
            }
        }
        cout << "Saldo: "<< saldo<<endl;
    }
};

struct Controller{
    Agiota agiota;

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "init"){
            int valor;
            in >> valor;
            agiota = Agiota(valor);
        }
        else if(op == "help")
            out <<"init; show; tr; his; mostrar; mt; end; clear\n";
        else if(op == "cli"){
            string nome, chave;
            in >> chave;
            getline(in,nome,'\n');
            if(agiota.inserir(nome, chave))
                out << "Se não pagar morre\n";
        }else if(op == "show"){
            out << agiota.toString()<< endl;
            out << agiota.saldo() << endl;
        }else if(op == "tr"){
            string chave;
            int value;
            in >> chave >> value;
            agiota.transf(chave, value);
        }else if(op == "his"){
            agiota.historico();
        }
        else if(op == "mostrar"){
            string name;
            in >> name;
            agiota.historico_individual(name);
        }
        else if(op == "pg"){
            string name;
            int valor;
            in >> name >> valor;
            agiota.pagar(name, valor);
        }else if(op == "mt"){
            string chave;
            in >> chave;
            agiota.matar(chave);
        }
        else if(op == "clear")
            system("clear");

        return out.str();
    }

    void exec(){
        string line;

        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            cout << " "<< shell(line)<< endl;
        }
    }
};


int main(){
    Controller controller;
    controller.exec();
    return 0;
}
