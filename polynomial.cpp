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

// Started on 14.10.2023. Last revision: 02.11.2023.

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
  if (b.empty()||(b.size()==1&&b.front()==0.0))
    return -1;
  else
    return b.size()-1;
}

double evaluate(const poly &a, double x) {
  double result = 0.0;
  for (int i = 0; i < a.size(); i++) {
    result += a[i] * pow(x, i);
  }
  return result;
}

intpoly convert(const poly &a) {
  intpoly result;
  for (int i = 0; i < a.size(); i++) {
    if (floor(a[i])!=a[i])
      throw std::domain_error("non-integer coefficient");
    result.push_back(a[i]);
  }
  return result;
}

poly unconvert(const intpoly &a) {
  poly result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(static_cast<double>(a[i]));
  }
  return(result);
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

poly Horner(const poly &a, double c, double &b) { //zmienić na poly
  if (deg(a)==-1)
    throw std::domain_error("empty polynomial");
  if (deg(a)==0)
    throw std::domain_error("polynomial has no roots");
  int n=deg(a);
  poly result(n);
  //std::cout<<a.size()<<result.size()<<std::endl;
  result.at(n-1)=a.at(n);
  for (int k=2;k<=n;++k) {
    result.at(n-k)=(a.at(n-(k-1))+c*result.at(n-(k-1)));
  }
  b=a.at(0)+c*result.at(0);
  result=minimize(result);
  return result;
}
