void remove_dupc2(char str[])
{
 int i,j;
 for ( i=0; str[i] ; i++)
 {
  if(str[i] == -1)
   continue;

  for ( j=i+1; str[j]; j++)
  {
   if( str[i] == str[j])
    str[j] = -1;
  }
 }

 for(j=0; str[j] && (str[j] != -1) ; j++) ;

 if(str[j])
  i=j;
 else
  i--;

 for( j=i+1; str[j]; j++)
 {
  if(str[j] == -1)
   continue;
  else
   str[i++] = str[j];
 }
 str[i]=str[j];
}