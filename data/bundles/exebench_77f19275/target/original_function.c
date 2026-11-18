void extract(char * instring, int inlength, int fieldno, int valueno, int subvalueno, int* outstart, int* outlength)
{
 int start_pos;
 int fieldn2;
 int field_end_pos;
 int valuen2;
 int value_end_pos;
 int subvaluen2;
 int subvalue_end_pos;
# 62 "extract.c"
 *outstart=0;
 *outlength=0;


 if (fieldno<=0)
 {
  if (fieldno<0) return;
  if (valueno||subvalueno) fieldno=1; else
  {
   *outlength=inlength;
   return;
  }
 }


 start_pos=0;
 fieldn2=1;




 while (fieldn2<fieldno)
 {
  for (;
    start_pos<inlength &&
    (instring[start_pos] != '\xCB' ||
    instring[start_pos+1] != '\xBE') ;
   start_pos++)
  {};

  if (start_pos>=inlength)
   return;
  start_pos += 2;
  fieldn2++;
 }


 for (field_end_pos=start_pos;
   field_end_pos<inlength &&
   (instring[field_end_pos]!='\xCB' ||
   instring[field_end_pos+1] != '\xBE');
  field_end_pos++)
 {};




 if (valueno<=0)
 {
  if (valueno<0)
   return;
  if (subvalueno)
   valueno=1;
  else
  {
   *outstart=start_pos;
   *outlength=field_end_pos-start_pos;
   return;
  }
 }





 valuen2=1;
 while (valuen2<valueno)
 {
  for ( ;
    start_pos<inlength &&
    (instring[start_pos]!='\xCB' ||
    instring[start_pos+1]!='\xBD');
   start_pos++)
  {};

  if (start_pos>=inlength)
   return;
  start_pos+=2;

  if (start_pos>field_end_pos)
   return;
  valuen2++;
 }


 for (value_end_pos=start_pos;
   value_end_pos<field_end_pos &&
   (instring[value_end_pos]!='\xCB' ||
   instring[value_end_pos+1]!='\xBD');
  value_end_pos++)
 {}





 if (subvalueno<=0)
 {
  if (subvalueno<0)
   return;
  *outstart=start_pos;
  *outlength=value_end_pos-start_pos;
 }





 subvaluen2=1;
 while (subvaluen2<subvalueno)
 {
  for ( ;
    start_pos<field_end_pos &&
    (instring[start_pos]!='\xCB' ||
    instring[start_pos+1]!='\xBC');
   start_pos++)
  {};

  if (start_pos>=inlength)
   return;
  start_pos++;

  if (start_pos>value_end_pos)
   return;
  subvaluen2++;
 }


 for (subvalue_end_pos=start_pos;
   subvalue_end_pos<value_end_pos &&
   (instring[subvalue_end_pos]!='\xCB' ||
   instring[subvalue_end_pos+1]!='\xBC');
  subvalue_end_pos++)
 {};
 if (subvalue_end_pos>=value_end_pos)
 {
  *outstart=start_pos;
  *outlength=value_end_pos-start_pos;
  return;
 }
 *outstart=start_pos;
 *outlength=subvalue_end_pos-start_pos;
 return;

}