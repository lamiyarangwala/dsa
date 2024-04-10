// Author: Lamiya Rangwala 
// Programming assignment 1: a program that takes as input an input file and
// outputs an output file. It keeps track of the foobar creatures listed 
// in the input file and outputs their strengths and names in the output. 

#include<iostream>
#include<fstream>
#include <string>
#include <vector>

/**
 * Foobar class
*/
class Foobar{
    std::string name;    
    int pos;

    protected:
        int get_pos() const {return pos;}

    public: 
    Foobar(std::string n) : pos(0), name(n) {}

        virtual int get_strength() {
            return get_pos(); 
        }

        std::string get_name() const {
            return name;
            }
        
        void set_pos(int p) {pos = p;}
};

/**
 * Foo class. Derived from parent Foobar. 
 * Overrides get_strength(), determined by multiplying position in line by 3
*/
class Foo : public Foobar {

    public:
        Foo(std::string n) : Foobar(n) {}

        int get_strength() {
            return get_pos() * 3;
        }
};

/**
 * Bar class. Derived from parent Foobar.
 * Overrides get_strength(), determined by adding 15 to position in line
*/
class Bar : public Foobar {
    
    public:
    Bar(std::string n) : Foobar(n) {}

    int get_strength() {
        return get_pos() + 15;
    }
};


/**
 * Reads file and creates a vector of pointers to Foobars
*/
std::vector<Foobar*> readFile(std::string& inFile){
    std::ifstream inputFile(inFile.c_str());
    std::vector<Foobar*> foobars;

    std::string type, name;

    while (inputFile >> type >> name){
        if (type == "foo"){
            foobars.push_back(new Foo(name));
            }

        else if (type == "bar"){
            foobars.push_back(new Bar(name));

        }
        else{
            foobars.push_back(new Foobar(name));

        }
        
    };
    return foobars;
    
};

/**
 * Updates position of Foobars in a vector depending on the index.
*/
void updatePosition(std::vector<Foobar*> *vector){

    std::vector<Foobar*> foobars = *vector;
    std::vector<Foobar*>::iterator itr = foobars.begin();
    int i = foobars.size();
    for (itr; itr<foobars.end();itr++){
        (*itr)->set_pos(i);
        i--;
        }
}

/**
 * Writes the name and strength of each Foobar in a vector to output file. 
*/
void writeOutput(std::vector<Foobar*> *vector, std::string outFile){
    
    std::vector<Foobar*> foobars = *vector;
    std::ofstream outputFile(outFile.c_str());
    
    std::vector<Foobar*>::iterator itr = foobars.begin();

    for (itr; itr<foobars.end();itr++){
        outputFile << (*itr)->get_name() << " " << (*itr)->get_strength() << "\n";
    }

}
/**
 * Main function. Foobars vector is passed by reference.
*/
int main(){
    std::string inn;
    std::string outt;

    std::cout << "Enter the name of the input file: ";
    std::cin >> inn;

    std::cout << "Enter the name of the output file: ";
    std::cin >> outt;

    std::vector<Foobar*> foobars = readFile(inn);


    std::vector<Foobar*>::iterator itr = foobars.begin();

    updatePosition(&foobars);
    writeOutput(&foobars, outt);

}
