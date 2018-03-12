#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string; // this will require -std=c++11 when compiling
using std::stoi; // this will require -std=c++11 when compiling
using std::ifstream;
using std::ofstream;
using std::vector;

// USAGE:
// readthoselines mybigfile.csv linenumbers.txt c
// this expects linenumbers.txt to contain an integer on each line and nothing else
// those integers must be sorted in ascending order!
// and those are the line numbers that get retrieved from mybigfile.csv
// they print to cout, so you probably want to pipe them into a new file.
// the letter on the end (c, b, l) is the same option for showing line numbers as in readaline

int main(int argc, char *argv[]) {
    int linenum = 1; // current line being read from bigfile
    int sampleline; // a line number from the line number file, on its way in or out of the vector of sample numbers
    vector<int> linenums; // the vector of line numbers to be sampled
    int samplesize = 0; // the size of the vector
    string lineopt = ""; // line number display option, argv[3]
    string linefill; // stuff to display with line number
    string line; // a line being read from some file
    string bigfile;
    ifstream rbfile;
    string linefile;
    ifstream rlfile;
    int numsampled = 0; // how many have been sampled from bigfile so far; gets compared with samplesize.

    if(argc<3) {
        cout << "ERROR: you need to specify two file names and an optional code for showing line numbers" << endl;
        return -1;
    }
    bigfile = argv[1];
    linefile = argv[2];
    if(argc>3) {
        lineopt = argv[3];
        if(lineopt=="b") { linefill="\n"; }
    }

// get line numbers for sampling
    rlfile.open(linefile,ifstream::in);
    if(rlfile) {
        getline(rlfile,line);
        while(!rlfile.eof() & line!="") {
            sampleline = stoi(line);
            linenums.push_back(sampleline);
            samplesize++;
            getline(rlfile,line);
        }
    }
    else {
        cout << "ERROR: line number file not found." << endl;
        return -1;
    }
    rlfile.close();

    // open big file and look for successive line numbers
    rbfile.open(bigfile,ifstream::in);
    sampleline = linenums[numsampled];
    if(rbfile) {
	    while(!rbfile.eof() && numsampled<samplesize) {
            getline(rbfile,line);
            if(linenum==sampleline) {
                if(lineopt=="c") { linefill=to_string(linenum)+", "; }
                if(lineopt=="l") { linefill=to_string(linenum)+"\n"; }
                cout << linefill << line << endl;
                linenum++;
                numsampled++;
                sampleline = linenums[numsampled];
            }
            else {
                linenum++;
            }
	    }
	  }
    else {
        cout << "ERROR: big file not found." << endl;
        return -1;
    }
    rbfile.close();
    return 0;
}
