/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

#include "Assign4.h"

 string GetFileName()
 {
   string fileName;
   cout << "Please enter a file to check: " ;
   getline(cin, fileName);
   return fileName;
 }

 void CheckFileNameValid(string& fileName)
 {
   ifstream inFile;
   bool isNotValid = true;

   do
   {
     inFile.open(fileName.c_str());

     //check if file exists
     if(inFile)
     {
       isNotValid = false; //is valid
     }
     else
     {
       cout << "Sorry, the file, \"" << fileName << "\", wasn't found.\n";
       fileName = GetFileName();//prompting for valid input

       isNotValid = true; //repeat loop
     }

     inFile.close();
   } while(isNotValid);


 }
