#include <stdio.h>
#include "category.h"

const char* getCategoryName(Category c) {
    if (c >= 0 && c < CATEGORY_COUNT) {
        return CategoryNames[c];
    }
    return (const char*) "NULL";
}