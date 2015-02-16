
#include "./headerfile/curlreq.h"

struct response_data *makeCURLRequest(char* reqbody,char* cookie,int memorySize,char* url){
                CURL *curl;

                        struct url_data data;
                        data.size = 0;
                        data.data = malloc(memorySize); /* reasonable size initial buffer */

                        if(NULL == data.data) {

                                    fprintf(stderr, "Failed to allocate memory.\n");
                                    return NULL;
                        }

                        struct site_cookie cookiec;
                        cookiec.size=0;
                        cookiec.cookie=malloc(256);
                        if(NULL == cookiec.cookie) {

                                    fprintf(stderr, "Failed to allocate memory.\n");
                                    return NULL;
                        }

                        struct response_data* res_data;
                        res_data=malloc(sizeof(struct response_data));
                        res_data->res_body=malloc(1000);
                        res_data->res_cookie=malloc(256);

                        if(NULL == res_data->res_body || NULL==res_data->res_cookie) {

                                    fprintf(stderr, "Failed to allocate memory.\n");
                                    return NULL;

                        }
                         struct curl_slist *headers = NULL;
                         headers = curl_slist_append(headers, "Accept: Subscription/x-www-form-urlencoded");
                         headers = curl_slist_append(headers, "Content-Type: Subscription/x-www-form-urlencoded");
                         headers = curl_slist_append(headers, "charsets: utf-8");

                        data.data[0] = '\0';
                        cookiec.cookie[0]= '\0';
                        res_data->res_body[0]='\0';
                        res_data->res_cookie[0]='\0';

                        buf_t *buf = buf_size(NULL, BUFFER_SIZE);

                        CURLcode res;
                        curl_global_init(CURL_GLOBAL_ALL);

                        curl = curl_easy_init();
                        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
                        //curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
                        curl_easy_setopt(curl, CURLOPT_URL,url);
                        curl_easy_setopt(curl, CURLOPT_POST, 1);
                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,reqbody);
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_data);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
                        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
                        curl_easy_setopt(curl, CURLOPT_HEADERDATA,&cookiec);
                        curl_easy_setopt(curl, CURLOPT_COOKIE,cookie);
                        res=curl_easy_perform(curl);

                        if(res != CURLE_OK){

                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                            return NULL;

                        }

                         curl_easy_cleanup(curl);
                         char *jsonstr = buf_tostr(buf);
                         free(buf->data);
                         free(buf);
                         strcpy(res_data->res_body,jsonstr);
                         strcpy(res_data->res_cookie,cookiec.cookie);

                return res_data;

}


