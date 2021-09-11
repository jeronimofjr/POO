#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

template<typename T>
class Repositorio{
    map<string, T> rep;
public:

    string show(string k){         
        if(!existe(k)){
            throw "fail: funcionario " + k + " não existe";
        }
     return rep.find(k)->second->toString();
    }

    bool existe(string k){
        if(rep.count(k) != 0)
            return true;
        return false;
    }
    void add(string k, T t){
        if(existe(k))
            throw k + " já existe";
        rep[k] = t;
    }
    T& get(string k){
        auto it = rep.find(k);
        if(it == rep.end())
            throw k + " não existe";
        return it->second;
    }
    
    void remove(string k){
        auto it = rep.find(k);
        if(it == rep.end())
            throw k + " não existe";
        rep.erase(k);
    }
};
// Classe abstrata
class Funcionario{
protected:
    string nome;
   int max_diarias;
   int qtd_diarias;
   double bonus;
   string tipo;
   public:
    Funcionario(string nome = "", int max_diarias = 0, double bonus = 0.00, string tipo = ""){
        this->tipo = tipo;
        this->bonus = bonus;
        this->nome = nome;
        this->max_diarias = max_diarias;
    }

   // virtual void setBonus(double valor) = 0;
    virtual int calculo_salario() = 0;
    virtual string getNome() = 0;
    virtual string toString() = 0;   
};

class Professor: public Funcionario{
    string nome;
    string classe;
    int diarias{0};
public:
    Professor(string nome = "", string classe = ""): 
    Funcionario(nome){
        this->classe = classe;
        max_diarias = 2;
        this->nome = nome;
    }
    int calculo_salario(){
        int salario;
        if(classe == "A")
            salario = 3000;
        else if(classe == "B")
            salario = 5000;
        else if(classe == "C")
            salario = 7000;
        else if(classe == "D")
            salario = 9000;
        else if(classe == "E")
            salario = 11000;
        return salario + diarias*100;
    }

    string getNome(){
        return this->nome;
    }
    string toString(){
        return "professor " + this->getNome() + "\n" +
         "classe " + classe + "\n" + 
        "salario " + to_string(calculo_salario());
    }
};

class STA: public Funcionario{
    int nivel;
    int diarias{0};
public:
    STA(string nome = "", int nivel = 0):
        Funcionario(nome){
            this->nivel = nivel;
    }

    int calculo_salario(){
        return 3000 + 300*nivel;
    }
    
    string getNome(){
        return this->nome;
    }
    string toString(){
        return "servidor " + this->getNome() + "\n" +
        " nível" + to_string(nivel) + "\n" +
        "salario " + to_string(calculo_salario());
    }
};

class Terceirizado: public Funcionario{
    int hrs;
    bool insalubre;
    public:
    Terceirizado(string nome = "", int hrs = 0, bool salu = false):
        Funcionario(nome){
            this->hrs = hrs;
            this->insalubre = salu;
    }

    string getNome(){
        return this->nome;
    }
    int calculo_salario(){
        if(insalubre == true)
            return (hrs*400) + 500;
        return hrs*400;
    }
    string toString(){
        return "Terceirizado " + this->getNome() + "\n" +
        " horas de trabalho " + to_string(hrs) + "\n" +
        "salario $" + to_string(calculo_salario());
    }
};

class Controller{
    Repositorio<Funcionario*> funcionarios;
    public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "help")
            cout << "1. Help\n2. AddProf\n3. show\n"
                << "4. addSta\n5. addTer\n6. rm\n"; 
        else if(op == "addProf"){
            string chave, cl;
            ss >> chave >> cl;
            funcionarios.add(chave, new Professor(chave, cl));
        }else if(op == "show"){
            string nome;
            ss >> nome;
            cout << funcionarios.show(nome) << endl;
        }else if(op == "addSta"){
            string chave;
            int nivel;
            ss >> chave >> nivel;
            funcionarios.add(chave, new STA(chave, nivel));
        }else if(op == "addTer"){
            string chave;
            int horas;
            ss >> chave >> horas;
            bool aux;
            if(horas > 5)
                aux = true;
            else
                aux = false;
            funcionarios.add(chave, new Terceirizado(chave, horas, aux));
        }else if(op == "rm"){
            string nome;
            ss >> nome;
            funcionarios.remove(nome);
        }else
            cout << "Comando inválido" << endl;
    }

    void exec(){
        string line;
        while(true){
            cout << "Help: ";
            getline(cin, line);
            if(line == "")
                continue;
            if(line == "end")
                break;
            try{
                shell(line);
            }catch(string ok){
                cout << ok << endl;
            }catch(char const *e){
                cout << e << endl;
            }
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}
