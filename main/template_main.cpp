/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <Arduino.h>
#include <WiFi.h>

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#define GPIO_NEOPIXEL 38

#define GPIO_CCD_VID 1
#define GPIO_CCD_EOS 2
#define GPIO_CCD_TRIG 42
#define GPIO_CCD_ST 41
#define GPIO_CCD_CLK 40


#ifdef GPIO_NEOPIXEL
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(1, GPIO_NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

void setup_io() {
	// all SPI pins to SDCARD are idle inputs pulled high on boot or sleep
	pinMode(GPIO_CCD_VID, INPUT);
	pinMode(GPIO_CCD_EOS, INPUT);
	pinMode(GPIO_CCD_TRIG, INPUT);

	pinMode(GPIO_CCD_ST, OUTPUT);
	digitalWrite(GPIO_CCD_ST, HIGH);
	
	pinMode(GPIO_CCD_CLK, OUTPUT);
	digitalWrite(GPIO_CCD_CLK, HIGH);	
}

void setup(void)
{
	Serial.begin(115200);

	Serial.println();
	Serial.println("VBSS Demo starting");
	Serial.println(String(__DATE__) + " " + String(__TIME__));

	delay(10);	
	
#ifdef GPIO_NEOPIXEL
	pixels.setPixelColor(0, pixels.Color(250, 0, 0)); // setup()
	pixels.show();									  // setup()
	delay(200);
	pixels.setPixelColor(0, pixels.Color(0, 250, 0)); // setup()
	pixels.show();									  // setup()
	delay(200);
	pixels.setPixelColor(0, pixels.Color(0, 0, 250)); // setup()
	pixels.show();									  // setup()
	delay(200);
	pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // setup()
	pixels.show();									// setup()
	delay(200);
#endif

	WiFi.mode(WIFI_OFF); // Disable WiFi
	btStop();			 // Disable Bluetooth

	setup_io();
			
}

void loop()
{
	
}