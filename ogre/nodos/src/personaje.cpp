#include <iostream>
#include <cmath>

#include <OGRE/OgreMath.h>

#include "personaje.h"

using namespace Ogre;
using namespace OIS;

using std::endl;
using std::cout;

Personaje::Personaje() {
    // Recuperamos el SceneManager
    SceneManager* gestorEscena = Root::getSingleton().getSceneManager("gestorEscena");
    
    // Creamos la entidad y el nodo del personaje
    entidad = gestorEscena->createEntity("Personaje", "personaje.mesh");
    nodo = gestorEscena->getRootSceneNode()->createChildSceneNode();
    nodo->attachObject(entidad);
    nodo->setPosition(0, 0, 0);
    
    // Establecemos posición, velocidad y orientación
    posicion = Ogre::Vector3(0, 0, 0);
    velocidad = Ogre::Vector3(0.05f, 0.05f, 0.05f);
    orientacionActual = Ogre::Degree(0);
    orientacionObjetivo = Ogre::Degree(0);
    
    girando = false;
}

Personaje::~Personaje() {
    // El nodo se destruye automáticamente
}

void Personaje::actualizar(OIS::Keyboard* teclado, Real deltaT) {
    // Según la tecla que pulsemo (WASD) tomamos una orientación objetivo
    // Podemos ir en 8 direcciones
    // Las orientaciones objetivo y actual nos ayudan a girar suavemente
    if (teclado->isKeyDown(KC_W) && teclado->isKeyDown(KC_D)) {
        nodo->translate(velocidad * Ogre::Vector3(0.7, 0, -0.7) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(135);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_W) && teclado->isKeyDown(KC_A)) {
        nodo->translate(velocidad * Ogre::Vector3(-0.7, 0, -0.7) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(225);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_S) && teclado->isKeyDown(KC_D)) {
        nodo->translate(velocidad * Ogre::Vector3(0.7, 0, 0.7) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(45);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_S) && teclado->isKeyDown(KC_A)) {
        nodo->translate(velocidad * Ogre::Vector3(-0.7, 0, 0.7) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(315);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_W)) {
        nodo->translate(velocidad * Ogre::Vector3(0, 0, -1) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(180);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_S)) {
        nodo->translate(velocidad * Ogre::Vector3(0, 0, 1) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(0);
        girando = true;
    }
    else if (teclado->isKeyDown(KC_D)) {
        nodo->translate(velocidad * Ogre::Vector3(1, 0, 0) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(90);
        girando = true;
    } 
    else if (teclado->isKeyDown(KC_A)){
        nodo->translate(velocidad * Ogre::Vector3(-1, 0, 0) * deltaT, Node::TS_WORLD);
        orientacionObjetivo = Ogre::Degree(270);
        girando = true;
    }
    
    // Si estamos girando para orientarnos hacia una dirección
    if (girando) {
        // Evitamos tomar el camino más largo
        if(std::abs(orientacionActual.valueDegrees() - orientacionObjetivo.valueDegrees()) > 180){
            if(orientacionObjetivo > orientacionActual){
                orientacionActual += Ogre::Degree(360);
            }else{
                orientacionActual -= Ogre::Degree(360);
            }
        }
        
        // Si sólo nos quedan 5 grados de diferencia, paramos el giro
        if (std::abs(orientacionActual.valueDegrees() - orientacionObjetivo.valueDegrees()) < 5) {
            orientacionActual = orientacionObjetivo;
            girando = false;
        }
        
        // Actualizamos la orientación actual
        orientacionActual = orientacionActual + (orientacionObjetivo - orientacionActual) / (100 / deltaT);
            
        // Orientamos el nodo según la orientación actual (parcial)
        nodo->setOrientation(Ogre::Quaternion(orientacionActual, Ogre::Vector3(0, 1, 0)));
    }
    cout << "Orientacion = " << nodo->getOrientation() << endl;
}

Ogre::SceneNode* Personaje::getNodo() {
    return nodo;
}

void Personaje::redimensionar(Ogre::Real cambio) {
    nodo->setScale(nodo->getScale() + Ogre::Vector3(cambio, cambio, cambio));
}
