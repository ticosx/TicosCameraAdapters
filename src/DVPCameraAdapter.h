#ifndef DVP_Camera_Adapter_h
#define DVP_Camera_Adapter_h

#include "CameraAdapter.h"

//dvp接口信息
typedef struct
{
    int pwdn_pin;
    int reset_pin;
    int xclk_pin;
    int sda_pin;
    int sck_pin;
    int data_pin[12];
    int pin_vsync;
    int pin_hsync;
    int pin_pclk;
    int xclk_freq_hz;
}dvp_info;

/*!
 * @brief DVP接口的摄像头
 */
class DVPCameraAdapter:public CameraAdapter{
public:
    DVPCameraAdapter(pixformat_t pixFormat,framesize_t frameSize,dvp_info*dvpInfo);
    virtual ~DVPCameraAdapter();
    virtual bool init() = 0;
    virtual bool deinit() = 0;
    virtual cam_hal_frame_t*getFrame() = 0;
    virtual bool refundFrame() = 0;  
    virtual bool frameVerFlip(bool enable) = 0;
    virtual bool frameHorFlip(bool enable) = 0;
    virtual pixformat_t getPixFormat() = 0;
    virtual framesize_t getFrameSize() = 0;
protected:
    dvp_info*dvpInfo;
};


#endif // DVP_Camera_Adapter_h


