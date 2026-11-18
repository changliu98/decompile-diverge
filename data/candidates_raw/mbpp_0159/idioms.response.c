char *getseason(char *month, int days)
{
  char *season;
  if (strcmp(month, "January") == 0 || strcmp(month, "February") == 0
      || strcmp(month, "March") == 0)
    season = "winter";
  else if (strcmp(month, "April") == 0 || strcmp(month, "May") == 0
      || strcmp(month, "June") == 0)
    season = "spring";
  else if (strcmp(month, "July") == 0 || strcmp(month, "August") == 0
      || strcmp(month, "September") == 0)
    season = "summer";
  else
    season = "autumn";
  if ((strcmp(month, "March") == 0 && days > 19)
      || (strcmp(month, "June") == 0 && days > 20)
      || (strcmp(month, "September") == 0 && days > 21)) {
    if (strcmp(month, "March") == 0)
      season = "spring";
    if (strcmp(month, "June") == 0)
      season = "summer";
    if (strcmp(month, "September") == 0)
      season = "autumn";
  }
  else if (strcmp(month, "December") == 0 && days > 20)
    season = "winter";
  return (season);
}