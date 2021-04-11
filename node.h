#ifndef NODE_H
#define NODE_H
#include <set>
#include <vector>

#include "token.h"

template <class T>
class node
{
private:

  std::vector<node<T>> childrenT;
  std::vector<node<T>> tokensT;
  T keyT;

  void preHelp(std::ostream& out, std::string indent);

public:
  node<T> (T key);
  std::string toString();
  void insert(node<T> child);
  void insert(token childToken);

  void preOrder();
  void preOrder(std::ostream& out);
};

template <class T>
node<T>::node(T key)
{
  keyT = key;
}

template <class T>
std::string node<T>::toString()
{
  if(tokensT.size() > 0)
  {
    std::string tokenStr("");
    int i = 0;

    for(int i = 0; i < tokensT.size() -1; i++)
    {
      tokenStr += tokensT[i].toString() + ", ";
    }

    tokenStr += tokensT[i].toString() + "\n";

    return keyT + " Tokens: " + tokenStr;
  }

  return keyT + "\n";
}

template <class T>
node<T>::insert(node<T> child)
{
  childrenT.push_back(child);
}

template <class T>
node<T>::insert(token childToken)
{
  tokensT.push_back(childToken);
}

template <class T>
void node<T>::preHelp(std::ostream& out, std::string indent)
{
  std::string newindent("      ");
  newindent += indent;

  out << indent << toString();

  for(int i = 0; i < childrenT.size(); i++)
  {
    childrenT[i].preHelp(out, newindent);
  }

}

template <class T>
node<T>::node()
{
  set = false;
}

// Each traversal has a standard cout stream as well as an
// overloaded function for ostream
template <class T>
void node<T>::preOrder()
{
  preHelp(std::cout, "");
}

template <class T>
void node<T>::preOrder(std::ostream& out)
{
  preHelp(out, "");
}

#endif
