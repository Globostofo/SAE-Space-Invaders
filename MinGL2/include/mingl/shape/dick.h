/**
 *
 * @file    dick.h
 * @author  R. Clement
 * @date    29/11/2021
 * @version 1.0
 * @brief   Représente une grosse teub
 *
 **/

#ifndef DICK_H
#define DICK_H

#include "shape.h"

#include "../transition/itransitionable.h"

namespace nsShape
{

/**
 * @class Dick
 * @brief Classe représentant une bite
 */
class Dick : public Shape, public nsTransition::ITransitionable
{

public:
    /**
     * @brief TransitionIds : Liste de toutes les transitions que cet élément peut exécuter
     */
    enum TransitionIds {
        TRANSITION_FILL_COLOR_RGB,      /**< Transition pour la couleur de remplissage      */
        TRANSITION_FILL_COLOR_ALPHA,    /**< Transition pour la transparence de remplissage */
        TRANSITION_POSITION,            /**< Transition pour la position de l'engin         */
        TRANSITION_LENGTH,              /**< Transition pour la longueur de l'engin         */
        TRANSITION_WIDTH,               /**< Transition pour la largeur de l'engin          */
        TRANSITION_DIRECTION,           /**< Transition pour la direction de l'engin        */
    };

    /**
     * @brief Constructeur pour la classe Dick
     * @param[in] pos : Position de l'engin
     * @param[in] length : Longueur de l'engin
     * @param[in] width : Largeur de l'engin
     * @param[in] dir : Direction de l'engin
     * @param[in] fillColor : Couleur de remplissage
     * @fn Dick(const nsGraphics::Vec2D &pos, const unsigned &length, const unsigned &width, const double &dir, const nsGraphics::RGBAcolor &fillColor);
     */
    Dick(const nsGraphics::Vec2D &pos, const unsigned &length, const unsigned &width, const double &dir, const nsGraphics::RGBAcolor &fillColor);

    /**
     * @brief Destructeur virtuel pour la classe Dick
     * @fn virtual ~Dick() override = default;
     */
    virtual ~Dick() override = default;

    virtual void draw(MinGL &window) const override;

    virtual void getValues(const int &id, std::vector<float> &values) override;
    virtual void setValues(const int &id, const std::vector<float> &values) override;

    /**
     * @brief Définit la nouvelle position de l'engin
     * @param[in] pos : Nouvelle position de l'engin
     * @fn void setPos(const nsGraphics::Vec2D &pos);
     */
    void setPos(const nsGraphics::Vec2D &pos);

    /**
     * @brief Récupère la position de l'engin
     * @fn const nsGraphics::Vec2D &getPos() const;
     */
    const nsGraphics::Vec2D &getPos() const;

    /**
     * @brief Définit la nouvelle longueur de l'engin
     * @param[in] length : Nouvelle longueur de l'engin
     * @fn void setLength(const unsigned &length);
     */
    void setLength(const unsigned &length);

    /**
     * @brief Récupère la longueur de l'engin
     * @fn const unsigned &getLength() const;
     */
    const unsigned &getLength() const;

    /**
     * @brief Définit la nouvelle largeur de l'engin
     * @param[in] width : Nouvelle largeur de l'engin
     * @fn void setWidth(const unsigned &width);
     */
    void setWidth(const unsigned &width);

    /**
     * @brief Récupère la largeur de l'engin
     * @fn const unsigned &getWidth() const;
     */
    const unsigned &getWidth() const;

    /**
     * @brief Définit la nouvelle direction de l'engin
     * @param[in] dir : Nouvelle direction de l'engin
     * @fn void setDirection(const double &DickWidth);
     */
    void setDirection(const double &dir);

    /**
     * @brief Récupère la direction de l'engin
     * @fn double getDirection() const;
     */
    const double &getDirection() const;

private:
    /**
     * @brief m_posistion : Position de l'engin
     */
    nsGraphics::Vec2D m_position;

    /**
     * @brief m_length : Longueur de l'engin
     */
    unsigned m_length;

    /**
     * @brief m_width : Largeur de l'engin
     */
    unsigned m_width;

    /**
     * @brief m_direction : Direction de l'engin
     */
    double m_direction;

}; // class Dick

} // namespace nsShape

#endif // Dick_H
