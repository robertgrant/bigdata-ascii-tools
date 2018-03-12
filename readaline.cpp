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

// USAGE:
// readaline myfile.csv 1000 [this will print the 1000th line]
// readaline myfile.csv 1000 2 [print the 1000th and 1001st lines]
// readaline myfile.csv 1000 2 b [as above but print a blank line between lines]
// readaline myfile.csv 1000 2 c [as above but print the line number at the beginning, followed by a comma]
// readaline myfile.csv 1000 2 l [as above but print the line number on its own line first]

int main(int argc, char *argv[]) {
    stringstream sarg;
    stringstream sarg2;
    int linestart=1;
    int nlines = 1;
    string lineopt = "";
    string linefill;
    string filename = argv[1];
    sarg << argv[2];
    sarg >> linestart;
    if(argc>3) {
	      sarg2 << argv[3];
	      sarg2 >> nlines;
    }
    if(argc>4) {
        lineopt = argv[4];
        if(lineopt=="b") { linefill="\n"; }
    }
    string line;
    bool done = false;
    int linenum = 1;
    ifstream rfile;
    rfile.open(filename,ifstream::in);
    if(rfile) {
	    while(!rfile.eof() && !done) {
            getline(rfile,line);
            if(linenum==linestart & nlines==1) {
                if(lineopt=="c") { linefill=to_string(linenum)+", "; }
                if(lineopt=="l") { linefill=to_string(linenum)+"\n"; }
                cout << linefill << line <<endl;
                linenum++;
                done = true;
            }
            else if(linenum==linestart & nlines>1) {
                for(int i=0; i<nlines; i++) {
                    if(lineopt=="c") { linefill=to_string(linenum)+", "; }
                    if(lineopt=="l") { linefill=to_string(linenum)+"\n"; }
                    cout << linefill << line << endl;
                    linenum++;
                    getline(rfile,line);
                }
                done = true;
            }
            else {
                linenum++;
            }
	    }
	}
  rfile.close();
  return 0;
}
