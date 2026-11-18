_Bool func0(char *str1)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  char popped;
  char parenthese;
  int i;
  int top;
  char stack [100];
  char *str1_local;
  
  top = -1;
  i = 0;
  do {
    sVar3 = strlen(str1);
    if (sVar3 <= (ulong)(long)i) {
      return top == -1;
    }
    cVar1 = str1[i];
    if (((cVar1 == '(') || (cVar1 == '{')) || (cVar1 == '[')) {
      stack[top + 1] = cVar1;
      top = top + 1;
    }
    else {
      if (top == -1) {
        return false;
      }
      iVar4 = top + -1;
      cVar2 = stack[top];
      if ((((cVar1 == ')') && (cVar2 != '(')) || ((cVar1 == '}' && (cVar2 != '{')))) ||
         ((top = iVar4, cVar1 == ']' && (cVar2 != '[')))) {
        return false;
      }
    }
    i = i + 1;
  } while( true );
}