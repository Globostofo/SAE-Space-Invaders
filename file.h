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
  * @brief fonction utilisé pour lire le fichier leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @fn void getLeaderBoard(std::vector<std::string> &leaderBoard)
**/
void getLeaderBoard(std::vector<std::string> &leaderBoard);

/*!
  * @brief fonction utilisé pour verifier si on peut ajouter le score du username, et le inserer dans la liste leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @param [in] username : nom utilisateur
  * @param [in] score: le score fait par l'utilisateur
  * @fn void addScore(vector<string> &leaderBoard,string username, unsigned score)
**/
void addScore(std::vector<std::string> &leaderBoard,std::string username, unsigned score);

/*!
  * @brief fonction utilisé pour ecrire dans le fichier leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @fn void writeLeaderBoard(vector<string> &leaderBoard)
**/
void writeLeaderBoard(std::vector<std::string> &leaderBoard);

/*!
  * @brief fonction utilisé pour acceder au valeurs dans le fichier de configuration.yaml
  * @param[in/out] dictionnaire avec les parametres
  * @fn void readConfFile(map<std::string,std::string> &settings;
**/
void readConfFile(std::map<std::string,std::string> &settings);

/*!
  * @brief fonction utilisé pour ecrire les valeurs dans le dictionnaire parametres, dans le fichier de configuration.yaml
  * @param[in/out] dictionnaire avec les parametres
  * @fn void writeConfigFile(map<std::string,std::string> &settings);
**/
void writeConfigFile(std::map<std::string,std::string> &settings);
}

#endif // FILE_H
