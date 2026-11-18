void _EJDBBSONCountUp(EJDBBSON obj) {
    ((volatile int32_t*)obj)[-1]++;
}