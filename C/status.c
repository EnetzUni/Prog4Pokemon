#include <stdio.h>
#include "status.h"

const char* GetStatusName(Status s) {
    if (s >= 0 && s < STATUS_COUNT) {
        return StatusNames[s];
    }
    return (Status) NULL;
}