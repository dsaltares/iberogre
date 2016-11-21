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
#include <cstdio>
#include <cstring>

#include <OGRE/Ogre.h>

#include "escenaSimple.h"

/**
 * @author David Saltares Márquez
 * @file escenaSimple.cpp
 * @date 17-11-2010
 */

using std::cout;
using std::endl;

EscenaSimple::EscenaSimple(): AplicacionOgre("OGRE - Overlays") {
    configurarSceneManager();
    crearCamara();
    prepararRecursos();
    crearEscena();
    iniciarTemporizador();
    iniciarDiccionarioMateriales();
    configurarOverlay();
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
    Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("General");
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
    camara->setPosition(6, 6, 8);
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
    gestorEscena->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    
    // Creamos el escenario
    escenarioNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("escenarioNodo");
    escenario = gestorEscena->createEntity("escenario", "plano.mesh");
    escenarioNodo->attachObject(escenario);
    
    // Creamos la bola
    bolaNodo = gestorEscena->getRootSceneNode()->createChildSceneNode("bolaNodo");
    bola = gestorEscena->createEntity("bola", "bola.mesh");
    bola->setMaterialName("verdeBrillo");
    bolaNodo->attachObject(bola);

    // Punto de luz 1
    luzPunto1 = gestorEscena->createLight("luzPunto1");
    luzPunto1->setType(Ogre::Light::LT_POINT);
    luzPunto1->setPosition(-4, 10, 1);
    luzPunto1->setSpecularColour(0.7, 0.7, 0.7); // Blanca
    luzPunto1->setDiffuseColour(0.7, 0.7, 0.7);

    // Punto de luz 2
    luzPunto2 = gestorEscena->createLight("luzPunto2");
    luzPunto2->setType(Ogre::Light::LT_POINT);
    luzPunto2->setPosition(4, 10, -1);
    luzPunto2->setSpecularColour(0.3, 0.3, 0.3); // Blanca
    luzPunto2->setDiffuseColour(0.3, 0.3, 0.3);

    // Punto de luz 2
    luzPunto3 = gestorEscena->createLight("luzPunto3");
    luzPunto3->setType(Ogre::Light::LT_POINT);
    luzPunto3->setPosition(5, 10, 10);
    luzPunto3->setSpecularColour(0.5, 0.5, 0.5); // Blanca
    luzPunto3->setDiffuseColour(0.5, 0.5, 0.5);


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
        
        // Actualizamos caption fpsInfo
        Ogre::Real fps = 1000.0 / deltaT;
        char strFPS[10];
        sprintf(strFPS, "%.2f", fps);
        fpsInfo->setCaption(Ogre::String("FPS: ") + Ogre::String(strFPS));
    }
}


bool EscenaSimple::keyPressed(const OIS::KeyEvent &arg) {
    if (arg.key == OIS::KC_ESCAPE)
        salir = true;
    
    // Buscamos la tecla en el diccionario de teclas
    std::map<OIS::KeyCode, Ogre::String>::iterator i;
    i = teclasMateriales.find(arg.key);
    
    // Si la encontramos, cambiamos de material
    if (i != teclasMateriales.end()) {
        cout << "Cambiamos al material " << i->second << endl;
        bola->setMaterialName(i->second);
        materialInfo->setCaption(Ogre::String("Material: ") + i->second);
    }

    return true;
}

void EscenaSimple::iniciarDiccionarioMateriales() {
    // Rellenamos el diccionario de teclas a nombre de materiales
    teclasMateriales[OIS::KC_1] = "verdeBrillo";
    teclasMateriales[OIS::KC_2] = "amarilloBrilloAlto";
    teclasMateriales[OIS::KC_3] = "rojoBrillo";
    teclasMateriales[OIS::KC_4] = "mundo";
    teclasMateriales[OIS::KC_5] = "mundoBrillo";
}

void EscenaSimple::configurarOverlay() {
    // Tomamos el overlay
    gestorOverlay = Ogre::OverlayManager::getSingletonPtr();
    
    // Recuperamos los elementos del overlay
    overlay = gestorOverlay->getByName("OverlayInfo");
    panelInfo = static_cast<Ogre::PanelOverlayElement*>(gestorOverlay->getOverlayElement("panelInfo"));
    tituloInfo = static_cast<Ogre::TextAreaOverlayElement*>(gestorOverlay->getOverlayElement("tituloInfo"));
    materialInfo = static_cast<Ogre::TextAreaOverlayElement*>(gestorOverlay->getOverlayElement("materialInfo"));
    fpsInfo = static_cast<Ogre::TextAreaOverlayElement*>(gestorOverlay->getOverlayElement("fpsInfo"));

    
    if (overlay->isInitialised())
        cout << "Overlay inicializado" << endl;
    else
        cout << "Overlay no inicializado" << endl;
    
    // Mostramos el overlay
    overlay->show();
}
