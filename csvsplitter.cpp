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
	int nlines=1000;
	stringstream sarg;
    string bigfile;

	if(argc!=3) {
	    cerr << "Arguments missing: should be big file name then lines per small file";
	    return -1;
	}
	sarg << argv[2];
	sarg >> nlines;
    bigfile=argv[1];
	if(bigfile=="") {
	    cerr << "bigfile is missing..." << endl;
	    return -1;
	}

	string line;
	string line1; // first line, to be added atop all splitfiles
	int fn=1;
	int gotline1=0;
	int lnum=1;
	int lmax=nlines+1;
	ifstream rfile;
    ofstream wfile;
    rfile.open(bigfile,ifstream::in);
	if(rfile) {
        while(!rfile.eof()) {
            string sfn=to_string(fn);
            cout << "Now writing file "+sfn << endl;
        	wfile.open("split"+sfn+".csv",ofstream::out);
					if(fn>1) {
						wfile << line1 << endl;
					}
    	    while (getline(rfile,line) && lnum<lmax) {
						if(gotline1==0) {
							line1=line; // store 1st line for later
							gotline1=1;
						}
    	    	wfile << line << endl;
    	    	++lnum;
    	    }
        	wfile.close();
        	++fn;
    	    lmax=lmax+nlines;
        }
    	rfile.close();
    	return 0;
    }
    else {
        cerr << bigfile << " does not exist" << endl;
        return -1;
    }
}
