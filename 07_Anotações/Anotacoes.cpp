#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdio>

using namespace std;

class Nota{
    string title;
    string text;
public:
    Nota(string title = "", string text = ""){
        this->title = title;
        this->text = text;
    }
    string getTitle(){
        return this->title;
    }
    string getText(){
        return this->text;
    }
    void setTitulo(string title){
        this->title = title;
    }
    void setText(string text){
        this->text = text;
    }
    string toString(){
    stringstream ss;
        ss << "[ TITULO: " << title << " ]" << "\n" << text;
            return ss.str();
    }
};

class Usuario{
    string username;
    string password;
    vector<Nota> notas;
public:
    Usuario(string username = "", string password = ""){
        this->username = username;
        this->password = password;
    }

    void addNote(Nota note){
        for(auto &elem : notas)
            if(elem.getTitle() == note.getTitle())
                throw "Fail: título já existe\n";
        notas.push_back(note);
    }

    bool rmNote(string titulo){
        for(auto it = notas.begin(); it != notas.end(); it++){
            if(it->getTitle() == titulo){
                notas.erase(it);
                return true;
            }
        }
        return false;
    }
    string getUsername(){
        return username;
    }

    bool validar(string pass){
        if(pass != password)
            throw "Password inválida\n";
        return true;
    }
    void changePass(string oldpass, string newpass){
        if(this->password == oldpass)
            this->password = newpass;
        else
            throw "Fail: senha errada\n";
    }


   string toString(){
       stringstream ss;
       ss << username << endl;
       for(auto elem : notas){
           ss << elem.toString() << "\n" << endl;
       }
       return ss.str();
   }

};

class Sistema{
    vector<Usuario> usuarios;
    Usuario user;
public:
    Sistema(){}


    void addUser(string name, string password){
        for(auto &elem : usuarios){
            if(elem.getUsername() == name)
                throw "Fail: usuário já existe\n";
        }
        usuarios.push_back(Usuario(name,password));
    }

    Usuario& getUser(string name){
        for(auto& user : usuarios){
            if(user.getUsername() == name)
                return user;
        }
        throw "Usuário não existe\n";
    }

    string toString(){
        stringstream ss;
        for(auto &elem : usuarios)
            ss << elem.getUsername() << endl;
        return ss.str();
    }
};

class GerLogin{
    Usuario * current;
    Sistema * sistema;
public:
    GerLogin(Sistema * sistema){
        this->sistema = sistema;
    }

    Usuario& getCurrent(){
        if(current == nullptr)
            throw "Fail: ninguém logado\n";
        return *current;
    }

    Usuario& setCurrent(string oldpass, string newpass){
        if(current == nullptr)
            throw "Ninguén logado\n";
        current->changePass(oldpass, newpass);
    }
    void login(string name, string pass){
        if(current != nullptr)
            throw "Fail: alguém ja está logado\n";
        Usuario& user = sistema->getUser(name);
        if(!user.validar(pass))
            throw "Senha incorreta\n";
        cout << "Usuário " << name << " logado\n";
        current = &user;
    }

    bool logout(){
        if(current == nullptr)
            throw "Fail: ninguém está logado\n";
        current = nullptr;
        return true;
    }
};

class Controller{
    Sistema sistema;
    Usuario * current;
    GerLogin gerlog;
public:
    Controller(): gerlog(&sistema){
        current = nullptr;
    }

    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;

        if(op == "addUser"){
            string name, pass;
            in >> name >> pass;
            sistema.addUser(name, pass);
        }else if(op == "show"){
            cout << gerlog.getCurrent().toString() << endl;
        }else if(op == "showUsers"){
            cout<< "\nUsuários cadastrados no sistema" << endl;
            cout << sistema.toString() << endl;
        }
        else if(op == "login"){
            string name, pass;
            in >> name >> pass;
            gerlog.login(name, pass);
        }else if(op == "logout"){
          // auto a = gerlog.getCurrent().getUsername();
           if(gerlog.logout())
               cout << "Usuário " << gerlog.getCurrent().getUsername() << " deslogado" << endl;
        }else if(op == "changePass"){
            string old, newpass;
            in >> old >> newpass;
            gerlog.setCurrent(old, newpass);
            cout << "Senha alterada" << endl;
        }else if(op == "addNota"){
            string texto, titulo;
            in >> titulo;
            getline(in, texto);
            gerlog.getCurrent().addNote(Nota(titulo, texto));
            cout << "Nota inserida" << endl;
        }else if(op == "rmNota"){
            string titulo;
            in >> titulo;
            gerlog.getCurrent().rmNote(titulo);
            cout << titulo << " apagada" << endl;
        }
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            try{
                shell(line);
            }catch(const char * e){
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