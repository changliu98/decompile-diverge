void
Mat_GetLibraryVersion(int *major,int *minor,int *release)
{
    if ( NULL != major )
        *major = 1;
    if ( NULL != minor )
        *minor = 5;
    if ( NULL != release )
        *release = 9;
}