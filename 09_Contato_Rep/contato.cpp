#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

template<typename T>
class Repositorio{
    map<string, T> rep;
    string tipo;
    public:
    Repositorio(string tipo = ""){
        this->tipo = tipo;
    }
    bool existe(string key){
        if(rep.count(key) != 0)
            return true;
        else
            throw tipo + " " + key + " não existe";
    }

    void add(string key, T t){
        if(rep.count(key) != 0)
            throw tipo + " " + key + " já existe";
        rep[key] = t;
    }

        T& get(string key){
        auto it = rep.find(key);
        if(it == rep.end())
            throw tipo + " " + key + " não existe";
        return it->second;
    }
    vector<T> getValues(){
        vector<T> values;
        for(auto& elem : rep)
            values.push_back(elem.second);
        return values;
    }
    vector<string> getKeys(){
        vector<string> keys;
        for(auto& elem : rep)
            keys.push_back(elem.first);
        return keys;
    }
    void remove(string key){
        auto it = rep.find(key);
        if(it == rep.end())
            throw tipo + " " + key + " não existe";
        rep.erase(key);
    }
};

class Fone{
    public:
    string id;
    string fone;
    int number;
    Fone(string id = "", string fone = "", int number = 0):
    id(id), fone(fone), number(number)
    {}

    static bool validate(string fone){
        string aux = "0123456789().";

        for(auto pos : fone)
            if(aux.find(pos) == string::npos)
                return false;
        return true;
    }
    friend ostream& operator<<(ostream &os, Fone fone);
};
    ostream& operator<<(ostream &os, Fone fone){
        os << "[" << fone.number << ":" <<fone.id << ":" << fone.fone << "]";
        return os;
    }
class Contato{
    public:
    string nome;
    Repositorio<Fone> fones;
    Contato(string name = "vazio"):
        nome(name)
    {
    }
    string toString(){
        stringstream ss;
        ss << nome << "=>" << " ";
        for(auto& elem : fones.getValues())
            ss << elem;
        return ss.str();
    }
    //friend ostream& operator<<(ostream &os, Contato con);
};
    
class Controller{
    public:
    Contato contato;
    int number = -1;

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "help"){
            cout << "1- init\n"
                    "2- add\n"
                    "3- show\n"
                    << endl;
        }else if(op == "init"){
            string nome;
            getline(ss, nome);
            contato = Contato(nome);
        }else if(op == "show"){
            cout << contato.toString() << endl;
        }else if(op == "add"){
                string id, fone;
                ss >> id >> fone;
                if(Fone::validate(fone)){
                    number++;
                contato.fones.add(fone, Fone(id,fone,number));
                    cout << "Sucesso" << endl;
                }else
                    cout << "Erro" << endl;
        }else if(op == "remove"){
            string fone;
            ss >> fone;
            contato.fones.remove(fone);
        }else if(op == "update"){
            string nome;
            ss >> nome;
            contato = Contato(nome);
            string aux;
            while(ss >> aux){
                stringstream ss(aux);
                string id, fone;
                getline(ss, id, ':');
                getline(ss, fone);
                if(Fone::validate(fone))
                    contato.fones.add(fone, Fone(id, fone));
            }
            cout << "Sucesso" << endl;
        }
        else
            cout << "Comando inválido" << endl;
    }
    void exec(){
        string line;
        while(true){
            getline(cin, line);
                cout << "$" << line << endl;
            if(line == "end")
                break;
            try{
                shell(line);
            }catch(string s){
                cout << s << endl;
            }
        }
    }
};
int main(){
    Controller cont;
    cont.exec();
    return 0;
}