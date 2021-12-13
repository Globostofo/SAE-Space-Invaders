/**
 *
 * @file    dick.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente une bite
 *
 **/

#include <cmath>

#include "mingl/shape/dick.h"
#include "mingl/macros.h"

nsShape::Dick::Dick(const nsGraphics::Vec2D &pos_, const unsigned &len_, const unsigned &w_, const double &dir_, const nsGraphics::RGBAcolor &fillColor_)
    : Shape(fillColor_, fillColor_)
    , m_position(pos_)
    , m_length(len_)
    , m_width(w_)
    , m_direction(dir_)
{} // Dick()

void nsShape::Dick::draw(MinGL& window) const
{
    UNUSED(window);

    auto drawLine = [](const nsGraphics::Vec2D &pos1, const nsGraphics::Vec2D &pos2, const unsigned &width, const nsGraphics::RGBAcolor &inColor) {
        // On met la couleur de la ligne
        glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha());

        // On règle l'épaisseur de la ligne
        glLineWidth(width);

        // On dessine la ligne
        glBegin(GL_LINES);
        glVertex2i(pos1.getX(), pos1.getY());
        glVertex2i(pos2.getX(), pos2.getY());
        glEnd();
    };

    auto drawCircle = [](const nsGraphics::Vec2D &position, const unsigned &radius, const nsGraphics::RGBAcolor &inColor) {
        int i;
        int triangleAmount = 20; // Nombre de triangles a dessiner

        // On règle la couleur du cercle
        glColor4ub(inColor.getRed(), inColor.getGreen(), inColor.getBlue(), inColor.getAlpha()); // Couleur du cercle

        GLfloat twicePi = 2.0f * M_PI;

        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(position.getX(), position.getY()); // Centre du cercle

        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(position.getX() + (radius * cos(i * twicePi / triangleAmount)),
                       position.getY() + (radius * sin(i * twicePi / triangleAmount)));
        }

        glEnd();
    };

    double g = m_direction+M_PI/2;
    double d = m_direction-M_PI/2;
    int w = m_width/2;
    nsGraphics::Vec2D burneGPos(cos(g)*w, sin(g)*w);
    nsGraphics::Vec2D burneDPos(cos(d)*w, sin(d)*w);
    nsGraphics::Vec2D glandPos(cos(m_direction)*m_length, sin(m_direction)*m_length);

    drawCircle(m_position+burneGPos, w, m_fillColor);
    drawCircle(m_position+burneDPos, w, m_fillColor);
    drawLine(m_position, m_position+glandPos, m_width, m_fillColor);
    drawCircle(m_position+glandPos, w, m_fillColor);

} // draw()

void nsShape::Dick::getValues(const int &id, std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            values[0] = m_fillColor.getRed();
            values[1] = m_fillColor.getGreen();
            values[2] = m_fillColor.getBlue();

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            values[0] = m_fillColor.getAlpha();

            break;

        case TRANSITION_POSITION:
            values[0] = m_position.getX();
            values[1] = m_position.getY();

            break;

        case TRANSITION_LENGTH:
            values[0] = m_length;

            break;

        case TRANSITION_WIDTH:
            values[0] = m_width;

            break;

        case TRANSITION_DIRECTION:
            values[0] = m_direction;

            break;
    }
} // getValues()

void nsShape::Dick::setValues(const int &id, const std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_FILL_COLOR_RGB:
            m_fillColor.setRed(values[0]);
            m_fillColor.setGreen(values[1]);
            m_fillColor.setBlue(values[2]);

            break;

        case TRANSITION_FILL_COLOR_ALPHA:
            m_fillColor.setAlpha(values[0]);

            break;

        case TRANSITION_POSITION:
            m_position.setX(values[0]);
            m_position.setY(values[1]);

            break;

        case TRANSITION_LENGTH:
            m_length = values[0];

            break;

        case TRANSITION_WIDTH:
            m_width = values[0];

            break;

        case TRANSITION_DIRECTION:
            m_direction = values[0];

            break;
    }
} // setValues()

void nsShape::Dick::setPos(const nsGraphics::Vec2D &pos) {
    m_position = pos;
} // setPos()

const nsGraphics::Vec2D &nsShape::Dick::getPos() const {
    return m_position;
} // getPos()

void nsShape::Dick::setLength(const unsigned &len) {
    m_length = len;
} // setLength()

const unsigned &nsShape::Dick::getLength() const {
    return m_length;
} // getLength()

void nsShape::Dick::setWidth(const unsigned &w) {
    m_width = w;
} // setWidth()

const unsigned &nsShape::Dick::getWidth() const {
    return m_width;
} // getWidth()

void nsShape::Dick::setDirection(const double &dir) {
    m_direction = fmod(dir, 2*M_PI);
} // setDirection()

const double &nsShape::Dick::getDirection() const {
    return m_direction;
} // getDirection()
