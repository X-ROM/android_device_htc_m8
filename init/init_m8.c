/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void gsm_properties();
void cdma_properties();

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char customizationid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.aa.customizationid", customizationid);

    if (strstr(customizationid, "696487")) {
        /* at&t */
        gsm_properties();
        property_set("ro.build.fingerprint", "htc/htc_europe/htc_m8:4.4.2/KOT49H/325784.5:user/release-keys");
        property_set("ro.build.description", "1.54.401.5 CL325784 release-keys");
        property_set("ro.product.model", "HTC One_M8");
        property_set("ro.product.device", "htc_m8");
    } else if (strstr(customizationid, "695578")) {
        /* sprint */
        cdma_properties();
        property_set("ro.build.fingerprint", "");
        property_set("ro.build.description", "");
        property_set("ro.product.model", "");
        property_set("ro.product.device", "");
    } else if (strstr(customizationid, "999999")) { // unreleased
        /* t-mobile */
        gsm_properties();
        property_set("ro.build.fingerprint", "");
        property_set("ro.build.description", "");
        property_set("ro.product.model", "");
        property_set("ro.product.device", "");
    } else if (strstr(customizationid, "682203")) {
        /* verizon */
        cdma_properties();
        property_set("ro.build.fingerprint", "htc/HTCOneM8vzw/htc_m8wl:4.4.2/KOT49H/315044.11:user/release-keys");
        property_set("ro.build.description", "1.12.605.11 CL315044 release-keys");
        property_set("ro.product.model", "HTC6525LVW");
        property_set("ro.product.device", "htc_m8wl");
    }

    property_get("ro.product.device", device);
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, device);

}

void gsm_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

void cdma_properties()
{
    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ril.subscription.types", "NV,RUIM");
    property_set("ro.cdma.subscribe_on_ruim_ready", "true");
    property_set("ro.ril.svdo", "true");
}
