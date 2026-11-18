int func0(int *transactions, int no_of_transactions)
{
 int i;
 int total = 0;

 for (i = 0; ; i++) {
  if (i >= no_of_transactions) {
   break;
  }
  total += transactions[i];
  if (total < 0) {
   return 1;
  }
 }

 return 0;
}