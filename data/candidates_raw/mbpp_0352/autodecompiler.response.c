int check_base_condition(char *base_from_user)
{
 int it[2];

 it[0] = 0;
 while (it[0] < strlen(base_from_user))
 {
  it[1] = it[0] + 1;
  while (it[1] < strlen(base_from_user))
  {
   if (base_from_user[it[0]] == base_from_user[it[1]])
    return (0);
   it[1]++;
  }
  it[0]++;
 }
 return (1);
}