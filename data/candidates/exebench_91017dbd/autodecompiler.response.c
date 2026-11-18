void ddelete_c(char *path, int *iostat, int plen){
    int istat;
    if( unlink(path) != 0 ){
 istat = (*___errno_location());
    }else{
 istat = 0;
    }
    *iostat = istat;
}