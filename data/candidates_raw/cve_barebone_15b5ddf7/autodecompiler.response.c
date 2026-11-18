void read_csc(char *inputFileName, unsigned int * row_count, unsigned int * column_count, unsigned int * element_count, double ** values, unsigned int ** row_indices, unsigned int ** column_start_indices)
{
    FILE *cscFile;
    char line[512];
    unsigned int i;
    unsigned int j;
    double x;
    unsigned int headerRead = 0;
    unsigned int * columnIdxID = NULL;
    unsigned int currentElementCount;

    cscFile = fopen(inputFileName, "r");
    if (cscFile == NULL)
    {
        return;
    }

    while (fgets(line, 512, cscFile) != NULL)
    {

        if (strlen(line) == 512)
        {
            free(*row_indices);
            free(*column_start_indices);
            free(*values);
            free(columnIdxID);

            *row_indices = NULL;
            *column_start_indices = NULL;
            *values = NULL;

            fclose(cscFile);
            return;
        }


        switch (line[0])
        {
        case '%':
            continue;
        default:
            break;
        }


        if (!headerRead)
        {
            if (___isoc99_sscanf(line, "%u %u %u", column_count, row_count, element_count) == 3)
            {
                *row_indices = (unsigned int *)malloc((*element_count)*sizeof(unsigned int));
                *column_start_indices = (unsigned int *)malloc(((*column_count)+1)*sizeof(unsigned int));
                *values = (double *)malloc((*element_count)*sizeof(double));

                columnIdxID = (unsigned int *)malloc((*column_count)*sizeof(unsigned int));

                if ((*row_indices == NULL) || (*column_start_indices == NULL) || (*values == NULL) || (columnIdxID == NULL))
                {
                    free(*row_indices);
                    free(*column_start_indices);
                    free(*values);
                    free(columnIdxID);

                    *row_indices = NULL;
                    *column_start_indices = NULL;
                    *values = NULL;

                    fclose(cscFile);
                    return;
                }


                memset(*row_indices, 0, (*element_count)*sizeof(unsigned int));
                memset(*column_start_indices, 0, ((*column_count)+1)*sizeof(unsigned int));
                memset(*values, 0, (*element_count)*sizeof(double));
                memset(columnIdxID, 0, (*column_count)*sizeof(unsigned int));


                for (i = 0; i <= *column_count; i++)
                {
                    (*column_start_indices)[i] = *element_count;
                }
                (*column_start_indices)[0] = 0;

                currentElementCount = 0;

                headerRead = 1;
            }
            else
            {
                fclose(cscFile);
                return;
            }
        }
        else
        {
            i = 0;
            j = 0;
            x = 0.0;

            if (___isoc99_sscanf(line, "%u %u %lf", &i, &j, &x) != 3)
            {
                free(*row_indices);
                free(*column_start_indices);
                free(*values);
                free(columnIdxID);

                *row_indices = NULL;
                *column_start_indices = NULL;
                *values = NULL;

                fclose(cscFile);
                return;
            }


            i--;
            j--;

            (*row_indices)[currentElementCount] = i;
            (*values)[currentElementCount] = x;

            currentElementCount++;


            columnIdxID[j] = 1;
            (*column_start_indices)[j+1] = currentElementCount;
        }
    }

    fclose(cscFile);


    if (currentElementCount != *element_count)
    {
        free(*row_indices);
        free(*column_start_indices);
        free(*values);
        free(columnIdxID);

        *row_indices = NULL;
        *column_start_indices = NULL;
        *values = NULL;

        return;
    }


    if (columnIdxID != NULL)
    {
        for (i = 0; i < *column_count; i++)
        {
            if (columnIdxID[i] == 0)
            {
                (*column_start_indices)[i+1] = (*column_start_indices)[i];
            }
        }

        free(columnIdxID);
    }
}