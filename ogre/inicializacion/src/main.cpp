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
 *  @date 31-01-2011
 */

#include "aplicacionOgre.h"

int main(int argc, char **argv) {
    AplicacionOgre* aplicacionOgre;
    aplicacionOgre = new AplicacionOgre();

    aplicacionOgre->comenzar();

    delete aplicacionOgre;
}

