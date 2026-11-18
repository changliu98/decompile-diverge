
void cgi_alert_get_action(char * shm){
 *(int *)(shm+sizeof(int)) = 3;
 *(int *)(shm+sizeof(int)*2) = 1;
}
