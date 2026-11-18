cJSON * cJSON_CreateNumber(double num)

{
  cJSON *pcVar1;
  cJSON *item;
  double num_local;
  
  pcVar1 = cJSON_New_Item(&global_hooks);
  if (pcVar1 != (cJSON *)0x0) {
    pcVar1->type = 8;
    pcVar1->valuedouble = num;
    if (num < DAT_00108010) {
      if (DAT_00108018 < num) {
        pcVar1->valueint = (int)num;
      }
      else {
        pcVar1->valueint = -0x80000000;
      }
    }
    else {
      pcVar1->valueint = 0x7fffffff;
    }
  }
  return pcVar1;
}