// CSCI 3300
// Assignment: 0
// Author:     Karl Abrahamson
// File:       assn0.cpp
// Tab stops:  none

/* This program shows the greatest common divisor
   of two numbers that are read from the user.
*/

#include <cstdio>
using namespace std;

//===========================================
//             gcd
//===========================================
// gcd(a,b) returns the greatest common
// divisor of a and b.
//===========================================

long gcd(long a, long b)
{
  if(a == 0)
  {
    return b;
  }
  else
  {
    return gcd(b % a, a);
  }
}

//===========================================
//               main
//===========================================

int main(int argc, char** argv)
{
  long a, b;

  printf("gcd of which two numbers? ");
  if(scanf("%li%li", &a, &b) == 2)
  {
    printf("The gcd of %li and %li is %li.\n", a, b, gcd(a,b));
  }
  return 0;
}

