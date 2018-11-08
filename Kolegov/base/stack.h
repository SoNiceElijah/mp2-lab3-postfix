#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

using namespace std;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }

  void Push(T elem)
  {
	  if (IsFull())
		  throw "stack full";

	  top++;
	  pMem[top] = elem;
  }
  T Pop()
  {
	  if (IsEmpty())
		  throw "Stack empty";
	  top--;
	  return pMem[top + 1];
  }

  int IsEmpty(void) const { return top == -1; }
  int IsFull(void) const { return top == size - 1; }
};

#endif
