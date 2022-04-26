/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org),
 * Additions Copyright (c) 2020, Espressif Systems (Shanghai) PTE LTD
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#pragma once

#include "tusb_option.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_TINYUSB_CDC_ENABLED
#   define CONFIG_TINYUSB_CDC_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_MSC_ENABLED
#   define CONFIG_TINYUSB_MSC_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_HID_ENABLED
#   define CONFIG_TINYUSB_HID_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_VENDOR_ENABLED
#   define CONFIG_TINYUSB_VENDOR_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_MIDI_ENABLED
#   define CONFIG_TINYUSB_MIDI_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_DFU_RT_ENABLED
#   define CONFIG_TINYUSB_DFU_RT_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_CUSTOM_CLASS_ENABLED
#   define CONFIG_TINYUSB_CUSTOM_CLASS_ENABLED 0
#endif

#ifndef CONFIG_TINYUSB_CONFIG_POWER_MA
#   define CONFIG_TINYUSB_CONFIG_POWER_MA 100
#endif

#define CFG_TUSB_DESC_MAXPOWER      CONFIG_TINYUSB_CONFIG_POWER_MA
#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED
#define CFG_TUSB_OS                 OPT_OS_FREERTOS

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
#   define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#   define CFG_TUSB_MEM_ALIGN       TU_ATTR_ALIGNED(4)
#endif

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE      64
#endif

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE      CONFIG_TINYUSB_CDC_RX_BUFSIZE
#define CFG_TUD_CDC_TX_BUFSIZE      CONFIG_TINYUSB_CDC_TX_BUFSIZE

// MSC Buffer size of Device Mass storage
#define CFG_TUD_MSC_BUFSIZE         CONFIG_TINYUSB_MSC_BUFSIZE

// HID buffer size Should be sufficient to hold ID (if any) + Data
#define CFG_TUD_HID_BUFSIZE         64 //CONFIG_TINYUSB_HID_BUFSIZE

// Vendor FIFO size of TX and RX
// If not configured vendor endpoints will not be buffered
#define CFG_TUD_VENDOR_RX_BUFSIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)
#define CFG_TUD_VENDOR_TX_BUFSIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)

// MIDI FIFO size of TX and RX
#define CFG_TUD_MIDI_RX_BUFSIZE   (TUD_OPT_HIGH_SPEED ? 512 : 64)
#define CFG_TUD_MIDI_TX_BUFSIZE   (TUD_OPT_HIGH_SPEED ? 512 : 64)

// Enabled device class driver
#if defined(CONFIG_TINYUSB_CDC_COUNT)
#define CFG_TUD_CDC                 CONFIG_TINYUSB_CDC_COUNT
#else
#define CFG_TUD_CDC                 0
#endif
#define CFG_TUD_MSC                 CONFIG_TINYUSB_MSC_ENABLED
#define CFG_TUD_HID                 CONFIG_TINYUSB_HID_ENABLED
#define CFG_TUD_VENDOR              CONFIG_TINYUSB_VENDOR_ENABLED
#define CFG_TUD_MIDI                CONFIG_TINYUSB_MIDI_ENABLED
#define CFG_TUD_DFU_RUNTIME         CONFIG_TINYUSB_DFU_RT_ENABLED
#define CFG_TUD_CUSTOM_CLASS        CONFIG_TINYUSB_CUSTOM_CLASS_ENABLED
// #define CFG_TUD_ENDPPOINT_MAX   8

#   if (CFG_TUD_ENDPPOINT_MAX < 8)
#       define CFG_TUD_ENDPPOINT_MAX 8
#       warning "CFG_TUD_ENDPPOINT_MAX was too low and was set to 8"
#   endif
#ifdef __cplusplus
}
#endif
