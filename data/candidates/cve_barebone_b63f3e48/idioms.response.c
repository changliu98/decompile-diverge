void DoCommand(char *FileName, int ShowIt)
{
  char *FileNamea = FileName;
  int ShowIta = ShowIt;
  int i;
  int e = 0;
  int TempUsed = 0;
  char TempName[-1];
  char ExecString[-1];
  char *ptr;
  struct stat statbuf;
  struct stat statbuf1;
  struct utimbuf utimebuf;
  int ret;
  for (i = GetFileNameLength(FileName) - 1; ; --i)
  {
    int isdir = 0;
    if (i > 0)
      isdir = FileNamea[i - 1] != '/';
    if (!isdir)
      break;
  }
  GetPathName(TempName, FileNamea, i);
  GetFileName(&TempName[i], "XXXXXX");
  GetDirName(TempName);
  if (TempName[0] == '\0')
    FatalError("Cannot find available temporary file name");
  for (i = 0; ; ++i)
  {
    if (ApplyCommand[i] == '&')
    {
      if (ApplyCommand[i + 1] == 'i')
      {
        e += GetString(&ExecString[e], FileNamea);
        ++i;
        continue;
      }
      if (ApplyCommand[i + 1] == 'o')
      {
        e += GetString(&ExecString[e], TempName);
        ++i;
        TempUsed = 1;
        continue;
      }
    }
    ExecString[e++] = ApplyCommand[i];
    if (ApplyCommand[i] == '\0')
      break;
  }
  if (ShowIta)
    OutputString("Cmd:%s\n", ExecString);
  ptr = GetErrorString();
  *ptr = '\0';
  i = System(ExecString);
  if (i != 0 || (ptr = GetErrorString()) != ((void *)0))
  {
    if (ptr != ((void *)0))
      GetSystemError("system");
    FatalError("Problem executing specified command");
  }
  if (TempUsed)
  {
    if (stat(TempName, &statbuf))
      FatalError("specified command did not produce expected output file");
    ret = stat(FileNamea, &statbuf1);
    DeleteFile(FileNamea);
    CopyFile(TempName, FileNamea);
    if (ret == 0)
    {
      SetFileMode(FileNamea, statbuf.st_mode);
      utimebuf.actime = statbuf.st_atim.tv_sec;
      utimebuf.modtime = statbuf.st_mtim.tv_sec;
      Utime(FileNamea, &utimebuf);
    }
  }
}