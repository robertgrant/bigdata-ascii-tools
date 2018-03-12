#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string; // this will require -std=c++11 when compiling
using std::ifstream;
using std::ofstream;
using std::stringstream;

int main(int argc, char *argv[]) {
    int nlines = 0;
    string line;
    string snlines;
    string lineblank;
    string filename = argv[1];
    ifstream rfile;
    rfile.open(filename,ifstream::in);
    if(rfile) {
	    while(!rfile.eof()) {
        getline(rfile,line);
        nlines++;
      }
      snlines = to_string(nlines);
      if(line=="") {
        lineblank = ", last line is blank.";
      }
      cout << filename << " : " << snlines << lineblank << endl;
    }
    else {
      cout << "ERROR: "+filename+" not found." << endl;
    }
    return 0;
}
