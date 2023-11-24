#include "bmp.h"
#include <fstream>
#include <iostream>
using namespace std;


// Definition der Funktion function1
bool BMP::read(const std::string& filename) {
    // open a file in read mode.
    auto ret = false;
   ifstream infile; 
   infile.open(filename); 
   return ret;
  
}

// Definition der Funktion function2
bool BMP::write(const std::string& filename) {
    auto ret = false;
    ifstream infile;
    cout << "Reading from the file" << endl; 
    infile >> data; 
    infile >> data; 
    cout << data << endl;
    return ret;
}
