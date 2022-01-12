#include "file.h"

using namespace std;

void nsFile::getLeaderBoard(vector<string> &leaderBoard){
    //leaderBoard init to 10
    string score;
    ifstream scoreFile ("leaderBoard.txt");
    for(vector<string>::iterator iter = leaderBoard.begin(); iter !=leaderBoard.end(); ++iter){
        getline(scoreFile,score);
        (*iter)=score;
    }
} // getLeaderBoard()

void nsFile::addScore(vector<string> &leaderBoard,string username, unsigned score){
    vector<unsigned> leaderBoardScores(10);
    vector<string> leaderBoardUsernames(10);

    unsigned i = 0;

    for(string &line : leaderBoard){

        string value="";
        bool isSeparatorfound = false;

        for(char &letter : line){
            if(letter == ':'){
                isSeparatorfound = true;
                continue;
            }
            if(isSeparatorfound){
                value+=string(1,letter);
            }
            else{
                leaderBoardUsernames[i]+=string(1,letter);
            }
        }
        if(isSeparatorfound){
            leaderBoardScores[i]=stoul(value);
        }
        ++i;
    }
    unsigned place;
    bool hasBeenAdded = false;
    for(unsigned j =0; j<leaderBoardScores.size(); ++j){
        if(leaderBoardScores[j]<score){
            place = j;
            hasBeenAdded = true;
            break;
        }
    }
    if(hasBeenAdded){
        for(unsigned j = leaderBoard.size()-1; j>place; --j){
            leaderBoardScores[j]=leaderBoardScores[j-1];
            leaderBoardUsernames[j]=leaderBoardUsernames[j-1];
        }
        leaderBoardScores[place]=score;
        leaderBoardUsernames[place]=username;
        for(unsigned j =0; j<leaderBoard.size(); ++j){
            leaderBoard[j]=leaderBoardUsernames[j]+":"+to_string(leaderBoardScores[j]);
        }
    }
}//addScore()

void nsFile::writeLeaderBoard(vector<string> &leaderBoard){
    ofstream scoreFile ("leaderBoard.txt");
    for(vector<string>::iterator iter = leaderBoard.begin() ; iter<leaderBoard.end(); ++iter){
        scoreFile<<*iter<<endl;
    }
}//writeLeaderBoard()

void nsFile::readConfFile(map<string,string> &settings) {

    ifstream configFile ("config.yaml");
    string line;

    while(getline(configFile,line)){
        unsigned separator=line.find(":");
        settings[line.substr(0,separator-1)]=line.substr(separator+1,line.size()-2);
    }
} // readConfFile()

void nsFile::writeConfigFile(map<string,string> &settings) {

    ofstream ofs ("config.yaml");
    for(map<string,string>::iterator iter = settings.begin(); iter!=settings.end(); ++iter){
        ofs<<(*iter).first<<":"<<(*iter).second<<endl;
    }
    ofs.close();
} // writeConfigFile()
