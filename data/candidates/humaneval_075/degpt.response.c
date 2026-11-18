int func0(int a)

{
  int i;
  int num;
  int a_local;
  undefined4 local_c;
  
  if (a < 2) {
    local_c = 0;
  }
  else {
    num = 0;
    a_local = a;
    for (i = 2; i * i <= a_local; i = i + 1) {
      for (; a_local % i == 0; a_local = a_local / i) {
        num = num + 1;
      }
    }
    if (1 < a_local) {
      num = num + 1;
    }
    local_c = (uint)(num == 3);
  }
  return local_c;
}