void* rb_xml_reader_attribute_hash(void* reader) {
    void* hash = rb_hash_new();
    
    if (!has_attributes(reader)) {
        return hash;
    }
    
    void* expanded_node = xmlTextReaderExpand(reader);
    struct xmlNode* attr = ((struct xmlNodeExpanded*)expanded_node)->properties;
    
    while (attr != NULL) {
        void* key = nokogiri_str_new2_stub(attr->name);
        void* value = NULL;
        
        void* content = xmlNodeGetContent(attr);
        if (content != NULL) {
            value = nokogiri_str_new2_stub(content);
            free(content);
        }
        
        rb_hash_aset(hash, key, value);
        attr = attr->next;
    }
    
    return hash;
}