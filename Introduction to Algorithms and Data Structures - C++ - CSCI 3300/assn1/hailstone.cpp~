// CSCI 3300
// Assignment: 1b
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
using namespace std;

//===========================================
//                next
//===========================================
//next(n) returns next value in the hailstone 
//sequence that follows n
//===========================================

int next(int n)
{
  int x = n;
  
  if (x % 2 == 0)
  {
    return x / 2;
  }
  else
  {
    return 3 * x + 1;
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
  for(int x = n; x > 1; x = next(x))
  {
    printf("%i ", x);
  }
  printf("1 ");
}

//===========================================
//                hailLength
//===========================================
//hailLength(n) returns the length of the 
//hailstone sequence starting at n
//===========================================

int hailLength(int n)
{
  int count = 1;
  int x = n;
  
  while(x > 1)
  {
    x = next(x);
    count++;
  }
  return count;
}

//===========================================
//                hailLargest
//===========================================
//hailLargest(n) returns the largest value of 
//the hailstone sequence starting at n
//===========================================

int hailLargest(int n)
{
  int ans = n;
  int x = n;
  
  while(x != 1)
  {
    if(ans <= x)
    {
      ans = x;
    }
    x = next(x);
  }
  return ans; 
}

//===========================================
//                hailMaxima
//===========================================
//hailMaxima(n) returns the number of local 
//maxima in the hailstone sequence starting
//at n
//===========================================

int hailMaxima(int n)
{
  int prev = n;
  int count = 0;
  
  for(int x = n; x != 1; x = next(x))
  {
    if(x > next(x) && x > prev)
    {
      count++;
    }
    prev = x;
  }
  return count;
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
  int x = n;
  int ans = hailLength(x);
  
  if(x == 1)
  {
    return 1;
  }
  
  while(x > 1)
  {
    if(ans <= hailLength(x))
    {
      ans = hailLength(x);
    }
    x = x - 1;
  }
  return ans;
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
  
  printf("\nThe length of the sequence is %i.\n", hailLength(n));
  
  printf("The largest number of the sequence is %i.\n", hailLargest(n));
  
  printf("There are %i local maxima.\n", hailMaxima(n));

  printf("The longest hailstone sequence starting with a number up to %i has length %i.\n", n, hailLargestLength(n));
  
  return 0;
}
