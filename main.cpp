#include<iostream>
#include<cstring>
#include <memory>
using namespace std;


class Animal
{

    public:
        Animal(const string &type, const string &name, const int &age);
        // Default constructor for item 13
        Animal(void);
        void printAnimal()
	    {
            cout<<"Type:"<<type<<" name:"<<name<<" age:"<<age;
        }
        Animal& operator=(Animal& other)       
        {
            // Verificam daca referinta obiectul other este diferita de cea a obiectului this -> item 11
            if(this != &other)
            {
                this->type= other.type;
                this->name = other.name;
                this->age = other.age;
            }
            else
            {
                cout<<"This and other have the same reference";
            }

            // Facem return *this pentru a ne asigura ca se pastrea referinta obiectului apelat -> item 10
            return *this;          
        }
        Animal* createAnimal();
        void setType(string type)
         {
            this->type = type;
         }
        void setName(string name)
        {
            this->name = name;
        }
        void setAge(int age)
        {
            this->age = age;
        }
        // Getter
        string getType() 
        {
            return this->type;
        }
        string getName() 
        {
            return this->name;
        }
        int getAge() 
        {
            return this->age;
        }



    private:
        string type;
        string name;
        int age;
};
//Am creeat constructorul cu member initialization list in interiorul acesteia->itemul 4
Animal::Animal(const string &type, const string &name, const int &age)
    :type(type),
    name(name),
    age(age)
{}
Animal::Animal()
    :type(),
    name(),
    age()
{}
//Am creeat un nou obiect Animal fara parametrii pentru item 13
Animal* createAnimal(){                   
    return (new Animal);
}
//Am creeat o functie in care facem return prematur->item 13
int function()
{
    Animal *a = createAnimal();
    a->setAge(3);
    if (a->getAge() != 0) return -1;
    cout<<"got to delete\n";
    delete a;
    return 0;
}
/*In clasa WildAnimals nu avem declarati de noi constructor, destructor, copy constructor si copy assignment operator deoarece ne asteptam ca C++ sa declare un copy constructor,copy
assignment operator, destructor si default contructor ->itemul 5*/
class WildAnimal{
    public:
        void printAnimal()
	{
            cout<<"Wild Animal";
    }
};
// Am creat clasa Uncopyable unde am pus pe privat copy constructorul si copy assigment operatorul
class Uncopyable{
    protected:
        Uncopyable(){}
        ~Uncopyable(){}

    private:
        Uncopyable(const Uncopyable&);  //copy constructor
        Uncopyable &operator = (const Uncopyable&); //copy assignment operator

};
//In clasa Pets dorim sa nu avem declarat un copy constructor sau un copy assignment operator
//Pt ca Pets mosteneste Uncopyable, compilatorul nu creeaza opy constructorul si copy assigment operatorul pentru ca nu are acces la ele->item 6
class Pet: Uncopyable{
    public:
        Pet(string name);
        void printAnimals()
        {
            cout<<pet_name<<endl;
        }
    private:
        string pet_name;

};
Pet::Pet(string name)
{
   pet_name=name;
}

class Dog: public Animal{
    public:
    Dog(const string &type, const string &name, const int &age, const string &breed); 
    Dog& operator=(Dog& rhs);
    void printDog()
	{
            Animal::printAnimal();
            cout<<" breed:"<<breed;
    }

    private:
    string breed;
};
// M-am folosit de constructorul clasei de baza pentru a initializa atributele mostenite din acea clasa -> item 12
Dog::Dog(const string &type, const string &name, const int &age, const string &breed)
:Animal(type,name,age),       
breed(breed)
{}

// M-am folosit de copy assignmentul de la clasa de baza pentru a fi sigur ca o sa copiem toate partile obiectului -> item 12
Dog&Dog::operator=(Dog& rhs){
    Animal::operator=(rhs);               
    breed = rhs.breed;
    return *this;
}

// Am creeat o clasa ZooGarden care verifica daca este inchisa sau deschisa pentru item 14
class ZooGarden{
    private:
        string name;
        bool locked = false;
    public:

    ZooGarden(string name){
        this->name = name;
    }

    ZooGarden(const ZooGarden &z){
        this->name = z.name;
        this->locked = z.locked;
    }

    ~ZooGarden(){
        std::cout<<"Zoo Garden deleted"<<std::endl;
    }

    string getName(){
        return this->name;
    }

    bool getLocked(){
        return this->locked;
    }

    void setLocked(bool locked){
        this->locked = locked;
    }

    void isZooGardenLocked(){
        if(this->locked == false) 
            std::cout<<"The Zoo Garden "<< this->name <<" is not locked"<<"\n";
        else
            std::cout<<"The Zoo Garden "<<this->name<<"is locked"<<"\n";
    }

};
// Functiile pentru inchis si deschis -> item 14
void lock(ZooGarden &z){         
    z.setLocked(true);
}

void unlock(ZooGarden &z){
    z.setLocked(false);
}

// Am creeat o clasa GatekeeperZoo pentru a deschide si inchide Zoo-ul ->item 14
class GatekeeperZoo{            
    private:
        ZooGarden &zoo;
    public:
    GatekeeperZoo(ZooGarden &z):
    zoo(z){
        lock(zoo);
    }
    ~GatekeeperZoo(){
        unlock(zoo);
    }
};



int main()
{
    //Item 4: sa initializam toate obiectele
    Animal animal1("Mammalian","Wolf",13);
    Pet pet1("Dog");
    animal1.printAnimal();

    //Item 5: In clasa WildAnimal nu are constructor, destructor, copy constructor si copy assignment operator dar sunt creeate de compilator
    WildAnimal wildanimal1; //Se apeleaza default constructorul
    WildAnimal wildanimal2(wildanimal1);  //Se apeleaza copy constructor
    wildanimal2 = wildanimal1; // Se apeleaza copy assignment
    wildanimal1.~WildAnimal(); //Se apeleaza destructorul
    //Item 6: Vrem sa nu lasam compilatorul sa creeze copy constructor si copy assignment operator
    // Pet pet2(pet1);
    // Pet pet2 = pet1;
    //Prin cele 2 linii de sus am vrut sa verific daca pet-ul nu poate accesa copy constructor si copy assignment operator

    Animal animal2("Mammalian","Lion",5);
    Animal animal3("Mammalian","Bear",2);
    Animal animal4("Mammalian","Tiger",6);
    //Item 10/11: Datorita "return *this" cele 3 obiecte o sa aibe aceeasi valoare dar fiecare o sa isi pastreze referinta diferita
    animal2=animal3=animal4;

    Dog dog1("Mammalian","Dog",3,"Pug");
    dog1.printDog();

    //Item 13: Creem pointeri inteligenti care sterg obiectele singuri.
    auto_ptr<Animal> animal5(createAnimal());
    animal5->setAge(2);
    auto_ptr<Animal> animal6(animal5);
    std::cout<<"\n"<<animal6->getAge()<<"\n"; 

    shared_ptr<Animal> animal7(createAnimal());
    animal7->setAge(3);
    shared_ptr<Animal> animal8;
    animal8 = animal7;
    std::cout<<"\n"<<animal7->getAge()<<"\n";     
    std::cout<<"\n"<<animal8->getAge()<<"\n";  

     //Daca apelam function nu va ajunge la delete deoarece face return prematur                                                    
    //function();

     //Item 14: simulare de lock si unlocked. La inceput este unlocked apoi este locked. 
    ZooGarden zoo("ValisZoo");
    zoo.isZooGardenLocked();                  
    std::cout<<"\n";
    GatekeeperZoo owner(zoo);      
    zoo.isZooGardenLocked();
    std::cout<<"\n";




    return 0;
}