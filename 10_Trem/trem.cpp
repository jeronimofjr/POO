#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

class Emb{ 
public:
    virtual string getId() = 0;
    virtual string toString() = 0;
    virtual ~Emb(){};
};

class Pass: public Emb {
    string id;
public:
    Pass(string id = ""):
        id(id){}
    virtual ~Pass(){
    }
    virtual string getId(){
        return id;
    }
    virtual string toString(){
        return id;
    }
};

class Vagao{ //contratos
public:
    virtual bool embarcar(Emb * emb) = 0;
    virtual ~Vagao(){};
    virtual bool desembarcar(string idPass) = 0;
    virtual string toString() = 0;
};

class VagaoPessoas : public Vagao {
    vector<Pass*> passageiros;
public:
    VagaoPessoas(int capacidade):
        passageiros(capacidade, nullptr)
    {}
    ~VagaoPessoas(){
        for(size_t i = 0; i < passageiros.size(); i++){
            if(passageiros[i] != nullptr)
                delete passageiros[i];
        }
    }

    virtual bool embarcar(Emb * emb){         
    for(size_t i = 0; i < passageiros.size(); i++){
        if((passageiros[i] != nullptr) && (passageiros[i]->getId() == emb->getId())){
            cout << "Passageiro já existe" << endl;
            return false;
        }
    }
        if(Pass * pass = dynamic_cast<Pass*>(emb)){
            for(size_t i = 0; i < passageiros.size(); i++){
                if(passageiros[i] == nullptr){
                    passageiros[i] = pass;
                    return true;
                }
            }
        }
        cout << "Carga máxima de passageiros" << endl;
        return false;
    }
    virtual bool desembarcar(string idPass){
         for(size_t i = 0; i < passageiros.size(); i++){
            if( (passageiros[i] != nullptr) && (passageiros[i]->getId() == idPass)){
                passageiros[i] = nullptr;
                return true;
            }  
         }
         return false;
    }
    virtual string toString(){
        stringstream ss;
        ss << "[ ";
        for(auto* pass : passageiros){
            if(pass == nullptr)
                ss << "- ";
            else
                ss << pass->toString() << " ";
        }
        ss << "]";
        return ss.str();
    }
};

class Movimento{
public:
    string identificacao;
    Movimento(string id = ""){
        this->identificacao = id;
    }
    string toString(){
        return identificacao;
    }
};

class Cadastro{
    string id;
public:
    Cadastro(string id = ""){
        this->id = id;
    }
    string toString(){
        return id;
    }
};

class Trem{
    vector<Vagao*> vagoes;
    vector<Movimento> movimentos;
    map<string, Cadastro> cadastros;
    int forca;
public:
    Trem(int forca = 0){
        this->forca = forca;
    }
    ~Trem(){
        for(auto * vagao : vagoes)
            delete vagao;
    }
    bool addVagao(Vagao * vagao){
        if((int) vagoes.size() < forca){
            vagoes.push_back(vagao);
            return true;
        }
        return false;
    }

    bool embarcar(Emb * emb){
        for(auto* vagao : vagoes){
            auto elem = cadastros.find(emb->getId());
            if(elem != cadastros.end())
                cout << "";
            else
                cadastros[emb->getId()] = (emb->getId());
            if(vagao->embarcar(emb)){
                movimentos.push_back(emb->getId() + " in");
                return true;
            }
        }
        return false;
    }
    bool desembarcar(string id){
        for(auto* vagao : vagoes){
            if(vagao->desembarcar(id))
            movimentos.push_back(id + " out");
                return true;
        }
        return false;
    }
    string toString(){
        stringstream ss;
        ss << "Trem: ";
        for(auto * vagao : vagoes)
            ss << vagao->toString() << " ";
        return ss.str();
    }

    string Historico(){
        stringstream ss;
        ss << "\nHISTÓRICO\n\n";
        for(auto elem : movimentos)
            ss << elem.toString() << " " << endl;
        return ss.str();
    }
    string Cadas(){
        stringstream ss;
        ss << "\nCADASTRADOS\n\n";
        for(auto elem : cadastros)
            ss << elem.first << " " << endl;
        return ss.str();
    }
};

template<class T>
T read(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

class Controller{
    Trem trem;
public:
    Controller(){
    }

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "init"){ //_forca
            trem = Trem(read<int>(ss));
        }else if(op == "help"){
            cout << "1. init \n"
                << "2. addvp \n"
                << "3. embp \n"
                << "4. show \n"
                << "5. desp \n"
                << "6. his \n"
                << "7. cad \n"
                << "8. help "
                << endl;
        }
        else if(op == "addvp"){
            Vagao * vagao = new VagaoPessoas(read<int>(ss));
            if(!trem.addVagao(vagao))
                delete vagao;
        }else if(op == "embp"){//nome
            Pass * pass = new Pass(read<string>(ss));
            if(!trem.embarcar(pass))
                delete pass;
        }else if(op == "show"){
            cout << trem.toString() << endl;
        }else if(op == "desp"){
            if(trem.desembarcar(read<string>(ss)))
                cout << "pegou o beco" << endl;
            else
                cout << "fail: Esse passageiro não está no trem" << endl;
        }else if(op == "his"){
            cout << trem.Historico() << endl;
        }else if(op == "cad"){
            cout << trem.Cadas() << endl;
        }
        else
            cout << "fail: comando invalido" << endl;
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            shell(line);
        }
    }
};

int main(){
    Controller cont;
    cont.exec();
}