#include <inc/lib.h>

#define BUF_SIZE 4096
#define FLAG_LOWER 0x20
#define FLAG_ALTNT_FORM 0x01
#define FLAG_LEFT_ADJUST 0x04
#define FLAG_ZERO_PAD 0x02
#define FLAG_SIGN 0x10

static char num_str_buf[BUF_SIZE];

char* uint32_to_str_hex(uint32_t num, int flag, int width) {
    uint32_t num_tmp = num;
    char* p = num_str_buf;
    char* q = NULL;
    int len = 0;
    char* str_first = NULL;
    char* str_end = NULL;
    char ch = 0;

    memset(num_str_buf, 0, sizeof(num_str_buf));

    char dic_lower[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char dic_upper[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char* dic = (flag & FLAG_LOWER) ? dic_lower : dic_upper;

    str_first = num_str_buf;

    *p++ = '0';
    *p++ = (flag & FLAG_LOWER) ? 'x' : 'X';

    if (!(flag & FLAG_ALTNT_FORM)) {
        str_first += 2;
    }

    do {
        *p++ = dic[num_tmp % 16];
        num_tmp /= 16;
    } while (num_tmp);
    *p = '\0';

    str_end = p;
    len = str_end - str_first;

    q = num_str_buf + 2;
    p--;
    while (q < p) {
        ch = *q;
        *q = *p;
        *p = ch;
        p--;
        q++;
    }

    if (len < width) {
        p = str_end;

        if (flag & FLAG_LEFT_ADJUST) {
        for (int i = 0; i < width - len; i++)
            *p++ = ' ';
        *p = '\0';
        str_end = p;
        } else {
        while (p >= str_first) {
            *(p + width - len) = *p;
            p--;
        }
        if (flag & FLAG_ALTNT_FORM)
            str_first[1] = (flag & FLAG_LOWER) ? 'x' : 'X';

        if (flag & FLAG_ZERO_PAD) {
            for (int i = 0; i < width - len; i++) {
            num_str_buf[i + 2] = '0';
            }
        } else {
            for (int i = 0; i < width - len; i++)
            str_first[i] = ' ';
        }
        }
    }

    if (num == 0 && flag & FLAG_ALTNT_FORM)
        str_first[1] = '0';

    return str_first;
}

char* uint64_to_str_hex(uint64_t num, int flag, int width) {
    uint64_t num_tmp = num;
    char* p = num_str_buf;
    char* q = NULL;
    int len = 0;
    char* str_first = NULL;
    char* str_end = NULL;
    char ch = 0;

    memset(num_str_buf, 0, sizeof(num_str_buf));

    char dic_lower[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char dic_upper[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char* dic = (flag & FLAG_LOWER) ? dic_lower : dic_upper;

    str_first = num_str_buf;

    *p++ = '0';
    *p++ = (flag & FLAG_LOWER) ? 'x' : 'X';

    if (!(flag & FLAG_ALTNT_FORM)) {
        str_first += 2;
    }

    while (num_tmp) {
        *p++ = dic[num_tmp % 16];
        num_tmp /= 16;
    }
    *p = '\0';

    str_end = p;
    len = str_end - str_first;

    q = num_str_buf + 2;
    p--;
    while (q < p) {
        ch = *q;
        *q = *p;
        *p = ch;
        p--;
        q++;
    }

    if (len < width) {
        p = str_end;

        while (p >= str_first) {
        *(p + width - len) = *p;
        p--;
        }

        if (flag & FLAG_ZERO_PAD) {
        for (int i = 0; i < width - len; i++) {
            num_str_buf[i + 2] = '0';
        }
        } else {
        for (int i = 0; i < width - len; i++)
            str_first[i] = ' ';
        }
    }

    return str_first;
}

char* uint32_to_str_oct(uint32_t num, int flag, int width) {
    uint32_t num_tmp = num;
    char* p = num_str_buf;
    char* q = NULL;
    int len = 0;
    char* str_first = NULL;
    char* str_end = NULL;
    char ch = 0;

    memset(num_str_buf, 0, sizeof(num_str_buf));

    char dic[] = {'0', '1', '2', '3', '4', '5', '6', '7'};

    str_first = num_str_buf;

    *p++ = '0';

    if (!(flag & FLAG_ALTNT_FORM)) {
        str_first += 1;
    }

    while (num_tmp) {
        *p++ = dic[num_tmp % 8];
        num_tmp /= 8;
    }
    *p = '\0';

    str_end = p;
    len = str_end - str_first;

    q = num_str_buf + 1;
    p--;
    while (q < p) {
        ch = *q;
        *q = *p;
        *p = ch;
        p--;
        q++;
    }

    if (len < width) {
        p = str_end;

        if (flag & FLAG_LEFT_ADJUST) {
        for (int i = 0; i < width - len; i++)
            *p++ = ' ';
        *p = '\0';
        str_end = p;
        } else {
        while (p >= str_first) {
            *(p + width - len) = *p;
            p--;
        }

        if (flag & FLAG_ZERO_PAD) {
            for (int i = 0; i < width - len; i++) {
            num_str_buf[i + 1] = '0';
            }
        } else {
            for (int i = 0; i < width - len; i++)
            str_first[i] = ' ';
        }
        }
    }

    return str_first;
}

char* int32_to_str_dec(int32_t num, int flag, int width) {
    int32_t num_tmp = num;
    char* p = num_str_buf;
    char* q = NULL;
    int len = 0;
    char* str_first = NULL;
    char* str_end = NULL;
    char ch = 0;

    memset(num_str_buf, 0, sizeof(num_str_buf));

    char dic[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    if (num_tmp < 0) {
        *p++ = '-';
    } else if (flag & FLAG_SIGN) {
        *p++ = '+';
    } else {
        *p++ = ' ';
    }
    str_first = num_str_buf;

    if (num_tmp >= 0 && !(flag & FLAG_SIGN)) {
        str_first++;
    }

    if (num_tmp == 0) {
        *p++ = '0';
    } else {
        if (num_tmp < 0)
        num_tmp = -num_tmp;

        while (num_tmp) {
        *p++ = dic[num_tmp % 10];
        num_tmp /= 10;
        }
    }
    *p = '\0';

    str_end = p;
    len = str_end - str_first;

    q = num_str_buf + 1;
    p--;
    while (q < p) {
        ch = *q;
        *q = *p;
        *p = ch;
        p--;
        q++;
    }

    if (len < width) {
        p = str_end;

        if (flag & FLAG_LEFT_ADJUST) {
        for (int i = 0; i < width - len; i++)
            *p++ = ' ';
        *p = '\0';
        str_end = p;
        } else {
        while (p >= str_first) {
            *(p + width - len) = *p;
            p--;
        }

        if (flag & FLAG_ZERO_PAD) {
            for (int i = 0; i < width - len; i++) {
            num_str_buf[i + 1] = '0';
            }
        } else {
            for (int i = 0; i < width - len; i++)
            str_first[i] = ' ';
        }
        }
    }

    return str_first;
}