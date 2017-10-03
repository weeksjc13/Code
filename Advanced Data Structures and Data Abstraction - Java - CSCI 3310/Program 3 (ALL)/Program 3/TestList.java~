import java.io.*;
import java.util.*;

public class TestList 
{
  public static void main(String[] args) 
  {
    List<PageUsage> freePageList = new List<PageUsage>();	//free pages available
  
    PageUsage newPageUsage1 = new PageUsage(1, 2);
    PageUsage newPageUsage2 = new PageUsage(3, 4);
    PageUsage newPageUsage3 = new PageUsage(5, 6);
    PageUsage newPageUsage4 = new PageUsage(7, 8);
  
    freePageList.add(1, newPageUsage4);
    freePageList.add(1, newPageUsage3);
    freePageList.add(1, newPageUsage2);
    freePageList.add(1, newPageUsage1);
  
    System.out.println("Contents of Free Page List");
    System.out.println("Start Page    End Page");
    for(int index = 1; index < freePageList.size() + 1; index++)
    {
      System.out.printf("      %d           %d\n", freePageList.get(index).getStart(), freePageList.get(index).getEnd());
    }
    System.out.println();
  }
}
