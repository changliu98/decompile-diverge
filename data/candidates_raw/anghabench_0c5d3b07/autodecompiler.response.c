__attribute__((used)) static char *priority_to_str(int prio)
{
 char *str;

 switch (prio) {
 case BT_MESH_PRIORITY_UNAVAILABLE:
  str = "Unavailable";
  break;
 case BT_MESH_PRIORITY_LOW:
  str = "Low";
  break;
 case BT_MESH_PRIORITY_NEUTRAL:
  str = "Neutral";
  break;
 case BT_MESH_PRIORITY_PREFERRED:
  str = "Preferred";
  break;
 default:
  str = "Invalid";
 }

 return str;
}