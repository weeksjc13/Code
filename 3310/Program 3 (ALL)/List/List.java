// CSCI 3310
// Program:    3
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       11/1/15
// File:       List.java

// ****************************************************
// Reference-based implementation of ADT list using arrays.
// Due to the limitations with array of generics, the
// "data type" for the list items is fixed to be of type
// PageUsage.  Any program using this class must specify
// <PageUsage> as the value for the type parameter.
// ****************************************************
public class List<T> 
{

  // reference to linked list of items

  public static final int MAX_LIST = 20;
  public static final int NULL = -1;
  
  private PageUsage item[] = new PageUsage[MAX_LIST];  // data
  private int      next[] = new int[MAX_LIST];       // pointer to next item

  private int head;     // pointer to front of list
  private int free;     // pointer to front of free list
  private int numItems; // number of items in list

  // Constructor must initialize used list to empty and free list to 
  // all available nodes.


  public List() 
  {
    int index;
    for (index = 0; index < MAX_LIST-1; index++)
    {
    	next[index] = index + 1;
    	next[MAX_LIST-1] = NULL;
    	numItems = 0;
    	head = NULL;
    	free = 0;
    }  
  }


  public void removeAll() // reinitialize all nodes to free
  {   
    int index;
    for (index = 0; index < MAX_LIST-1; index++)
    {
      next[index] = index + 1;
      next[MAX_LIST-1] = NULL;
      numItems = 0;
      head = NULL;
      free = 0;
    } 
  }


  public boolean isEmpty() // returns true if the list is empty, false if the list is not empty
  {
    if(numItems == 0)
    {
      return true;
    }
    return false;
  }


  public int size() // returns the size of the list
  {  
    return numItems;
  }  


  // --------------------------------------------------
  // Locates a specified node in a linked list.
  // Precondition: index is the number of the desired
  // node. Assumes that 1 <= index <= numItems
  // Postcondition: Returns a reference to the desired 
  // node.
  // --------------------------------------------------
  private int find(int index)
  {
    int curr = head;
    for(int i = 1; i < index; i++)
    {
      curr = next[curr];
    }
    return curr;
  }


  public PageUsage get(int index) //returns PageUsage item at index
  {
    return item[index - 1];
  } 

  public void add(int index, PageUsage newItem) //adds newItem to the list at index
  {
    if((index < 1) || (index > numItems + 1))
    {
      System.out.println("Index: out of bounds.");
    }
    else
    {
      for(int pos = numItems - 1; pos >= index - 1; pos--)
      {
        item[pos + 1] = item[pos];
      }
    }
    item[index - 1] = newItem;
    numItems++;
  }


  public void remove(int index) //removes an item at the index position in list
  {
    if((index < 1) || (index > numItems + 1))
    {
      System.out.println("Index: out of bounds.");
    }
    else
    {
      for(int pos = index - 1; pos >= numItems - 1; pos++)
      {
        item[pos] = item[pos + 1];
      }
    }
    numItems--;
  }
}
