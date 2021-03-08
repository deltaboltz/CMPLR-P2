#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"

token scan(std::istream& in, int lineNum, int charNum);

#endif
