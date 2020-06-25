#include <stdio.h>
#include "contiki.h"
#include "lib/random.h"
#include "net/rime.h"
#include "net/rime/collect.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include "dev/i2cmaster.h"
#include "dev/tmp102.h"
#include "net/netstack.h"
#include "dev/battery-sensor.h"
#include "dev/leds.h"
#include "dev/z1-phidgets.h"

#define TMP102_READ_INTERVAL (CLOCK_SECOND/2)

static struct collect_conn tc; 
static struct etimer et;

float floor(float x) { 
	if(x >= 0.0f) {
	return (float) ((int) x);
	}else {
	return (float) ((int) x - 1);
	}
	}

static const char * getBattery() { 
	char result[32]="";
	uint16_t bateria = battery_sensor.value(0); 
	float mv = (bateria * 2.500 * 2) / 4096; 
	sprintf(result,"Battery: %i ", bateria);
return &result;
}

static const char * getConsumption() { 
	char result[32]=""; 
	leds_toggle(LEDS_GREEN);
	if (phidgets.value(PHIDGET3V_1) < 100) {
	 leds_on(LEDS_RED);
	} else {
	leds_off(LEDS_RED);
	}
sprintf(result,"Phidget 3V2:%d\n",phidgets.value(PHIDGET3V_2)); 
return &result;
}

static const char * getTemperature() { 
	int16_t tempint;
	uint16_t tempfrac; 
	int16_t raw; 
	uint16_t absraw; 
	int16_t sign;
	char minus = ' ';
	char cadena[32]=""; 
	sign = 1;
		raw = tmp102_read_temp_raw(); 
		absraw = raw;
		if(raw < 0) {
			absraw = (raw ^ 0xFFFF) + 1; 
			sign = -1;
		}
	tempint = (absraw >> 8) * sign; 
	tempfrac = ((absraw >> 4) % 16) * 625;
	minus = ((tempint == 0) & (sign == -1))? '-' : ' '; 
	sprintf(cadena,"Temp = %c%d.%04d ", minus, tempint, tempfrac); 
	return &cadena;
}


PROCESS(example_collect_process, "Test collect process"); 
AUTOSTART_PROCESSES(&example_collect_process);

static void recv (const rimeaddr_t *originator, uint8_t seqno, uint8_t hops)
{
	printf("Sink got message from %d.%d, seqno %d, hops %d: len %d '%s'\n",	originator->u8[0], originator->u8[1],seqno, hops, packetbuf_datalen(), (char *)packetbuf_dataptr());
}

static const struct collect callbacks callbacks = { recv };

PROCESS_THREAD(example_collect_process, ev, data)
{
	static struct etimer periodic;

	PROCESS_BEGIN();
	SENSORS_ACTIVATE(battery_sensor); 
	SENSORS_ACTIVATE(phidgets); 
	SENSORS_ACTIVATE(button_sensor);
	collect_open(&tc, 130, COLLECT_ROUTER, &callbacks); 
if(rimeaddr_node_addr.u8[0] == 1 && rimeaddr_node_addr.u8[1] == 0)
{
	printf("I am sink\n"); 
	collect_set_sink(&tc, 1);
}
static struct etimer et; 
tmp102_init();
etimer_set(&et, TMP102_READ_INTERVAL); 
PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et)); 
while(1) {
/* Send a packet every 30 seconds. */ 
if(etimer_expired(&periodic)) {
	etimer_set(&periodic, CLOCK_SECOND * 30); 
	etimer_set(&et, random_rand() % (CLOCK_SECOND * 30));
} 
PROCESS_WAIT_EVENT();
if(etimer_expired(&et)) {
	static rimeaddr_t oldparent; 
	const rimeaddr_t *parent; 
	printf("Sending\n"); 
	packetbuf_clear();
	char result[128] =""; 
	strcat(result,getTemperature ()); 
	strcat(result,getBattery()); 
	strcat(result,getConsumption());
	packetbuf_set_datalen(sprintf(packetbuf_dataptr(),"%s", result )+2);
	printf(result); 
	collect_send(&tc, 15);
	parent = collect_parent(&tc); 
	if(!rimeaddr_cmp(parent, &oldparent)) {
		if(!rimeaddr_cmp(&oldparent, &rimeaddr_null)) { 
			printf("#L %d 0\n", oldparent.u8[0]);
		}
	if(!rimeaddr_cmp(parent, &rimeaddr_null)) { 
		printf("#L %d 1\n", parent->u8[0]);
		}
	rimeaddr_copy(&oldparent, parent);
}
}
}
SENSORS_DEACTIVATE(battery_sensor); 
PROCESS_END();
}
