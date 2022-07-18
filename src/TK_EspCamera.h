#ifndef TK_Esp_Camera_h
#define TK_Esp_Camera_h

#include "DVPCameraAdapter.h"
#include "esp_camera.h"

/*!
 * @brief 乐鑫科技esp32-camera库所支持的摄像头
 */
class TK_EspCamera : public DVPCameraAdapter{
public:
    TK_EspCamera(camera_config_t*camCfg);
    virtual ~TK_EspCamera();
    virtual bool init() override ;
    virtual bool deinit() override ;
    virtual cam_hal_frame_t*getFrame() override ;
    virtual bool refundFrame() override ;
    virtual bool frameVerFlip(bool enable) override ;
    virtual bool frameHorFlip(bool enable) override ;
    virtual pixformat_t getPixFormat() override ;
    virtual framesize_t getFrameSize() override ;
/*!
 *    @brief  设置xclk信号频率
 *    @return 设置成功则返回 true
 *    @note   fre单位为hz，若摄像头没有初始化，会直接返回true
 */
    virtual bool setXclkFre(int fre);
/*!
 *    @brief  获取xclk信号频率
 *    @return xclk信号频率
 *    @note   fre单位为hz，若摄像头没有初始化，会直接返回频率的缓存值
 */
    virtual int getXclkFre();
/*!
 *    @brief  设置帧大小
 *    @par    帧大小 见sensor.h
 *    @return xclk信号频率
 */
    virtual bool setFrameSize(framesize_t frameSize);

    virtual bool frame2Jpg(uint8_t quality,uint8_t ** out, size_t * out_len);
    virtual bool frame2Bmp(uint8_t ** out, size_t * out_len);
private:
    bool reinit();
    bool isInit;
    sensor_t*sensor;
    camera_fb_t*espFbBuf;
    camera_config_t config;
};

#endif // TK_Esp_Camera_h




