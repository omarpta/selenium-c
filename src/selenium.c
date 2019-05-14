#include "selenium.h"

struct HtmlData
{
    char *str;
    size_t size;
};


static int selenium_request(SELENIUM *selenium, SELENIUM_METHOD method, char *urlPart ,char* postdata, char **ret_str);
static size_t
WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
static char *get_browser_name(SELENIUM_WEBDRIVER_TYPE webdriver);
static void set_selenium_error_messagess(SELENIUM *, int);
static void lstr(char *);
static void lstr(char *msg) {
    printf("%s\n", msg);
}
static void set_selenium_error_messagess(SELENIUM *selenium, int error_code) {
    char error_code_str[3];
    gpointer errorMessage;
    gpointer errorShortMessage;
    getmessage:
    sprintf(error_code_str, "%d", error_code);
    errorMessage = g_hash_table_lookup(selenium->priv.errorsMessages, error_code_str);
    errorShortMessage = g_hash_table_lookup(selenium->priv.errorsShortMessages, error_code_str);
    selenium->last_error_code = error_code;

    selenium->last_error_message[0] = '\0';
    selenium->last_error_short_message[0] = '\0';
    if (errorMessage != NULL && errorShortMessage != NULL) {
        sprintf(selenium->last_error_message,"%s", (char *) errorMessage);
        sprintf(selenium->last_error_short_message,"%s",  (char *) errorShortMessage);
    } else { error_code_str[0] = '\0'; error_code = 13; goto getmessage; }

    //g_free(errorMessage);
    //g_free(errorShortMessage);

}

void selenium_new(SELENIUM * selenium, char *url, int port) {
    selenium->priv.browser_agent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36";
    selenium->url = url;
    selenium->port = port;
    strcpy(selenium->session.session_id, "");
    selenium->priv.session_url = (char*) malloc((strlen(selenium->url) + 16) * sizeof(char));
    strcpy(selenium->priv.session_url, selenium->url);
    strcat(selenium->priv.session_url, "/wd/hub/session");
    selenium->desired_capabilites.browser = CHROME;
    selenium->desired_capabilites.platform = "Linux";
    selenium->priv.errorsMessages = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(selenium->priv.errorsMessages, "0","The command executed successfully.");
    g_hash_table_insert(selenium->priv.errorsMessages, "6","A session is either terminated or not started");
    g_hash_table_insert(selenium->priv.errorsMessages, "7","An element could not be located on the page using the given search parameters.");
    g_hash_table_insert(selenium->priv.errorsMessages, "8","A request to switch to a frame could not be satisfied because the frame could not be found.");
    g_hash_table_insert(selenium->priv.errorsMessages, "9","The requested resource could not be found, or a request was received using an HTTP method that is not supported by the mapped resource.");
    g_hash_table_insert(selenium->priv.errorsMessages, "10","An element command failed because the referenced element is no longer attached to the DOM.");
    g_hash_table_insert(selenium->priv.errorsMessages, "11","An element command could not be completed because the element is not visible on the page.");
    g_hash_table_insert(selenium->priv.errorsMessages, "12","An element command could not be completed because the element is in an invalid state (e.g. attempting to click a disabled element).");
    g_hash_table_insert(selenium->priv.errorsMessages, "13","An unknown server-side error occurred while processing the command.");
    g_hash_table_insert(selenium->priv.errorsMessages, "15","An attempt was made to select an element that cannot be selected.");
    g_hash_table_insert(selenium->priv.errorsMessages, "17","An error occurred while executing user supplied JavaScript.");
    g_hash_table_insert(selenium->priv.errorsMessages, "19","An error occurred while searching for an element by XPath.");
    g_hash_table_insert(selenium->priv.errorsMessages, "21","An operation did not complete before its timeout expired.");
    g_hash_table_insert(selenium->priv.errorsMessages, "23","A request to switch to a different window could not be satisfied because the window could not be found.");
    g_hash_table_insert(selenium->priv.errorsMessages, "24","An illegal attempt was made to set a cookie under a different domain than the current page.");
    g_hash_table_insert(selenium->priv.errorsMessages, "25","A request to set a cookie's value could not be satisfied.");
    g_hash_table_insert(selenium->priv.errorsMessages, "26","A modal dialog was open, blocking this operation");
    g_hash_table_insert(selenium->priv.errorsMessages, "27","An attempt was made to operate on a modal dialog when one was not open.");
    g_hash_table_insert(selenium->priv.errorsMessages, "28","A script did not complete before its timeout expired.");
    g_hash_table_insert(selenium->priv.errorsMessages, "29","The coordinates provided to an interactions operation are invalid.");
    g_hash_table_insert(selenium->priv.errorsMessages, "30","IME was not available.");
    g_hash_table_insert(selenium->priv.errorsMessages, "31","An IME engine could not be started.");
    g_hash_table_insert(selenium->priv.errorsMessages, "32","Argument was an invalid selector (e.g. XPath/CSS).");
    g_hash_table_insert(selenium->priv.errorsMessages, "33","A new session could not be created.");
    g_hash_table_insert(selenium->priv.errorsMessages, "34","Target provided for a move action is out of bounds.");
    g_hash_table_insert(selenium->priv.errorsMessages, "100","CURL Request error.");
    selenium->priv.errorsShortMessages = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(selenium->priv.errorsShortMessages, "0","Success");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "6","NoSuchDriver");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "7","NoSuchElement");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "8","NoSuchFrame");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "9","UnknownCommand");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "10","StaleElementReference");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "11","ElementNotVisible");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "12","InvalidElementState");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "13","UnknownError");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "15","ElementIsNotSelectable");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "17","JavaScriptError");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "19","XPathLookupError");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "21","Timeout");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "23","NoSuchWindow");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "24","InvalidCookieDomain");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "25","UnableToSetCookie");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "26","UnexpectedAlertOpen");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "27","NoAlertOpenError");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "28","ScriptTimeout");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "29","InvalidElementCoordinates");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "30","IMENotAvailable");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "31","IMEEngineActivationFailed");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "32","InvalidSelector");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "33","SessionNotCreatedException");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "34","MoveTargetOutOfBounds");
    g_hash_table_insert(selenium->priv.errorsShortMessages, "100","CurlRequestError");


};

int selenium_get_element_by(SELENIUM *selenium, SELENIUM_ELEMENT_SELECTOR selector, char* selector_data, SELENIUM_ELEMENT *element) {
    int rc = SELENIUM_SUCCESS;


    if (strlen(selenium->session.session_id) > 0) {
        SELENIUM_JSON json_obj;
        SELENIUM_JSON value;
        char *output_json = NULL;
        int status;
        sds input_json = sdsempty();
        char *using_type, *selenium_internal_id;

        element->priv.selenium_internal_id[0] = '\0';
        switch (selector) {
            case SELENIUM_ELEMENT_ID:
            using_type = "id";
            break;
            case SELENIUM_ELEMENT_NAME:
            using_type = "name";
            break;
            default:
            break;
        }
        input_json = sdscatprintf(input_json, "{\"using\":\"%s\",\"value\":\"%s\"}", using_type, selector_data);
        //lstr(input_json);

        rc = selenium_request(selenium, SELENIUM_POST, "/element", input_json, &output_json);
        //lstr(output_json);
        if (rc == SELENIUM_SUCCESS) {
            //printf("%d\n", rc);
            JSON_LOAD_OBJ(json_obj, output_json);
            JSON_GET_INT(json_obj, "status", status);
            rc = status;

            //printf("%s\n", output_json);
            if (rc == SELENIUM_SUCCESS) {
                JSON_GET_OBJ(json_obj, "value", value);
                JSON_GET_STR(value, "ELEMENT", selenium_internal_id);
                strcat(element->priv.selenium_internal_id, selenium_internal_id);
            }
            JSON_UNLOAD_OBJ(json_obj);
        } else {
            rc = SELENIUM_CURL_REQUEST_ERROR;
        }



        free(output_json);
        sdsfree(input_json);
    } else {
        rc = SELENIUM_SESSIONNOTCREATEDEXCEPTION;
    }

    set_selenium_error_messagess(selenium, rc);
    return rc;
}

int selenium_navigate(SELENIUM *selenium, char *url) {
    int rc = SELENIUM_SUCCESS;


    if (strlen(selenium->session.session_id) > 0) {
        SELENIUM_JSON json_obj;
        char *output_json = NULL;
        int status;
        char *input_json = (char*) malloc((strlen(url) + 11) * sizeof(char));
        sprintf(input_json, "{\"url\":\"%s\"}", url);
        //lstr(input_json);


        rc = selenium_request(selenium, SELENIUM_POST, "/url", input_json, &output_json);
        //lstr(output_json);

        if (rc == SELENIUM_SUCCESS) {
            JSON_LOAD_OBJ(json_obj, output_json);
            JSON_GET_INT(json_obj, "status", status);
            rc = status;
            JSON_UNLOAD_OBJ(json_obj);
        } else {
            rc = SELENIUM_CURL_REQUEST_ERROR;
        }



        free(output_json);
        free(input_json);
    } else {
        rc = SELENIUM_SESSIONNOTCREATEDEXCEPTION;
    }

    set_selenium_error_messagess(selenium, rc);
    return rc;
}


int selenium_clean(SELENIUM *selenium) {

    int rc = SELENIUM_SUCCESS;


    if (strlen(selenium->session.session_id) > 0) {
        SELENIUM_JSON json_obj;
        char *output_json = NULL;
        int status;


        rc = selenium_request(selenium, SELENIUM_DELETE, "/window", "", &output_json);

        if (rc == SELENIUM_SUCCESS) {
            JSON_LOAD_OBJ(json_obj, output_json);
            JSON_GET_INT(json_obj, "status", status);
            if (status != 0) {
                rc = status;
            }
            JSON_UNLOAD_OBJ(json_obj);
        } else {
            rc = SELENIUM_CURL_REQUEST_ERROR;
        }


        free(output_json);
    }
    free(selenium->priv.session_url);
    set_selenium_error_messagess(selenium, rc);
    g_hash_table_destroy(selenium->priv.errorsMessages);
    g_hash_table_destroy(selenium->priv.errorsShortMessages);


    return rc;
}




int selenium_create_session(SELENIUM *selenium) {
    int rc= 1;
    sds json = sdsempty();
    json = sdscatprintf(json, "{\"desiredCapabilities\":{\"browserName\":\"%s\",\"platform\":\"%s\"}}",
            get_browser_name(selenium->desired_capabilites.browser),
            selenium->desired_capabilites.platform);

    char *output_json = NULL;
    SELENIUM_JSON json_obj;
    char *session;
    int status;

    rc = selenium_request(selenium, SELENIUM_POST, "", json, &output_json);
    //printf("%s\n", session_creation_json);

    JSON_LOAD_OBJ(json_obj, output_json);



    JSON_GET_INT(json_obj, "status", status);
    if (status != 0) {
        rc = status;
    } else {
        JSON_GET_STR(json_obj, "sessionId", session);
        if (session != NULL) {
            strcpy(selenium->session.session_id, session);
            selenium->priv.session_url = (char*) realloc(selenium->priv.session_url,  (strlen(selenium->priv.session_url) + strlen(selenium->session.session_id) + 2) * sizeof(char));
            strcat(selenium->priv.session_url, "/");
            strcat(selenium->priv.session_url, selenium->session.session_id);
        }
    }

    JSON_UNLOAD_OBJ(json_obj);
    free(output_json);
    sdsfree(json);

    set_selenium_error_messagess(selenium, rc);
    return rc;
}

int selenium_advanced_request(SELENIUM *selenium, SELENIUM_METHOD method, char *urlPart ,char* postdata, char **ret_str) {
    int rc = selenium_request(selenium, method, urlPart, postdata, ret_str);


    set_selenium_error_messagess(selenium, rc);
    return rc;
}

static int selenium_request(SELENIUM *selenium, SELENIUM_METHOD method, char *urlPart ,char* postdata, char **ret_str){
    CURL *curl;
    CURLcode res;
    char *url;

    struct HtmlData html;

    url = (char*) malloc((strlen(selenium->priv.session_url) + strlen(urlPart) + 2) * sizeof(char));
    sprintf(url, "%s%s", selenium->priv.session_url, urlPart);
    printf("URL: %s\n", url);

    html.str = malloc(1);
    html.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    struct curl_slist *headers = NULL;
    //curl_slist_append(headers, "Accept: application/json");
    curl_slist_append(headers, "Content-Type: application/json");
    curl_slist_append(headers, "charsets: utf-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    switch(method) {
        case SELENIUM_POST:
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        break;
        case SELENIUM_DELETE:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
        default:
        break;
    }

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_PORT, (long)selenium->port);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&html);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36");
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    *ret_str = html.str;
    curl_easy_cleanup(curl);

    free(url);
    curl_global_cleanup();
    curl_slist_free_all(headers);

    return res;
}

static size_t
WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    struct HtmlData *mem = (struct HtmlData *)userp;

    char *ptr = realloc(mem->str, mem->size + realsize + 1);
    if(ptr == NULL)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->str = ptr;
    memcpy(&(mem->str[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->str[mem->size] = 0;

    return realsize;
}

static char *get_browser_name(SELENIUM_WEBDRIVER_TYPE webdriver) {
    switch (webdriver) {
        case CHROME:
        return "chrome";
        break;
        case FIREFOX:
        return "firefox";
        break;
        default:
        return "unknown";
        break;
    };
}
