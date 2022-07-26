#include "TK_EspCamera.h"
#include "Log.h"

TK_EspCamera::TK_EspCamera(camera_config_t *camCfg) \
 : DVPCameraAdapter(camCfg->pixel_format,camCfg->frame_size,NULL){
    config = *camCfg;
    isInit = false;
}

TK_EspCamera::~TK_EspCamera(){
    deinit();
}

bool TK_EspCamera::init()
{
    if(isInit){
        return reinit();
    }
    if(esp_camera_init(&config) == ESP_OK)
    {
        sensor = esp_camera_sensor_get();
        isInit = true;
        return isInit;
    }
    logWarn("EspCamera int Err");
    return isInit;
}

bool TK_EspCamera::deinit()
{
    if(!isInit){
        return true; 
    }

    if(esp_camera_deinit() == ESP_OK){
        isInit = false;
    }else{
        isInit = true;
    }
    return !isInit;
}

bool TK_EspCamera::reinit()
{
    deinit();
    return init();
}

cam_hal_frame_t* TK_EspCamera::getFrame()
{
    espFbBuf = esp_camera_fb_get();
    if(espFbBuf == NULL){
        logWarn("TK_EspCamera get frame err");
    }
    frameBuf.buf = espFbBuf->buf;
    frameBuf.len = espFbBuf->len;
    logDebug("TK_EspCamera class get frame");
    return &frameBuf;
}

bool TK_EspCamera::refundFrame()
{
    if(espFbBuf != NULL){
        esp_camera_fb_return(espFbBuf);
    }
    logDebug("TK_EspCamera class refund frame");
    return true;
}

bool TK_EspCamera::frameVerFlip(bool enable)
{
    if(enable){
        sensor->set_vflip(sensor,1);
    }else{
        sensor->set_vflip(sensor,0);
    }
    return true;
}

bool TK_EspCamera::frameHorFlip(bool enable)
{
    if(enable){
        return false;
    }
    return true;
}

bool TK_EspCamera::setXclkFre(int fre)
{
    config.xclk_freq_hz = fre;
    #if 0
    if(fre > 5000000 && config.frame_size > FRAMESIZE_XGA) //15M
    {
        config.xclk_freq_hz = 5000000;
        return false;
    }
    #endif
    if(isInit){
        return init();
    }
    return true;
}

int TK_EspCamera::getXclkFre()
{
    return config.xclk_freq_hz;
}

pixformat_t TK_EspCamera::getPixFormat()
{
    return this->pixFormat;
}

framesize_t TK_EspCamera::getFrameSize()
{
    return this->frameSize;
}

bool TK_EspCamera::setFrameSize(framesize_t frameSize)
{
    #if 0
    if(frameSize > FRAMESIZE_XGA && config.xclk_freq_hz > 8000000){
        config.xclk_freq_hz = 8000000;
    }
    if(frameSize <= FRAMESIZE_XGA && config.xclk_freq_hz < 15000000){
        config.xclk_freq_hz = 15000000;
    }
    #endif
    config.frame_size = frameSize;
    this->frameSize = frameSize;
    if(isInit){
        return init();
    }
    return true;
}

bool TK_EspCamera::frame2Jpg(uint8_t quality,uint8_t ** out, size_t * out_len){
    if(espFbBuf != NULL){
        return frame2jpg(espFbBuf,quality,out,out_len);
    }
    return false;
}

bool TK_EspCamera::frame2Bmp(uint8_t ** out, size_t * out_len)
{
    if(espFbBuf != NULL){
        return frame2bmp(espFbBuf,out,out_len);
    }
    return false;
}
