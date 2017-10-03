// Program:    1
// Class:      CSCI 3675
// Author:     Josh Weeks
// Date:       9/6/16
// File:       ArithmeticTest.java
// Tabs:       None

//=================================================================
// ArithmeticTest prints the results from each of the funtions that
// exist in Arithmetic.java on the byte arrays A and B
// A represents a binary number as does B, example A = 111 B = 1010
//
// There are 3 functions being tested:
// 1.product(A, B) A*B
// 2.sum(A, B) A+B
// 3.inc(A) A+1
// 
// You will give the size of A and B first then enter the binary
// number itself one at a time, pressing enter after each 1 or 0
//
// print(A) prints the array A
//=================================================================

import java.util.*;
import java.io.*;

public class ArithmeticTest
{
  //=================================================================
  // print(A) prints the byte array A
  //=================================================================
  public static void print(byte[] A)
  {
    int aSize = A.length;
    
    for(int x = aSize - 1; x > -1; x--)
    {
      System.out.print(A[x]);
    }
  }
  
  public static void main(String[] args)
  {
    Scanner keyboard = new Scanner(System.in);
    
    System.out.println("Enter SIZE of FIRST binary number:");
    int aSize = keyboard.nextInt();
    byte[] A = new byte[aSize];
    System.out.println();
    
    System.out.println("Enter SIZE of SECOND binary number:");
    int bSize = keyboard.nextInt();
    byte[] B = new byte[bSize];
    System.out.println();
    
    System.out.println("FIRST binary number: Enter 1 or 0, press ENTER after each 1 or 0 until you reach the size of the binary number:");
    for(int i = aSize - 1; keyboard.hasNextByte() && aSize > 0; i--)
    {
      A[i] = keyboard.nextByte();
      if(i == 0)
      {
        break;
      }
    }
    
    System.out.println("Here is your FIRST binary number:");
    print(A);
    System.out.println("\n");
    
    System.out.println("SECOND binary number: Enter 1 or 0, press ENTER after each 1 or 0 until you reach the size of the binary number:");
    for(int i = bSize - 1; keyboard.hasNextByte() && bSize > 0; i--)
    {
      B[i] = keyboard.nextByte();
      if(i == 0)
      {
        break;
      }
    }
    
    System.out.println("Here is your SECOND binary number:");
    print(B);
    System.out.println("\n");
    
    
    //PRODUCT TESTING*****
    System.out.println("\nPRODUCT*****");
    print(A);
    System.out.println(" * ");
    print(B);
    System.out.println(" = ");
    print(Arithmetic.product(A, B));
    System.out.println("\n");
    
    //SUM TESTING*****
    System.out.println("\nSUM*****");
    print(A);
    System.out.println(" + ");
    print(B);
    System.out.println(" = ");
    print(Arithmetic.sum(A, B));
    System.out.println("\n");
    
    //INCREMENT TESTING*****
    System.out.println("\nINCREMENT*****");
    System.out.println("Array BEFORE increment");
    print(A);
    System.out.println("\nArray AFTER increment");
    print(Arithmetic.inc(A));
    System.out.println();
  }
}
