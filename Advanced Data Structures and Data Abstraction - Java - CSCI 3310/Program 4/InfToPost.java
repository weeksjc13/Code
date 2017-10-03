// CSCI 3310
// Program:    4
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       11/18/15
// File:       InfToPost.java

// InfToPost reads an infix expression then prints the postfix and result
// of the evaluation of the postfix expression.
// There are two parts of input:
// PART1: letters A-Z can be assigned values using the input format: D = 15
// Any letters not assigned a value will have an initial value: A = 1,
// B = 2, C = 3, ... Z = 26.
// When done assigning values $PART2 will begin part 2 of the input.
// PART2: Infix expressions can be input using the following format: C-(B+(C+(A-E)))-X
// The give infix will produce the postfix and the result (result according to the
// values assigned in PART1)
// ASSUMPTIONS:
// 1. all input is correctly formatted
// PART1: <letter><asst_op><number> example: D = 15
// PART2: example: C-(B+(C+(A-E)))-X
// 2. no attempts to divide by 0
// 3. Any letters not assigned a value will have an initial value: A = 1,
// B = 2, C = 3, ... Z = 26.

import java.io.*;
import java.util.*;

public class InfToPost
{
  public static final Stack <Character> opStack = new Stack<Character>();  //holds operators until needed
  public static final Stack <Integer> operandsStack = new Stack<Integer>();  //holds operands until needed

  
  // int addr(char ch) returns the equivalent integer address for the letter
  // given in ch, 'A' returns 0, 'Z' returns 25 and all other letters return
  // their corresponding position as well.
  public static int addr(char ch)
  {
    return (int) ch - (int) 'A';
  }
  
  
  // initializeLetterValues(int[] letterValues)
  // letterValues[0] = 1 corresponds with A
  // letterValues[1] = 2 corresponds with B
  // letterValues[25] = 26 corresponds with Z
  // A = 1, B = 2, ... Z = 26
  // ASSUME array is of size 26 (26 letters in alphabet)
  public static void initializeLetterValues(int[] letterValues)
  {
    for(int index = 0; index < 26; index++)
    {
      letterValues[index] = index + 1;
    }
  }
  
  
  // printLetterValues(int[] letterValues) prints every item in an array
  // ASSUME array is of size 26 (26 letters in alphabet)
  // *debugging purposes*
  public static void printLetterValues(int[] letterValues)
  {
    for(int index = 0; index < 26; index++)
    {
      System.out.printf("letterValues[%d] = %d\n", index, letterValues[index]);
    }
  }
  
  
  // assignValues(Scanner keyboard, int[] letterValues) parameters:
  // 1. keyboard - to get input from the user
  // 2. letterValues - holds the value for each letter (A-Z)
  // assignValues(Scanner keyboard, int[] letterValues) takes input
  // <letter> <asst_op> <number> from the keyboard
  // <number> is assigned to the <letter>'s value
  public static void assignValues(Scanner keyboard, int[] letterValues)
  {
    char letter = ' '; //letter that value will be assigned
    char asst_op = ' '; //operator '=' (ignored)
    int number = 1; //number to be assigned to the letter
    
    letter = keyboard.next().charAt(0);
    while(letter != '$')
    {
      asst_op = keyboard.next().charAt(0);
      number = keyboard.nextInt();
      letterValues[addr(letter)] = number;
      letter = keyboard.next().charAt(0);
    }
  }
  
  
  // String helpRightParen(String postfix) parameters:
  // 1. postfix - the current postfix expression, will add if the stack is
  // not empty the top of the stack is not a left paren
  // String helpRightParen(String postfix) is right parenthesis handling for infix to postfix.
  // Returns postfix after evaluating.
  public static String helpRightParen(String postfix)
  {
    //System.out.printf("helpRightParen: postfix = %s\n", postfix); //debugging
    //NOTE: I do not stack right parens
    while(!opStack.empty() && !opStack.peek().equals(new Character('(')))
    {
      postfix = postfix + opStack.pop();
      //System.out.printf("helpRightParen: postfix = %s\n", postfix); //debugging
    }
    if(!opStack.empty())
    {
      opStack.pop(); //pop left parenthesis
    }
    return postfix;
  }
  
  
  // String helpAddSubtract(String postfix, char ch) parameters:
  // 1. postfix - the current postfix expression, will add if the stack is
  // not empty and the top of the stack is not a left paren
  // 2. ch - the character in the infix currently being evaluated
  // String helpAddSubtract(String postfix, char ch) is addition and subtaction handling 
  // for infix to postfix. Precedence: top of stack is not [ ( ].
  // Returns postfix after evaluating.
  public static String helpAddSubtract(String postfix, char ch)
  {
    //System.out.printf("helpAddSubtract: ch = %c  postfix = %s\n", ch, postfix); //debugging
    while(!opStack.empty() && !opStack.peek().equals(new Character('('))) 
    {
      postfix = postfix + opStack.pop();
      //System.out.printf("helpAddSubtract: ch = %c  postfix = %s\n", ch, postfix); //debugging
    }
    opStack.push(ch); //push + or - (ch)
    return postfix;
  }
  
  
  // String helpMultiplyDivide(String postfix, char ch) parameters:
  // 1. postfix - the current postfix expression, will add if the stack is
  // not empty, the top of the stack is not a left paren, not a +, not a -
  // 2. ch - the character in the infix currently being evaluated
  // String helpMultiplyDivide(String postfix, char ch) is multiply and divide handling 
  // for infix to postfix. Precedence: top of stack is not [ - or + or ( ]. 
  // Returns postfix after evaluating.
  public static String helpMultiplyDivide(String postfix, char ch)
  {
    //System.out.printf("helpMultiplyDivide: ch = %c  postfix = %s\n", ch, postfix); //debugging
    while(!opStack.empty() && !opStack.peek().equals(new Character('(')) && !opStack.peek().equals(new Character('+')) && !opStack.peek().equals(new Character('-'))) 
    {
      postfix = postfix + opStack.pop();
      //System.out.printf("helpMultiplyDivide: ch = %c  postfix = %s\n", ch, postfix); //debugging
    }
    opStack.push(ch); //push * or / (ch)
    return postfix;
  }
  
  
  // String infixToPostfix(String infix) parameters:
  // 1. infix - the infix that is to be changed into postfix
  // String infixToPostfix(String infix) returns the postfix of the given infix
  public static String infixToPostfix(String infix)
  {
    String postfix = ""; //the postfix expression
      
    for(int index = 0; index < infix.length(); index++) //moves through infix string
    {
      char ch = infix.charAt(index); //the character in the infix currently being used
        
      if(ch == '(')
      {
        opStack.push('(');
      }
      else if(ch == ')')
      {
        postfix = helpRightParen(postfix);
      }
      else if(ch == '+' || ch == '-')
      {
        postfix = helpAddSubtract(postfix, ch);
      }
      else if(ch == '*' || ch == '/')
      {
        postfix = helpMultiplyDivide(postfix, ch);
      }
      else //not an operator
      {
        postfix = postfix + ch; //add letter to the postfix
      }
    }
    while(!opStack.empty()) //pops remaining operator on stack when nothing left in the infix string
    {
      if (!opStack.peek().equals(new Character('('))) //do not pop right paren
      {
        postfix = postfix + opStack.pop();
      }
    }
    return postfix;
  }
  
  
  // calcResult(String postfix, int[] letterValues) parameters:
  // 1. postfix - the postfix to be evaluated
  // 2. letterValues - an array that holds the letter values for the letters in the postfix
  // calcResult(String postfix, int[] letterValues) returns a resulting value from the 
  // evaluation of the postfix expression.
  public static int calcResult(String postfix, int[] letterValues)
  {
    char ch; //the character in the postfix currently being used
    int operand1; //the first operand
    int operand2; //the second operand
    int result; //the result of an operation between the two operands
    int charValue; //if it is an operand then this is the number value of the letter
    
    for(int index = 0; index < postfix.length(); index++)
    {
      ch = postfix.charAt(index);
      
      if(ch != '*' && ch != '/' && ch != '+' && ch != '-')
      {
        charValue = letterValues[addr(ch)];
        operandsStack.push(charValue);
      }
      else
      {
        operand2 = operandsStack.pop();
        operand1 = operandsStack.pop();
        if(ch == '-')
        {
          result = operand1 - operand2;
          operandsStack.push(result);
        }
        if(ch == '+')
        {
          result = operand1 + operand2;
          operandsStack.push(result);
        }
        if(ch == '*')
        {
          result = operand1 * operand2;
          operandsStack.push(result);
        }
        if(ch == '/')
        {
          result = operand1 / operand2;
          operandsStack.push(result);
        }
      }
    }
    result = operandsStack.pop();
    return result;
  }
  
  
  // simulate(Scanner keyboard, int[] letterValues) parameters:
  // 1. keyboard - to get input from the user
  // 2. letterValues - holds the integer value of each of the letters A-Z
  // simulate(Scanner keyboard, int[] letterValues) prints the infix, postfix, and the result of the postfix
  // given the infix
  public static void simulate(Scanner keyboard, int[] letterValues)
  {
    while(keyboard.hasNext())
    {
      String infix = keyboard.next();
      System.out.printf("Infix: %S\n", infix);
      String postfix = infixToPostfix(infix);
      System.out.printf("Postfix: %S\n", postfix);
      System.out.printf("Result: %S\n\n", calcResult(postfix, letterValues));
    }
  }
  
  
  public static void main(String[] args) 
  {
    int[] letterValues = new int[26]; // letterValues array holds integer values for each letter in A-Z
    initializeLetterValues(letterValues);
    Scanner keyboard = new Scanner(System.in); // read input
    assignValues(keyboard, letterValues);
    simulate(keyboard, letterValues);
  }

}
