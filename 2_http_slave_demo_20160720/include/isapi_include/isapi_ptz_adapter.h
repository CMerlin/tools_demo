#ifndef _ISAPI_PTZ_ADAPTER_H_
#define _ISAPI_PTZ_ADAPTER_H_

#include "isapi_adapter.h"
#include "config_usr.h"
#include "config.h"
#include "sys_net.h"
#include "sys_netapi.h"


typedef enum
{
    WEB_PTZ_CMD_STOP,
    WEB_PTZ_CMD_UP,            // ��
    WEB_PTZ_CMD_DOWN,          // ��
    WEB_PTZ_CMD_LEFT,          // ��
    WEB_PTZ_CMD_RIGHT,         // ��
    WEB_PTZ_CMD_FOCUS_INC,     /* �۽�+ */
    WEB_PTZ_CMD_FOCUS_DEC,     /* �۽�- */
    WEB_PTZ_CMD_IRIS_INC,      /* ��Ȧ+ */
    WEB_PTZ_CMD_IRIS_DEC,      /* ��Ȧ- */
    WEB_PTZ_CMD_ZOOM_DEC,      /* ����+ */
    WEB_PTZ_CMD_ZOOM_INC,      /* ����- */
    WEB_PTZ_CMD_F1,            // ����
    WEB_PTZ_CMD_F1_1,
    WEB_PTZ_CMD_F2,            // ����
    WEB_PTZ_CMD_F2_1,
    WEB_PTZ_CMD_AUTO,          // �Զ�
    WEB_PTZ_CMD_AUTO_1,
    WEB_PTZ_CMD_PRESET_SET,    // Ԥ��
    WEB_PTZ_CMD_PRESET_GET,    // ����
    WEB_PTZ_CMD_SETUP,
    WEB_PTZ_CMD_ENTER,
    WEB_PTZ_CMD_PAGEUP,
    WEB_PTZ_CMD_PAGEDOWN,
    WEB_PTZ_CMD_BRUSH,         // ��ˢ
    WEB_PTZ_CMD_LEFT_UP,       //24����
    WEB_PTZ_CMD_LEFT_DOWN,     //25����
    WEB_PTZ_CMD_RIGHT_UP,      //26����
    WEB_PTZ_CMD_RIGHT_DOWN,    //27����
    WEB_PTZ_CMD_PRESET_CLR,    //28Ԥ�õ����
    WEB_PTZ_CMD_SET_PATTERN_START, //29�켣Ѳ��--���ÿ�ʼ
    WEB_PTZ_CMD_SET_PATTERN_END,   //30�켣Ѳ��--���ý���
    WEB_PTZ_CMD_SET_PATTERN_RUN,   //31�켣Ѳ��--����

} ADDTYPE_E;



typedef struct
{
    uint32  channel;    // ͨ����
    uint32  command;    // ��̨�������� Ϊ0x00010028��ֹͣ
    uint32  index;      // Ԥ�Ƶ��(�������Чֵ��ΧӰ��)[0, 255]
    uint32  speed;      // �����ٶ� [0, 255] ��0���ٶ���������
} PTZ_DEVICE_CTRL;


int web_ptz_ctrl (PTZ_DEVICE_CTRL* ptz_ctrl);

#endif

