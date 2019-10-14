#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size) : top(-1) {
	  size = _size;
    if ((size < 1) || (size > MaxStackSize))
      throw "too_large_or_negative_length";
    pMem = new T[size];
  }
  ~TStack() { delete[] pMem; }

  bool IsEmpty(void) const { return top == -1; }
  bool IsFull(void) const { return top == size - 1; }

  void Push(const T& Val)  {
	  if (IsFull()) throw "stack_is_full";
	  pMem[++top] = Val;
  }
  virtual T Pop(void)  {
	  if (IsEmpty()) throw "stack_is_empty";
	  return pMem[top--];
  }
  virtual T Top(void) {
	  if (IsEmpty()) throw "stack_is_empty";
	  return pMem[top];
  }
};

#endif