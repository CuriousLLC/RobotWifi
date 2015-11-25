#include "main.h"
#include "user_config.h"

void
init_wifi()
{
    // ap_conf is copied into the current config and then no longer needed
    struct softap_config ap_conf;

    if (wifi_set_opmode_current(SOFTAP_MODE) == 0) {
        os_printf("Failed to set SoftAP mode\n");
    }

    // If we already have a config, use it to populate defaults
    wifi_softap_get_config(&ap_conf);

    // Try to copy the user data safely
    os_strncpy(ap_conf.ssid, SSID, 31);
    os_strncpy(ap_conf.password, SSID_PASSWORD, 63);
    ap_conf.authmode = AUTH_WPA2_PSK;
    ap_conf.ssid_len = strlen(SSID);
    ap_conf.max_connection = 4;
    ap_conf.ssid_hidden = 0;
    ap_conf.channel = 0;
    ap_conf.beacon_interval = 250;
    
    wifi_softap_set_config_current(&ap_conf);
}

void 
handle_wifi_event(System_Event_t *evt)
{
    os_printf("Got a Wifi event: %d\n", evt->event);
    switch (evt->event) {
        case EVENT_SOFTAPMODE_STACONNECTED:
            os_printf("Station connected: %s AID %d\n", 
                    MAC2STR(evt->event_info.sta_connected.mac),
                    evt->event_info.sta_connected.aid);
            break;
        case EVENT_SOFTAPMODE_STADISCONNECTED:
            os_printf("Station disconnect: %s AID %d\n",
                    MAC2STR(evt->event_info.sta_disconnected.mac),
                    evt->event_info.sta_disconnected.aid);
            break;
        default:
            break;
    }
}