/* WARNING: Unknown calling convention -- yet parameter storage is locked */

wchar_t load_terminfo(void)

{
  wchar_t wVar1;
  int iVar2;
  char *term_00;
  char *pcVar3;
  char *cdir;
  char *dir;
  char *dirs;
  char *home;
  char *terminfo;
  char *term;
  char tmp [4096];
  wchar_t rv;
  wchar_t local_c;
  
  term_00 = getenv("TERM");
  if (term_00 == (char *)0x0) {
    local_c = L'\xffffffff';
  }
  else {
    pcVar3 = getenv("TERMINFO");
    if ((pcVar3 == (char *)0x0) || (wVar1 = load_terminfo_from_path(pcVar3,term_00), wVar1 != L'\0')
       ) {
      pcVar3 = getenv("HOME");
      if (pcVar3 != (char *)0x0) {
        iVar2 = snprintf(tmp,0x1000,"%s/.terminfo",pcVar3);
        if ((iVar2 < 0) || (0xfff < iVar2)) {
          return L'\xffffffff';
        }
        wVar1 = load_terminfo_from_path(tmp,term_00);
        if (wVar1 == L'\0') {
          return L'\0';
        }
      }
      pcVar3 = getenv("TERMINFO_DIRS");
      if (pcVar3 != (char *)0x0) {
        iVar2 = snprintf(tmp,0x1000,"%s",pcVar3);
        if ((iVar2 < 0) || (0xfff < iVar2)) {
          return L'\xffffffff';
        }
        dir = strtok(tmp,":");
        while (dir != (char *)0x0) {
          if ((*dir != '\0') && (wVar1 = load_terminfo_from_path(dir,term_00), wVar1 == L'\0')) {
            return L'\0';
          }
          dir = strtok((char *)0x0,":");
        }
      }
      wVar1 = load_terminfo_from_path("/usr/local/etc/terminfo",term_00);
      if (wVar1 == L'\0') {
        local_c = L'\0';
      }
      else {
        wVar1 = load_terminfo_from_path("/usr/local/share/terminfo",term_00);
        if (wVar1 == L'\0') {
          local_c = L'\0';
        }
        else {
          wVar1 = load_terminfo_from_path("/usr/local/lib/terminfo",term_00);
          if (wVar1 == L'\0') {
            local_c = L'\0';
          }
          else {
            wVar1 = load_terminfo_from_path("/etc/terminfo",term_00);
            if (wVar1 == L'\0') {
              local_c = L'\0';
            }
            else {
              wVar1 = load_terminfo_from_path("/usr/share/terminfo",term_00);
              if (wVar1 == L'\0') {
                local_c = L'\0';
              }
              else {
                wVar1 = load_terminfo_from_path("/usr/lib/terminfo",term_00);
                if (wVar1 == L'\0') {
                  local_c = L'\0';
                }
                else {
                  wVar1 = load_terminfo_from_path("/usr/share/lib/terminfo",term_00);
                  if (wVar1 == L'\0') {
                    local_c = L'\0';
                  }
                  else {
                    wVar1 = load_terminfo_from_path("/lib/terminfo",term_00);
                    if (wVar1 == L'\0') {
                      local_c = L'\0';
                    }
                    else {
                      local_c = L'\xffffffff';
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      local_c = L'\0';
    }
  }
  return local_c;
}