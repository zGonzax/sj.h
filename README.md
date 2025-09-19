# sj.h
A tiny little JSON parsing library

- ~150 lines of C99
- Zero-allocations with minimal state
- Error messages with `line:column:` location
- No number parsing: `strtod`, `atoi`? Handle them how you want
- No string parsing: bring your own unicode surrogate pair handling (or don't)


## Usage
A small program to load a rectangle from a JSON string into a `Rect` struct:
```c
char *json_text = "{ \"x\": 10, \"y\": 20, \"w\": 30, \"h\": 40 }";

typedef struct { int x, y, w, h; } Rect;

bool eq(sj_Value val, char *s) {
    size_t len = val.end - val.start;
    return strlen(s) == len && !memcmp(s, val.start, len);
}

int main(void) {
    Rect rect = {0};

    sj_Reader r = sj_reader(json_text, strlen(json_text));
    sj_Value obj = sj_read(&r);

    sj_Value key, val;
    while (sj_iter_object(&r, obj, &key, &val)) {
        if (eq(key, "x")) { rect.x = atoi(val.start); }
        if (eq(key, "y")) { rect.y = atoi(val.start); }
        if (eq(key, "w")) { rect.w = atoi(val.start); }
        if (eq(key, "h")) { rect.h = atoi(val.start); }
    }

    printf("rect: { %d, %d, %d, %d }\n", rect.x, rect.y, rect.w, rect.h);
    return 0;
}
```

See the [**demo**](demo/) folder for further usage examples.


## License
This is free and unencumbered software released into the public domain. See
[LICENSE](LICENSE) for details.