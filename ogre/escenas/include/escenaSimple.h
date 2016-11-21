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

#ifndef IBEROGRE_EJEMPLOS_OGRE_ESCENAS_H_
#define IBEROGRE_EJEMPLOS_OGRE_ESCENAS_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>

#include "aplicacionOgre.h"


//! Clase para crear una escena simple de ejemplo con Ogre

/**
 * @author David Saltares Márquez
 * @file escenaSimple.h
 * @date 17-11-2010
 *
 * Clase descendiente de AplicacionOgre que se encarga de crear una escena
 * simeple con un modelo y una luz. Ejemplo para el articulo "Creación
 * básica de escenas".
 */
class EscenaSimple: public AplicacionOgre {
    public:
        /**
         *  Constructor
         * 
         *  Se inicializa Ogre y crea una escena básica
         */
        EscenaSimple();
        
        /**
         *  Destructor
         * 
         *  Cierra Ogre y sale de la aplicación
         */
        ~EscenaSimple();
        
        /**
         *  Bucle principal
         * 
         *  Inicia el bucle principal, comienza a renderizar y capturar
         *  eventos hasta que el usuario cierra la aplicación
         */
         void buclePrincipal();
        
    private:
        // Objetos Ogre
        Ogre::Camera* camara;
        Ogre::Viewport* viewport;
        Ogre::SceneManager* gestorEscena;
        
        // Fichero de recursos
        Ogre::String recursosCfg;
        
        // Nombre aplicación
        Ogre::String nombreVentana;
        
        // Entidad y nodo
        Ogre::Entity* entidadPersonaje;
        Ogre::SceneNode* nodoPersonaje;
        
        // Luz
        Ogre::Light* luzPrincipal;
    
        void prepararRecursos();
        void configurarSceneManager();
        void crearCamara();
        void crearEscena();
};

#endif
