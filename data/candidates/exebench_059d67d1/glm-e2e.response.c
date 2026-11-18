void sun_timeofday2time(long time, int *hours, int *minutes, int *seconds) {
    *hours = time / 3600;
    *minutes = (time % 3600) / 60;
    *seconds = time % 60;
}