#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "token.h"
#include "fsa.h"

using namespace std;

tokenID filterKeyword(std::string cap)
{
  if (cap == "begin") return keyword;
  if (cap == "end") return keyword;
  if (cap == "loop") return keyword;
  if (cap == "whole") return keyword;
  if (cap == "void") return keyword;
  if (cap == "exit") return keyword;
  if (cap == "getter") return keyword;
  if (cap == "outter") return keyword;
  if (cap == "main") return keyword;
  if (cap == "if") return keyword;
  if (cap == "then") return keyword;
  if (cap == "assign") return keyword;
  if (cap == "data") return keyword;
  if (cap == "proc") return keyword;

  return identifier;
}

token scan(std::istream& in, const int lineNum, const int charNum)
{
    int linePos = lineNum;
    int charPos = charNum;
    int lineSize = 0;
    int charSize = 0;
    int state = 1;
    char c = char(32);
    std::string capture("");

    while(state > 0 && state <= 1000)
    {
        in.get(c);
        if(in.eof() || in.fail())
        {
            c = (char)-1;
        }

        if(state==1)
        {
            if (c > 32 && c != 36)
            {
                //Is not leading whitespace, capture this (except $)
                capture += std::string(1, c);
                charSize++;
            }
            else if (c == 36)
            {
                //set token to start at beginning of next line
                linePos++;
                charPos = 1;
                lineSize++;
                charSize = 1-charNum;
            }
            else if (c == 32 || c == 9)
            {
                //shift forward start of token index
                charPos++;
                charSize++;
            }
            else if (c == 10)
            {
                //shift down start of token index
                linePos++;
                charPos = 1;
                lineSize++;
                charSize = 1-charNum;
            }
        }
        else if (state > 1 && state < 11)
        {
            capture += std::string(1, c);
            charSize++;
        }

        state = fsa[state][(int)c];
    }

    in.unget();
    charSize--;

    std::string e(1,c);
    capture = capture.substr(0,capture.length()-1);
    std::pair<int, int> pos = std::make_pair(linePos,charPos);
    std::pair<int, int> size = std::make_pair(lineSize, charSize);
    std::pair<int, int> erpos = std::make_pair(lineNum+lineSize, charNum+charSize);

    switch(state)
    {
        case -1: return token(error,"No valid token begins with character '" + e + "'", erpos, size);
        case 0: return token(error,"Illegal character '" + e + "'", erpos, size);
        case 1001: return token(filterKeyword(capture), capture, pos, size);
        case 1005: return token(eoftk, "EOF", pos, size);
    }

    return token((tokenID)state, capture, pos, size);
}
