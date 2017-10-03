// CSCI 3310
// Program:    2
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       10/6/15
// File:       MemSim.java

import java.io.*;
import java.util.*;

public class MemSim 
{
  public static final int NUM_PAGES = MemParam.NUM_PAGES;		//maximum number of pages
  public static final int NUM_PROGRAMS = MemParam.NUM_PROGRAMS;		//maximum number of programs
  public static final int MAX_SIZE = MemParam.MAX_SIZE;
  public static final int PAGE_SIZE = MemParam.PAGE_SIZE;		//the number of bytes that a single page can hold


  //makeFreePageList() initializes freePageList
  public static void makeFreePageList()
  {
    PageUsage pageUsage = new PageUsage(0, NUM_PAGES-1);
    freePageList.add(1, pageUsage);
  }


  //makeProgramsArray() initializes programsArray
  public static void makeProgramsArray()
  {
    for(int index = 0; index < NUM_PROGRAMS; index++)
    {
      List<PageUsage> memoryUsageList = new List<PageUsage>();
      programsArray[index] = new ProgInfo();
      programsArray[index].bytes = 0;
      programsArray[index].prog_usage = memoryUsageList;
    }
  }


  //initiate(int id, int numBytes) takes two parameters: 1.the id of a program that does not 
  //currently exist and will be created and 2.the number of bytes the program requires.
  //initiate(int id, int numBytes) updates the free pages and the programs page usage. Displays
  //the program id and the number of bytes that program uses.
  public static void initiate(int id, int numBytes)
  {
    int pagesNeeded;		//pages needed by program
		
    System.out.printf("Program %d initiated, size = %d\n", id, numBytes);
		
    //finds how many pages are needed by the program
    if(numBytes % PAGE_SIZE > 0)
    {
      pagesNeeded = (numBytes / PAGE_SIZE) + 1;
    }
    else
    {
      pagesNeeded = numBytes / PAGE_SIZE;
    }
		
    while(pagesNeeded != 0)
    {
      //start and end update every time the loop is activated
      int start = freePageList.get(1).getStart();	//the first free page's beginning
      int end = freePageList.get(1).getEnd();		//the first free page's ending
      //first item in free page list has the needed pages for program
      if((end - start) + 1 > pagesNeeded)
      {
        PageUsage programPageUse = new PageUsage(start, start + pagesNeeded - 1);
        freePageList.get(1).setStart(start + pagesNeeded);
        programsArray[id].prog_usage.add(programsArray[id].prog_usage.size() + 1, programPageUse);
        programsArray[id].bytes = numBytes;
        break;
      }
      //needs to find more free pages
      else
      {
        programsArray[id].prog_usage.add(programsArray[id].prog_usage.size() + 1, freePageList.get(1));
        programsArray[id].bytes = numBytes;
        freePageList.remove(1);
        pagesNeeded  = pagesNeeded - (end - start) - 1;
      }
    }
  }


  //terminate(int id) takes one parameter: the id of an active program that will be terminated.
  //terminate(int id) updates the amount of free pages and resets the programs bytes and the 
  //number of used pages. Displays the program id terminated and number of pages freed.
  public static void terminate(int id)
  {
    int totalPagesFreed = 0;		//total number of pages freed after terminating a program
    for(int index = 1; index < programsArray[id].prog_usage.size() + 1; index++)
    {
      freePageList.add(1, programsArray[id].prog_usage.get(index));
      totalPagesFreed = totalPagesFreed + (programsArray[id].prog_usage.get(index).getEnd() - programsArray[id].prog_usage.get(index).getStart()) + 1;
    }
    //reset program information
    programsArray[id].prog_usage.removeAll();
    programsArray[id].bytes = 0;
    System.out.printf("Program %d terminated, %d pages freed\n", id, totalPagesFreed);
  }


  //countUsedPages() returns number of pages occupied by active programs
  public static int countUsedPages()
  {
    int usedPages = NUM_PAGES;		//total number of pages being used by active programs
    for(int index = 1; index < freePageList.size() + 1; index++)
    {
      usedPages = usedPages - ((freePageList.get(index).getEnd() - freePageList.get(index).getStart()) + 1);
    }
    return usedPages;
  }


  //countActivePrograms() returns number of programs that are using 1 or more bytes
  public static int countActivePrograms()
  {
    int activePrograms = 0;
    for(int index = 0; index < NUM_PROGRAMS; index++)
    {
      if(programsArray[index].bytes > 0)
      {
        activePrograms++;
      }
    }
    return activePrograms - 1;
  }


  //prints program usage list
  public static void printPageUsage(int id, int numBytes)
  {
    System.out.printf("Page usage for Program %d --- size = %d bytes\n", id, numBytes);
    System.out.println("Start Page    End Page");
    for(int index = 1; index < programsArray[id].prog_usage.size() + 1; index++)
    {
      System.out.printf("      %d           %d\n", programsArray[id].prog_usage.get(index).getStart(), programsArray[id].prog_usage.get(index).getEnd());
    }
    System.out.println();
  }


  //printFreePage() prints free page list
  public static void printFreePage()
  {
    System.out.println("Contents of Free Page List");
    System.out.println("Start Page    End Page");
    for(int index = 1; index < freePageList.size() + 1; index++)
    {
      System.out.printf("      %d           %d\n", freePageList.get(index).getStart(), freePageList.get(index).getEnd());
    }
    System.out.println();
  }


  public static void main(String[] args) 
  {
    ProgInfo[] programsArray = new ProgInfo[NUM_PROGRAMS];
    List<PageUsage> freePageList = new List<PageUsage>();	//free pages available
    makeFreePageList();
    makeProgramsArray();

    Scanner keyboard = new Scanner(System.in);

    while (keyboard.hasNext())
    {
      String op_code = keyboard.next();		//action on program (initiate, terminate, print, exit)
      int prog_id = keyboard.nextInt();		//program id number
      int size = keyboard.nextInt();		//bytes the program will use

      if(op_code.equals("i"))
      {
        if(programsArray[prog_id].bytes > 0)
        {
          System.out.printf("ERROR on initiate command: Program %d already exists.\n\n", prog_id);
        }
        //free pages < neededPages
        else if((NUM_PAGES - countUsedPages()) < (size / PAGE_SIZE) + (size % PAGE_SIZE))
        {
          System.out.printf("ERROR on initiate command: insufficient space for Program %d.\n\n", prog_id);
        }
        else
        {
          initiate(prog_id, size);
        }
      }
      else if(op_code.equals("t"))
      {
        if(programsArray[prog_id].bytes > 0)
        {
          terminate(prog_id);
        }
        else
        {
          System.out.printf("ERROR on terminate command: Program %d does not exist.\n\n", prog_id);
        }
      }
      else if(op_code.equals("p"))
      {
        if (prog_id < 0)
        {
          printFreePage();
        }
        else
        {
          if(programsArray[prog_id].bytes > 0)
	  {
            printPageUsage(prog_id, programsArray[prog_id].bytes);
          }
          else
          {
            System.out.printf("ERROR on print command: Program %d does not exist.\n\n", prog_id);
          }
        }
      }
      else if(op_code.equals("x"))
      {
        System.out.printf("SIMULATOR EXIT: %d programs exist, occupying %d pages.\n", countActivePrograms(), countUsedPages());
      }
    }
    keyboard.close();	
  }
}
