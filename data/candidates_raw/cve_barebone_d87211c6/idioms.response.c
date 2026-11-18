static struct _xmlNode *xml_get_attributes(struct _xmlTextReader *reader)
{
  struct _xmlNode *attributes = ((void *)0);
  struct _xmlNode *property = ((void *)0);
  struct _xmlNode *name = ((void *)0);
  char *value = ((void *)0);
  struct _xmlNode *rb_name = ((void *)0);
  struct _xmlNode *rb_value = ((void *)0);
  attributes = xml_get_nodelist();
  if ( !xml_is_start_element(reader) )
    return attributes;
  property = xml_get_property(reader);
  for ( property = property->properties;
        property != ((void *)0);
        property = property->next )
  {
    name = (struct _xmlNode *)property->name;
    rb_name = xml_get_string((char *)name);
    rb_value = ((void *)0);
    value = xml_get_string_value(property);
    if ( value != ((void *)0) )
    {
      rb_value = xml_get_string((char *)value);
      xml_free(value);
    }
    xml_set_attribute(attributes, rb_name, rb_value);
  }
  return attributes;
}