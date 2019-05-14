#ifndef SELENIUM_H_INCLUDED
#define SELENIUM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "sds/sds.h"
#include "cJSON/cJSON.h"
#include <glib.h>

typedef enum {
    SELENIUM_SUCCESS = 0,
    SELENIUM_NOSUCHDRIVER = 6,
    SELENIUM_NOSUCHELEMENT = 7,
    SELENIUM_NOSUCHFRAME = 8,
    SELENIUM_UNKNOWNCOMMAND = 9,
    SELENIUM_STALEELEMENTREFERENCE = 10,
    SELENIUM_ELEMENTNOTVISIBLE = 11,
    SELENIUM_INVALIDELEMENTSTATE = 12,
    SELENIUM_UNKNOWNERROR = 13,
    SELENIUM_ELEMENTISNOTSELECTABLE = 15,
    SELENIUM_JAVASCRIPTERROR = 17,
    SELENIUM_XPATHLOOKUPERROR = 19,
    SELENIUM_TIMEOUT = 21,
    SELENIUM_NOSUCHWINDOW = 23,
    SELENIUM_INVALIDCOOKIEDOMAIN = 24,
    SELENIUM_UNABLETOSETCOOKIE = 25,
    SELENIUM_UNEXPECTEDALERTOPEN = 26,
    SELENIUM_NOALERTOPENERROR = 27,
    SELENIUM_SCRIPTTIMEOUT = 28,
    SELENIUM_INVALIDELEMENTCOORDINATES = 29,
    SELENIUM_IMENOTAVAILABLE = 30,
    SELENIUM_IMEENGINEACTIVATIONFAILED = 31,
    SELENIUM_INVALIDSELECTOR = 32,
    SELENIUM_SESSIONNOTCREATEDEXCEPTION = 33,
    SELENIUM_MOVETARGETOUTOFBOUNDS = 34,
    SELENIUM_CURL_REQUEST_ERROR = 100,
} SELENIUM_CODE;

typedef enum {
    SELENIUM_ELEMENT_ID,
    SELENIUM_ELEMENT_NAME
} SELENIUM_ELEMENT_SELECTOR;

typedef enum {
    CHROME,
    FIREFOX
} SELENIUM_WEBDRIVER_TYPE;

typedef enum {
    SELENIUM_POST,
    SELENIUM_DELETE
} SELENIUM_METHOD;

struct selenium_element_priv {
    char selenium_internal_id[30];
};
struct selenium_element {
    struct selenium_element_priv priv;
};

struct selenium_priv {
    char *browser_agent;
    char *session_url;
    GHashTable* errorsMessages;
    GHashTable* errorsShortMessages;
};
struct desired_capabilites {
    SELENIUM_WEBDRIVER_TYPE browser;
    char *platform;
};

struct session {
    char session_id[33];
};
struct selenium {
    struct selenium_priv priv;
    struct desired_capabilites desired_capabilites;
    struct session session;
    char *error;
    char *url;
    int port;
    int last_error_code;
    char last_error_message[300];
    char last_error_short_message[50];
};

#define SELENIUM_JSON cJSON *

#define JSON_LOAD_OBJ(JSON, JSTR) JSON = cJSON_Parse(JSTR);

#define JSON_GET_STR(JSON, ATTRIBUTE, VARIABLE) \
if (JSON != NULL) { \
    cJSON *attribute_json_ ## VARIABLE = cJSON_GetObjectItemCaseSensitive(JSON, ATTRIBUTE); \
    if (cJSON_IsString(attribute_json_ ## VARIABLE) && (attribute_json_ ## VARIABLE->valuestring != NULL)) { \
        VARIABLE = strdup(attribute_json_ ## VARIABLE->valuestring);  \
    } \
    else { VARIABLE = NULL; } \
} else { VARIABLE = NULL; };

#define JSON_GET_INT(JSON, ATTRIBUTE, VARIABLE) \
if (JSON != NULL) { \
    cJSON *attribute_json_ ## VARIABLE = cJSON_GetObjectItemCaseSensitive(JSON, ATTRIBUTE); \
    if (cJSON_IsBool(attribute_json_ ## VARIABLE)) { \
        if (cJSON_IsTrue(attribute_json_ ## VARIABLE)) VARIABLE = 1; \
        if (cJSON_IsFalse(attribute_json_ ## VARIABLE)) VARIABLE = 0; \
    } else if (cJSON_IsNumber(attribute_json_ ## VARIABLE)) { \
        VARIABLE = attribute_json_ ## VARIABLE->valueint;  \
    } \
    else { VARIABLE = 0; } \
} else { VARIABLE = 0; };


#define JSON_GET_OBJ(JSON, ATTRIBUTE, VARIABLE) \
if (JSON != NULL) { \
    cJSON *attribute_json_ ## VARIABLE = cJSON_GetObjectItemCaseSensitive(JSON, ATTRIBUTE); \
    if (cJSON_IsObject(attribute_json_ ## VARIABLE)) { \
        VARIABLE = attribute_json_ ## VARIABLE;  \
    } \
    else { VARIABLE = 0; } \
} else { VARIABLE = 0; };

#define JSON_UNLOAD_OBJ(JSON) cJSON_Delete(JSON);

typedef struct selenium SELENIUM;
typedef struct selenium_element SELENIUM_ELEMENT;
void selenium_new(SELENIUM *, char*, int);
int selenium_clean(SELENIUM *);
int selenium_create_session(SELENIUM *);
int selenium_navigate(SELENIUM *, char*);
int selenium_get_element_by(SELENIUM *, SELENIUM_ELEMENT_SELECTOR, char*, SELENIUM_ELEMENT*);
int selenium_advanced_request(SELENIUM *, SELENIUM_METHOD , char *,char* , char **);



#endif // SELENIUM_H_INCLUDED
