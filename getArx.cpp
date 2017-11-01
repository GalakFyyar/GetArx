//#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "sha1.h"
using namespace std;

bool isHex(const string &x);
bool isEnd(const string &x);

int main(){
    system("baseball.bat");

    ifstream file("DeComp.txt");
    ofstream fileOut("Strings.txt");
    string pLine;
    string line;

    //Extract relevant strings from DeComp.txt, write to Strings.txt
    while(getline(file, line)){
        if(line.length() > 46){
            string typeToken = line.substr(47, 4);
                if(typeToken == "Stri"){
                    if(pLine.substr(47) != "class ChoiceQuestion"){
                        string token = line.substr(54);
                        if(isEnd(token))
                            break;
                        fileOut << token << endl;
                    }
                }
            pLine = line;
        }
    }
    file.close();
    fileOut.close();

    //Run cmd command to remove DeComp.txt
    system("DEL /F DeComp.txt");

    //Count number lines in Strings.txt
    ifstream fileS("Strings.txt");
    unsigned  lnum = 0;
    string token;
    while(getline(fileS, token)){
        lnum++;
    }
    fileS.close();

    //Populate array of answers and hashes
    ifstream fileS2("Strings.txt");
    string lines[lnum];
    unsigned i = 0;
    while(getline(fileS2, token)){
        lines[i] = token;
        i++;
    }
    fileS2.close();

    system("DEL /F Strings.txt");

    ofstream fileA("Ans.txt");
    string salt = "tToOaQ4oIGgud1RPH29OJLK6yOUhTbbb";

    string ppToken;
    string pToken;
    token = "";

    for(unsigned int j = 2; j < lnum; j++){
        ppToken = lines[j-2];
        pToken = lines[j-1];
        token = lines[j];

        if(isHex(ppToken) && isHex(pToken) && isHex(token)){
            for(unsigned int k = j; k < lnum-1 && !isHex(lines[k+1]); k++){
                string choice = lines[k+1];
                string salted = choice + salt;
                const char* c = salted.c_str();

                char hexstring[41];
                unsigned int len = salted.length();
                unsigned char hash[20];
                sha1::calc(c, len, hash);
                sha1::toHexString(hash, hexstring);

                if(ppToken == hexstring){
                    fileA << choice << endl;
                    break;
                }
            }
        }
    }
    fileA.close();
}

bool isHex(const string &x){
    bool r = false;
    if(x.length() == 40)
        if(string::npos == x.find_first_not_of("0123456789ABCDEF"))
            r = true;
    return r;
}

bool isEnd(const string &x){
    bool r = false;
    bool isThree = x.length() == 3;
    bool isFour = x.length() == 4;

    if(isThree || isFour){
        if(x.substr(0,2) == "ch"){
            string x2 = x.substr(2,1);
            if(isThree){
                if(string::npos != x2.find_first_of("0123456789")){
                    r = true;
                }
            }else{
                if(string::npos != x2.find_first_of("0123456789") && string::npos != x.substr(3,1).find_first_of("0123456789")){
                    r = true;
                }
            }
        }
    }
    return r;
}
