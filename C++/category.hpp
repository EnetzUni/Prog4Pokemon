#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#pragma once

/** 
 * @enum Category
 * @brief Represents the category of the move.
 *
 * - PHYSICAL: The category of the attack is Physical, it uses Attack and Defense.
 * - SPECIAL: The category of the attack is Special, it uses Special Attack and Special Defense.
 * - STATUS: Non-damaging moves that apply effects.
 */
enum class Category { 
    PHYSICAL, SPECIAL, STATUS 
};

#endif