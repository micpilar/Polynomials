// Program do testowania modułu "polynomial".
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
#include "polynomial.h"

using std::vector;
using std::cout;
using std::endl;

void test_add() {
  poly p1;
  p1.push_back(0);
  p1.push_back(1);
  p1.push_back(3.5);
  p1.push_back(0);
  p1.push_back(6);
  p1.push_back(0);

  poly p2;
  p2.push_back(5);
  p2.push_back(6);
  p2.push_back(8);

  poly wynik;
  wynik=add(p1,p2);
  cout<<"Test dodawania:"<<endl;
  cout<<"\tp1(x) = "<<p1<<endl;
  cout<<"\tp2(x) = "<<p2<<endl;
  cout<<"\tp1(x)+p2(x) = "<<wynik<<endl;
}

void test_sub() {
  poly p1;
  p1.push_back(0);
  p1.push_back(1);
  p1.push_back(3.5);
  p1.push_back(0);
  p1.push_back(6);
  p1.push_back(0);

  poly p2;
  p2.push_back(5);
  p2.push_back(6);
  p2.push_back(8);

  poly wynik;
  wynik=sub(p1,p2);
  cout<<"Test odejmowania:"<<endl;
  cout<<"\tp1(x) = "<<p1<<endl;
  cout<<"\tp2(x) = "<<p2<<endl;
  cout<<"\tp1(x)-p2(x) = "<<wynik<<endl;
}

void test_lagrange() {
  vector<double> x,y;
  x.push_back(1);
  y.push_back(2);
  x.push_back(2);
  y.push_back(3);
  x.push_back(3);
  y.push_back(4);
  x.push_back(4);
  y.push_back(5);
  x.push_back(5);
  y.push_back(6);

  poly wynik=lagrange(x,y);
  cout<<"Test interpolacji Lagrange'a:"<<endl;
  for (int i=0;i<x.size();i++) {
    cout<<"\t("<<x[i]<<";"<<y[i]<<") ";
  }
  cout<<endl;
  cout<<"\tWielomian przechodzący przez te punkty: "<<wynik<<endl;
  //cout<<"\tx = "<<x<<endl;
  //cout<<"\ty = "<<y<<endl;
}

void test_mul() {
  poly p1;
  p1.push_back(0);
  p1.push_back(1);
  p1.push_back(3.5);
  p1.push_back(0);
  p1.push_back(6);
  p1.push_back(0);

  poly p2;
  p2.push_back(5);
  p2.push_back(6);
  p2.push_back(8);

  poly wynik;
  wynik=mul(p1,p2);
  cout<<"Test mnożenia:"<<endl;
  cout<<"\tp1(x) = "<<p1<<endl;
  cout<<"\tp2(x) = "<<p2<<endl;
  cout<<"\tp1(x)*p2(x) = "<<wynik<<endl;
}

void test_horner() {
  poly p1;
  p1.push_back(-2);
  p1.push_back(4);
  p1.push_back(-5);
  p1.push_back(2);

  double c=1;
  
  poly wynik;
  double reszta;
  wynik=Horner(p1,c,reszta);
  cout<<"Test schematu Hornera"<<endl;
  cout<<"\tp1(x) = "<<p1<<endl;
  cout<<"\tc = "<<c<<endl;
  cout<<"\tp1(x)/(x-c) = "<<wynik<<endl;
  cout<<"\treszta = "<<reszta<<endl;
}

int main() {
  test_add();
  test_sub();
  test_mul();
  test_lagrange();
  test_horner();
  return 0;
}
