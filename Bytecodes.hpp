#include <iostream>

using namespace std;

class Instructions {
    private:
        string name;
        int nOpnds = 0;
    public:
        Instructions(string name_) {
            name = name_;
        }

        Instructions(string name_, int nOpnds_) {
            name = name_;
            nOpnds = nOpnds_;
        }

        string get_name() {
            return name;
        }

        int get_nOpnds() {
            return nOpnds;
        }
};

Instructions instr[] = {
    {"HALT"},
    {"ICONST", 1},
    {"PRINT", -1},
    {"GSTORE", 1},
    {"GLOAD", 1},
    {"IADD"},
    {"BR", 1},
    {"BRT", 1},
    {"ILT"},
    {"CALL", 2},
    {"RET"},
    {"LOAD", 1},
    {"IMUL"},
    {"ISUB"},
    {"BRF"}
};


int const HALT = 0;
int const ICONST = 1;
int const PRINT = 2;
int const GSTORE = 3; 
int const GLOAD = 4; 
int const IADD = 5;
int const BR = 6;
int const BRT = 7;
int const ILT = 8;
int const CALL = 9;
int const RET = 10;
int const LOAD = 11;
int const IMUL = 12;
int const ISUB = 13;
int const BRF = 14;
