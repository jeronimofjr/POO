#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Passageiro{
    string id;
    string idade;

    Passageiro(string id = "", string idade = ""){
        this->id = id;
        this->idade = idade;
    }
};

struct Topic{
    vector<Passageiro*> cadeiras;
    int pref;

    Topic(int qtd = 0, int pf = 0): cadeiras(qtd,nullptr){
        pref = pf;
    }

    ~Topic(){
        for(Passageiro *passageiro: cadeiras)
            delete(passageiro);
    }


    bool meajuda(string nome){
        for(Passageiro *passageiro: cadeiras){
            if(passageiro == nullptr)
                continue;
            else if((passageiro->id == nome) && (passageiro != nullptr))
                return false;
        }
        return true;
    }


    bool embarcar(string nome, string idade){
        int qtd = (int) cadeiras.size();
        int disp = 0;

        if(!meajuda(nome)){
            cout << nome<<" Ja esta na topic\n";
            return false;
        }

        int aux = std::stoi(idade);

        if(aux > 60){
            for(int i = 0; i < pref; i++){
                if(cadeiras[i] == nullptr){
                    cadeiras[i] = new Passageiro(nome,idade);
                    cout<<"Done\n";
                    return true;
                }
            }
        }

        for(int i = 0 ;  i < qtd; i++){
            if(i+1 > pref && cadeiras[i] == nullptr){
                cadeiras[i] = new Passageiro(nome,idade);
                cout<<"Done\n";
                disp = 1;
                return true;
            }
        }
        if(disp == 0){
            for(int i = 0; i < pref; i++){
                if(cadeiras[i] == nullptr){
                    cadeiras[i] = new Passageiro(nome,idade);
                    cout<<"Done\n";
                    return true;
                }
            }
        }
        cout <<"Lotacao maxima \n";
        return true;
    }

    bool desembarcar(string nome){
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(cadeiras[i] == nullptr)
                continue;
            else if(nome == cadeiras[i]->id  && (cadeiras[i] != nullptr)){
                delete(cadeiras[i]);
                cadeiras[i] = nullptr;
                cout<<"Done\n";
                return true;
            }
        }
        cout<<"fail: "<<nome<<" nao esta no trem\n";
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(int j = 0; j < (int) cadeiras.size(); j++){

            if(cadeiras[j] == nullptr){
                if(j < pref)
                    ss << "@ ";
                else
                    ss << "= ";
            }
            else if(j < pref)
                ss <<"@"<<cadeiras[j]->id<<":"<<cadeiras[j]->idade<< " ";
            else if(j >= pref)
                ss <<"#"<<cadeiras[j]->id<<":"<<cadeiras[j]->idade << " ";

        }
        ss << "]";
        return ss.str();
    }


};

int main(){
    Topic vagao;
    string op;

    while(true){
        cin >> op;
        if(op == "end")
            break;
        else if(op == "show"){
            cout << vagao.toString() << endl;
        }else if(op == "new"){
            int qtd;
            int prefe;
            cin >> qtd >> prefe;
            vagao = Topic(qtd,prefe);
        }else if(op == "in"){
            string nome, idade;
            cin >> nome >> idade;
            vagao.embarcar(nome, idade);
        }else if(op == "out"){
            string nome;
            cin >> nome;
            vagao.desembarcar(nome);
        }
    }
}
