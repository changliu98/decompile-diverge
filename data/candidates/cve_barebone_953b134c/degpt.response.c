void listdir(uint depth,int f,void *tls_fd,char *name)

{
  size_t sVar1;
  PureFileInfo *__ptr;
  int iVar2;
  char *__s;
  int *piVar3;
  char *pcVar4;
  char *pcVar5;
  undefined1 auStack_68 [15];
  bool local_59;
  size_t sizeof_subdir;
  char *alloca_subdir;
  int d;
  PureFileInfo *r;
  PureFileInfo *s;
  char *names;
  PureFileInfo *dir;
  char *name_local;
  void *tls_fd_local;
  int f_local;
  uint depth_local;
  
  if ((depth < max_ls_depth) && (matches < max_ls_files)) {
    name_local = name;
    tls_fd_local = tls_fd;
    f_local = f;
    depth_local = depth;
    s = sreaddir(&names);
    dir = s;
    if (s == (PureFileInfo *)0x0) {
      addreply(0xe2,"Sorry, we were unable to read [%s]",name_local);
    }
    else {
      for (; s->name_offset != 0xffffffffffffffff; s = s + 1) {
        d = 0;
        if ((*s->names_pnt)[s->name_offset] == '.') {
          if (opt_a != 0) {
            if (((*s->names_pnt)[s->name_offset + 1] == '\0') ||
               (((*s->names_pnt)[s->name_offset + 1] == '.' &&
                ((*s->names_pnt)[s->name_offset + 2] == '\0')))) {
              listfile(s,(char *)0x0);
            }
            else {
              d = listfile(s,(char *)0x0);
            }
          }
        }
        else {
          d = listfile(s,(char *)0x0);
        }
        if (d == 0) {
          s->name_offset = 0xffffffffffffffff;
        }
      }
      outputfiles(f_local,tls_fd_local);
      pcVar5 = auStack_68;
      for (r = dir; local_59 = opt_R != 0 && r != s, __s = pcVar5, opt_R != 0 && r != s; r = r + 1)
      {
        if (r->name_offset != 0xffffffffffffffff) {
          pcVar4 = *r->names_pnt;
          sVar1 = r->name_offset;
          *(undefined8 *)(pcVar5 + -8) = 0x101b6b;
          iVar2 = chdir(pcVar4 + sVar1);
          if (iVar2 == 0) {
            sizeof_subdir = 0x1001;
            __s = pcVar5 + -0x1010;
            alloca_subdir = __s;
            if (__s == (char *)0x0) break;
            pcVar4 = *r->names_pnt;
            sVar1 = r->name_offset;
            *(undefined8 *)(pcVar5 + -0x1018) = 0x101bc8;
            iVar2 = snprintf(__s,0x1001,"%s/%s",name_local,pcVar4 + sVar1);
            if (iVar2 < 0x1001) {
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101beb;
              wrstr(f_local,tls_fd_local,"\r\n\r\n");
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101bfb;
              wrstr(f_local,tls_fd_local,alloca_subdir);
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101c0e;
              wrstr(f_local,tls_fd_local,":\r\n\r\n");
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101c24;
              listdir(depth_local + 1,f_local,tls_fd_local,alloca_subdir);
            }
            if (max_ls_files <= matches) break;
            *(undefined8 *)(pcVar5 + -0x1018) = 0x101c51;
            iVar2 = chdir("..");
            if (iVar2 != 0) {
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101c66;
              iVar2 = chdir(wd);
              if (iVar2 == 0) {
                *(undefined8 *)(pcVar5 + -0x1018) = 0x101c78;
                iVar2 = chdir(name_local);
                if (iVar2 == 0) goto LAB_00101cb2;
              }
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101c86;
              piVar3 = __errno_location();
              iVar2 = *piVar3;
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101c8d;
              pcVar4 = strerror(iVar2);
              *(undefined8 *)(pcVar5 + -0x1018) = 0x101ca8;
              die(0x1a5,3,"chdir: %s",pcVar4);
            }
          }
        }
LAB_00101cb2:
        pcVar5 = __s;
      }
      __s[-8] = -0x2f;
      __s[-7] = '\x1c';
      __s[-6] = '\x10';
      __s[-5] = '\0';
      __s[-4] = '\0';
      __s[-3] = '\0';
      __s[-2] = '\0';
      __s[-1] = '\0';
      free(names);
      __ptr = dir;
      __s[-8] = -0x26;
      __s[-7] = '\x1c';
      __s[-6] = '\x10';
      __s[-5] = '\0';
      __s[-4] = '\0';
      __s[-3] = '\0';
      __s[-2] = '\0';
      __s[-1] = '\0';
      free(__ptr);
    }
  }
  return;
}