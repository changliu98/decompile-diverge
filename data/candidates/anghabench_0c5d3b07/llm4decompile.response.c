const char *get_priority_string(int prio)
{
 const char *str;

 switch (prio) {
 case Priority_Unavailable:
  str = "Unavailable";
  break;
 case Priority_Low:
  str = "Low";
  break;
 case Priority_Neutral:
  str = "Neutral";
  break;
 case Priority_Preferred:
  str = "Preferred";
  break;
 default:
  str = "Invalid";
  break;
 }

 return str;
}