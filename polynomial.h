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
