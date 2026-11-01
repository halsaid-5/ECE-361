#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>
int sensor_read(uint32_t *base,time_t timestamp,reading_t *out){
    if(!base||!out)return -1;
    int rc=0;uint32_t temp=iom361_readReg(base,TEMP_REG,&rc);if(rc)return -1;
    uint32_t humid=iom361_readReg(base,HUMID_REG,&rc);if(rc)return -1;
    out->timestamp=timestamp;
    out->temp_c=roundf(((float)temp/1048576.0f*200.0f-50.0f)*10.0f)/10.0f;
    out->rh_pct=roundf(((float)humid/1048576.0f*100.0f)*10.0f)/10.0f;
    return 0;
}
