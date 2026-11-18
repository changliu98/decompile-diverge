void c_unlink_(char *path, int *iostat, int plen){
    int istat;
    if( unlink(path) != 0 ){
 istat = (*___errno_location());
    }else{
 istat = 0;
    }
    *iostat = istat;
}