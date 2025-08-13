/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <Arduino.h>
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#define GPIO_NEOPIXEL 38

#ifdef GPIO_NEOPIXEL
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(1, GPIO_NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

void setup(void)
{
	Serial.begin(115200);
	
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
	
    Serial.println();
	Serial.println("Hello world!");
    Serial.println();

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    Serial.printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");
    Serial.println();

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    Serial.printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    Serial.println();
        
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        Serial.printf("Get flash size failed");
    	Serial.println();        
        return;
    }

    Serial.printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    Serial.println();           

    Serial.printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
       Serial.println();

    for (int i = 10; i >= 0; i--) {
        Serial.printf("Restarting in %d seconds...\n", i);
    	Serial.println();        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    Serial.printf("Restarting now.\n");
    Serial.println();
    
    fflush(stdout);
    esp_restart();
}

void loop()
{
	
}