enum GF_Err Media_CheckDataEntry(struct _GF_MediaBox *self, unsigned int dataEntryIndex, struct _GF_DataEntryURLBox **dataEntryURLBox)
{
    if (self == ((void *)0))
    {
        return GF_ERR_INVALID_PARAM;
    }
    if (dataEntryIndex == 0 || dataEntryIndex > GF_MediaBox_GetNumDataEntries(self))
    {
        return GF_ERR_INVALID_PARAM;
    }
    struct _GF_DataEntryURLBox *dataEntry = GF_MediaBox_GetDataEntryURLBoxAt(self->information->dataInformation->dref->child_boxes, dataEntryIndex - 1);
    if (dataEntry == ((void *)0))
    {
        return GF_ERR_NOT_FOUND;
    }
    if (dataEntry->flags == 1)
    {
        return GF_OK;
    }
    if (dataEntry->type == 0x7061696c)
    {
        return GF_ERR_UNSUPPORTED;
    }
    struct _GF_DataMap *dataMap;
    enum GF_Err err;
    if (self->mediaTrack->moov->mov->openMode == GF_ISOM_OPEN_WRITE)
    {
        err = GF_MediaBox_GetMapForURL(dataEntry->location, ((void *)0), 1, &dataMap);
    }
    else
    {
        err = GF_MediaBox_GetMapForURL(dataEntry->location, self->mediaTrack->moov->mov->fileName, 1, &dataMap);
    }
    if (err != GF_OK)
    {
        return err;
    }
    GF_MediaBox_FreeDataMap(dataMap);
    return GF_OK;
}