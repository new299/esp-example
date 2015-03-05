#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"
#include "user_config.h"
#include "uart.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void loop(os_event_t *events);
LOCAL os_timer_t network_timer;

static void ICACHE_FLASH_ATTR loop(os_event_t *events) {
  uart0_tx_buffer("Hello World\n",12);
}

//Init function 
void ICACHE_FLASH_ATTR user_init() {

    // Set UART Speed (default appears to be rather odd 77KBPS)
    uart_init(BIT_RATE_9600,BIT_RATE_9600);

    //Start os task
    system_os_task(loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(user_procTaskPrio, 0, 0 );
}
