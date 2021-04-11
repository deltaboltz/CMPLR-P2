/*
* By: Connor Schultz
* Date Made: 04/03/2021
* Files Needed: any file with extension .sp21
* Made For: CS-4280 (Program Translation Project) @ UMSL
*/

#include <iostream>
#include <string>
#include <fstream>
#include "testScanner.h"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc == 1)
  {
    testScan(cin);
  }
  else if(argc == 2) //check to see if the file has the proper extension
  {
    string fext, filename(""), filearg(argv[1]);
    int length = filearg.length();

    if(length > 4)
    {
      fext = filearg.substr(length-5, length);

      if(fext == ".sp21")
      {
        filename = filearg;
      }
    }

    if(filename == "")
    {
      filename = filearg + ".sp21";
    }

    ifstream fs(filename.c_str());

    if(fs)
    {
      testScan(fs);
    }
    else
    {
      cout << filename << " - CANNOT be opened.";
      return 1;
    }
  }
  else
  {
    cout << "Wrong number of arguments were given";
    return 2;
  }

  return 0;
}
