#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <thread>   //gerer les frames et le temps
#include <string>   //convert char type to std::string
#include <map>      //store game themes
#include <fstream>  //read leaderBoard File

#include "mingl/shape/rectangle.h"
#include "mingl/mingl.h"
#include "mingl/gui/glut_font.h"
#include "mingl/gui/text.h"
#include "mingl/shape/line.h"
#include "mingl/event/event.hpp"

namespace nsMenu {

/*!
  * @struct structure contenant l'element button
  * @fn button{std::string content, int buttonId,  nsGraphics::RGBAcolor bgColor,  nsGraphics::RGBAcolor borderColor,  nsGraphics::RGBAcolor textColor }
**/
struct Button {
    //texte a afficher et couleur dans laquelle l'afficher

    std::string content;
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
}; // struct Button

/*!
  * @brief fonction pour verifier si on appuye sur la fenetre de jeu et si un bouton est concerné
  * @param[in/out] EventManager
  * @param[in] btns : vecteur contenant les boutons
  * @fn int events(nsEvent::EventManager &eventM, const std::vector<button> &btns)
**/
int events(nsEvent::EventManager &eventM, const std::vector<Button> &btns);

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
void placeBtns(const MinGL &window, std::vector<Button> &btns);

/*!
  * @brief fonction utilisé pour afficher les boutons dans la fenetre : window
  * @param[in/out] window
  * @param[in] btns : vecteur contenant la liste des boutons à afficher
  * @fn void drawBtns(MinGL &window, const std::vector<button> &btns)
**/
void drawBtns(MinGL &window, const std::vector<Button> &btns);

/*!
  * @brief fonction utilisé pour lire le fichier leaderBoard
  * @param[in/out] leaderBoard : liste avec les noms des players et leur score, avec indice 0 pour le meilleur et 9 pour le pire
  * @fn void getLeaderBoard(std::vector<std::string> &leaderBoard)
**/
void getLeaderBoard(std::vector<std::string> &leaderBoard);

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

/*!
  * @brief fonction utilisé pour commencer le jeu
  * @param[in/out] window
  * @fn void startButton(MinGL &window
**/
void startButton(MinGL &window);;

/*!
  * @brief fonction acceder au menu qui affiche la liste des meilleurs scores
  * @param[in/out] window
  * @fn void scoreButton(MinGL &window);
**/
void scoreButton(MinGL &window);

/*!
  * @brief fonction utilisé pour acceder au menu des reglages
  * @param[in/out] window
  * @fn void settingsButton(MinGL &window);
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
  * @brief fonction pour lancer le menu principal
  * @fn void menu()
**/
void menu();

} // namespace nsMenu

#endif // MENU_H
