
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


  public boolean isEmpty() // ** YOU IMPLEMENT **
  {
    if(numItems = 0)
    {
      return true;
    }
    return false;
  }


  public int size() // ** YOU IMPLEMENT **
  {  
    return numItems;
  }  


  //** YOU IMPLEMENT **
  // --------------------------------------------------
  // Locates a specified node in a linked list.
  // Precondition: index is the number of the desired
  // node. Assumes that 1 <= index <= numItems
  // Postcondition: Returns a reference to the desired 
  // node.
  // --------------------------------------------------
  private int find(int index)
  {
    return index - 1;
  }


  public PageUsage get(int index) // ** YOU IMPLEMENT **
  {
    return items[index - 1];
  } 
  

  public void add(int index, PageUsage newItem) // ** YOU IMPLEMENT **
  {  
    items[index - 1] = newItem;
    next[index - 1] = null;
    free = index;
    numItems++;
  }  
  

  public void remove(int index) // ** YOU IMPLEMENT **
  {
    numItems--;
    next[index - 1] = numItems + 1;
    
  }
}
