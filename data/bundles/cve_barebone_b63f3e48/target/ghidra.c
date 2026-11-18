void DoCommand(char *FileName,int ShowIt)

{
  bool bVar1;
  int iVar2;
  size_t sVar3;
  int *piVar4;
  bool bVar5;
  utimbuf mtime;
  int stat_result;
  stat buf;
  stat dummy;
  int TempUsed;
  char TempName [4106];
  char ExecString [12288];
  int e;
  int a;
  int ShowIt_local;
  char *FileName_local;
  
  bVar1 = false;
  e = 0;
  sVar3 = strlen(FileName);
  iVar2 = (int)sVar3;
  do {
    a = iVar2 + -1;
    bVar5 = false;
    if (0 < a) {
      bVar5 = FileName[iVar2 + -2] != '/';
    }
    iVar2 = a;
  } while (bVar5);
  memcpy(TempName,FileName,(long)a);
  strcpy(TempName + a,"XXXXXX");
  mktemp(TempName);
  if (TempName[0] == '\0') {
    ErrFatal("Cannot find available temporary file name");
  }
  a = 0;
  do {
    if (ApplyCommand[a] == '&') {
      if (ApplyCommand[a + 1] == 'i') {
        iVar2 = shellescape(ExecString + e,FileName);
        a = a + 1;
        e = iVar2 + e;
      }
      else {
        if (ApplyCommand[a + 1] != 'o') goto LAB_00101677;
        iVar2 = shellescape(ExecString + e,TempName);
        a = a + 1;
        bVar1 = true;
        e = iVar2 + e;
      }
    }
    else {
LAB_00101677:
      ExecString[e] = ApplyCommand[a];
      e = e + 1;
      if (ApplyCommand[a] == '\0') {
        if (ShowIt != 0) {
          printf("Cmd:%s\n",ExecString);
        }
        piVar4 = __errno_location();
        *piVar4 = 0;
        iVar2 = system(ExecString);
        if ((iVar2 != 0) || (piVar4 = __errno_location(), *piVar4 != 0)) {
          piVar4 = __errno_location();
          if (*piVar4 != 0) {
            perror("system");
          }
          ErrFatal("Problem executing specified command");
        }
        if (bVar1) {
          iVar2 = stat(TempName,(stat *)&dummy);
          if (iVar2 == 0) {
            iVar2 = stat(FileName,(stat *)&buf);
            unlink(FileName);
            rename(TempName,FileName);
            if (iVar2 == 0) {
              chmod(FileName,buf.st_mode);
              mtime.actime = buf.st_atim.tv_sec;
              mtime.modtime = buf.st_mtim.tv_sec;
              utime(FileName,(utimbuf *)&mtime);
            }
          }
          else {
            ErrFatal("specified command did not produce expected output file");
          }
        }
        return;
      }
    }
    a = a + 1;
  } while( true );
}