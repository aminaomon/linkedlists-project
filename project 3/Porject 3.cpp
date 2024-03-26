//OXO220016
//Ominakhon Omonullaeva
#include <iostream>
#include<fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

//structure
struct player{

    string name;
    int highScore;
    string initials;
    int numPlays;
    double revenue;
    player *next;

};


//adds to end of linked list
void endOfList(player *bruh, player *&head){
//adds to linked list if null else skips to nullptr
    if(head == nullptr){

        head = bruh;

    }else{

        player *tempPos = head;

        while(tempPos -> next != nullptr){
            tempPos = tempPos -> next;
        }

        tempPos -> next = bruh;

    }//close if else

}


//adds to linked list database
void addToList(string line, player *&head){
    
    player *temp = new player;
    temp -> next = nullptr;
    long long unsigned int start = 0;
    long long unsigned int end;

    end = line.find(",");
    temp -> name = line.substr(start, end);

    start = end + 2;
    end = line.find(",", start);
    string high = line.substr(start, end - start);
    int highS = stoi (high);
    temp -> highScore = highS;

    start = end + 2;
    end = line.find(",", start);
    temp -> initials = line.substr(start, end - start);

    start = end + 2;
    end = line.find(",", start);
    string play = line.substr(start, end - start);
    int playS = stoi (play);
    temp -> numPlays = playS;

    start = end + 3;
    string rev = line.substr(start);
    double revS = stod (rev);
    temp -> revenue = revS;

    endOfList(temp, head);



}//close addToLIst

void addRecord(string line, player *&head){
    player *temp = new player;
    long long unsigned int start = 1;
    long long unsigned int end;

    end = line.find('"', start);
    temp -> name = line.substr(start, end - 1);
   

    start = end + 2;
    end = line.find(' ', start);
    string high = line.substr(start, end - start);
    int highS = stoi (high);
    temp -> highScore = highS;
    

    start = end + 1;
    end = line.find(' ', start);
    temp -> initials = line.substr(start, end - start);
    

    start = end + 1;
    end = line.find(' ', start);
    string play = line.substr(start, end - start);
    int playS = stoi (play);
    temp -> numPlays = playS;
 

    start = end + 2;
    string rev = line.substr(start);
    double revS = stod (rev);
    temp -> revenue = revS;
   

    endOfList(temp, head);

    cout << "RECORD ADDED" << endl;
    cout << "Name: " << temp -> name << endl;
    cout << "High Score: " << temp -> highScore << endl;
    cout << "Initials: " << temp -> initials << endl;
    cout << "Plays: " << temp -> numPlays << endl;
    cout << "Revenue: $" << temp -> revenue << endl;

}//close addfunction

void searchRecord(string term, player *&head){
    player *search = head;
    int count = 0;
    
    while(search != nullptr){
        
        string phrase;
        phrase = search -> name;
        size_t found = phrase.find(term);
        
        if(found < 100){
            count ++;
            
            cout << phrase << " FOUND" << endl;
            cout << "High Score: " << search -> highScore << endl;
            cout << "Initials: " << search -> initials << endl;
            cout << "Plays: " << search ->numPlays << endl;
            cout << "Revenue: $" << fixed << setprecision(2) << search -> revenue << endl;
        }
        search = search -> next;
    }

    if(count == 0){
        cout << term << " NOT FOUND" << endl;
    }

}//close searchRec

void editRecord(string line, player *&head){
    player *pos = head;
    long long unsigned int start = 1;
    long long unsigned int end;
    string num;
    string type;
    string value;

    end = line.find('"', start);
    string term = line.substr(start, end - 1);

    start = end + 2;
    end = line.find (' ', start);
    num = line.substr(start, end - start);

    start = end + 1;
    value = line.substr(start);

    while(pos != nullptr){
        if(pos -> name == term){

            if(stoi(num) == 1){

                type = "high score";
                pos -> highScore = stoi(value);

            }else if(stoi(num) == 2){

                type = "initials";
                pos -> initials = value;
                
            }else if(stoi(num) == 3){

                type = "plays";
                pos -> numPlays = stoi(value);

            }
            
            break;
        }

        pos = pos -> next;
    }

    cout << term << " UPDATED" << endl;
    cout << "UPDATE TO " << type << " - VALUE " << value << endl;
    cout << "Name: " << pos -> name << endl;
    cout << "High Score: " << pos -> highScore << endl;
    cout << "Initials: " << pos -> initials << endl;
    cout << "Plays: " << pos ->numPlays << endl;
    cout << "Revenue: $" << fixed << setprecision(2) << pos -> revenue << endl; 

} //close editRec

void printList(player *&head, ofstream &file){
 player *skim = head;
    while(skim != nullptr){
        file << skim -> name << ", " << skim -> highScore << ", "
        << skim -> initials << ", " << skim -> numPlays  << ", $" 
         << fixed << setprecision(2) << skim -> revenue << endl;

        skim = skim -> next;
    }

}//close printlist

int main(){

    //variables
   string db;
   string batch;
   string info;
   ifstream batchFile;
   fstream dbFile;
   ofstream outfile("freeplay.dat");
   player *head = nullptr;

    //user input
   cout << "Enter Database name : " << endl;
   cin >> db;
   dbFile.open(db);
   

   cout << "Enter Batch name : " << endl;
   cin >> batch;
   batchFile.open(batch);

    //confirms files are open
   if(!dbFile.is_open() || !batchFile.is_open()){
    cout << "Error" << endl;
    return 0;
   }

    while(!dbFile.eof()){
        getline(dbFile, info);
        addToList(info, head);
    }

    while(!batchFile.eof()){
        getline(batchFile, info);

        if(info[0] == '1'){

            info = info.substr(2);
            addRecord(info, head);
            cout << endl;

        }else if(info[0] == '2'){

            info = info.substr(2);
            searchRecord(info, head);
            cout << endl;

        }else if(info[0] == '3'){

            info = info.substr(2);
            editRecord(info, head);
            
        }else if(info[0] == '4'){
            
        }else if(info[0] == '5'){
            
        }


    }


    //prints linked list to freeplay.dat
   printList(head, outfile);

    dbFile.close();
    batchFile.close();
    delete head;
    
    return 0;
}