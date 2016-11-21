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

#include <OGRE/Ogre.h>

#include "escenaSimple.h"

/**
 * @author David Saltares Márquez
 * @file escenaSimple.cpp
 * @date 17-11-2010
 */

using std::cout;
using std::endl;

EscenaSimple::EscenaSimple(): AplicacionOgre("OGRE - Sonido") {
    configurarSceneManager();
    crearCamara();
    prepararRecursos();
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
    camara->setPosition(6, 3.5, 14);
    camara->lookAt(0, 0, 0);
     
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
    
    // Cargamos sonido
    SoundFXManager* gestorSonido = SoundFXManager::getSingletonPtr();
    SongManager* gestorMusica = SongManager::getSingletonPtr();
    
    risas = gestorSonido->load("risa.wav");
    aplausos = gestorSonido->load("aplauso.wav");
    abucheos = gestorSonido->load("abucheo.wav");
    
    inicio = gestorMusica->load("inicio.ogg");
    final = gestorMusica->load("final.ogg");
    melodia = gestorMusica->load("melodia.ogg");
    
    // Cargamos escenario
    cartel = gestorEscena->createEntity("cartel", "cartel.mesh");
    cartelNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("cartelNodo");
    cartelNodo->attachObject(cartel);
    
    suelo = gestorEscena->createEntity("suelo", "suelo.mesh");
    sueloNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("sueloNodo");
    sueloNodo->attachObject(suelo);
    
    escenario = gestorEscena->createEntity("escenario", "escenario.mesh");
    escenarioNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("escenarioNodo");
    escenarioNodo->attachObject(escenario);
    
    plano1 = gestorEscena->createEntity("plano1", "plano1.mesh");
    plano1Nodo = gestorEscena->getRootSceneNode()->createChildSceneNode("plano1Nodo");
    plano1Nodo->attachObject(plano1);
    
    plano2 = gestorEscena->createEntity("plano2", "plano2.mesh");
    plano2Nodo = gestorEscena->getRootSceneNode()->createChildSceneNode("plano2Nodo");
    plano2Nodo->attachObject(plano2);
    
    plano3 = gestorEscena->createEntity("plano3", "plano3.mesh");
    plano3Nodo = gestorEscena->getRootSceneNode()->createChildSceneNode("plano3Nodo");
    plano3Nodo->attachObject(plano3);
    
    silla = gestorEscena->createEntity("silla", "silla.mesh");
    sillaNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("sillaNodo");
    sillaNodo->attachObject(silla);
    
    micro = gestorEscena->createEntity("micro", "micro.mesh");
    microNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("microNodo");
    microNodo->attachObject(micro);
    
    // Punto de luz 1
    luzPunto1 = gestorEscena->createLight("luzPunto1");
    luzPunto1->setType(Ogre::Light::LT_POINT);
    luzPunto1->setPosition(-4.16, 2.28, 5.236);
    luzPunto1->setSpecularColour(0.6, 0.6, 0.2); // Amarilla
    luzPunto1->setDiffuseColour(0.6, 0.6, 0.2);

    // Punto de luz 2
    luzPunto2 = gestorEscena->createLight("luzPunto2");
    luzPunto2->setType(Ogre::Light::LT_POINT);
    luzPunto2->setPosition(5.207, 2.28, 5.650);
    luzPunto2->setSpecularColour(0.6, 0.6, 0.6); // Blanca
    luzPunto2->setDiffuseColour(1, 1, 1);

    // Punto de luz 3
    luzDir = gestorEscena->createLight("luzPunto3");
    luzDir->setType(Ogre::Light::LT_SPOTLIGHT);
    luzDir->setDirection(0, 0, 0);
    luzDir->setPosition(-4, 3, 0);
    luzDir->setSpecularColour(0.1, 0.1, 0.2); // Azul
    luzDir->setDiffuseColour(0.1, 0.1, 0.2);
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
    
    // Comprobamos pulsaciones para música y sonidos
    else if (arg.key == OIS::KC_1)
        inicio->play();
    else if (arg.key == OIS::KC_2)
        melodia->play();
    else if (arg.key == OIS::KC_3)
        final->play();
    else if (arg.key == OIS::KC_4)
        aplausos->play();
    else if (arg.key == OIS::KC_5)
        risas->play();
    else if (arg.key == OIS::KC_6)
        abucheos->play();
    
    return true;
}
