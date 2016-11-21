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
 *  @date 11-12-2010
 */

#include <iostream>

#include <OGRE/Ogre.h>

using std::cout;
using std::endl;

using Ogre::Quaternion;
using Ogre::Real;
using Ogre::Vector3;
using Ogre::Degree;

int main(int argc, char **argv) {
    cout << endl << "EJEMPLO DE CUATERNIOS" << endl;
    cout << "=====================" << endl << endl;
    
    // Varios constructores
    Quaternion q1;                                  //Constructor predeterminado q1 = (1, 0, 0, 0)
    Quaternion q2(1, 0, 0, 0);                      // q2 = (1, 0, 0, 0)
    Quaternion q3(Degree(180), Vector3(0, 1, 0));   // q3 180 grados sobre el eje Y
    Quaternion q4(Degree(90), Vector3(1, 0, 0));    // q4 90 grados sobre el eje X
    
    // Operador de inserción en flujo
    cout << "q1 = " << q1 << endl;
    cout << "q2 = " << q2 << endl;
    cout << "q3 = " << q3 << endl;
    cout << "q4 = " << q4 << endl;
    
    cout << endl << "Operadores básicos" << endl;
    
    // Operadores básicos
    cout << "q3 + q4 = " << q3 + q4 << endl;
    cout << "q3 - q4 = " << q3 - q4 << endl;
    cout << "q3 * 5 = " << q3 * 5 << endl;    
    cout << "q3 * q4 = " << q3 * q4 << endl;        // El producto no es conmutativo
    cout << "q4 * q3 = " << q4 * q3 << endl; 
    
    cout << endl << "Otras operaciones" << endl;
    
    // Otras operaciones
    cout << "Rotación sobre el eje Y de q3 = " << q3.getYaw() << endl;
    cout << "Rotación sobre el eje X de q3 = " << q3.getPitch() << endl;
    cout << "Rotación sobre el eje Y de q4 = " << q4.getYaw() << endl;
    cout << "Rotación sobre el eje X de q4 = " << q4.getPitch() << endl;
    
    cout << endl << "Operadores de comparación" << endl;
    
    if (q3 == q4)
        cout << "q3 == q4" << endl;
    else
        cout << "q3 != q4" << endl;
        
    if (q1 == q2)
        cout << "q2 == q2" << endl;
    else
        cout << "q2 != q2" << endl;
    
    cout << endl;
    
    return 0;
}
