/**
 * @file RAK13011_switch.cpp
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief RAK13011 Reed relay switch
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "main.h"

//******************************************************************//
// RAK13011 INT1_PIN
//******************************************************************//
// Slot A      WB_IO1
// Slot B      WB_IO2 ( not recommended, pin conflict with IO2)
// Slot C      WB_IO3
// Slot D      WB_IO5
// Slot E      WB_IO4
// Slot F      WB_IO6
//******************************************************************//

#define RAK13011_SLOT 'C'

/** Interrupt pin, depends on slot */
// Slot A
#if RAK13011_SLOT == 'A'
#pragma message "Slot A"
#define SW_INT_PIN WB_IO1
// Slot B
#elif RAK13011_SLOT == 'B'
#pragma message "Slot B"
#define SW_INT_PIN WB_IO2
// Slot C
#elif RAK13011_SLOT == 'C'
#pragma message "Slot C"
#define SW_INT_PIN WB_IO3
// Slot D
#elif RAK13011_SLOT == 'D'
#pragma message "Slot D"
#define SW_INT_PIN WB_IO5
// Slot E
#elif RAK13011_SLOT == 'E'
#pragma message "Slot E"
#define SW_INT_PIN WB_IO4
// Slot F
#elif RAK13011_SLOT == 'F'
#pragma message "Slot F"
#define SW_INT_PIN WB_IO6
#endif

volatile uint8_t events_queue[50] = {0};

volatile uint8_t event_ptr = 0;

volatile int switch_status = 0;

void switch_int_handler(void)
{
	MYLOG("REED", "Interrupt");
	switch_status = digitalRead(SW_INT_PIN);
	if (switch_status == LOW)
	{
		digitalWrite(LED_GREEN, HIGH);
		digitalWrite(LED_BLUE, LOW);
		events_queue[event_ptr] = 0;
		event_ptr++;
	}
	else
	{
		digitalWrite(LED_GREEN, LOW);
		digitalWrite(LED_BLUE, HIGH);
		events_queue[event_ptr] = 1;
		event_ptr++;
	}
	handle_rak13011(NULL);
		// // Wake the switch handler
		// api.system.timer.start(RAK_TIMER_2, 500, NULL);
}

bool init_rak13011(void)
{
	// Create a timers for handling the events
	api.system.timer.create(RAK_TIMER_2, handle_rak13011, RAK_TIMER_ONESHOT);
	api.system.timer.create(RAK_TIMER_3, handle_rak13011, RAK_TIMER_ONESHOT);

	MYLOG("REED", "Initialize Interrupt on pin %d", SW_INT_PIN);
	pinMode(SW_INT_PIN, INPUT);
	attachInterrupt(SW_INT_PIN, switch_int_handler, CHANGE);
	MYLOG("REED", "Interrupt Initialized ");

	return true;
}

void handle_rak13011(void *)
{
	if (!tx_active)
	{
		event_ptr -= 1;

		if (switch_status == digitalRead(SW_INT_PIN))
		{
			MYLOG("REED", "Switch Status confirmed");
		}
		else
		{
			MYLOG("REED", "Switch bouncing");
			return;
		}

		// Reset automatic interval sending if active
		if (g_send_repeat_time != 0)
		{
			// Restart a timer
			api.system.timer.stop(RAK_TIMER_0);
			api.system.timer.start(RAK_TIMER_0, g_send_repeat_time, NULL);
		}

		// Clear payload
		g_solution_data.reset();

		g_solution_data.addPresence(LPP_CHANNEL_SWITCH, events_queue[event_ptr] == 0 ? 0 : 1);

		// Add battery voltage
		g_solution_data.addVoltage(LPP_CHANNEL_BATT, api.system.bat.get());

		// Send the packet
		send_packet();
	}

	if (event_ptr != 0)
	{
		// Event queue is not empty. Trigger next packet in 5 seconds
		api.system.timer.start(RAK_TIMER_3, 5000, NULL);
	}
}
