#ifndef MENU_H
#define MENU_H

/*!
  * @author Ceccarelli Luca - Clement Romain - Saadi Nils - Valls Marion
  * @date 9 jan 2021
  * @brief fichier permettant de créer des menus pour commencer le jeu
**/

#define FPS_LIMIT 60

#include <iostream>
#include <thread>   //gerer les frames et le temps
#include <string>   //convert char type to string
#include <map>      //store game themes
#include <fstream>  //read leaderBoard File

#include "mingl/shape/rectangle.h"
#include "mingl/mingl.h"
#include "mingl/gui/glut_font.h"
#include "mingl/gui/text.h"
#include "mingl/shape/line.h"
#include "mingl/event/event.hpp"

using namespace std;

/*!
  * @brief structure contenant l'element button
  * @fn button{string content, int buttonId,  nsGraphics::RGBAcolor bgColor,  nsGraphics::RGBAcolor borderColor,  nsGraphics::RGBAcolor textColor }
**/
struct button{
    //texte a afficher et couleur dans laquelle l'afficher

    string content;
    int buttonId;
    nsGraphics::RGBAcolor bgColor;
    nsGraphics::RGBAcolor borderColor;
    nsGraphics::RGBAcolor textColor;

    nsGui::Text text{nsGraphics::Vec2D{0,0},
                     content,
                     textColor,
                     nsGui::GlutFont::GlutFonts::BITMAP_9_BY_15,
                     nsGui::Text::ALIGNH_CENTER,
                     nsGui::Text::ALIGNV_CENTER};
    nsShape::Rectangle rect{nsGraphics::Vec2D{0,0},
                            nsGraphics::Vec2D{0,0},
                            bgColor,
                            borderColor};
};//button

/*!
  * @brief fonction pour verifier si on appuye sur la fenetre de jeu et si un bouton est concerné
  * @param[in/out] EventManager
  * @param[in] btns : vecteur contenant les boutons
  * @fn int events(nsEvent::EventManager &eventM, const vector<button> &btns)
**/
int events(nsEvent::EventManager &eventM, const vector<button> &btns);

/*!
  * @brief fonction pour recuperer la derniere touche qui as été appuyé sur le clavier
  * @param[in/out] window
  * @fn char getLastPressedChar(MinGL &window)
**/
char getLastPressedChar(MinGL &window);

/*!
  * @brief fonction pour placer des boutons centrés horizontalement et verticalement
  * @param[in/out] window : fenetre
  * @param[in] b : vecteur de struct contenant le texte à afficher et la couleur dans laquelle l'afficher
  * @param[in] width : largeur de la fenetre
  * @param[in] height : hauteur de la fenetre
**/
void placeBtns(const MinGL &window, vector<button> &btns);

/*!
  * @brief fonction utilisé pour afficher les boutons dans la fenetre : window
  * @param[in/out] window
  * @param[in] btns : vecteur contenant la liste des boutons à afficher
  * @fn void drawBtns(MinGL &window, const vector<button> &btns)
**/
void drawBtns(MinGL &window, const vector<button> &btns);

/*!
  * @brief fonction utilisé pour lire le fichier leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @fn void getLeaderBoard(vector<string> &leaderBoard)
**/
void getLeaderBoard(vector<string> &leaderBoard);

/*!
  * @brief fonction utilisé pour acceder au valeurs dans le fichier de configuration.yaml
  * @param[in/out] dictionnaire avec les parametres
  * @fn void readConfFile(map<string,string> &settings
**/
void readConfFile(map<string,string> &settings);

/*!
  * @brief fonction utilisé pour ecrire les valeurs dans le dictionnaire parametres, dans le fichier de configuration.yaml
  * @param[in/out] dictionnaire avec les parametres
  * @fn void writeConfigFile(map<string,string> &settings)
**/
void writeConfigFile(map<string,string> &settings);

/*!
  * @brief fonction utilisé pour commencer le jeu
  * @param[in/out] window
  * @fn void startButton(MinGL &window
**/
void startButton(MinGL &window);

/*!
  * @brief fonction acceder au menu qui affiche la liste des meilleurs scores
  * @param[in/out] window
  * @fn void scoreButton(MinGL &window)
**/
void scoreButton(MinGL &window);

/*!
  * @brief fonction utilisé pour acceder au menu des reglages
  * @param[in/out] window
  * @fn void settingsButton(MinGL &window)
**/
void settingsButton(MinGL &window);

/*!
  * @brief fonction qui sert à verifier quel bouton as été appuyé sur le menu principale, pour changer de fenetre
  * @param[in/out] window : fenetre
  * @param[in/out] content : contenu du bouton appuyé
  * @fn void checkContent(MinGL &window, int &content)
**/
void checkContent(MinGL &window, int &content);

/*!
  * @brief fonction pour lancer le menu principale
  * @fn void menu()
**/
void menu();


#endif // MENU_H
