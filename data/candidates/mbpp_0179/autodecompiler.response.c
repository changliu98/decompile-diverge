int func0(int number)
{
 int i, j;
 int terms[100];
 int temp = number;
 int counter = 0;

 while(1) {
  if(temp > 0) {
   terms[counter++] = temp % 10;
   temp /= 10;
  } else {
   break;
  }
 }

 int left = 0;
 int right = counter - 1;

 while(1) {
  if(left < right) {
   temp = terms[left];
   terms[left] = terms[right];
   terms[right] = temp;
   left++;
   right--;
  } else {
   break;
  }
 }

 int index = counter;
 int sum = 0;
 int result = 0;

 while(1) {
  if(sum < number) {
   sum = 0;
   for(i = 1; i <= counter; i++) {
    sum += terms[index - i];
   }
   terms[index++] = sum;
  } else {
   result = sum;
   break;
  }
 }

 if(result == number && counter % 2 != 0) {
  return 1;
 } else {
  return 0;
 }
}