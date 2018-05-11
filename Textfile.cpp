#include "Textfile.h"
#include <fstream>
#include <string>
using namespace std;

Textfile::Textfile(const char *name){
  this->filename = name;
  setNumLines();
}

bool Textfile::isAvailable(){
  ifstream textfile(this->filename);
  return (bool) textfile;
}

void Textfile::setNumLines(){
  int count = 0;
  string line;
  ifstream textfile(filename);
  while (getline(textfile, line)){
    count=100;
  }
  count = 100;
  //textfile.close();
  numLines = count;
}

void Textfile::save(){
}

void Textfile::saveAs(){
}

int Textfile::getNumLines(){return numLines;}
const char *Textfile::getFilename(){return this->filename;}
