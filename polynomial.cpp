// Implementacja modułu "polynomial".
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

#include <iostream>
#include <stdexcept>
#include "polynomial.h"

poly& minimize(poly &a) {
  while (!a.empty() && a.back() == 0.0) {
      a.pop_back();
  }
  return a;
}

int deg(const poly &b) {
  if (b.empty())
    return -1;
  else
    return b.size()-1;
}

poly add(const poly &c,const poly &d) {
  poly wynik;
  for (int i = 0; i <= std::min(deg(c),deg(d)); ++i) {
    wynik.push_back(c[i]+d[i]);
  }
  for (int i = std::min(deg(c),deg(d))+1; i <= std::max(deg(c),deg(d)); ++i) {
    wynik.push_back((deg(c)<deg(d)) ? d[i] : c[i]);
  }
  minimize(wynik);
  return wynik;
}

poly mul(const poly &e,const poly &f) {
  poly wynik;
  for (int k=0 ; k<=deg(e)+deg(f); ++k) {
    double suma=0;
    for (int i=0 ; i<=k ; ++i) {
      if (i<=deg(e) && k-i<=deg(f)) {
        suma += e[i]*f[k-i];
      }
    }
    wynik.push_back(suma);
  }
  minimize(wynik);
  return wynik;
}

poly sub(const poly &c,const poly &d) {
  poly minus1;
  minus1.push_back(-1);
  poly minusd;
  minusd=mul(d,minus1);
  return add(c,minusd);
}

poly lagrange (const std::vector<double> x, const std::vector<double> y) {
  int n=x.size();
  if(y.size()!=x.size())
    throw std::domain_error("x and y must have the same size");
  poly wynik;
  for (int i=0; i<n; ++i) {
    poly iloczyn;
    iloczyn.push_back(1);
    for (int j=0; j<n; ++j) {
      if (i==j)
        continue;
      poly czynnik;
      czynnik.push_back(-x[j]/(x[i]-x[j]));
      czynnik.push_back(1.0/(x[i]-x[j]));
      iloczyn=mul(iloczyn,czynnik);
    }
    poly y_i;
    y_i.push_back(y[i]);
    iloczyn=mul(iloczyn,y_i);
    wynik=add(wynik,iloczyn);
  }
  minimize(wynik);
  return wynik;
}
