#ifndef PET_H
#define PET_H

#include <iostream>
#include <sstream>
using namespace std;

class Pet{
private:
    string nome;
    int energyMax, hungryMax, cleanMax; 
    int energy, hungry, clean;   
    int age; // {0};
    int diamond; // {0};
    bool alive {true};


public:
    Pet(string nome = "pet", int energyMax = 0, int hungryMax = 0, int cleanMax = 0);
    
    string getNome();  //declaracao
    void setNome(string nome){
        this->nome = nome;
    }
    int getEnergyMax(){
        return energyMax;
    }
    int getHungryMax(){
        return hungryMax;
    }
    int getCleanMax(){
        return cleanMax;
    }
    int getDiamond(){
        return diamond;
    }
    int getAge(){
        return age;
    }

    string toString(){
        stringstream ss;
        ss << "N:" << nome << ", " 
           << "E:" << energy << "/" << energyMax << ", "
           << "H:" << hungry << "/" << hungryMax << ", "
           << "C:" << clean  << "/" << cleanMax  << ", "
           << "D:" << diamond << ", A:" << age;
        return ss.str();
    }

    void setEnergy(int value){
        if(value <= 0){
            this->alive = false;
            energy = 0;
            cout << "fail: pet está morto por cansaço" << endl;
        }else if(value > energyMax){
            value = energyMax;
        }else
            energy = value;
    }
    void setHungry(int value){
        if(value <= 0){
            this->alive = false;
            hungry = 0;
            cout << "fail: pet está morto por fome" << endl;
        }else if(value > hungryMax){
            hungry = hungryMax;
        }else
            hungry = value;
    }
    void setClean(int value){
        if(value <= 0){
            this->alive = false;
            clean = 0;
            cout << "fail: pet está morto por causa da sujeira" << endl;
        }else if(value > cleanMax){
            value = cleanMax;
        }else
            clean = value;
    }
    void setDiamond(int value){
        this->diamond += value;
    }
    void setAge(int value){
        this->age += value;
    }
    bool testAlive(){
        if(alive)
            return true;
        cout << "fail: pet esta morto" << endl;
        return false;
    }

    void play(){
        if(!testAlive())
            return;
        setEnergy(energy - 2);
        setHungry(hungry - 1);
        setClean(clean - 3);
        setDiamond(1);
        setAge(1);
    }
    void eat(){
        if(!testAlive())
            return;
        setEnergy(energy - 1);
        setClean(clean - 2);
        setHungry(hungry + 4);
        setAge(1);
    }
    void sleep(){
        if(!testAlive())
            return;
        if((energyMax - energy) < 5 ){
            cout << "fail: não esta com sono" << endl;
            return;
        }
        setHungry(hungry - 1);
        setAge(energyMax - energy);
        setEnergy(energyMax);
        
    }
    void cleans(){
        if(!testAlive())
            return;
        setHungry(hungry - 1);
        setClean(cleanMax);
        setEnergy(energy - 3);
        setAge(2);
    }
};

class Controller{
    public:
    Pet pet;

    void shell(string line){
        stringstream ss(line);
        //stringstream out;
        string op;
        ss >> op;
        if(op == "init"){
            int energia, fome, limp;
            string nome;
            ss >> energia >> fome >> limp;
            getline(ss, nome);
            pet = Pet(nome, energia, fome, limp);
        }else if(op == "show"){
            cout << pet.toString() << endl;
        }else if(op == "play"){
            pet.play();
        }else if(op == "eat"){
            pet.eat();
        }else if(op == "sleep"){
            pet.sleep();
        }else if(op == "clean"){
            pet.cleans();
        }
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            shell(line);
        }
    }
};

#endif

#include "pet.hpp"
#include <iostream>

Pet::Pet(std::string nome, int energyMax, int hungryMax, int cleanMax):
    nome(nome), 
    energyMax(energyMax), hungryMax(hungryMax), cleanMax(cleanMax),
    energy(energyMax), hungry(hungryMax), clean(cleanMax){
    this->age = 0;
    this->diamond = 0;
}

string Pet::getNome(){
    return nome;
}




#include <iostream>
#include "pet.hpp"
using namespace std;
int main(){
    Controller c;
    c.exec();
    
    /*while(true){
        cin >> op;
        if(op == "init"){
            int energia, fome, limp;
            string nome;
            cin >> energia >> fome >> limp;
            getline(cin, nome);
            pet = Pet(nome, energia, fome, limp);
        }else if(op == "show"){
            cout << pet.toString() << endl;
        }else if(op == "play"){
            pet.play();
        }else if(op == "eat"){
            pet.eat();
        }else if(op == "sleep"){
            pet.sleep();
        }else if(op == "clean"){
            pet.cleans();
        }
    }*/
    
    return 0;
}