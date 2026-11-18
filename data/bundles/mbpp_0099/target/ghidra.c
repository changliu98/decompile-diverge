char * func0(int n)

{
  char cVar1;
  char temp;
  int end;
  int start;
  int index;
  int n_local;
  
  index = 0;
  for (n_local = n; 0 < n_local; n_local = n_local / 2) {
    func0::binary[index] = (char)(n_local % 2) + '0';
    index = index + 1;
  }
  func0::binary[index] = '\0';
  for (start = 0; end = index + -1, start < end; start = start + 1) {
    cVar1 = func0::binary[start];
    func0::binary[start] = func0::binary[end];
    func0::binary[end] = cVar1;
    index = end;
  }
  return func0::binary;
}