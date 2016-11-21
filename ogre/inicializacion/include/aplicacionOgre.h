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

#ifndef IBEROGRE_EJEMPLOS_OGRE_INICIALIZACION_H_
#define IBEROGRE_EJEMPLOS_OGRE_INICIALIZACION_H

#include <OGRE/Ogre.h>

//! Aplicación básica de Ogre, configura, inicializa y cierra el motor

/**
 * @author David Saltares Márquez
 * @file aplicacionOgre.h
 * @date 31-01-2011
 *
 * Clase que se encarga de configurar Ogre, crear los Logs, iniciar la
 * biblioteca y cerrarla.
 */

class AplicacionOgre {
    public:
        /**
         *  Constructor
         *
         *  Crea la aplicación, configura e inicializa Ogre.
         */
        AplicacionOgre();

        /**
         *  Destruye la aplicación y cierra Ogre.
         */
        ~AplicacionOgre();

        /**
         *  Inicia la aplicación (sólo muestra un mensaje de log en la consola)
         */
        void comenzar();
    private:
        // Objetos Ogre
        Ogre::Root* raiz;
        Ogre::LogManager* gestorLogs;
        Ogre::Log* logSistema;
        Ogre::Log* logJuego;
};

#endif  // IBEROGRE_EJEMPLOS_OGRE_INICIALIZACION_H_
