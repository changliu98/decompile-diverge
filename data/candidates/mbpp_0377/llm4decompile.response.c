char * func0(char * s, char c){
 int counts = 0;
 for(int i=0; s[i]!='\0'; i++){
  if(s[i] == c)
   counts++;
 }
 char * t = malloc(strlen(s)-counts+1);
 int j=0;
 for(int i=0; s[i]!='\0'; i++){
  if(s[i] != c){
   t[j] = s[i];
   j++;
  }
 }
 t[j] = '\0';
 return t;
}