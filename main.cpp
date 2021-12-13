#define FPS_LIMIT 60

#include <iostream>
#include <cmath>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/gui/glut_font.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/triangle.h"
#include "mingl/gui/text.h"
#include "mingl/gui/sprite.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;
using namespace nsGui;

int main() {
    // Initialise le système
    MinGL window("S102", Vec2D(800, 600), Vec2D(850, 80), KBlack);
    window.initGlut();
    window.initGraphic();

    // Création des objets


    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine nos objets


        // On finit la frame en cours
        window.finishFrame();

        // On clear le buffer
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
