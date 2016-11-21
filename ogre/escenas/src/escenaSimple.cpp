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

#include "escenaSimple.h"

/**
 * @author David Saltares Márquez
 * @file escenaSimple.cpp
 * @date 17-11-2010
 */

using std::cout;
using std::endl;

EscenaSimple::EscenaSimple(): AplicacionOgre("OGRE - Creacion basica de escenas") {
    configurarSceneManager();
    crearCamara();
    prepararRecursos();
    crearEscena();
}

EscenaSimple::~EscenaSimple() {}

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
    gestorEscena = raiz->createSceneManager(Ogre::ST_GENERIC);
    
    // Elegimos el tipo de sombra
    gestorEscena->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void EscenaSimple::crearCamara() {
     // Creamos y configuramos la cámara
     camara = gestorEscena->createCamera("camara");
     camara->setNearClipDistance(5);
     camara->setFarClipDistance(1000);
     camara->setPosition(15, 15, 15);
     camara->lookAt(0, 0, 0);
     
     // Añadimos un Viewport
     Ogre::Viewport* viewport = ventana->addViewport(camara);
     viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

     // Adaptamos la proporción de la cámara para que encaje con el viewport
     camara->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
                            Ogre::Real(viewport->getActualHeight()));
}

void EscenaSimple::crearEscena() {
    // Luz ambiente
    gestorEscena->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
    
    // Creamos al personaje
    entidadPersonaje = gestorEscena->createEntity("Personaje", "personaje.mesh");
    nodoPersonaje = gestorEscena->getRootSceneNode()->createChildSceneNode();
    nodoPersonaje->attachObject(entidadPersonaje);
    nodoPersonaje->setPosition(0, 0, 0);
    
    // Preparamos la luz
    luzPrincipal = gestorEscena->createLight("LuzPrincipal");
    luzPrincipal->setPosition(20, 80, 50);
}

void EscenaSimple::buclePrincipal() {
    // Mientras no se cierre la ventana
    while (!salir) {
        // Actualizamos la entrada
        teclado->capture();
        raton->capture();
        
        // Sacamos todos los eventos de ventana de la pila
        Ogre::WindowEventUtilities::messagePump();
        
        // Renderizamos la escena
        raiz->renderOneFrame();
    }
}
