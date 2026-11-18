int check_attr_len(int attr_len, int attr_type) {
    return attr_len == attr_type || 
           attr_type == OVS_ATTR_NESTED || 
           attr_type == OVS_ATTR_VARIABLE;
}