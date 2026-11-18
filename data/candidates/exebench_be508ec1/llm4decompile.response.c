void string_reverse(char* string){
 char* start = string;
 char* end = string;

 while(end && *end){
  end++;
 }

 for(end--; start < end; start++, end--){
  *start = *start ^ *end;
  *end = *end ^ *start;
  *start = *start ^ *end;
 }
}