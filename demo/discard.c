// demonstrates the library correctly discarding nested objects which weren't
// handled by the user when iterating an object

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SJ_IMPL
#include "../sj.h"


char* json_text = "{"
    "\"first_name\": \"John\","
    "\"last_name\": \"Smith\","
    "\"address\": {"
    "  \"street_address\": \"21 2nd Street\","
    "  \"city\": \"New York\","
    "  \"state\": \"NY\","
    "},"
    "\"age\": 27,"
    "}";


bool eq(sj_Value val, char *s) {
    size_t len = val.end - val.start;
    return strlen(s) == len && !memcmp(s, val.start, len);
}

void print(sj_Value val) {
    printf("%.*s\n", (int)(val.end-val.start), val.start);
}

int main(void) {
    sj_Reader r = sj_reader(json_text, strlen(json_text));
    sj_Value obj = sj_read(&r);

    sj_Value key, val;
    while (sj_iter_object(&r, obj, &key, &val)) {
        if (eq(key, "first_name")) { print(val); }
        if (eq(key,  "last_name")) { print(val); }
        if (eq(key,        "age")) { print(val); }
    }

    return 0;
}