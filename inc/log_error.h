#ifndef __LOG_ERROR_H__
#define __LOG_ERROR_H__

#include "stdbool.h"

void
log_error(bool ex, const char *format, ...);

#endif /* __LOG_ERROR_H__ */