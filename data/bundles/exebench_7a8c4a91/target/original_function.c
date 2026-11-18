void removeCharactersInPlace(char* aString, char* excludeChars) {




    char* address = aString;


    while( *aString != '\0' ) {


        bool found = false;
        char* excludePtr = excludeChars;
        do {
            found = *aString == *excludePtr ? true : false;
            ++excludePtr;
        } while( *excludePtr != '\0' && !found );



        if (!found) {
            *address = *aString;
            ++address;
        }

        ++aString;
    }


    *address = '\0';
}