#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &score, vector<char> &grade){
    string name;
    char format[] = "%[^:]: %d %d %d";
    ifstream source;
    source.open("name_score.txt");
    string textline;
    while(getline(source,textline)){
        char name[100];
        int a,b,c;
        sscanf(textline.c_str(), format, name, &a, &b, &c);
        score.push_back(a+b+c);
        names.push_back(name);
        grade.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){
    string text;
    cout << "Please input your command: ";
    getline(cin,text);
    int x = text.find_first_of(" ");
    command = text.substr(0,x);
    key = text.substr(x+1);
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = names.size();
    int status = 0;
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl << names[i] << "'s grade = " << grades[i] << endl;
            status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    int N = grades.size();
    int status = 0;
    char ikey[100];
    strcpy(ikey,key.c_str());
    cout << "---------------------------------\n";
    for(int i = 0 ; i < N ; i++){
        if(*ikey == grades[i]){
        cout << names[i] << " (" << scores[i] << ")" << endl;
        status = 1;
        }
    }
    if(status != 1) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}