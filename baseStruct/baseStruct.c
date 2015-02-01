#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>


#include "../hedder/uthash.h"
#include "baseStruct.h"

char** str_split(char* a_str, const char a_delim)
{

    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    //allocate memory for final result
    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        //get a token one by one
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
void add_item(char* key, char *value,struct keyValue_struct** list) {

    //make a pointer to the one node
    struct keyValue_struct *s;
    //allocate memory for that
    s = malloc(sizeof(struct keyValue_struct));

    strcpy(s->key, key);
    strcpy(s->value,value);
    /* key: name of key field */
    HASH_ADD_INT(*list,key, s );

}
char* JSONstringify(struct keyValue_struct** list)
{
    char* msg;
    struct keyValue_struct *s;
    msg=malloc(500);
    strcpy(msg,"{");
    //if (formData) {


    for(s=*list; s != NULL; s=(struct keyValue_struct*)(s->hh.next)) {

        if (s->key && strcmp(s->value,"")) {

            //ap_rprintf(r, "%s = %s\n", formData[i].key, formData[i].value);
            strcat(msg,"\"");
            strcat(msg,s->key);
            strcat(msg,"\":\"");
            strcat(msg,s->value);
            strcat(msg,"\",");

        } else if (s->key) {

            //ap_rprintf(r, "%s\n", formData[i].key);
            strcat(msg,"\"");
            strcat(msg,s->key);
            strcat(msg,"\":\"");
            strcat(msg,"\",");
        } else if (!strcmp(s->value,"")) {

            //ap_rprintf(r, "= %s\n", formData[i].value);
            strcat(msg,"\"");
            strcat(msg,"\":\"");
            strcat(msg,s->value);
            strcat(msg,"\",");

        } else {
            break;
        }
    }
    strcat(msg,"}");
    msg[strlen(msg)-2]=' ';
    return msg;
    //}
    return NULL;
}
void getKeyValue(struct keyValue_struct** list) {
    struct keyValue_struct *s;
    //travel through hashmap and prints all key-value pairs
    for(s=*list; s != NULL; s=(struct keyValue_struct*)(s->hh.next)) {
        printf("%s:%s\n", s->key, s->value);
    }
}
struct keyValue_struct *getValue(char* key,struct keyValue_struct** list) {
    struct keyValue_struct *s;

    HASH_FIND_INT( *list, key, s );  /* s: output pointer */

    return s;
}


//http://creativeandcritical.net/str-replace-c/
char *str_replace(const char *str, const char *old, const char *newOne)
{
    char *ret, *r;
    const char *p, *q;
    size_t oldlen = strlen(old);
    size_t count, retlen, newlen = strlen(newOne);

    if (oldlen != newlen) {
        for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
            count++;
        /* this is undefined if p - str > PTRDIFF_MAX */
        retlen = p - str + strlen(p) + count * (newlen - oldlen);
    } else
        retlen = strlen(str);

    if ((ret = malloc(retlen + 1)) == NULL)
        return NULL;

    for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) {
        /* this is undefined if q - p > PTRDIFF_MAX */
        ptrdiff_t l = q - p;
        memcpy(r, p, l);
        r += l;
        memcpy(r, newOne, newlen);
        r += newlen;
    }
    strcpy(r, p);

    return ret;
}

void add_toList(struct keyValue_struct** list,char* data,char splitCon1,char splitCon2){
    char** tokens;
    char** keyPair;
    char* req;

    req=malloc(sizeof(char)*strlen(data)+1);
    strcpy(req,data);
    /*let's say json string or query string should be in this format
        json_str={"a":12,...}
        query_str= name=Johne&password=ttyugfd and so.
        when it is splitted by condition one those strings are look like this
        json_str_tokens [a:123,...]
        query_str_tokens [name=John,password=ttyugfd] ...
        when splited strings are splitted by second condition. Then
        key and value can be  seperated easylly so then those key-value pairs are saved in hashmap
        this is what this function does
    */
    tokens = str_split(req,splitCon1);

    if (tokens)
    {
        int i,j;
        for (i = 0; *(tokens + i); i++)
        {
            j=0;
            keyPair=str_split(*(tokens + i), splitCon2);
            if(keyPair){
                char* key;
                key=malloc(100);
                if(*(keyPair+j)){

                    char test_buffer[100];
                    strcpy(test_buffer,*(keyPair+j));
                    char* trimmed=str_trim(test_buffer);
                    strcpy(key,trimmed);
                    j++;
                }

                if(*(keyPair+j)){
                    add_item(key,*(keyPair+j),list);
                }else{
                    add_item(key,"",list);
                }

            }
            //free(*(tokens + i));

        }
        //printf("\n");
        //free(tokens);
    }
}


//http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
char *str_trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace(*frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace(*(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}
