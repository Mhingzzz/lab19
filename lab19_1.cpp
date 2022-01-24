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

void importDataFromFile(string file, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string s;
    char n[200];
    int a,b,c,sum;
    fstream myfile;
    myfile.open(file);

    while(getline(myfile,s)){
        string g = s;
        char *text = new char[g.size()+1];
        char form[] = "%[^:]: %d %d %d";
        strcpy(text,g.c_str());
        sscanf(text, form, n,&a, &b, &c);
        sum = a + b + c;
        names.push_back(n);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));

    }   
}

void getCommand(string &command, string &key){
    cout << "Please input your command :";
    cin >> command;
    if (toUpperStr(command) == "NAME" ||toUpperStr(command) == "GRADE" )
    {
        cin.ignore();
        getline(cin, key);
    }
    
    
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool condi = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++)
    {
        if (toUpperStr(key) == toUpperStr(names.at(i)))
        {
            condi = true;
            cout << names.at(i) <<"'s " << scores.at(i) <<endl;
            cout << names.at(i) <<"'s " << grades.at(i) <<endl;
        }
        
    }
    if (condi == false)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
    
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){

    bool condi = false;
    vector<char> k(key.begin(), key.end());
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++)
    {
        if (k.at(0) == grades.at(i))
        {
            condi = true;
            cout << names.at(i) << " " <<"("<<scores.at(i)<<")"<<endl;
        }
        
    }
    if (condi == false)
    {
        cout << "Cannot found.\n";
    }
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