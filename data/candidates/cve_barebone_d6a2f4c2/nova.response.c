static void nfs_printfh(struct sltg_typelib *sltg, const void *data, unsigned int size)
{
    static const char * const type_names[] = { "Void", "Bool", "Char", "WChar", "Byte", "Short", "UShort", "Int", "UInt", "Long", "ULong", "Hyper", "Float", "Double", "Currency", "Date", "BStr", "Dispatch", "Error", "Variant", "Unknown", "Decimal", "Int16", "Int32", "Int64", "Int128", "Int256", "UInt16", "UInt32", "UInt64", "UInt128", "UInt256", "IDispatch", "Struct", "Union", "Enum", "Interface", "CoClass", "Alias", "OleClass", "DispatchInterface", "Void*" };
    static char type_name[64];
    const struct sltg_type *type;
    unsigned int i, j, k, l, m, n;
    char *p;

    if (sltg->typelib.typelib_version)
    {
        static const char * const type_names_v1[] = { "Void", "Bool", "Char", "WChar", "Byte", "Short", "UShort", "Int", "UInt", "Long", "ULong", "Hyper", "Float", "Double", "Currency", "Date", "BStr", "Dispatch", "Error", "Variant", "Unknown", "Decimal", "Int16", "Int32", "Int64", "Int128", "Int256", "UInt16", "UInt32", "UInt64", "UInt128", "UInt256", "IDispatch", "Struct", "Union", "Enum", "Interface", "CoClass", "Alias", "OleClass", "DispatchInterface", "Void*", "Char*", "WChar*", "Byte*", "Short*", "UShort*", "Int*", "UInt*", "