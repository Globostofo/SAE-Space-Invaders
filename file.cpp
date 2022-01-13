/*!
 *
 * @file    file.cpp
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   File Management
 *
 **/

#include "file.h"

using namespace std;

void nsFile::getLeaderBoard(vector<string> &leaderBoard){
    string score;
    ifstream scoreFile (nsConsts::leaderboard);
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

void nsFile::writeLeaderBoard(vector<string> leaderBoard){
    ofstream scoreFile (nsConsts::leaderboard);
    for(vector<string>::iterator iter = leaderBoard.begin() ; iter<leaderBoard.end(); ++iter)
        scoreFile<<*iter<<endl;
}//writeLeaderBoard()

void nsFile::readConfFile(map<string,string> &settings) {

    ifstream configFile (nsConsts::config);
    string line;

    while(getline(configFile,line)){

        string value="";
        string key="";
        bool isSeparatorfound = false;

        for(char letter : line){
            if(letter == ':'){
                isSeparatorfound = true;
                continue;
            }
            if(isSeparatorfound){
                value+=string(1,letter);
            }
            else{
                key+=string(1,letter);
            }
        }
        settings[key]=value;
    }
} // readConfFile()

void nsFile::writeConfigFile(map<string,string> settings) {

    ofstream ofs (nsConsts::config);
    for(map<string,string>::iterator iter = settings.begin(); iter!=settings.end(); ++iter){
        ofs<<(*iter).first<<":"<<(*iter).second<<endl;
    }
    ofs.close();
} // writeConfigFile()
