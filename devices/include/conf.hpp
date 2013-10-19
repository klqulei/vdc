
 
#ifndef _CONF_H_
#define _CONF_H_

#include "utility.hpp"

#define CONF_NAME_MAX 128
#define CONF_MAP_MAX 512
#define CONF_USER_PASSWORD_MAX 1024
#define CONF_PATH_MAX 1024
/* 0xFF FFFF to 0xFFFF FFFF is for status for the map */
#define CONF_MAP_INVALID_MIN 0xFFFFFF
#define CONF_KEY_STR_MAX 16

#define VSC_CONF_KEY "ConfVSCSystem"
#define VSC_CONF_CHANNEL_KEY "ConfVSCDevice"
#define VSC_CONF_CH_PARAM_MAX 1024
//TODO add user password

typedef enum
{
    VSC_DEVICE_CAM = 1,
    VSC_DEVICE_NODE,
    VSC_DEVICE_RECORDER,

    VSC_DEVICE_LAST
} VSCDeviceType;

/* Device Type */
typedef enum
{
    VSC_SUB_DEVICE_USB_CAM = 1,
    VSC_SUB_DEVICE_FILE,
    VSC_SUB_DEVICE_RTSP,
    VSC_SUB_DEVICE_ONVIF,

    VSC_SUB_DEVICE_LAST
} VSCDeviceSubType;

#pragma pack(push,  1 )
typedef struct __VSCConfSystemKey {
    s8 Key[CONF_KEY_STR_MAX];
    __VSCConfSystemKey()
    {
        memset(Key, 0, CONF_KEY_STR_MAX);
        strcpy(Key, VSC_CONF_KEY);
    }
}VSCConfSystemKey;

typedef struct __VSCConfDeviceKey {
    u32 nId;
    s8 Key[CONF_KEY_STR_MAX];
    __VSCConfDeviceKey(u32 id)
    {
        memset(Key, 0, CONF_KEY_STR_MAX);
        strcpy(Key, VSC_CONF_CHANNEL_KEY);
        nId = id;
    }
}VSCConfDeviceKey;


typedef struct __VSCConfData__ {
    u32 DeviceMap[CONF_MAP_MAX];
    u32 Language;
    u32 DeviceNum;
}VSCConfData__;

typedef struct __VSCConfData {
    union {
        VSCConfData__ conf;
        u8 whole[1024 * 128];
    } data;
}VSCConfData;

typedef struct __VSCDeviceData__ {
    u32 nId;
    VSCDeviceType nType;
    VSCDeviceSubType nSubType;

    s8 Name[CONF_NAME_MAX];
    s8 Param[VSC_CONF_CH_PARAM_MAX];

    s8 IP[VSC_CONF_CH_PARAM_MAX];
    s8 Port[VSC_CONF_CH_PARAM_MAX];
    s8 User[VSC_CONF_CH_PARAM_MAX];
    s8 Password[VSC_CONF_CH_PARAM_MAX];

    /* Camera Param */
    s8 RtspLocation[VSC_CONF_CH_PARAM_MAX];
    s8 FileLocation[VSC_CONF_CH_PARAM_MAX];
    s8 OnvifAddress[VSC_CONF_CH_PARAM_MAX];
    s8 CameraIndex[VSC_CONF_CH_PARAM_MAX];/* This is For USB Camera */

    u32 UseProfileToken;/* 1 stand for use, 0 stand for do not use */
    s8 OnvifProfileToken[VSC_CONF_CH_PARAM_MAX];
}VSCDeviceData__;

typedef struct __VSCDeviceData {
    union {
        VSCDeviceData__ conf;
        u8 whole[1024 * 128];
    } data;
}VSCDeviceData;
#pragma pack(pop)

#endif /* _CONF_H_ */
