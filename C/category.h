#ifndef CATEGORY_H
#define CATEGORY_H

/** 
 * @enum Category
 * @brief Represents the category of the move.
 *
 * - PHYSICAL: The category of the attack is Physical, it uses Attack and Defense.
 * - SPECIAL: The category of the attack is Special, it uses Special Attack and Special Defense.
 * - STATUS: Non-damaging moves that apply effects.
 */
typedef enum { 
    PHYSICAL, SPECIAL, STATUS, CATEGORY_COUNT
} Category;

static const char* const CategoryNames[] = {
    [PHYSICAL] = "PHYSICAL",
    [SPECIAL]  = "SPECIAL",
    [STATUS]   = "STATUS"
};

const char* getCategoryName(Category);

#endif