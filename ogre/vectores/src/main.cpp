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
 *  @file main.cpp
 *  @author David Saltares Márquez
 *  @date 5-11-2010
 */

#include <iostream>

#include <OGRE/Ogre.h>

using std::cout;
using std::endl;

using Ogre::Vector3;
using Ogre::Real;

int main(int argc, char **argv) {
    cout << endl << "EJEMPLO DE VECTORES" << endl;
    cout << "===================" << endl << endl;
    
    // Varios constructores
    Vector3 v1;                     // Predeterminado: v1 = (basura, basura, basura)
    Vector3 v2(3.0f, -1.2f, 7.2f);  // v2 = (3.0, -1.2, 7.2)
    Vector3 v3(1.0f);               // v3 = (1, 1, 1)
    Vector3 v4(v2);                 // v4 = v2
    Vector3 v5(5.0f, 2.3f, -2.4f);
    
    // Operador de inserción en flujo
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v3 = " << v3 << endl;
    cout << "v4 = " << v4 << endl;
    
    cout << endl << "Operadores básicos" << endl;
    
    // Operadores básicos
    cout << "v2 + v3 = " << v2 + v3 << endl;
    cout << "v2 - v3 = " << v2 - v3 << endl;
    cout << "v2 * v3 = " << v2 * v3 << endl;    // Producto componente a componente
    cout << "v2 / v3 = " << v2 / v3 << endl;    // Producto componente a componente
    cout << "3.5 * v2 = " << v2 * 3.5f << endl; // Producto por un escalar
    cout << "v2 / 3.5 = " << v2 / 3.5f << endl; // Cociente por un escalar
    
    cout << endl << "Otras operaciones" << endl;
    
    // Otras operaciones
    cout << "Magnitud v2 = " << v2.length() << endl;
    cout << "Magnitud cuadrada v2 = " << v2.squaredLength() << endl;
    cout << "Distancia v2 y v3 = " << v2.distance(v3) << endl;
    cout << "Distancia cuadrada v2 y v3 = " << v2.squaredDistance(v3) << endl;
    cout << "Producto escalar v2 y v5 = " << v2.dotProduct(v5) << endl;
    cout << "Producto vectorial v2 y v5 = " << v2.crossProduct(v5) << endl;
    cout << "Punto medio v2 y v5 = " << v2.midPoint(v5) << endl;
    cout << "Vector perpendicular a v2 = " << v2.perpendicular() << endl;
    cout << "Ángulo entre v2 y v5 (radianes) = " << v2.angleBetween(v5) << endl;
    
    cout << endl << "Operadores de comparación" << endl;
    
    if (v2 == v3)
        cout << "v2 == v3" << endl;
    else
        cout << "v2 != v3" << endl;
        
    if (v2 < v3)
        cout << "v2 < v3" << endl;
    else if (v2 > v3)
        cout << "v2 > v3" << endl;
    
    cout << endl;
    
    return 0;
}
