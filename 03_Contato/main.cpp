#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Fone{
    string id;
    string fone;

    Fone(string id = "", string fone = ""):
        id(id), fone(fone)
    {
    }

   static bool validate(string fone){
        string aux = "0123456789().";

        for(auto pos : fone)
            if(aux.find(pos) == string::npos)
                return false;
        return true;
    }

    string toString(){
        stringstream ss;
        ss << this->id << ":" << this->fone;
        return ss.str();
    }

};

struct Contato{
    string nome;
    vector<Fone> fones;

    Contato(string name = "vazio"):
        nome(name)
    {
    }

    bool add(Fone fone){
        for(auto telefone : fones)
            if(telefone.fone == fone.fone){
                cout << "failure: fone duplicado";
                return false;
           }
        fones.push_back(fone);
        return  true;
    }

    bool rm(int indice){
        int qtd = (int) fones.size();
        if(indice >= qtd || indice < 0){
            cout <<"Fail\n";
            return false;
        }

        fones.erase(fones.begin() + indice);
        return true;
    }

    string toString(){
        stringstream ss;

        ss << nome<<"=>"<< " ";
        for(int i = 0; i < (int) fones.size(); i++)
            ss << "[" << i << ":" << fones[i].toString() << "]";

        return ss.str();
    }
};

struct Controller{
    Contato contato;

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >>op;
        if(op == "help"){
            out << "Show; init; add; rm; end\n";
        }else if(op == "show")
            out << contato.toString()<<endl;
        else if(op == "init"){
            string nome;
            in >> nome;
            contato = Contato(nome);
            out << "Sucesso\n";
        }else if(op == "rm"){
            int ind;
            in >> ind;
            contato.rm(ind);
        }else if(op == "add"){
            string id,numero;
            in >> id >> numero;
            if(Fone::validate(numero)){
                if(contato.add(Fone(id,numero)));
                out <<"sucesso\n";
            }
            else
                cout<<"Erro\n";
        }
        else if(op == "update"){
            string nome;
            in >> nome;
            contato = Contato(nome);
            string aux;
            while(in >> aux){
                stringstream ss(aux);
                string id,fone;
                getline(ss,id, ':');
                getline(ss,fone);
                if(Fone::validate(fone))
                    contato.add(Fone(id,fone));
            }
            out << "sucesso\n";
        }
        return out.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            cout << shell(line)<<endl;
        }
    }
};

int main(){
    Controller controle;
    controle.exec();
    return 0;
}
