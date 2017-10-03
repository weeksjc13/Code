// CSCI 3300
// Assignment: 2b
// Author:     Josh Weeks
// File:       hailstone.cpp
// Tab stops:  none

//===========================================
//            hailstone program
//===========================================
//Takes an int from the user, n, and returns  
//several statistics about the hailstone
//sequence.
//
//The next number in a hailstone sequence
//when the previous number is even is n/2.
//When the previous number is odd 3*n+1.
//===========================================

#include <cstdio>
#include <algorithm>
using namespace std;

//===========================================
//                next
//===========================================
//next(n) returns next value in the hailstone 
//sequence that follows n
//===========================================

int next(int n)
{
  if (n % 2 == 0)
  {
    return n / 2;
  }
  else
  {
    return 3 * n + 1;
  }
}

//===========================================
//                hailOut
//===========================================
//hailOut(n) prints the hailstone sequence 
//to the standard output
//===========================================

void hailOut(int n)
{
  if(n > 1)
  {
    printf("%i ", n);
    hailOut(next(n));
  }
  else
  {
    printf("1 ");
    return;
  }
}

//===========================================
//                hailLength
//===========================================
//hailLength(n) returns the length of the 
//hailstone sequence starting at n
//===========================================

int hailLength(int n)
{
  if(n == 1)
  {
    return 1;
  }
  else
  {
    return hailLength(next(n)) + 1;;
  }
}

//===========================================
//                hailLargest
//===========================================
//hailLargest(n) returns the largest value of 
//the hailstone sequence starting at n
//===========================================

int hailLargest(int n)
{
  if(n == 1)
  {
    return 1;
  }
  else
  {
    return max(hailLargest(next(n)), n);
  }
}

//===========================================
//                hailMaximaHelper
//===========================================
//hailMaximaHelper(n, prev) returns the
//number of local maxima of the hailstone 
//sequence starting at n
//Assume: prev comes before n
//===========================================

int hailMaximaHelper(int n, int prev)
{
  if(n == 1)
  {
    return 0;
  }
  else if(n > next(n) && n > prev)
  {
    return hailMaximaHelper(next(n), n) + 1;
  }
  else
  {
    return hailMaximaHelper(next(n), n);
  }
}

//===========================================
//                hailMaxima
//===========================================
//hailMaxima(n) returns the number of local 
//maxima
//===========================================

int hailMaxima(int n)
{
  return hailMaximaHelper(next(n), n);
}

//===========================================
//                hailLargestLength
//===========================================
//hailLargestLength(n) returns the largest 
//possible length of a sequence that starts
//from 1 to n
//===========================================

int hailLargestLength(int n)
{
  if(n == 1)
  {
    return 1;
  }
  else
  {
    return max(hailLargestLength(n-1), hailLength(n));
  }
}

//===========================================
//                main
//===========================================

int main()
{
  int n = 0;
  printf("What number shall I start with? ");
  scanf("%i", &n);
  
  printf("The hailstone sequence starting at %i is:\n", n);
  hailOut(n);
  
  printf("\nThe length of the squence is %i.\n", hailLength(n));
  
  printf("The largest number of the sequence is %i.\n", hailLargest(n));
  
  printf("There are %i local maxima.\n", hailMaxima(n));

  printf("The longest hailstone sequence starting with a number up to %i has length %i.\n", n, hailLargestLength(n));
  
  return 0;
}
