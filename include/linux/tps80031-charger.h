/*
 * include/linux/tps80031-charger.h
 *
 * Battery charger driver interface for TI TPS80031 PMIC
 *
 * Copyright (C) 2011 NVIDIA Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef __LINUX_TPS80031_CHARGER_H
#define __LINUX_TPS80031_CHARGER_H

#include <linux/regulator/machine.h>

enum charging_states {
	charging_state_idle,
	charging_state_charging_in_progress,
	charging_state_charging_completed,
	charging_state_charging_stopped,
};

enum charging_type {
	NONE_CHARGER,
	USB_CHARGER,
	AC_CHARGER,
	OTG_CHARGER,
};

#if defined(CONFIG_BATTERY_BQ27x00)
/* Charging status detect by PMU,M470's gasgauge doesn't work well in DSG update */
enum {
	CHARGING_UNKNOW	= 0,
	CHAEGING_DISCHG,
	CHAEGING_CHGING,
	CHAEGING_DONE,
	CHARGING_OVER_HEAT,
	CHARGING_OVER_VOLTAGE,
	CHARGING_GATED,
	CHARGING_VBUS_NO_PRESENT,
};
#endif

/**
 * Callback type definition which is called when any state changed in the
 * charging.
 */
typedef void (*charging_callback_t)(enum charging_states state, void *args);

struct tps80031_charger_platform_data {
	int regulator_id;
	int max_charge_volt_mV;
	int max_charge_current_mA;
	int charging_term_current_mA;
	int refresh_time;
	int irq_base;
	int watch_time_sec;
	int safety_timer_en;
	long safety_timer_sec;
	int  jeita_current_en;
	int  jeita_limited_temp_low;
	int  jeita_limited_temp_high;
	int  jeita_limited_temp_cap;
	int  jeita_limited_current;
	int  jeita_limited_voltage;
	struct regulator_consumer_supply *consumer_supplies;
	int num_consumer_supplies;
	int (*board_init)(void *board_data);
	void *board_data;
};

/**
 * Register the callback function for the client. This callback gets called
 * when there is any change in the chanrging states.
 */
extern int register_charging_state_callback(charging_callback_t cb, void *args);

#endif /*__LINUX_TPS80031_CHARGER_H */
