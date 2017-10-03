// CSCI 4630
// Program:    4
// Class:      CSCI 4630
// Author:     Josh Weeks
// Date:       4/26/16
// File:       myls.c

// *COMPILING NOTES*
// gcc myls.c -o myls
// *RUNNING NOTES*
// ./myls 
// ./myls myls.c

// prints: # file links, user that owns file, group of users that can use file, file size in bytes, and the file name

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <err.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main (int argc, char **argv)
{
  DIR *midir;

  struct dirent* info_archivo;
  struct stat fStats;
  struct tm* time;
  struct passwd* uid;
  struct group* gid;

  char paths[256]; 
  char date[25];
  char* arg = argv[1];

  if (argc != 2) //no third argument
  {
    char currentBuffer[256];
    getcwd(currentBuffer, sizeof(currentBuffer));
    printf("%s\n", currentBuffer);
    arg = currentBuffer;
  }
  
  midir = opendir(arg); //open directory

  if(stat(arg, &fStats) == 0 && S_ISDIR(fStats.st_mode))  //need loop
  {
    while((info_archivo = readdir(midir)) != 0)  //looping
    {
      strcat(paths, info_archivo->d_name);
      strcpy(paths, arg);
      strcat(paths, "/");
      
      if(!stat(paths, &fStats))  //STAT SUCCESS
      {
        //read, write, execute
        printf((S_ISDIR(fStats.st_mode))  ? "d" : "-");
        printf((fStats.st_mode & S_IRUSR) ? "r" : "-");
        printf((fStats.st_mode & S_IWUSR) ? "w" : "-");
        printf((fStats.st_mode & S_IXUSR) ? "x" : "-");
        printf((fStats.st_mode & S_IRGRP) ? "r" : "-");
        printf((fStats.st_mode & S_IWGRP) ? "w" : "-");
        printf((fStats.st_mode & S_IXGRP) ? "x" : "-");
        printf((fStats.st_mode & S_IROTH) ? "r" : "-");
        printf((fStats.st_mode & S_IWOTH) ? "w" : "-");
        printf((fStats.st_mode & S_IXOTH) ? "x" : "-");
      } 
      else
      {
        perror("***STAT ERROR***");
      }

        //ID
        uid = getpwuid(fStats.st_uid);
        gid = getgrgid(fStats.st_gid);
        //time
        time = localtime(&fStats.st_mtime);
        strftime(date, 25, "%b %d %H:%M", time);
        
        //printing information
        printf("\t %d ", fStats.st_nlink);        //# file links
        printf("\t %s ", uid ->pw_name);          //user that owns file
        printf("\t %s ", gid ->gr_name);          //group of users that can use file
        printf("\t %i ", fStats.st_size);         //file size, bytes
        printf("\t %s ", date);                   //last change date
        printf("\t %s \n", info_archivo->d_name); //file name
      }

      closedir(midir);  //close directory
    }
    else    //single file
    {
      //read, write, execute
      printf((S_ISDIR(fStats.st_mode))  ? "d" : "-");
      printf((fStats.st_mode & S_IRUSR) ? "r" : "-");
      printf((fStats.st_mode & S_IWUSR) ? "w" : "-");
      printf((fStats.st_mode & S_IXUSR) ? "x" : "-");
      printf((fStats.st_mode & S_IRGRP) ? "r" : "-");
      printf((fStats.st_mode & S_IWGRP) ? "w" : "-");
      printf((fStats.st_mode & S_IXGRP) ? "x" : "-");
      printf((fStats.st_mode & S_IROTH) ? "r" : "-");
      printf((fStats.st_mode & S_IWOTH) ? "w" : "-");
      printf((fStats.st_mode & S_IXOTH) ? "x" : "-");
      
      //id
      uid = getpwuid(fStats.st_uid);
      gid = getgrgid(fStats.st_gid);
      //time
      time = localtime(&fStats.st_mtime);
      strftime(date, 25, "%b %d %H:%M", time);
      
      //printing information
      printf("\t%d ", fStats.st_nlink);     //# file links
      printf("\t%s ", uid ->pw_name);       //user that owns file
      printf("\t%s ", gid ->gr_name);       //group of users that can use file
      printf("\t%i ", fStats.st_size);      //file size, bytes
      printf("\t%s ", date);                //last change date
      printf("\t%s \n", arg);               //file name
    }
}
