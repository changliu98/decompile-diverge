void __cdecl DoCommand(const char *FileName, int ShowIt)
{
  int v2; // eax
  int v3; // eax
  char v4; // cl
  int v5; // eax
  bool v6; // [rsp+Fh] [rbp-4171h]
  utimbuf mtime; // [rsp+10h] [rbp-4170h] BYREF
  int stat_result; // [rsp+24h] [rbp-415Ch]
  stat buf; // [rsp+28h] [rbp-4158h] BYREF
  stat dummy; // [rsp+B8h] [rbp-40C8h] BYREF
  int TempUsed; // [rsp+14Ch] [rbp-4034h]
  char TempName[4106]; // [rsp+150h] [rbp-4030h] BYREF
  char ExecString[12288]; // [rsp+1160h] [rbp-3020h] BYREF
  int e; // [rsp+416Ch] [rbp-14h]
  int a; // [rsp+4170h] [rbp-10h]
  int ShowIta; // [rsp+4174h] [rbp-Ch]
  const char *FileNamea; // [rsp+4178h] [rbp-8h]

  FileNamea = FileName;
  ShowIta = ShowIt;
  TempUsed = 0;
  e = 0;
  for ( a = strlen(FileName) - 1; ; --a )
  {
    v6 = 0;
    if ( a > 0 )
      v6 = FileNamea[a - 1] != 47;
    if ( !v6 )
      break;
  }
  memcpy(TempName, FileNamea, a);
  strcpy(&TempName[a], "XXXXXX");
  mktemp(TempName);
  if ( !TempName[0] )
    ErrFatal("Cannot find available temporary file name");
  for ( a = 0; ; ++a )
  {
    if ( *(_BYTE *)(ApplyCommand + a) == 38 )
    {
      if ( *(_BYTE *)(ApplyCommand + a + 1) == 105 )
      {
        v2 = shellescape(&ExecString[e], FileNamea);
        e += v2;
        ++a;
        continue;
      }
      if ( *(_BYTE *)(ApplyCommand + a + 1) == 111 )
      {
        v3 = shellescape(&ExecString[e], TempName);
        e += v3;
        ++a;
        TempUsed = 1;
        continue;
      }
    }
    v4 = *(_BYTE *)(ApplyCommand + a);
    v5 = e++;
    ExecString[v5] = v4;
    if ( !*(_BYTE *)(ApplyCommand + a) )
      break;
  }
  if ( ShowIta )
    printf("Cmd:%s\n", ExecString);
  *__errno_location() = 0;
  a = system(ExecString);
  if ( a || *__errno_location() )
  {
    if ( *__errno_location() )
      perror("system");
    ErrFatal("Problem executing specified command");
  }
  if ( TempUsed )
  {
    if ( stat(TempName, &dummy) )
      ErrFatal("specified command did not produce expected output file");
    stat_result = stat(FileNamea, &buf);
    unlink(FileNamea);
    rename(TempName, FileNamea);
    if ( !stat_result )
    {
      chmod(FileNamea, buf.st_mode);
      mtime.actime = buf.st_atim.tv_sec;
      mtime.modtime = buf.st_mtim.tv_sec;
      utime(FileNamea, &mtime);
    }
  }
}