#ifndef __ESP_DEBUG_INTERFACE__
#define __ESP_DEBUG_INTERFACE__

#ifdef ESP32

extern "C" {
    #include "esp_log.h"
    #include "esp_err.h"
}
#ifndef panic()
#define panic() abort()
#endif 

#define ESP.wdtFeed()

#else

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

typedef int32_t esp_err_t;

/* Definitions for error constants. */

#define ESP_OK          0
#define ESP_FAIL        -1

#define ESP_ERR_NO_MEM          0x101
#define ESP_ERR_INVALID_ARG     0x102
#define ESP_ERR_INVALID_STATE   0x103
#define ESP_ERR_INVALID_SIZE    0x104
#define ESP_ERR_NOT_FOUND       0x105
#define ESP_ERR_NOT_SUPPORTED   0x106
#define ESP_ERR_TIMEOUT         0x107
#define ESP_ERR_INVALID_RESPONSE    0x108
#define ESP_ERR_INVALID_CRC     0x109
#define ESP_ERR_INVALID_VERSION     0x10A
#define ESP_ERR_INVALID_MAC     0x10B

#define ESP_ERR_WIFI_BASE       0x3000 /*!< Starting number of WiFi error codes */

void _esp_error_check_failed(esp_err_t rc, const char *file, int line, const char *function, const char *expression) __attribute__((noreturn));

#ifndef __ASSERT_FUNC
/* This won't happen on IDF, which defines __ASSERT_FUNC in assert.h, but it does happen when building on the host which
   uses /usr/include/assert.h or equivalent.
*/
#ifdef __ASSERT_FUNCTION
#define __ASSERT_FUNC __ASSERT_FUNCTION /* used in glibc assert.h */
#else
#define __ASSERT_FUNC "??"
#endif
#endif

/**
 * Macro which can be used to check the error code,
 * and terminate the program in case the code is not ESP_OK.
 * Prints the error code, error location, and the failed statement to serial output.
 *
 * Disabled if assertions are disabled.
 */
#ifdef NDEBUG
#define ESP_ERROR_CHECK(x) do {                                         \
        esp_err_t rc = (x);                                             \
        (void) sizeof(rc);                                              \
    } while(0);
#else
#define ESP_ERROR_CHECK(x) do {                                         \
        esp_err_t rc = (x);                                             \
        if (rc != ESP_OK) {                                             \
            _esp_error_check_failed(rc, __FILE__, __LINE__,             \
                                    __ASSERT_FUNC, #x);                 \
        }                                                               \
    } while(0);
#endif



#define __ESP_LOG_H__

#include <stdarg.h>


/**
 * @brief Log level
 *
 */
typedef enum {
    ESP_LOG_NONE,       /*!< No log output */
    ESP_LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    ESP_LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    ESP_LOG_INFO,       /*!< Information messages which describe normal flow of events */
    ESP_LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    ESP_LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} esp_log_level_t;

typedef int (*vprintf_like_t)(const char *, va_list);

#ifndef ESP8266_DEBUG_TARGET
#define ESP8266_DEBUG_TARGET Serial
#endif


#define ARDUHAL_LOG_LEVEL_NONE       (0)
#define ARDUHAL_LOG_LEVEL_ERROR      (1)
#define ARDUHAL_LOG_LEVEL_WARN       (2)
#define ARDUHAL_LOG_LEVEL_INFO       (3)
#define ARDUHAL_LOG_LEVEL_DEBUG      (4)
#define ARDUHAL_LOG_LEVEL_VERBOSE    (5)



#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else //CONFIG_LOG_COLORS
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif //CONFIG_LOG_COLORS

#define LOG_FORMAT   "[%s][%s][%s:%i] %s(): "

#define LOG_LOCAL_LEVEL  ((esp_log_level_t) ARDUHAL_LOG_LEVEL_INFO)


#define ESP_LOGE( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ARDUHAL_LOG_LEVEL_ERROR)   { ESP8266_DEBUG_TARGET.printf(LOG_FORMAT, "E", tag, __FILE__, __LINE__, __FUNCTION__); ESP8266_DEBUG_TARGET.printf(format, ##__VA_ARGS__); ESP8266_DEBUG_TARGET.println(); }
#define ESP_LOGW( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ARDUHAL_LOG_LEVEL_WARN)    { ESP8266_DEBUG_TARGET.printf(LOG_FORMAT, "W", tag, __FILE__, __LINE__, __FUNCTION__); ESP8266_DEBUG_TARGET.printf(format, ##__VA_ARGS__); ESP8266_DEBUG_TARGET.println(); }
#define ESP_LOGI( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ARDUHAL_LOG_LEVEL_INFO)    { ESP8266_DEBUG_TARGET.printf(LOG_FORMAT, "I", tag, __FILE__, __LINE__, __FUNCTION__); ESP8266_DEBUG_TARGET.printf(format, ##__VA_ARGS__); ESP8266_DEBUG_TARGET.println(); }
#define ESP_LOGD( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ARDUHAL_LOG_LEVEL_DEBUG)   { ESP8266_DEBUG_TARGET.printf(LOG_FORMAT, "D", tag, __FILE__, __LINE__, __FUNCTION__); ESP8266_DEBUG_TARGET.printf(format, ##__VA_ARGS__); ESP8266_DEBUG_TARGET.println(); }
#define ESP_LOGV( tag, format, ... )  if (LOG_LOCAL_LEVEL >= ARDUHAL_LOG_LEVEL_VERBOSE) { ESP8266_DEBUG_TARGET.printf(LOG_FORMAT, "V", tag, __FILE__, __LINE__, __FUNCTION__); ESP8266_DEBUG_TARGET.printf(format, ##__VA_ARGS__); ESP8266_DEBUG_TARGET.println(); }


#endif
#endif