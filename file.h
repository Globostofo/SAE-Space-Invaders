/*!
 *
 * @file    file.h
 * @author  Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
 * @date    January 2022
 * @brief   File Management
 *
 **/

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>   //convert char type to std::string
#include <vector>
#include <map>      //store game themes
#include <fstream>  //read Files

#include "consts.h"

namespace nsFile {

/*!
  * @brief procedure used to read and get the leaderboard in the leaderboard.txt file
  * @param[in/out] leaderBoard : list of the names of the players and their scores need to be initialized with a lenght of 10
  * @fn void getLeaderBoard(std::vector<std::string> &leaderBoard)
**/
void getLeaderBoard(std::vector<std::string> &leaderBoard);

/*!
  * @brief procedure used to verify if we can add a score in the file, and add it to the list if so
  * @param[in/out] leaderBoard : list of the names of the players and their scores
  * @param [in] username : user name
  * @param [in] score: user score
  * @fn void addScore(vector<string> &leaderBoard,string username, unsigned score)
**/
void addScore(std::vector<std::string> &leaderBoard,const std::string username, const unsigned score);

/*!
  * @brief procedure used to write the list leaderBoard in the leaderboard.txt file
  * @param[in] leaderBoard : list of the names of the players and their scores
  * @fn void writeLeaderBoard(vector<string> &leaderBoard)
**/
void writeLeaderBoard(const std::vector<std::string> leaderBoard);

/*!
  * @brief procedure used to get the informations from configuration.yaml and put them in a dictionnary
  * @param[in/out] settings : dictionnary with the settings extracted
  * @fn void readConfFile(map<std::string,std::string> &settings;
**/
void readConfFile(std::map<std::string,std::string> &settings);

/*!
  * @brief procedure used to write the elements in the dictionnary settings, into the configuration.yaml
  * @param[in] settings : dictionnary with the settings to write
  * @fn void writeConfigFile(map<std::string,std::string> &settings);
**/
void writeConfigFile(const std::map<std::string,std::string> settings);
}

#endif // FILE_H
