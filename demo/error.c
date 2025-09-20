// demonstrates using the `sj_location` function to display a custom error with
// a line:col location

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SJ_IMPL
#include "../sj.h"


char* json_text = "{\n"
/* line 2 */ "    \"first_name\": \"John\",\n"
/* line 3 */ "    \"last_name\": \"Smith\",\n"
/* line 4 */ "    \"age\": \"27\"\n"
/* line 5 */ "}";


bool eq(sj_Value val, char *s) {
    size_t len = val.end - val.start;
    return strlen(s) == len && !memcmp(s, val.start, len);
}


int main(void) {
    sj_Reader r = sj_reader(json_text, strlen(json_text));
    sj_Value obj = sj_read(&r);

    sj_Value key, val;
    while (sj_iter_object(&r, obj, &key, &val)) {
        if (eq(key, "age")) {
            if (val.type != SJ_NUMBER) {
                int line, col;
                sj_location(&r, val.start, &line, &col);
                printf("error at line %d, col %d: value for field 'age' should be a number\n", line, col);
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}