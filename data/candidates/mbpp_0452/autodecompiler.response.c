int func0(int cost, int sale)
{
 int money;

 if(sale > cost){
  money = sale - cost;
 }
 else{
  money = 0;
 }

 return money;
}