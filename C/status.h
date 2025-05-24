#ifndef STATUS_H
#define STATUS_H

/**
 * @enum Status
 * @brief Represents the various status conditions a Pokemon can experience in battle.
 */
typedef enum {
    BURN, FREEZE, PARALYSIS, POISOND, BPOISOND, SLEEP, CONFUSION, STATUS_COUNT
} Status;

static const char* const StatusNames[] = {
    [BURN]       = "BURN",
    [FREEZE]     = "FREEZE",
    [PARALYSIS]  = "PARALYSIS",
    [POISOND]     = "POISOND",
    [BPOISOND]    = "BPOISOND",
    [SLEEP]      = "SLEEP",
    [CONFUSION]  = "CONFUSION"
};

const char* getStatusName(Status);

#endif