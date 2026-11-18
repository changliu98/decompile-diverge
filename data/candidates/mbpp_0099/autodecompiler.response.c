char *func0(int decimal) {
 int temp, index;
 index = 0;

 while(1) {
  if(decimal > 0) {
   func0.binary[index++] = decimal % 2 + '0';
   decimal = decimal / 2;
  } else {
   func0.binary[index] = '\0';
   break;
  }
 }


 int start, end;
 start = 0;
 end = index - 1;
 while(start < end) {
  swap = func0.binary[start];
  func0.binary[start] = func0.binary[end];
  func0.binary[end] = swap;
  start++;
  end--;
 }

 return func0.binary;
}