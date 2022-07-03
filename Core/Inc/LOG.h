#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#include "SEGGER.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

extern void LOG_init(void);
extern void LOG(char * tag, char TYPE, char * text);

#ifdef __cplusplus
}
#endif

#endif /* SRC_LOG_H_ */
