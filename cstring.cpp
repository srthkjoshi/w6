#include "cstring.h"

namespace sdds {
    void strCpy(char* des, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            des[i] = src[i];
            i++;
        }
        des[i] = '\0';
    }

    void strnCpy(char* des, const char* src, int len) {
        int i = 0;
        while (src[i] != '\0' && i < len) {
            des[i] = src[i];
            i++;
        }
        if (i < len) {
            des[i] = '\0';
        }
    }

    int strCmp(const char* s1, const char* s2) {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
            i++;
        }
        return s1[i] - s2[i];
    }

    int strnCmp(const char* s1, const char* s2, int len) {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < len) {
            i++;
        }
        if (i == len) {
            return 0;
        }
        return s1[i] - s2[i];
    }

    int strLen(const char* s) {
        int len = 0;
        while (s[len] != '\0') {
            len++;
        }
        return len;
    }

    const char* strStr(const char* str1, const char* str2) {
        int len1 = strLen(str1);
        int len2 = strLen(str2);
        for (int i = 0; i <= len1 - len2; i++) {
            int j;
            for (j = 0; j < len2; j++) {
                if (str1[i + j] != str2[j]) {
                    break;
                }
            }
            if (j == len2) {
                return &str1[i];
            }
        }
        return nullptr;
    }

    void strCat(char* des, const char* src) {
        int len1 = strLen(des);
        int len2 = strLen(src);
        int i;
        for (i = 0; i < len2; i++) {
            des[len1 + i] = src[i];
        }
        des[len1 + i] = '\0';
    }
}
