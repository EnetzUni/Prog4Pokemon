#ifndef CATEGORY_H
#define CATEGORY_H

#ifdef __cplusplus
extern "C" {
#endif

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

const char* getCategoryName(Category);

#ifdef __cplusplus
}
#endif

static const char* const CategoryNames[] = {
    [PHYSICAL] = "PHYSICAL",
    [SPECIAL]  = "SPECIAL",
    [STATUS]   = "STATUS"
};

#endif