#ifndef ENEMY_H
#define ENEMY_H

#include "mingl/graphics/vec2d.h"
#include "mingl/gui/sprite.h"

namespace nsGame {

    /*!
     * @struct Enemy
     * @brief Structure de données regroupant les diverses informations d'un invader
     */
    struct Enemy {

        /*!
         * @brief sprite : apparence de l'enemi
         */
        nsGui::Sprite sprite;

        /*!
         * \brief lifes : nombre de vie de l'enemi
         */
        int lifes;
    };

    /*!
     * @brief EnemySprites : liste de tous les sprites disponibles pour les enemis
     */
    enum EnemySprites {
        LINUX   /**< Sprite du pingouin */
    };

    /*!
     * @brief Constructeur pour la structure Enemy
     * @param[in] sprite : image représentant l'enemi
     * @param[in] position : position de création de l'enemi
     * @param[in] lifes : nombre de vies initial de l'enemi
     * @fn Enemy createEnemy(const EnemySprites & sprite, const nsGraphics::Vec2D & position, const int & lifes);
     */
    Enemy createEnemy(const EnemySprites & sprite, const int & lifes);

    /*!
     * @brief Afficheur pour la structure Enemy
     * @param[in] enemy : cible de la requête
     * @fn void displayEnemy(const Enemy & enemy);
     */
    void displayEnemy(MinGL & window, const Enemy & enemy);

    /*!
     * @brief Récupère l'apparence de l'ennemi
     * @param[in] enemy : cible de la requête
     * @fn nsGui::Sprite getEnemySprite(const Enemy & enemy);
     */
    nsGui::Sprite getEnemySprite(const Enemy & enemy);

    /*!
     * @brief Définit la nouvelle apparence de l'enemi
     * @param [in/out] enemy : cible de la requête
     * @param[in] sprite : nouvelle apparence
     * @fn void setEnemySprite(Enemy & enemy, const EnemySprites & sprite);
     */
    void setEnemySprite(Enemy & enemy, const EnemySprites & sprite);

    /*!
     * @brief Récupère le nombre de vie de l'enemi
     * @param[in] enemy : cible de la requête
     * @fn int getEnemyLifes(const Enemy & enemy);
     */
    int getEnemyLifes(const Enemy & enemy);

    /*!
     * @brief Définit le nouveau nombre de vies
     * @param[in/out] enemy : cible de la requête
     * @param[in] lifes : nouveau nombre de vies
     * @fn void setEnemyLifes(Enemy & enemy, const int & lifes);
     */
    void setEnemyLifes(Enemy & enemy, const int & lifes);

    /*!
     * @brief Récupère la taille du sprite de l'enemi
     * @param[in] enemy : cible de la requête
     * @fn nsGraphics::Vec2D getEnemySize(Enemy & enemy);
     */
    nsGraphics::Vec2D getEnemySize(const Enemy & enemy);

}

#endif // ENEMY_H
