void __cdecl DoCommand(const char *FileName, int ShowIt)
{
  bool is_temp_used = false;
  utimbuf mtime;
  int stat_result;
  struct stat original_stat;
  struct stat temp_stat;
  char TempName[4106];
  char ExecString[12288];
  int exec_len = 0;
  int base_name_len;
  
  // Find the length of the base name (ignoring trailing slashes)
  for ( base_name_len = strlen(FileName) - 1; ; --base_name_len )
  {
    bool is_not_slash = false;
    if ( base_name_len > 0 )
      is_not_slash = FileName[base_name_len - 1] != '/';
    if ( !is_not_slash )
      break;
  }
  
  // Construct a template for mktemp by replacing the base name with "XXXXXX"
  memcpy(TempName, FileName, base_name_len);
  strcpy(&TempName[base_name_len], "XXXXXX");
  mktemp(TempName);
  
  if ( !TempName[0] )
    ErrFatal("Cannot find available temporary file name");
  
  // Build the execution string by parsing the ApplyCommand template
  for ( int i = 0; ; ++i )
  {
    // Check for template variables '&i' (input file) and '&o' (output file)
    if ( ApplyCommand[i] == '&' )
    {
      if ( ApplyCommand[i + 1] == 'i' )
      {
        exec_len += shellescape(&ExecString[exec_len], FileName);
        ++i; // Skip the 'i'
        continue;
      }
      if ( ApplyCommand[i + 1] == 'o' )
      {
        exec_len += shellescape(&ExecString[exec_len], TempName);
        ++i; // Skip the 'o'
        is_temp_used = true;
        continue;
      }
    }
    
    // Copy standard characters to the execution string
    ExecString[exec_len++] = ApplyCommand[i];
    if ( !ApplyCommand[i] )
      break;
  }
  
  if ( ShowIt )
    printf("Cmd:%s\n", ExecString);
    
  // Execute the command
  errno = 0;
  int exit_status = system(ExecString);
  if ( exit_status || errno )
  {
    if ( errno )
      perror("system");
    ErrFatal("Problem executing specified command");
  }
  
  // If the command used an output file, replace the original with the temp file
  if ( is_temp_used )
  {
    if ( stat(TempName, &temp_stat) )
      ErrFatal("specified command did not produce expected output file");
      
    // Preserve the original file's metadata
    stat_result = stat(FileName, &original_stat);
    unlink(FileName);
    rename(TempName, FileName);
    
    if ( !stat_result )
    {
      chmod(FileName, original_stat.st_mode);
      mtime.actime = original_stat.st_atim.tv_sec;
      mtime.modtime = original_stat.st_mtim.tv_sec;
      utime(FileName, &mtime);
    }
  }
}