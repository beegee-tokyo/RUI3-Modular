# 1 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
/**

 * @file RUI3-Modular.ino

 * @author Bernd Giesecke (bernd@giesecke.tk)

 * @brief RUI3 based code for easy testing of WisBlock I2C modules

 * @version 0.1

 * @date 2022-10-29

 *

 * @copyright Copyright (c) 2022

 *

 */
# 11 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
# 12 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino" 2

/** Initialization results */
bool ret;

/** LoRaWAN packet */
WisCayenne g_solution_data(255);

/** Packet is confirmed/unconfirmed (Set with AT commands) */
bool g_confirmed_mode = false;
/** If confirmed packet, number or retries (Set with AT commands) */
uint8_t g_confirmed_retry = 0;
/** Data rate  (Set with AT commands) */
uint8_t g_data_rate = 3;

/** fPort to send packages */
uint8_t set_fPort = 2;

/**

 * @brief Callback after packet was received

 *

 * @param data Structure with the received data

 */
# 34 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void receiveCallback(SERVICE_LORA_RECEIVE_T *data)
{
 do { if ("RX-CB") Serial.printf("[%s] ", "RX-CB"); Serial.printf("RX, port %d, DR %d, RSSI %d, SNR %d", data->Port, data->RxDatarate, data->Rssi, data->Snr); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
 for (int i = 0; i < data->BufferSize; i++)
 {
  Serial.printf("%02X", data->Buffer[i]);
 }
 Serial.print("\r\n");

 /*************************************************/
 /*************************************************/
 /** Insert here sensor specific downlink handler */
 /*************************************************/
 /*************************************************/
 // if ((gnss_format == FIELD_TESTER) && (data->Port == 2))
 // {
 // 	int16_t min_rssi = data->Buffer[1] - 200;
 // 	int16_t max_rssi = data->Buffer[2] - 200;
 // 	int16_t min_distance = data->Buffer[3] * 250;
 // 	int16_t max_distance = data->Buffer[4] * 250;
 // 	int8_t num_gateways = data->Buffer[5];
 // 	Serial.printf("+EVT:FieldTester %d gateways\n", num_gateways);
 // 	Serial.printf("+EVT:RSSI min %d max %d\n", min_rssi, max_rssi);
 // 	Serial.printf("+EVT:Distance min %d max %d\n", min_distance, max_distance);
 // }
}

/**

 * @brief Callback after TX is finished

 *

 * @param status TX status

 */
# 66 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void sendCallback(int32_t status)
{
 do { if ("TX-CB") Serial.printf("[%s] ", "TX-CB"); Serial.printf("TX status %d", status); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
 digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x0);
 /***********************************************/
 /***********************************************/
 /** Insert here sensor specific initialization */
 /***********************************************/
 /***********************************************/
 // gnss_active = false;
}

/**

 * @brief Callback after join request cycle

 *

 * @param status Join result

 */
# 83 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void joinCallback(int32_t status)
{
 // MYLOG("JOIN-CB", "Join result %d", status);
 if (status != 0)
 {
  if (!(ret = api.lorawan.join()))
  {
   do { if ("JOIN-CB") Serial.printf("[%s] ", "JOIN-CB"); Serial.printf("LoRaWan OTAA - join fail! \r\n"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }
 }
 else
 {
  bool result_set = api.lorawan.dr.set(g_data_rate);
  do { if ("JOIN-CB") Serial.printf("[%s] ", "JOIN-CB"); Serial.printf("Set the data rate  %s", result_set ? "Success" : "Fail"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  do { if ("JOIN-CB") Serial.printf("[%s] ", "JOIN-CB"); Serial.printf("LoRaWan OTAA - joined! \r\n"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x0);
 }
}

/**

 * @brief Arduino setup, called once after reboot/power-up

 *

 */
# 106 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void setup()
{
 if (api.lorawan.nwm.get() == 1)
 {
  g_confirmed_mode = api.lorawan.cfm.get();

  g_confirmed_retry = api.lorawan.rety.get();

  g_data_rate = api.lorawan.dr.get();

  // Setup the callbacks for joined and send finished
  api.lorawan.registerRecvCallback(receiveCallback);
  api.lorawan.registerSendCallback(sendCallback);
  api.lorawan.registerJoinCallback(joinCallback);
 }

 pinMode(0/*LED1*/ /* IO_SLOT*//*PA0*/, 0x1);
 digitalWrite(0/*LED1*/ /* IO_SLOT*//*PA0*/, 0x1);
 pinMode(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x1);
 digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x1);

 pinMode(8/*IO2*/ /* SLOT_A SLOT_B*/, 0x1);
 digitalWrite(8/*IO2*/ /* SLOT_A SLOT_B*/, 0x1);

 // Start Serial
 Serial.begin(115200);
# 150 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
 // For RAK3172 just wait a little bit for the USB to be ready
 udrv_app_delay_ms(5000);


 Serial.println("RAKwireless RUI3 Node");
 Serial.println("------------------------------------------------------");
 Serial.println("Setup the device with WisToolBox or AT commands before using it");
 Serial.println("------------------------------------------------------");

 /* Initialize sensor modules */
 init_modules();

 // Register the custom AT command to get device status
 if (!init_status_at())
 {
  do { if ("SETUP") Serial.printf("[%s] ", "SETUP"); Serial.printf("Add custom AT command STATUS fail"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
 }
 digitalWrite(0/*LED1*/ /* IO_SLOT*//*PA0*/, 0x0);

 // Register the custom AT command to set the send interval
 if (!init_interval_at())
 {
  do { if ("SETUP") Serial.printf("[%s] ", "SETUP"); Serial.printf("Add custom AT command Send Interval fail"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
 }

 // Get saved sending interval from flash
 get_at_setting();

 // Create a timer.
 api.system.timer.create(RAK_TIMER_0, sensor_handler, RAK_TIMER_PERIODIC);
 if (g_send_repeat_time != 0)
 {
  // Start a timer.
  api.system.timer.start(RAK_TIMER_0, g_send_repeat_time, 
# 183 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino" 3 4
                                                         __null
# 183 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
                                                             );
 }

 if (api.lorawan.nwm.get() == 0)
 {
  digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x0);

  sensor_handler(
# 190 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino" 3 4
                __null
# 190 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
                    );
 }
}

/**

 * @brief sensor_handler is a timer function called every

 * g_send_repeat_time milliseconds. Default is 120000. Can be

 * changed in main.h

 *

 */
# 200 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void sensor_handler(void *)
{
 // MYLOG("UPLINK", "Start");
 digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x1);

 if (api.lorawan.nwm.get() == 1)
 { // Check if the node has joined the network
  if (!api.lorawan.njs.get())
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Not joined, skip sending"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
   return;
  }
 }

 // Clear payload
 g_solution_data.reset();

/**************************************/
/**************************************/
/** Insert here sensor specific codes */
/**************************************/
/**************************************/
# 223 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino" 2
 // #ifdef _RAK1904_ACC_H_
 // 	if (handle_rak1904_int())
 // 	{
 // 		return;
 // 	}
 // #endif
 // #ifdef _RAK1905_ACC_H_
 // 	if (handle_rak1905_int())
 // 	{
 // 		return;
 // 	}
 // #endif
 // #ifdef _RAK12500_GNSS_H_
 // 	start_gnss();
 // 	return;
 // #endif

 // #ifdef _RAK12027_SEISMIC_H_
 // 	handle_rak12027();
 // 	return;
 // #endif

 // Add battery voltage
 g_solution_data.addVoltage(1 /* Base Board*/, api.system.bat.get());

 // Read sensor data
 get_sensor_values();

 // Send the packet
 send_packet();
}

/**

 * @brief This example is complete timer

 * driven. The loop() does nothing than

 * sleep.

 *

 */
# 261 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void loop()
{
 api.system.sleep.all();
}

/**

 * @brief Send the data packet that was prepared in

 * Cayenne LPP format by the different sensor and location

 * aqcuision functions

 *

 */
# 272 "d:\\#Github\\RUI3-Examples\\RUI3-Modular\\RUI3-Modular.ino"
void send_packet(void)
{
 if (api.lorawan.nwm.get() == 1)
 {
  do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Send packet with size %d on port %d", g_solution_data.getSize(), set_fPort); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);

  // Send the packet
  if (api.lorawan.send(g_solution_data.getSize(), g_solution_data.getBuffer(), set_fPort, g_confirmed_mode, g_confirmed_retry))
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Packet enqueued"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }
  else
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Send failed"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }
 }
 else
 {
  do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Send packet with size %d over P2P", g_solution_data.getSize() + 8); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);

  digitalWrite(1/*LED2*/ /* IO_SLOT*//*PA1*/, 0x0);
  uint8_t packet_buffer[g_solution_data.getSize() + 8];
  if (!api.lorawan.deui.get(packet_buffer, 8))
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Could not get DevEUI"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }

  memcpy(&packet_buffer[8], g_solution_data.getBuffer(), g_solution_data.getSize());

  for (int idx = 0; idx < g_solution_data.getSize() + 8; idx++)
  {
   Serial.printf("%02X", packet_buffer[idx]);
  }
  Serial.println("");

  if (api.lorawan.psend(g_solution_data.getSize() + 8, packet_buffer))
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Packet enqueued"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }
  else
  {
   do { if ("UPLINK") Serial.printf("[%s] ", "UPLINK"); Serial.printf("Send failed"); Serial.printf("\n"); } while (0); udrv_app_delay_ms(100);
  }
 }
}
