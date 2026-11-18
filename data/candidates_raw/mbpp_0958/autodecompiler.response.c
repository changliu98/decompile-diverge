char *func0(int number)
{
 int i;
 char *symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
 int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
 strcpy(func0.roman_num,"");
 for(i=0;;i++)
 {
  if(number>0)
  {
   while(number>=value[i])
   {
    strcat(func0.roman_num,symbol[i]);
    number-=value[i];
   }
  }
  else break;
 }
 return func0.roman_num;
}