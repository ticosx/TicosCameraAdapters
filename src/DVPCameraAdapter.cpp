#include "DVPCameraAdapter.h"

DVPCameraAdapter::DVPCameraAdapter(pixformat_t pixFormat,framesize_t frameSize,dvp_info*dvpInfo) \
: CameraAdapter(pixFormat,frameSize){
    if(dvpInfo != NULL)
    {
        this->dvpInfo = new dvp_info;
        *this->dvpInfo = *dvpInfo;
    }else{this->dvpInfo = NULL;}
}

DVPCameraAdapter::~DVPCameraAdapter(){if(dvpInfo!=NULL) delete dvpInfo;}


