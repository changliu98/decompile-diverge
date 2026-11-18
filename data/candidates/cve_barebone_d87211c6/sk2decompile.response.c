static VALUE rb_xml_reader_attribute_hash(VALUE reader) {
  VALUE hash = rb_hash_new();
  if (has_attributes((xmlTextReaderPtr)reader)) {
    xmlNodePtr node = xmlTextReaderExpand((xmlTextReaderPtr)reader);
    xmlAttrPtr attr;
    for (attr = node->properties; attr; attr = attr->next) {
      VALUE name = nokogiri_str_new2_stub((const char *)attr->name);
      VALUE value = ((VALUE)0);
      xmlChar *content = xmlNodeGetContent(attr);
      if (content) {
        value = nokogiri_str_new2_stub((const char *)content);
        free(content);
      }
      rb_hash_aset(hash, name, value);
    }
  }
  return hash;
}