// Plik nagłówkowy modułu "polynomial".
//
// Copyright (C) 2023 by Michał Pilarczyk.
//
// This is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this software; see the file "LICENSE". If not,
// please, see <https://www.gnu.org/licenses/>.

// Started on 14.10.2023. Last revision: 15.10.2023.

#pragma once
#include <vector>

// Wielomian jest reprezentowany przez vector<double> który zawiera współczynniki wielomianu od a0 do an. Przykładowo [1,3,6] znaczy 1+3x+6x^2.
// UWAGA: wielomian całkowicie zerowy (w=0) ma stopień -nieskończoność, jednak w tym programie output musi być liczbą całkowitą, więc nadam mu stopień -1.

typedef std::vector<double> poly;


poly& minimize(poly &b); //minimalizuje reprezentację wielomianu (usuwa zera z tyłu)
int deg(const poly &a); //zwraca stopień wielomianu
poly add(const poly &c,const poly &d); //zwraca wektor będący reprezentacją wielomianu sumy dwóch wielomianów
poly sub(const poly &e,const poly &f); //zwraca wektor będący reprezentacją wielomianu różnicy dwóch wielomianów
poly mul(const poly &g,const poly &h); //zwraca wektor będący reprezentacją wielomianu mnożenia dwóch wielomianów
poly lagrange(const std::vector<double> x, const std::vector<double> y); //zwraca wektor będący reprezentacją wielomianu interpolyjnego obliczonego według wzorów Lagrange'a; wartości wielomianu w punktach x[i] wynoszą y[i]

template <typename STREAM>
STREAM &operator<<(STREAM &s, const poly &p)
{
  bool wypisane=false;
  for (int i=0;i<=deg(p);++i) {
    if(p[i]==0)
      continue;
    if(wypisane)
      s<<"+";
    s<<p[i];
    if (i>1)
      s<<"*x^"<<i;
    if(i==1)
      s<<"*x";
    wypisane=true;
  }
  if(!wypisane)
    s<<"0";
  return s;
}
