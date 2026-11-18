char *func0(char *month, int days)
{
 char *season;

 if (!strcmp(month, "January") || !strcmp(month, "February") || !strcmp(month, "March"))
  season = "winter";
 else if (!strcmp(month, "April") || !strcmp(month, "May") || !strcmp(month, "June"))
  season = "spring";
 else if (!strcmp(month, "July") || !strcmp(month, "August") || !strcmp(month, "September"))
  season = "summer";
 else
  season = "autumn";

 if ((!strcmp(month, "March") && days >= 20) || (!strcmp(month, "June") && days >= 21) || (!strcmp(month, "September") && days >= 22))
 {
  if (!strcmp(month, "March"))
   season = "spring";
  if (!strcmp(month, "June"))
   season = "summer";
  if (!strcmp(month, "September"))
   season = "autumn";
 }
 else if (!strcmp(month, "December") && days >= 21)
  season = "winter";

 return season;
}