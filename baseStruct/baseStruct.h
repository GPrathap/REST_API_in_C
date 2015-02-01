
#include "../hedder/uthash.h"

/**
 * This struct is used to save one key-value pair
 */
struct keyValue_struct {

    char key[128]; /* I'll use this field as the key */
    char value[512]; /*value with respec to key */
    UT_hash_handle hh;/* makes this structure hashable */

};

/**
 * String replace
 * @param		str  string is to be modified
 * @param		old  string is to be replaced
 * @param		new string is to be added
 */
char *str_replace(const char *str, const char *old, const char *newOne);

/**
 * Spliting string into n number of parts
 * @param		a_str    string is to be splitted
 * @param		a_delim  setting a delimiter
 */
char** str_split(char* a_str, const char a_delim);

/**
 * Addind key-value pair to list(hashmap)
 * @param		key    key
 * @param		value  value
 * @param		list   pointer to hashmap
 */
void add_item(char* key, char *value,struct keyValue_struct** list);

/**
 * Create a json string using  key-value pairs
 * @param		list  pointer to list(hashmap)
 */
char* JSONstringify(struct keyValue_struct** list);

/**
 * Print all key-value pairs in the hashmap
 * @param		list pointer to list(hashmap)
 */
void getKeyValue(struct keyValue_struct** list);

/**
 * Getting value for given key from list(hashmap)
 * @param		key  key
 * @param		list pointer to hashmap
 */
struct keyValue_struct *getValue(char* key,struct keyValue_struct** list);

/**
 * adding key-value pairs to hashmap
 * @param		data        json string or query string
 * @param       splitCon1   first splitting string into parts using this
 * @param       splitCon2   splited strings are splited using this
 * @param		list pointer to hashmap
 */
void add_toList(struct keyValue_struct** list,char* data,char splitCon1,char splitCon2);

/**
 * Removing withspaces
 * @param		source,str string is to be modified
 */
void str_removeSpace(char* source);
char *str_trim(char *str);



