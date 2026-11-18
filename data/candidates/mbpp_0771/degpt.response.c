_Bool func0(char *exp)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  char last_open;
  char ch;
  int i;
  int top;
  char stack [100];
  int len;
  char *exp_local;
  _Bool local_9;
  
  sVar3 = strlen(exp);
  if ((int)sVar3 % 2 == 0) {
    top = -1;
    for (i = 0; i < (int)sVar3; i = i + 1) {
      cVar1 = exp[i];
      if (((cVar1 == '(') || (cVar1 == '{')) || (cVar1 == '[')) {
        stack[top + 1] = cVar1;
        top = top + 1;
      }
      else if (((cVar1 == ')') || (cVar1 == '}')) || (cVar1 == ']')) {
        if (top == -1) {
          return false;
        }
        iVar4 = top + -1;
        cVar2 = stack[top];
        if (((cVar2 == '(') && (cVar1 != ')')) ||
           (((cVar2 == '{' && (cVar1 != '}')) || ((top = iVar4, cVar2 == '[' && (cVar1 != ']'))))))
        {
          return false;
        }
      }
    }
    local_9 = top == -1;
  }
  else {
    local_9 = false;
  }
  return local_9;
}