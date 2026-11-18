void DoCommand(char *FileName,int ShowIt)
{
    char TempName[4096];
    char ExecString[12288];
    int a,e;
    int TempUsed=0;
    int stat_result;
    struct stat buf,dummy;
    struct utimbuf mtime;





    a=strlen(FileName);
    do {
        a--;
    } while (a>0 && FileName[a-1]!='/');
    memcpy(TempName,FileName,(size_t)a);
    strcpy(TempName+a,"XXXXXX");
    mktemp(TempName);
    if (TempName[0]=='\0') ErrFatal("Cannot find available temporary file name");





    a=0;
    e=0;
    while (1) {
        if (ApplyCommand[a]=='&') {
            a++;
            if (ApplyCommand[a]=='i') {
                e+=shellescape(ExecString+e,FileName);
                a++;
                continue;
            } else if (ApplyCommand[a]=='o') {
                e+=shellescape(ExecString+e,TempName);
                TempUsed=1;
                a++;
                continue;
            }
        }
        ExecString[e]=ApplyCommand[a];
        e++;
        if (ApplyCommand[a]=='\0') break;
        a++;
    }
    if (ShowIt) printf("Cmd:%s\n",ExecString);





    *__errno_location()=0;
    stat_result=system(ExecString);
    if (stat_result!=0 || *__errno_location()!=0) {
        if (*__errno_location()!=0) perror("system");
        ErrFatal("Problem executing specified command");
    }





    if (TempUsed) {
        if (!stat(TempName,&dummy)) {
            stat_result=stat(FileName,&buf);
            unlink(FileName);
            rename(TempName,FileName);
            if (stat_result==0) {
                chmod(FileName,buf.st_mode);
                mtime.actime=buf.st_atime;
                mtime.modtime=buf.st_mtime;
                utime(FileName,&mtime);
            }
        } else ErrFatal("specified command did not produce expected output file");
    }
}