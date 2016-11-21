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

#ifndef IBEROGRE_EJEMPLOS_OGRE_NODOS_INCLUDE_PERSONAJE_H_
#define IBEROGRE_EJEMPLOS_OGRE_NODOS_INCLUDE_PERSONAJE_H_

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

class Personaje {
    public:
        //enum Direccion {ARRIBA, ARIBADERECHA, DERECHA, DERECHAABAJO, ABAJO, ABAJOIZQUIERDA, IZQUIERDA, IZQUIERDAARRIBA}
        Personaje();
        ~Personaje();
        void actualizar(OIS::Keyboard* teclado, Ogre::Real deltaT);
        Ogre::SceneNode* getNodo();
        void redimensionar(Ogre::Real cambio);
    private:
        Ogre::SceneNode* nodo;
        Ogre::Entity* entidad;
        Ogre::Vector3 velocidad;
        Ogre::Vector3 posicion;
        Ogre::Degree orientacionActual;
        Ogre::Degree orientacionObjetivo;
        bool girando;
};


#endif  // IBEROGRE_EJEMPLOS_OGRE_NODOS_INCLUDE_PERSONAJE_H_
