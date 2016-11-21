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

/**
 * @author David Saltares Márquez
 * @file aplicacionOgre.cpp
 * @date 31-01-2011
 */

#include "aplicacionOgre.h"


AplicacionOgre::AplicacionOgre() {
    // Elegimos el fichero plugins (según Debug o Release)
#ifdef _DEBUG
    Ogre::String pluginsCfg = "pluginsDebug.cfg";
#else
    Ogre::String pluginsCfg = "plugins.cfg";
#endif

    // Ficheros de configuración y de logging
    Ogre::String ogreCfg = "ogre.cfg";
    Ogre::String nombreLogSistema = "ogre.log";
    Ogre::String nombreLogJuego = "logJuego.log";

    // Creamos el gestor de logs
    gestorLogs = new Ogre::LogManager();

    // Creamos el log del sistema
    logSistema = gestorLogs->createLog(nombreLogSistema, true, false, false);

    // Creamos el log de juego
    logJuego = gestorLogs->createLog(nombreLogJuego, false, true, false);

    // Creamos el objeto principal de Ogre, la raíz
    raiz = new Ogre::Root(pluginsCfg, ogreCfg);

    // Diálogo para configurar Ogre
    if (!raiz->restoreConfig() && !raiz->showConfigDialog()) {
        logJuego->logMessage("AplicacionOgre::iniciarOgre(): El usuario ha cancelado el diálogo de configuración");
        exit(1);
    }

    // Inicializamos Ogre sin crear una ventana
    raiz->initialise(false);
}


AplicacionOgre::~AplicacionOgre() {
    // Al destruir la raíz, cerramos Ogre de manera limpia
    delete raiz;
}

void AplicacionOgre::comenzar() {
    // Mostramos un mensaje y terminamos
    logJuego->logMessage("AplicacionOgre::comenzar(): Se ha iniciado Ogre correctamente");
    logJuego->logMessage("AplicacionOgre::comenzar(): Nos disponemos a terminar");
}

