#include <stdio.h>
#include "category.h"

const char* GetCategoryName(Category c) {
    if (c >= 0 && c < CATEGORY_COUNT) {
        return CategoryNames[c];
    }
    return (Category) NULL;
}