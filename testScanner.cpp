#include <iostream>
#include <string>
#include <fstream>
#include "scanner.h"
#include "token.h"

using namespace std;

void testScan(std::istream& in)
{
  int lineNum = 1;
  int charNum = 1;

  token t = scan(in, lineNum, charNum);

  while(t.id != eoftk && t.id > 1000)
  {
    lineNum += std::get<0>(t.size);
    charNum += std::get<1>(t.size);
    cout << t.toString() << "\n";
    t = scan(in, lineNum, charNum);
  }

  cout << t.toString() << "\n";
}
