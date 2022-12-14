/**
 * @file sensor_handler.h
 * @author Bernd Giesecke (bernd@giesecke.tk)
 * @brief Module specific calls for the sensor handler function
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifdef _RAK1904_ACC_H_
if (handle_rak1904_int())
{
	return;
}
#endif
#ifdef _RAK1905_ACC_H_
if (handle_rak1905_int())
{
	return;
}
#endif
#ifdef _RAK12500_GNSS_H_
start_gnss();
return;
#endif

#ifdef _RAK12027_SEISMIC_H_
handle_rak12027();
return;
#endif
