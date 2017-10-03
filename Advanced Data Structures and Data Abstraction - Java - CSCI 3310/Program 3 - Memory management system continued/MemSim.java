// CSCI 3310
// Program:    3
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       11/1/15
// File:       MemSim.java

//MemSim simulates a memory management system for programs. Memory is organized as pages with each
//page storing a set amount of bytes.
//MemParam gorverns the max pages, max programs, max bytes one program can use, and the number of
//bytes that one page can hold.
//Input will be in the format <opcode><prog_id><size>
//<prog_id> is the id of a program and <size> is the number of bytes that the program needs.
//There are four <opcode>'s ('i', 't', 'p', and 'x') that govern what function the program will execute:
// 1.initialize 'i' - creates space for one program.
// 2.terminate 't' - resets the programs information to an inactive program and updates free pages. 
//<size> does not effect terminate.
// 3.print 'p' - displays an existing programs pages being used and the bytes the program uses. If 
//<prog_id> is a negative number then free pages will be displayed. <size> does not effect print.
// 4.exit 'x' - ends program and displays total programs in memory and the number of occupied pages.
//<prog_id> and <size> do not effect exit
// 5.grow 'g' - adds <size> bytes to program <prog_id> and updates the programs used pages and the free pages
// 6.shrink 's' - removes <size> bytes from a program <prog_id> and updates the programs used pages and the free pages
//=======================================================================================================
//Error handling, error message occurs if:
// 1.initialize 'i' and the program already exists
// 2.initialize 'i' and there is not enough memory to hold the program
// 3.initialize 'i' and the <size> exceeds the maximum number of bytes
// 4.terminate 't' and the program does not exist
// 5.print 'p'  and the program does not exist
// 6.grow 'g' and the program does not exist
// 7.grow 'g' and there is not enough available space
// 8.grow 'g' and the maximum size of the program is exceeded
// 9.shrink 's' and the program does not exist
// 10.shrink 's' and <size> exceeds the bytes the program currently has

import java.io.*;
import java.util.*;

public class MemSim 
{
  public static final int NUM_PAGES = MemParam.NUM_PAGES;	//maximum number of pages
  public static final int NUM_PROGRAMS = MemParam.NUM_PROGRAMS;	//maximum number of programs
  public static final int MAX_SIZE = MemParam.MAX_SIZE;		//maximum number of bytes one program can use
  public static final int PAGE_SIZE = MemParam.PAGE_SIZE;	//the number of bytes that a single page can hold


  //makeFreePageList(freePageList) takes one parameter:
  //1.freePageList - initializes freePageList
  public static void makeFreePageList(List<PageUsage> freePageList)
  {
    PageUsage pageUsage = new PageUsage(0, NUM_PAGES-1);	//hold the initial free pages
    freePageList.add(1, pageUsage);
  }


  //makeProgramsArray(programsArray) takes one parameter:
  //1.programsArray - initializes programsArray
  public static void makeProgramsArray(ProgInfo[] programsArray)
  {
    for(int index = 0; index < NUM_PROGRAMS; index++)
    {
      List<PageUsage> memoryUsageList = new List<PageUsage>();	//empty list used to eventually hold the pages used by the program
      programsArray[index] = new ProgInfo();
      programsArray[index].bytes = -1;
      programsArray[index].prog_usage = memoryUsageList;
    }
  }


  //initiate(id, numBytes, freePageList, programsArray) takes four parameters: 
  //1.id - id of a program that does not currently exist and will be created
  //2.numBytes - the number of bytes the program requires.
  //3.freePageList - needed pages for the program will be removed from freePageList
  //4.programsArray - give the program information (bytes and used pages)
  //initiate(int id, int numBytes) updates the free pages and the programs page usage. Displays
  //the program id and the number of bytes that program uses.
  public static void initiate(int id, int numBytes, List<PageUsage> freePageList, ProgInfo[] programsArray)
  {
    if(programsArray[id].bytes > -1)
    {
      System.out.printf("ERROR on initiate command: Program %d already exists.\n\n", id);
    }
    else if(MAX_SIZE < numBytes)		//tests if size exceeds the maximum size for a program
    {
      System.out.printf("ERROR on initiate command: Program %d requires more than the maximum program size of %d.\n\n", id, MAX_SIZE);
    }
    else if((NUM_PAGES - countUsedPages(freePageList)) < (numBytes / PAGE_SIZE) + (numBytes % PAGE_SIZE))	//free pages < neededPages
    {
      System.out.printf("ERROR on initiate command: insufficient space for Program %d.\n\n", id);
    }
    else
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
  }


  //terminate(id, freePageList, programsArray) takes three parameters: 
  //1.id - id of an active program that will be terminated.
  //2.freePageList - will be updated with freed pages
  //3.programsArray - will be reset to make the program inactive
  //terminate(id, freePageList, programsArray) updates the amount of free pages and resets the programs 
  //bytes and the number of used pages. Displays the program id terminated and number of pages freed.
  public static void terminate(int id, List<PageUsage> freePageList, ProgInfo[] programsArray)
  {
    if(id > NUM_PROGRAMS - 1 || id < 0)
    {
      System.out.printf("ERROR on terminate command: Program %d does not exist.\n\n", id);
    }
    else if(programsArray[id].bytes <= -1)
    {
      System.out.printf("ERROR on terminate command: Program %d does not exist.\n\n", id);
    }
    else
    {
      int totalPagesFreed = 0;		//total number of pages freed after terminating a program
      for(int index = 1; index < programsArray[id].prog_usage.size() + 1; index++)
      {
        freePageList.add(1, programsArray[id].prog_usage.get(index));
        totalPagesFreed = totalPagesFreed + (programsArray[id].prog_usage.get(index).getEnd() - programsArray[id].prog_usage.get(index).getStart()) + 1;
      }
      //reset program information
      programsArray[id].prog_usage.removeAll();
      programsArray[id].bytes = -1;
      System.out.printf("Program %d terminated, %d pages freed\n", id, totalPagesFreed);
    }
  }


  //grow(id, growBytes, freePageList, programsArray) takes four parameter:
  //1.id - id of active program that will be grown
  //2.growBytes - amount of bytes to add to the program
  //3.freePageList - list of free pages
  //4.programsArray - holds the program information of the active program that will be grown
  //grow(id, growBytes, freePageList, programsArray) adds bytes to the program and allocates memory
  //in the programs usage and updates the free page list
  public static void grow(int id, int growBytes, List<PageUsage> freePageList, ProgInfo[] programsArray)
  {
    int extraBytes = programsArray[id].bytes % PAGE_SIZE;					//left over bytes from last page used
    if(extraBytes > 0)
    {
      extraBytes = PAGE_SIZE - extraBytes;
    }
    int currentPages = (programsArray[id].bytes / PAGE_SIZE);					//pages used by the program currently
    if(programsArray[id].bytes % PAGE_SIZE > 0)
    {
      currentPages++;
    }
    int newSize = (currentPages * PAGE_SIZE) - extraBytes + growBytes; 				//the bytes to taken up by the program after grow
    int freeBytes = (NUM_PAGES - countUsedPages(freePageList)) * PAGE_SIZE + extraBytes;	//total free bytes in freePageList
    int pagesNeeded = ((growBytes - extraBytes) / PAGE_SIZE);					//pages needed to grow the program
    if(((growBytes - extraBytes) / PAGE_SIZE) > 0)
    {
      pagesNeeded++;
    }

    if(programsArray[id].bytes <= -1)
    {
      System.out.printf("ERROR on grow command: Program %d does not exist.\n\n", id);
    }
    else if(freeBytes < newSize)
    {
      System.out.printf("ERROR on grom command: Insufficient space for Program %d.\n\n", id);
    }
    else if(MAX_SIZE < newSize)
    {
      System.out.printf("ERROR on grow command: MAX_SIZE exceeded for Program %d.\n\n", id);
    }
    else
    {
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
          programsArray[id].bytes = newSize;
          break;
        }
        //needs to find more free pages
        else
        {
          programsArray[id].prog_usage.add(programsArray[id].prog_usage.size() + 1, freePageList.get(1));
          programsArray[id].bytes = newSize;
          freePageList.remove(1);
          pagesNeeded  = pagesNeeded - (end - start) - 1;
        }
      }
      programsArray[id].bytes = newSize;
      System.out.printf("Program %d increased by %d bytes, new size = %d.\n\n", id, growBytes, newSize);
    }
    
  }


  //shrink(id, growBytes, freePageList, programsArray) takes four parameter:
  //1.id - id of active program that will be grown
  //2.shrinkBytes - amount of bytes to remove from the program
  //3.freePageList - list of free pages
  //4.programsArray - holds the program information of the active program that will be grown
  //shrink(id, growBytes, freePageList, programsArray) removes bytes from the program and allocates memory
  //in the programs usage and updates the free page list
  public static void shrink(int id, int size, List<PageUsage> freePageList, ProgInfo[] programsArray)
  {
    if(programsArray[id].bytes <= -1)
    {
      System.out.printf("ERROR on shrink command: Program %d does not exist.\n\n", id);
    }
    else if(programsArray[id].bytes < size)
    {
      System.out.printf("ERROR on shrink command: insufficient allocation for Program %d.\n\n", id);
    }
    else if(programsArray[id].bytes == size) //clears list and sets bytes to 0
    {
      List<PageUsage> memoryUsageList = new List<PageUsage>();	//empty list
      programsArray[id].bytes = 0;
      programsArray[id].prog_usage = memoryUsageList;
    }
    else if(size < (programsArray[id].bytes % PAGE_SIZE))
    {
      programsArray[id].bytes = programsArray[id].bytes - size;
      System.out.printf("Program %d decreased by %d bytes, new size = %d\n\n", id, size, programsArray[id].bytes);
    }
    else if(programsArray[id].prog_usage.size() > 0)
    {
      int pages = (size / PAGE_SIZE); //keeps up with pages that will be freed by shrink
      if((size % PAGE_SIZE) - (programsArray[id].bytes % PAGE_SIZE) > 0)
      {
        pages++;
      }

      int start = programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getStart();	//start of last prog usage
      int end = programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getEnd();         //end of last prog usage
      
      //System.out.printf("\n\nDEBUG: start:%d   end:%d  pages:%d\n\n", start, end, pages);
      
      while((end - start) + 1 < pages) // not enough in last prog usage to shrink
      {
        pages = pages - ((end - start) + 1);
        freePageList.add(1, programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()));
        programsArray[id].prog_usage.remove(programsArray[id].prog_usage.size());
        //System.out.printf("\n\nLOOP DEBUG: start:%d   end:%d  pages:%d\n\n", start, end, pages);
        if(programsArray[id].prog_usage.size() > 0)
        {
          start = programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getStart();
          end = programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getEnd();
        }
        else
        {
          break;
        }
      }
      
      int listSize = programsArray[id].prog_usage.size(); //size of last prog usage
      
      // enough in last prog usage to shrink now
      if(pages > 0)
      {
        programsArray[id].prog_usage.get(listSize).setEnd(programsArray[id].prog_usage.get(listSize).getEnd() - pages);
        //add to free page
        PageUsage newFree = new PageUsage(programsArray[id].prog_usage.get(listSize).getEnd() + 1, programsArray[id].prog_usage.get(listSize).getEnd() + pages);
        freePageList.add(1, newFree);
      }
      
      if(programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getStart() > programsArray[id].prog_usage.get(programsArray[id].prog_usage.size()).getEnd()) // start page greater than end page
      {
        programsArray[id].prog_usage.remove(programsArray[id].prog_usage.size());
      }
      
      programsArray[id].bytes = programsArray[id].bytes - size;
      System.out.printf("Program %d decreased by %d bytes, new size = %d\n\n", id, size, programsArray[id].bytes);
    }
  }


  //countUsedPages(freePageList) takes one parameter:
  //1.freePageList - used to find pages being used
  //countUsedPages(freePageList) returns number of pages occupied by active programs
  public static int countUsedPages(List<PageUsage> freePageList)
  {
    int usedPages = NUM_PAGES;		//total number of pages being used by active programs
    for(int index = 1; index < freePageList.size() + 1; index++)
    {
      usedPages = usedPages - ((freePageList.get(index).getEnd() - freePageList.get(index).getStart()) + 1);
    }
    return usedPages;
  }


  //countActivePrograms() takes one parameter:
  //1.programsArray - used to find active programs
  //countActivePrograms() returns number of programs that are using 1 or more bytes
  public static int countActivePrograms(ProgInfo[] programsArray)
  {
    int activePrograms = 0;
    for(int index = 0; index < NUM_PROGRAMS; index++)
    {
      if(programsArray[index].bytes > -1)
      {
        activePrograms++;
      }
    }
    return activePrograms;
  }


  //print
  public static void print(int id, ProgInfo[] programsArray, List<PageUsage> freePageList)
  {
    if(id > NUM_PROGRAMS - 1)
    {
      System.out.printf("ERROR on terminate command: Program %d does not exist.\n\n", id);
    }
    else if (id < 0)
    {
      printFreePage(freePageList);
    }
    else
    {
      if(programsArray[id].bytes > -1)
      {
        printPageUsage(id, programsArray[id].bytes, programsArray);
      }
      else
      {
        System.out.printf("ERROR on print command: Program %d does not exist.\n\n", id);
      }
    }
  }
  

  //prints program usage list
  public static void printPageUsage(int id, int numBytes, ProgInfo[] programsArray)
  {
    System.out.printf("Page usage for Program %d --- size = %d bytes\n", id, numBytes);
    System.out.println("Start Page    End Page");
    for(int index = 1; index < programsArray[id].prog_usage.size() + 1; index++)
    {
      System.out.printf("      %d           %d\n", programsArray[id].prog_usage.get(index).getStart(), programsArray[id].prog_usage.get(index).getEnd());
    }
    System.out.println();
  }


  //printFreePage(freePageList) takes one parameter:
  //1.freePageList - prints the entire freePageList
  public static void printFreePage(List<PageUsage> freePageList)
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
    List<PageUsage> freePageList = new List<PageUsage>();	//free pages available
    ProgInfo[] programsArray = new ProgInfo[NUM_PROGRAMS];	//array holding program information (bytes and list of used pages)
    makeFreePageList(freePageList);
    makeProgramsArray(programsArray);

    Scanner keyboard = new Scanner(System.in);			//open keyboard

    while (keyboard.hasNext())
    {
      String op_code = keyboard.next();		//action on program (initiate, terminate, print, exit)
      int prog_id = keyboard.nextInt();		//program id number
      int size = keyboard.nextInt();		//bytes the program will use

      if(op_code.equals("i"))
      {
        initiate(prog_id, size, freePageList, programsArray);
      }
      else if(op_code.equals("t"))
      {
        terminate(prog_id, freePageList, programsArray);
      }
      else if(op_code.equals("p"))
      {
        print(prog_id, programsArray, freePageList);
      }
      else if(op_code.equals("g"))
      {
        grow(prog_id, size, freePageList, programsArray);
      }
      else if(op_code.equals("s"))
      {
        shrink(prog_id, size, freePageList, programsArray);
      }
      else if(op_code.equals("x"))
      {
        System.out.printf("SIMULATOR EXIT: %d programs exist, occupying %d pages.\n", countActivePrograms(programsArray), countUsedPages(freePageList));
      }
    }
    
    keyboard.close();	
  }
}
