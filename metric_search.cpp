//this is the code for metric that parses thru personal files and indexes thms and lemmas
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//we create a helper function to check if the begin is one of the environments we are looking for
//so we want to exclude documents, centers, equations, etc
bool hasEnvironment(string line){
    return (line.find("{lem}") != string::npos ||
            line.find("{thm}") != string::npos ||
            line.find("{cor}") != string::npos ||
            line.find("{defn}") != string::npos ||
            line.find("{axm}") != string::npos);
}

int main(){
    //remove("output.txt");

    string parseText;

    ofstream MyOutFile("database.txt");
    
    ifstream MyReadFile("C:\\Users\\rakmo\\OneDrive\\Desktop\\Analysis Notes\\notes.tex");

    //this is a vector we use to store promising lines
    vector<string> begin_list;

    //this signifies if we have found a proper begin; we then just need to find an end
    bool begin_found = false;

    while (getline (MyReadFile, parseText)) {
        // Output the text from the file
        cout << parseText << endl;
        //we check for a latex beginning marker and environment container markers
        if(parseText.find("\\begin") != string::npos 
        && hasEnvironment(parseText)){
            begin_list.push_back(parseText);
            begin_found = true;
        }
        else if(begin_found){
            if(parseText.find("\\end") != string::npos 
            && hasEnvironment(parseText)){
                begin_list.push_back(parseText);
                begin_found = false;
            }
            else{
                begin_list.push_back(parseText);
            }
        }
    }

    for(string lines : begin_list){
        MyOutFile << lines << endl;
    }


    MyReadFile.close();
    MyOutFile.close();
}
