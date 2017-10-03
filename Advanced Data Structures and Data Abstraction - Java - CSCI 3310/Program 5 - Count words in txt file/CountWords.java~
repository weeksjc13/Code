// CSCI 3310
// Program:    5
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       11/29/15
// File:       CountWords.java

//CountWords reads a file and returns results about the words in the file.
//Example output: Letter <letter> <list_size> <word> <frequency>
//letter - starting letter of all words in the table
//list_size - number of unique words in table (no matter how many times a word occurs it only counts as one unique word)
//word - the most commonly occuring word in the table
//frquency - the number of times that word occurs in the table

import java.util.*;

public class CountWords
{
  public static final int TABLESIZE = 2003;  // hash table size
  
  
  //initializeList(List<Hashtable<String, WordItem>> tablesList) parameter:
  //1. tablesList - list to be filled with tables
  //initializeList(List<Hashtable<String, WordItem>> tablesList) creates 26 tables for each letter of the
  //alphabet. Table for a is at index 0, b is at index 1...z is at index 25.
  public static void initializeList(List<Hashtable<String, WordItem>> tablesList)
  {
    for(int index = 0; index < 26; index++)
    {
      tablesList.add(new Hashtable<String, WordItem>(TABLESIZE));
    }
  }
  
  
  //storeWord(List<Hashtable<String, WordItem>> tablesList, String word) parameters:
  //1. tablesList - a list of tables, contains a table for a-z, a is at index 0, b is at index 1...z is at index 25
  //2. word - the word that is being stored into tablesList
  //storeWord(List<Hashtable<String, WordItem>> tablesList, String word) stores word into tablesList in the 
  //table that corresponds to the first letter of word.
  public static void storeWord(List<Hashtable<String, WordItem>> tablesList, String word)
  {
    char firstLetter = word.charAt(0); //first letter in word
    int tableNumber = (int) firstLetter - (int) 'a'; //location of hash table in array list
      
    if(tablesList.get(tableNumber).containsKey(word))
    {
      tablesList.get(tableNumber).get(word).incCount();
    }
    else
    {
      tablesList.get(tableNumber).put(word, new WordItem(word));
    }
  }
  
  
  //storeWordHelper(List<Hashtable<String, WordItem>> tablesList, TextIterator iterator) parameters:
  //1. tablesList - a list of tables, contains a table for a-z, a is at index 0, b is at index 1...z is at index 25
  //2. iterator - holds words that need to be stored
  //storeWordHelper(List<Hashtable<String, WordItem>> tablesList, TextIterator iterator) grabs a word from iterator
  //and stores it into tablesList at the appropriate table.
  public static void storeWordHelper(List<Hashtable<String, WordItem>> tablesList, TextIterator iterator)
  {
    while(iterator.hasNext())
    {
      String word = iterator.next(); //word to be stored
      storeWord(tablesList, word);
    }
  }
  
  
  //finalResults(ArrayList<Hashtable<String, WordItem>> tablesList) parameter:
  //1. tablesList - a list of tables, contains a table for a-z, a is at index 0, b is at index 1...z is at index 25.
  //Each table is filled with the words that will produce the results.
  //finalResults(ArrayList<Hashtable<String, WordItem>> tablesList) produces results for each table in tablesList.
  //Example output: Letter <letter> <list_size> <word> <frequency>
  //letter - starting letter of all words in the table
  //list_size - number of unique words in table (no matter how many times a word occurs it only counts as one unique word)
  //word - the most commonly occuring word in the table
  //frquency - the number of times that word occurs in the table
  public static void finalResults(ArrayList<Hashtable<String, WordItem>> tablesList)
  {
    String word = ""; //most commonly occurring word in the table
    int list_size = 0; //number of unique words in the table
    int word_frequency = 0; //frequency of most commonly occuring word
    int tableNumber = 0; //location of the table in tablesList
    int totalUnique = 0; //total number of unique words
	  
    for(char ch = 'a' ; ch <= 'z'; ch++)
    {
      tableNumber = (int) ch - (int) 'a';
      list_size = tablesList.get(tableNumber).size();
      totalUnique = totalUnique + list_size;
      if(list_size > 0)
      {
        word_frequency = Collections.max(tablesList.get(tableNumber).values()).getCount();
        word = Collections.max(tablesList.get(tableNumber).values()).getWord();
        System.out.printf("Letter %c %5d %15s %6d \n", ch, list_size, word, word_frequency);
      }
      else
      {
        System.out.printf("Letter %c %5d \n", ch, list_size);
      }
    }
    System.out.printf("\nThere were a total of %d unique words.\n", totalUnique);
  }
  
  
  public static void main(String [] args)
  {
     if (args.length < 1)
     {
       System.out.print("ERROR: insufficient number of command line ");
       System.out.println("arguments. Program aborted.");
       return;
     }
    
    ArrayList<Hashtable<String, WordItem>> tablesList = new ArrayList<Hashtable<String, WordItem>>(); //list of tables
    initializeList(tablesList);
    
    String input = args[0]; //input file
    TextIterator iterator = new TextIterator(); //will hold a string of each word in input file
    iterator.readText(input); //fill iterator with text from input file
    
    storeWordHelper(tablesList, iterator);
    
    finalResults(tablesList);
  }
}
