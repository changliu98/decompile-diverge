int parse_device(dev_t *pdev,archive *a,char *val)

{
  unsigned_long uVar1;
  int iVar2;
  char *error;
  dev_t result;
  pack_t *pack;
  int argc;
  char *dev;
  char *p;
  unsigned_long numbers [3];
  char *val_local;
  archive *a_local;
  dev_t *pdev_local;
  int local_c;
  
  error = (char *)0x0;
  val_local = val;
  a_local = a;
  pdev_local = pdev;
  memset(pdev,0,8);
  dev = strchr(val_local,0x2c);
  if (dev == (char *)0x0) {
    result = mtree_atol(&val_local);
LAB_00101796:
    *pdev_local = result;
    local_c = 0;
  }
  else {
    *dev = '\0';
    dev = dev + 1;
    pack = pack_find(val_local);
    if (pack == (pack_t *)0x0) {
      archive_set_error(a_local,0x16,"Unknown format `%s\'",val_local);
      local_c = -0x14;
    }
    else {
      argc = 0;
      do {
        p = la_strsep(&dev,",");
        if (p == (char *)0x0) {
          if (argc < 2) {
            archive_set_error(a_local,0x16,"Not enough arguments");
            return -0x14;
          }
          result = (*pack)(argc,numbers,&error);
          if (error != (char *)0x0) {
            archive_set_error(a_local,0x16,"%s",error);
            return -0x14;
          }
          goto LAB_00101796;
        }
        if (*p == '\0') {
          archive_set_error(a_local,0x16,"Missing number");
          return -0x14;
        }
        uVar1 = mtree_atol(&p);
        iVar2 = argc + 1;
        numbers[argc] = uVar1;
        argc = iVar2;
      } while (iVar2 < 4);
      archive_set_error(a_local,0x16,"Too many arguments");
      local_c = -0x14;
    }
  }
  return local_c;
}