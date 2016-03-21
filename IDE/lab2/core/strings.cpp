//
// Created by nick on 3/13/16.
//

#include <stdio.h>
#include <string.h>
#include "strings.h"

char *replace_str(char *str, char *orig, char *rep, int start)
{
    static char temp[4096];
    static char buffer[4096];
    char *p;

    strcpy(temp, str + start);

    if(!(p = strstr(temp, orig)))  // Is 'orig' even in 'temp'?
        return temp;

    strncpy(buffer, temp, p-temp); // Copy characters from 'temp' start to 'orig' str
    buffer[p-temp] = '\0';

    sprintf(buffer + (p - temp), "%s%s", rep, p + strlen(orig));
    sprintf(str + start, "%s", buffer);

    return str;
}

char* reformat(char* input)
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ')
            output[j]=input[i];
        else
            j--;
    }
    output[j]=0;
    replace_str(output, (char *) "+-", (char *) "-", 0);
    replace_str(output, (char *) "-+", (char *) "-", 0);
    replace_str(output, (char *) "--", (char *) "+", 0);
    replace_str(output, (char *) "++", (char *) "+", 0);
    replace_str(output, (char *) "**", (char *) "*", 0);
    replace_str(output, (char *) "//", (char *) "/", 0);

    return output;
}