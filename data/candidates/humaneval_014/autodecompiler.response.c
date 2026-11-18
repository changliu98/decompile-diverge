char **func0(buf,return_count)
     char *buf;
     int *return_count;
{
  char **return_vec;
  char *temp;
  int i;
  int len;

  len = strlen(buf);

  return_vec = (char **)malloc(sizeof(char *) * len);
  temp = (char *)malloc(sizeof(char) * (len + 1));
  strcpy(temp,"");
  i = 0;
  while(1){
    if (i >= len){ break;}
    {int z=strlen(temp);temp=(char *)realloc(temp,z+2);temp[z]=buf[i];temp[z+1]='\0';};
    return_vec[i] = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy(return_vec[i],temp);
    i++;
  }
  free(temp);
  *return_count = len;
  return(return_vec);
}