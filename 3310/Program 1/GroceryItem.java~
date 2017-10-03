// CSCI 3310
// Program:    1
// Class:      CSCI 3310
// Author:     Josh Weeks
// Date:       9/16/15
// File:       GroceryItem.java

//==============================================================
//    GroceryItem class
//==============================================================
//    A grocery item object's information consists of
//    1. a product number (five-digits)
//    2. description (no blanks)
//    3. quantity (maximum 9999)
//    4. price (a real number)
//    5. tax (F - food, N - nonfood)
//    The GroceryItem class has three methods; readItem reads a 
//    single item's information, itemSearch finds if an item exists,
//    and printInventory prints an entire inventory of GroceryItems.
//==============================================================

import java.util.*;

public class GroceryItem
{
   
    private int productNum;		//product number of the grocery item (5-digit positive)
    private String description;		//description of the grocery item (at most 12 chars w/ no spaces)
    private int quantity;		//quantity of the grocery item (no larger than 9999)
    private double price;		//price of the grocery item
    private String tax;			//the type of tax for the grocery item ('F' - food item and 'N'- non food product)
   
    //accessors
   
    public int getProductNum()
    {
        return productNum;
    }
    public String getDescription()
    {
        return description;
    }
    public int getQuantity()
    {
        return quantity;
    }
    public double getPrice()
    {
        return price;
    }
    public String getTax()
    {
        return tax;
    }
   
    //mutators
   
    public void setProductNum(int productNum)
    {
        this.productNum = productNum;
    }
    public void setDescription(String description)
    {
        this.description = description;
    }
    public void setQuantity(int quantity)
    {
        this.quantity = quantity;
    }
    public void setPrice(double price)
    {
        this.price = price;
    }
    public void setTax(String tax)
    {
        this.tax = tax;
    }
   
    //==============================================================
    //  readItem
    //==============================================================
    //    This method takes a Scanner object that represents the input file being
    //    read. This methods purpose is to read all information for one inventory
    //    item.
    //==============================================================
   
    public void readItem(Scanner fileInput)
    {
        setProductNum(fileInput.nextInt());
        setDescription(fileInput.next());
        setQuantity(fileInput.nextInt());
        setPrice(fileInput.nextDouble());
        setTax(fileInput.next());
    }
   
    //==============================================================
    //  itemSearch
    //==============================================================
    //    This method takes three parameters
    //    1. an array of GroceryItem objects that represent an entire inventory of objects
    //    2. an integer that determines how much of the array is being used
    //    3. an integer representing a product item
    //    This method searches the array of items for the item with the matching third parameter.
    //    This method returns the index within the array where the information for the item is stored.
    //    This method returns -1 if there is no item with the matching third parameter.
    //==============================================================
   
    public static int itemSearch(GroceryItem[] inventory, int usedSpace, int productNumber)
    {
        for (int index = 0; index < usedSpace; index++)		//an index for the loop               
        {
            if (inventory[index].productNum == productNumber)
            {
                return index;
            }
        }
       
        return -1;
    }
   
    //==============================================================
    //  printInventory
    //==============================================================
    //    This method takes two parameters
    //    1. an array of GroceryItem objects that represent an entire inventory of objects
    //    2. an integer that determines how much of the array is being used
    //    This method prints the information on an array of items with one item per line.
    //==============================================================
   
    public static void printInventory (GroceryItem[] inventory, int usedSpace)
    {
        System.out.println("Product Number  Description    Quantity  Price  Tax\n");
       
        for (int index = 0; index < usedSpace; index++)		//an index for the loop
        {
            if (index != usedSpace)
            {
                System.out.printf("%5d           ", inventory[index].productNum);
                System.out.printf("%-12s    ", inventory[index].description);
                System.out.printf("%4d  ", inventory[index].quantity);
                System.out.printf("%7.2f   ", inventory[index].price);
                System.out.printf("%s   \n", inventory[index].tax);
            }
        }
    }
}



