/**
 * This file is part of IberOgre examples.
 *
 * IberOgre examples are free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License ad
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) ant later version.
 *
 * IberOgre examples are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IberOgre examples.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <utility>

#include <OGRE/Ogre.h>

#include "escenaSimple.h"

/**
 * @author David Saltares Márquez
 * @file escenaSimple.cpp
 * @date 17-11-2010
 */

using std::cout;
using std::endl;

EscenaSimple::EscenaSimple(): AplicacionOgre("OGRE - Particulas") {
    configurarSceneManager();
    crearCamara();
    prepararRecursos();
    cargarParticulas();
    crearEscena();
    iniciarTemporizador();
}

EscenaSimple::~EscenaSimple() {
    delete temporizador;
}

void EscenaSimple::prepararRecursos() {
    Ogre::String nombreGrupo, nombreTipo, nombreArchivo;
    Ogre::ConfigFile ficheroConfig;
 
    // Abrimos el fichero de recursos
    ficheroConfig.load("resources.cfg");
 
    // Iterador para recorrer grupos
    Ogre::ConfigFile::SectionIterator iteradorGrupo = ficheroConfig.getSectionIterator();
 
    // Mientras haya grupos
    while (iteradorGrupo.hasMoreElements()) {
        // Tomamos el nombre del grupo
        nombreGrupo = iteradorGrupo.peekNextKey();
 
        // Vamos a recorrer los archivos del grupo
        Ogre::ConfigFile::SettingsMultiMap *opciones = iteradorGrupo.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
 
        for (i = opciones->begin(); i != opciones->end(); ++i) {
            nombreTipo = i->first;
            nombreArchivo = i->second;
            
            cout << "Archivo: " << nombreArchivo << endl;
            cout << "Tipo: " << nombreTipo << endl;
 
            // Añadimos la localización del archivo con su nombre, su tipo y grupo
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(nombreArchivo,
                                                                           nombreTipo,                                                                     
                                                                           nombreGrupo);
        }
    }
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void EscenaSimple::configurarSceneManager() {
    // Creamos un SceneManager genérico
    gestorEscena = raiz->createSceneManager(Ogre::ST_GENERIC, "gestorEscena");
    
    // Elegimos el tipo de sombra
    gestorEscena->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void EscenaSimple::crearCamara() {
    // Creamos y configuramos la cámara
    camara = gestorEscena->createCamera("camara");
    camara->setNearClipDistance(5);
    camara->setFarClipDistance(1000);
    camara->setPosition(0, 15, 125);
     
    // Añadimos un Viewport
    viewport = ventana->addViewport(camara);

    // Adaptamos la proporción de la cámara para que encaje con el viewport
    camara->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
                           Ogre::Real(viewport->getActualHeight()));
                            
    camaraNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("camaraNodo");
    camaraNodo->attachObject(camara);
}

void EscenaSimple::crearEscena() {
    // Luz ambiente
    gestorEscena->setAmbientLight(Ogre::ColourValue(0, 0, 0));

    // Punto de luz 1
    luzPunto1 = gestorEscena->createLight("luzPunto1");
    luzPunto1->setType(Ogre::Light::LT_POINT);
    luzPunto1->setPosition(-4, 10, 1);
    luzPunto1->setSpecularColour(0.2, 0.2, 0.2); // Blanca
    luzPunto1->setDiffuseColour(0.2, 0.2, 0.2);

    // Punto de luz 2
    luzPunto2 = gestorEscena->createLight("luzPunto2");
    luzPunto2->setType(Ogre::Light::LT_POINT);
    luzPunto2->setPosition(4, 10, -1);
    luzPunto2->setSpecularColour(0.1, 0.1, 0.1); // Blanca
    luzPunto2->setDiffuseColour(0.1, 0.1, 0.1);

    // Punto de luz 2
    luzPunto3 = gestorEscena->createLight("luzPunto3");
    luzPunto3->setType(Ogre::Light::LT_POINT);
    luzPunto3->setPosition(5, 10, 10);
    luzPunto3->setSpecularColour(0.1, 0.1, 0.1); // Blanca
    luzPunto3->setDiffuseColour(0.1, 0.1, 0.1);

    // Partículas por defecto
    particulas = gestorEscena->createParticleSystem("PEExamples/space", "PEExamples/space");
    nodoParticulas = gestorEscena->getRootSceneNode()->createChildSceneNode("nodoParticulas");
    nodoParticulas->attachObject(particulas);
    
     // Creamos un SkyDome
    gestorEscena->setSkyDome(true, "cielo", 50, 1.5, 5000, true);
}

void EscenaSimple::iniciarTemporizador() {
    temporizador = new Ogre::Timer;
    ultimoFrame = 0.0f;
    deltaT = 0.0;
}

void EscenaSimple::buclePrincipal() {
 
    // Lanzamos el timer
    temporizador->reset();
    
    // Mientras no se cierre la ventana
    while (!salir) {
        // Actualizamos la entrada
        teclado->capture();
        raton->capture();
        
        // Sacamos todos los eventos de ventana de la pila
        Ogre::WindowEventUtilities::messagePump();
        
        // Renderizamos la escena
        raiz->renderOneFrame();
        
        // Calculamos deltaT
        deltaT = temporizador->getMilliseconds() - ultimoFrame;
        ultimoFrame = temporizador->getMilliseconds();
    }
}


bool EscenaSimple::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
        salir = true;
    
    // Buscamos la tecla en el diccionario de teclas
    std::map<OIS::KeyCode, Ogre::String>::iterator i;
    i = teclasParticulas.find(arg.key);
    
    // Si la encontramos, destruimos el sistema actual y cargamos el siguiente
    if (i != teclasParticulas.end()) {
        cout << "Cambiamos al sistema de partículas " << i->second << endl;
        
        // Desvinculamos la partícula actual
        nodoParticulas->detachObject(particulas);
        
        // Destruimos el sistema actual
        gestorEscena->destroyParticleSystem(particulas);
        
        // Cargamos el nuevo sistema
        particulas = gestorEscena->createParticleSystem(i->second, i->second);
        
        // Adjuntamos el sistema al nodo
        nodoParticulas->attachObject(particulas);
    }

    return true;
}

void  EscenaSimple::cargarParticulas() {
    teclasParticulas[OIS::KC_1] = "PEExamples/blast";
    teclasParticulas[OIS::KC_2] = "PEExamples/blast2";
    teclasParticulas[OIS::KC_3] = "PEExamples/eruption";
    teclasParticulas[OIS::KC_4] = "PEExamples/pentagram";
    teclasParticulas[OIS::KC_5] = "PEExamples/flow";
    teclasParticulas[OIS::KC_6] = "PEExamples/flame";
    teclasParticulas[OIS::KC_7] = "PEExamples/floatyGreeny";
    teclasParticulas[OIS::KC_8] = "PEExamples/ringOfFire";
    teclasParticulas[OIS::KC_9] = "PEExamples/space";
}
