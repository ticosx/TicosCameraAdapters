## TicosCameraAdapters

- DVPCameraAdapter class
- TK_EspCameraAdapter class

Example:

```c
#include "TK_EspCamera.h"

TK_EspCamera* camera;

void setup()
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = getValue<input_D0>(ctx);
    config.pin_d1 = getValue<input_D1>(ctx);
    config.pin_d2 = getValue<input_D2>(ctx);
    config.pin_d3 = getValue<input_D3>(ctx);
    config.pin_d4 = getValue<input_D4>(ctx);
    config.pin_d5 = getValue<input_D5>(ctx);
    config.pin_d6 = getValue<input_D6>(ctx);
    config.pin_d7 = getValue<input_D7>(ctx);
    config.pin_xclk = getValue<input_XCLK>(ctx);
    config.pin_pclk = getValue<input_PCLK>(ctx);
    config.pin_vsync = getValue<input_VSYNC>(ctx);
    config.pin_href = getValue<input_HREF>(ctx);
    config.pin_sscb_sda = getValue<input_SIOD>(ctx);
    config.pin_sscb_scl = getValue<input_SIOC>(ctx);
    config.pin_pwdn = -1;
    config.pin_reset = -1;
    config.xclk_freq_hz = 15000000;
    config.pixel_format = PIXFORMAT_RGB565;

    config.jpeg_quality = 12;
    config.fb_count = 2;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.frame_size = FRAMESIZE_QVGA;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    
    camera = new TK_EspCamera(&config);
    camera->init();
}

void loop()
{
    uint8_t * buf = NULL;
    size_t buf_len = 0;
    char filename[256];
    camera->setFrameSize(FRAMESIZE_SXGA);	//设置帧大小
    camera->frameVerFlip(true);				//使能帧画面水平翻转
    cam_hal_frame_t*fb = camera->getFrame();		//获取一帧
    size_t size = dump(getValue<input_FILE>(ctx), filename);
    filename[size] = 0;
    camera->frame2Jpg(80, &buf, &buf_len);		//转化为jpg
    camera->refundFrame();			//退还帧画面
}
```

