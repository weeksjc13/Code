// Program:    1
// Class:      CSCI 3675
// Author:     Josh Weeks
// Date:       9/6/16
// File:       Arithmetic.java
// Tabs:       None

//=================================================================
// Arithmetic has three funtions that work as the following:
// Note: all parameters are byte arrays that represent a binary
// number, for example 101010
// The byte array is represented in the array with the low order
// bit at the beginning, for example 010101
// 1.inc(A) returns and array of bits representing A+1
// 2.sum(A,B) returns an array of bits representing A+B
// 3.product(A,B) returns an array of bits representing A*B
//=================================================================

import java.util.*;
import java.io.*;

public class Arithmetic
{
  //=================================================================
  // zeroEliminator(A) eliminates high order zeroes from a byte array
  // that represents a binary number
  // NOTE: 1100 is represent in the array as 0011 (low order bit
  // first)
  // If A = 01100 then 110 will be returned
  //=================================================================
  public static byte[] zeroEliminator(byte[] A)
  {
    int aSize = A.length;
    int bSize;
    int extra = 0;
    boolean allZero = true;
    byte[] B;
    
    //find how extra array space there is
    for(int i = aSize - 1; i > -1; i--)
    {
      if(A[i] == 0)
      {
        extra++;
      }
      else
      {
        allZero = false;
        break;
      }
    }
    
    if(allZero == true)  //if all zeroes then B = [0]
    {
      B = new byte[1];
      B[0] = 0;
      return B;
    }
    else
    {
      bSize = aSize - extra;
      B = new byte[bSize];
    }
    
    //eliminate extra array slots
    for(int i = 0; i < bSize; i++)
    {
      B[i] = A[i];
    }
    
    return B;
  }
  
  //=================================================================
  // inc(A) returns an array of bits representing A+1.
  //=================================================================

  public static byte[] inc(byte[] A)
  {
    int size = A.length;            //size of array A
    byte[] B = new byte[size];      //will hold answer if array is correct size
    byte[] C = new byte[size + 1];  //will hold answer if array size needs to be increased by 1
    int cSize = C.length;           //size of array C
    boolean carry;                  //carry is true if last position changed from 1 to 0
    
    //empty array
    if(size == 0)
    {
      C[0] = 1;
      return C;
    }
    
    //copy A into B
    for(int z = 0; z < size; z++)
    {
      B[z] = A[z];
    }
    
    if(B[0] == 0)               //low order bit is 0
    {
      B[0] = 1;                 //increment
      return zeroEliminator(B);
    }
    else                        //low order bit is 1
    {
      B[0] = 0;                 //low order bit change to 0
      carry = true;             //true if last position changed from 1 to 0
      
      for(int x = 1; carry == true; x++)
      {
        if(x == size)           //carry is true and the end of array has been reached, array needs to be 1 size larger (will use array C for answer)
        {
          //copy B into C
          for(int y = 0; y < cSize - 1; y++)
          {
            C[y] = B[y];
          }
          
          C[cSize - 1] = 1;
          return zeroEliminator(C);
        }
        
        if(B[x] == 1)           //increment, carry stays true
        {
          B[x] = 0;
        }
        else                    //carry becomes false breaks out of loop
        {
          B[x] = 1;
          carry = false;
        }
      }
    }
    return zeroEliminator(B);
  }
  
  

  //=================================================================
  // sum(A,B) returns an array of bits representing A+B.
  //=================================================================

  public static byte[] sum(byte[] A, byte[] B)
  {
    int aSize = A.length;                //size of array A
    int bSize = B.length;                //size of array B
    int cSize = Math.max(aSize, bSize);  //size of answer array (may increase by 1)
    byte[] C = new byte[cSize];          //array C will hold final answer if there IS NO overflow
    byte[] D = new byte[cSize + 1];      //array D will hold final answer if there IS overflow
    int dSize = D.length;                //size of array D
    int sum = 0;                         //sum of current addition column
    int carry = 0;                       //number to be carried to next addition column
    
    for(int x = 0; ; x++)
    {
      sum = 0;             //reset sum
      
      if(carry == 1 && x == cSize)
      {
        //copy C into D
        for(int z = 0; z < cSize; z++)
        {
          D[z] = C[z];
        }
        D[dSize - 1] = 1;  //overflow, make highest order one since the carry is 1
        return zeroEliminator(D);
      }
      
      if(carry == 0 && x == cSize)
      {
        return zeroEliminator(C);
      }
      
      if(x < aSize)        //avoid checking non-existing array index
      { 
        if(A[x] == 1)
        {
          sum++;
        }
      }
      if(x < bSize)        //avoid checking non-existing array index
      {
        if(B[x] == 1)
        {
          sum++;
        }
      }
      
      sum = sum + carry;
      
      //cases used to find the answer byte to store in C[x], also account for carrying a 1 if needed for next sum
      if(sum == 0)
      {
        C[x] = 0;
        carry = 0;
      }
      else if(sum == 1)
      {
        C[x] = 1;
        carry = 0;
      }
      else if(sum == 2)
      {
        C[x] = 0;
        carry = 1;
      }
      else
      {
        C[x] = 1;
        carry = 1;
      } 
    }
  }

  
  
  //=================================================================
  // product(A,B) returns an array of bits representing A*B.
  //=================================================================

  public static byte[] product(byte[] A, byte[] B)
  {
    int sizeA = A.length;        //size of array A
    int sizeB = B.length;        //size of array B
    int sizeC = sizeA + sizeB;   //temporary size of arrays C and D
    byte[] C;                    //temporary array used to add
    byte[] D = new byte[sizeC];  //temporary array used to add
    int zeroes = 0;              //number of zeroes to be tacked onto the low order end of the array (used when adding)
    //int extra = 0;               //number of extra array slots after answer is found
    
    if((sizeA == 1 && A[0] == 0) || (sizeB == 1 && B[0] == 0))  //case for 0*0 and 0*1 = 0
    {
      C = new byte[1];
      C[0] = 0;
      return C;
    }
    
    C = new byte[sizeC];
    
    for(int x = 0; x < sizeA; x++)     //for each A sum must be called once
    {
      for(int y = 0; y < sizeB; y++)   //create C
      {
        if(A[x] == 1)
        {
          C[y + zeroes] = B[y];
        }
        else 
        {
          C[y + zeroes] = 0;
        }
      }
      zeroes++;
      D = sum(C, D);                  //get sum and store in D
      for(int i = 0; i < sizeC; i++)  //zero out C array
      {
        C[i] = 0;
      }
    }
    
    return zeroEliminator(D);
    
    /*
    //find how extra array space there is
    for(int i = sizeC - 1; i > -1; i--)
    {
      if(D[i] == 0)
      {
        extra++;
      }
      else
      {
        break;
      }
    }
    
    int sizeE = sizeC - extra;
    byte[] E = new byte[sizeE];
    
    //eliminate extra array slots
    for(int i = 0; i < sizeE; i++)
    {
      E[i] = D[i];
    }
    
    return E;
    */
  }
}


