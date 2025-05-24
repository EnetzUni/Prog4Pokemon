#include <stdio.h>
#include "status.h"

const char* getStatusName(Status s) {
    if (s >= 0 && s < STATUS_COUNT) {
        return StatusNames[s];
    }
    return (const char*) "NULL";
}