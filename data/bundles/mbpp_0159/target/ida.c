const char *__cdecl func0(const char *month, int days)
{
  const char *season; // [rsp+8h] [rbp-18h]

  if ( !strcmp(month, "January") || !strcmp(month, "February") || !strcmp(month, "March") )
  {
    season = "winter";
  }
  else if ( !strcmp(month, "April") || !strcmp(month, "May") || !strcmp(month, "June") )
  {
    season = "spring";
  }
  else if ( !strcmp(month, "July") || !strcmp(month, "August") || !strcmp(month, "September") )
  {
    season = "summer";
  }
  else
  {
    season = "autumn";
  }
  if ( !strcmp(month, "March") && days > 19
    || !strcmp(month, "June") && days > 20
    || !strcmp(month, "September") && days > 21 )
  {
    if ( !strcmp(month, "March") )
      season = "spring";
    if ( !strcmp(month, "June") )
      season = "summer";
    if ( !strcmp(month, "September") )
      return "autumn";
  }
  else if ( !strcmp(month, "December") && days > 20 )
  {
    return "winter";
  }
  return season;
}