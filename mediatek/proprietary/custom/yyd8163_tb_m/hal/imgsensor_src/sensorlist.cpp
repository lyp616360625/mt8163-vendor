/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

#include <utils/Log.h>
#include <utils/Errors.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_sensor.h"
#include "camera_calibration_cam_cal.h"
#include "kd_imgsensor.h"

#define YUV_INFO(_id, name, getCalData)\
    { \
    _id, name, \
    NSFeature::YUVSensorInfo<_id>::createInstance(name, #name), \
    (NSFeature::SensorInfoBase*(*)()) \
    NSFeature::YUVSensorInfo<_id>::getInstance, \
    NSFeature::YUVSensorInfo<_id>::getDefaultData, \
    getCalData, \
	NSFeature::YUVSensorInfo<_id>::getNullFlickerPara \
    }
#define RAW_INFO(_id, name, getCalData)\
    { \
    _id, name, \
    NSFeature::RAWSensorInfo<_id>::createInstance(name, #name), \
    (NSFeature::SensorInfoBase*(*)()) \
    NSFeature::RAWSensorInfo<_id>::getInstance, \
    NSFeature::RAWSensorInfo<_id>::getDefaultData, \
    getCalData, \
	NSFeature::RAWSensorInfo<_id>::getFlickerPara \
    }

MSDK_SENSOR_INIT_FUNCTION_STRUCT SensorList[] =
{
/*IMX*/
#if defined(IMX220_MIPI_RAW)
    RAW_INFO(IMX220_SENSOR_ID, SENSOR_DRVNAME_IMX220_MIPI_RAW,NULL),
#endif
#if defined(IMX219_MIPI_RAW)
    RAW_INFO(IMX219_SENSOR_ID, SENSOR_DRVNAME_IMX219_MIPI_RAW, CAM_CALGetCalData),
#endif
#if defined(IMX214_MIPI_RAW)
    RAW_INFO(IMX214_SENSOR_ID, SENSOR_DRVNAME_IMX214_MIPI_RAW,NULL),
#endif
#if defined(IMX179_MIPI_RAW)
    RAW_INFO(IMX179_SENSOR_ID, SENSOR_DRVNAME_IMX179_MIPI_RAW,NULL),
#endif
#if defined(IMX132_MIPI_RAW)
    RAW_INFO(IMX132MIPI_SENSOR_ID, SENSOR_DRVNAME_IMX132_MIPI_RAW, NULL),
#endif
#if defined(IMX135_MIPI_RAW)
    RAW_INFO(IMX135_SENSOR_ID, SENSOR_DRVNAME_IMX135_MIPI_RAW,NULL),
#endif
#if defined(IMX105_MIPI_RAW)
    RAW_INFO(IMX105_SENSOR_ID, SENSOR_DRVNAME_IMX105_MIPI_RAW,NULL),
#endif
#if defined(IMX073_MIPI_RAW)
    RAW_INFO(IMX073_SENSOR_ID, SENSOR_DRVNAME_IMX073_MIPI_RAW,NULL),
#endif
/*OV (OmniVision)*/
#if defined(OV16825_MIPI_RAW)
    RAW_INFO(OV16825MIPI_SENSOR_ID, SENSOR_DRVNAME_OV16825_MIPI_RAW, NULL),
#endif
#if defined(OV13850_MIPI_RAW)
    RAW_INFO(OV13850_SENSOR_ID, SENSOR_DRVNAME_OV13850_MIPI_RAW,NULL),
#endif
#if defined(OV12830_MIPI_RAW)
    RAW_INFO(OV12830_SENSOR_ID, SENSOR_DRVNAME_OV12830_MIPI_RAW, NULL),
#endif
#if defined(OV9760_MIPI_RAW)
    RAW_INFO(OV9760MIPI_SENSOR_ID,SENSOR_DRVNAME_OV9760_MIPI_RAW,NULL),
#endif
#if defined(OV9740_MIPI_YUV)
    YUV_INFO(OV9740MIPI_SENSOR_ID, SENSOR_DRVNAME_OV9740_MIPI_YUV, NULL),
#endif
#if defined(OV9726_RAW)
    RAW_INFO(OV9726_SENSOR_ID,SENSOR_DRVNAME_0V9726_RAW,NULL),
#endif
#if defined(OV9726_MIPI_RAW)
    RAW_INFO(OV9726MIPI_SENSOR_ID,SENSOR_DRVNAME_OV9726_MIPI_RAW,NULL),
#endif
#if defined(OV8865_MIPI_RAW)
    RAW_INFO(OV8865_SENSOR_ID, SENSOR_DRVNAME_OV8865_MIPI_RAW,NULL),
#endif
#if defined(OV8858_MIPI_RAW)
    RAW_INFO(OV8858_SENSOR_ID, SENSOR_DRVNAME_OV8858_MIPI_RAW,NULL),
#endif
#if defined(OV8830_RAW)
    RAW_INFO(OV8830_SENSOR_ID, SENSOR_DRVNAME_OV8830_RAW, NULL),
#endif
#if defined(OV8825_MIPI_RAW)
    RAW_INFO(OV8825_SENSOR_ID, SENSOR_DRVNAME_OV8825_MIPI_RAW, NULL),
#endif
#if defined(OV7675_YUV)
    YUV_INFO(OV7675_SENSOR_ID, SENSOR_DRVNAME_OV7675_YUV, NULL),
#endif
#if defined(OV5693_MIPI_RAW)
    RAW_INFO(OV5693_SENSOR_ID, SENSOR_DRVNAME_OV5693_MIPI_RAW, NULL),
#endif
#if defined(OV5670_MIPI_RAW)
    RAW_INFO(OV5670MIPI_SENSOR_ID, SENSOR_DRVNAME_OV5670_MIPI_RAW, NULL),
#endif
#if defined(OV5650_RAW)
    RAW_INFO(OV5650_SENSOR_ID, SENSOR_DRVNAME_OV5650_RAW,NULL),
#endif
#if defined(OV5650MIPI_RAW)
    RAW_INFO(OV5650MIPI_SENSOR_ID, SENSOR_DRVNAME_OV5650MIPI_RAW,NULL),
#endif
#if defined(OV5648_MIPI_RAW)
    RAW_INFO(OV5648MIPI_SENSOR_ID, SENSOR_DRVNAME_OV5648_MIPI_RAW, NULL),
#endif
#if defined(OV5647_MIPI_RAW)
    RAW_INFO(OV5647MIPI_SENSOR_ID, SENSOR_DRVNAME_OV5647MIPI_RAW, NULL),
#endif
#if defined(OV5647_RAW)
    RAW_INFO(OV5647_SENSOR_ID, SENSOR_DRVNAME_OV5647_RAW, NULL),
#endif
#if defined(OV5645_MIPI_YUV)
    YUV_INFO(OV5645MIPI_SENSOR_ID,SENSOR_DRVNAME_OV5645_MIPI_YUV, OV5645_MIPI_YUV_SensorInit),
#endif
#if defined(OV5642_RAW)
    RAW_INFO(OV5642_SENSOR_ID, SENSOR_DRVNAME_OV5642_RAW, NULL),
#endif
#if defined(OV5642_MIPI_YUV)
    YUV_INFO(OV5642_SENSOR_ID, SENSOR_DRVNAME_OV5642_MIPI_YUV, NULL),
#endif
#if defined(OV5642_MIPI_RGB)
    YUV_INFO(OV5642_SENSOR_ID, SENSOR_DRVNAME_OV5642_MIPI_RGB, NULL),
#endif
#if defined(OV5642_MIPI_JPG)
    YUV_INFO(OV5642_SENSOR_ID, SENSOR_DRVNAME_OV5642_MIPI_JPG, NULL),
#endif
#if defined(OV5642_YUV)
    YUV_INFO(OV5642_SENSOR_ID, SENSOR_DRVNAME_OV5642_YUV, NULL),
#endif
#if defined(OV4688_MIPI_RAW)
    RAW_INFO(OV4688MIPI_SENSOR_ID, SENSOR_DRVNAME_OV4688_MIPI_RAW, NULL),
#endif
#if defined(OV3640_RAW)
    {OV3640_SENSOR_ID, SENSOR_DRVNAME_OV3640_RAW,NULL),
#endif
#if defined(OV3640_YUV)
    YUV_INFO(OV3640_SENSOR_ID, SENSOR_DRVNAME_OV3640_YUV, NULL),
#endif
#if defined(OV3640_YUV_AF)
    YUV_INFO(OV3640_SENSOR_ID, SENSOR_DRVNAME_OV3640_YUV, NULL),
#endif
#if defined(OV2680_MIPI_RAW)
    RAW_INFO(OV2680MIPI_SENSOR_ID, SENSOR_DRVNAME_OV2680_MIPI_RAW,NULL),
#endif
#if defined(OV2722_MIPI_RAW)
    RAW_INFO(OV2722MIPI_SENSOR_ID, SENSOR_DRVNAME_OV2722_MIPI_RAW, NULL),
#endif
#if defined(OV2659_YUV)
    YUV_INFO(OV2659_SENSOR_ID, SENSOR_DRVNAME_OV2659_YUV,NULL),
#endif
#if defined(OV2655_YUV)
    YUV_INFO(OV2650_SENSOR_ID, SENSOR_DRVNAME_OV2655_YUV,NULL),
#endif
#if defined(OV2650_RAW)
    RAW_INFO(OV2650_SENSOR_ID, SENSOR_DRVNAME_OV2650_RAW,NULL),
#endif
/*S5K*/
#if defined(S5K2P8_MIPI_RAW)
    RAW_INFO(S5K2P8_SENSOR_ID, SENSOR_DRVNAME_S5K2P8_MIPI_RAW, NULL),
#endif
#if defined(S5K3H2YX_MIPI_RAW)
    RAW_INFO(S5K3H2YX_SENSOR_ID, SENSOR_DRVNAME_S5K3H2YX_MIPI_RAW, NULL),
#endif
#if defined(S5K3H7Y_MIPI_RAW)
    RAW_INFO(S5K3H7Y_SENSOR_ID, SENSOR_DRVNAME_S5K3H7Y_MIPI_RAW, NULL),
#endif
#if defined(S5K4H5YC_MIPI_RAW)
    RAW_INFO(S5K4H5YC_SENSOR_ID, SENSOR_DRVNAME_S5K4H5YC_MIPI_RAW, NULL),
#endif
#if defined(S5K4H5YX_2LANE_MIPI_RAW)
    RAW_INFO(S5K4H5YX_2LANE_SENSOR_ID, SENSOR_DRVNAME_S5K4H5YX_2LANE_MIPI_RAW, NULL),
#endif
#if defined(S5K5E2YA_MIPI_RAW)
    RAW_INFO(S5K5E2YA_SENSOR_ID, SENSOR_DRVNAME_S5K5E2YA_MIPI_RAW, NULL),
#endif
#if defined(S5K5CAGX_YUV)
    YUV_INFO(S5K5CAGX_SENSOR_ID, SENSOR_DRVNAME_S5K5CAGX_YUV, NULL),
#endif
#if defined(S5K4E1GA_MIPI_RAW)
    RAW_INFO(S5K4E1GA_SENSOR_ID, SENSOR_DRVNAME_S5K4E1GA_MIPI_RAW, NULL),
#endif
#if defined(S5K4ECGX_YUV)
    YUV_INFO(S5K4ECGX_SENSOR_ID, SENSOR_DRVNAME_S5K4ECGX_YUV, NULL),
#endif
#if defined(S5K4ECGX_MIPI_YUV)
    YUV_INFO(S5K4ECGX_SENSOR_ID, SENSOR_DRVNAME_S5K4ECGX_MIPI_YUV, NULL),
#endif
#if defined(S5K4ECGX_MIPI_JPG)
    YUV_INFO(S5K4ECGX_SENSOR_ID, SENSOR_DRVNAME_S5K4ECGX_MIPI_JPG, NULL),
#endif
#if defined(S5K8AAYX_MIPI_YUV)
    YUV_INFO(S5K8AAYX_MIPI_SENSOR_ID, SENSOR_DRVNAME_S5K8AAYX_MIPI_YUV, NULL),
#endif
#if defined(S5K8AAYX_YUV)
    YUV_INFO(S5K8AAYX_MIPI_SENSOR_ID, SENSOR_DRVNAME_S5K8AAYX_YUV, NULL),
#endif
/*HI*/
#if defined(HI841_MIPI_RAW)
    RAW_INFO(HI841_SENSOR_ID, SENSOR_DRVNAME_HI841_MIPI_RAW,HI841_MIPI_RAW_SensorInit),
#endif
#if defined(HI707_YUV)
    YUV_INFO(HI707_SENSOR_ID, SENSOR_DRVNAME_HI707_YUV, NULL),
#endif
#if defined(HI704_YUV)
    YUV_INFO(HI704_SENSOR_ID, SENSOR_DRVNAME_HI704_YUV, NULL),
#endif
#if defined(HI551_MIPI_RAW)
    RAW_INFO(HI551_SENSOR_ID, SENSOR_DRVNAME_HI551_MIPI_RAW, NULL),
#endif
#if defined(HI545_MIPI_RAW)
    RAW_INFO(HI545MIPI_SENSOR_ID, SENSOR_DRVNAME_HI545_MIPI_RAW, NULL),
#endif
#if defined(HI544_MIPI_RAW)
    RAW_INFO(HI544MIPI_SENSOR_ID, SENSOR_DRVNAME_HI544_MIPI_RAW, NULL),
#endif
#if defined(HI542_RAW)
    RAW_INFO(HI542_SENSOR_ID, SENSOR_DRVNAME_HI542_RAW, NULL),
#endif
#if defined(HI542_MIPI_RAW)
    RAW_INFO(HI542MIPI_SENSOR_ID, SENSOR_DRVNAME_HI542MIPI_RAW, NULL),
#endif
#if defined(HI253_YUV)
    YUV_INFO(HI253_SENSOR_ID, SENSOR_DRVNAME_HI253_YUV, NULL),
#endif
#if defined(HI191_MIPI_RAW)
    RAW_INFO(HI191MIPI_SENSOR_ID, SENSOR_DRVNAME_HI191_MIPI_RAW, NULL),
#endif
/*MT*/
#if defined(MT9P012_RAW)
    RAW_INFO(MT9P012_SENSOR_ID, SENSOR_DRVNAME_MT9P012_RAW,NULL),
#endif
#if defined(MT9P015_RAW)
    RAW_INFO(MT9P015_SENSOR_ID, SENSOR_DRVNAME_MT9P015_RAW,NULL),
#endif
#if defined(MT9P017_RAW)
    RAW_INFO(MT9P017_SENSOR_ID, SENSOR_DRVNAME_MT9P017_RAW,NULL),
#endif
#if defined(MT9P017_MIPI_RAW)
    RAW_INFO(MT9P017MIPI_SENSOR_ID, SENSOR_DRVNAME_MT9P017_MIPI_RAW,NULL),
#endif
#if defined(MT9T113_YUV)
    YUV_INFO(MT9T113_SENSOR_ID, SENSOR_DRVNAME_MT9T113_YUV, NULL),
#endif
#if defined(MT9T113_MIPI_YUV)
    YUV_INFO(MT9T113MIPI_SENSOR_ID, SENSOR_DRVNAME_MT9T113_MIPI_YUV,NULL),
#endif
#if defined(MT9V113_YUV)
    YUV_INFO(MT9V113_SENSOR_ID, SENSOR_DRVNAME_MT9V113_YUV, NULL),
#endif
#if defined(MT9V114_YUV)
    YUV_INFO(MT9V114_SENSOR_ID, SENSOR_DRVNAME_MT9V114_YUV, NULL),
#endif
#if defined(MT9D115_MIPI_RAW)
    RAW_INFO(MT9D115_SENSOR_ID, SENSOR_DRVNAME_MT9D115_MIPI_RAW,NULL),
#endif
#if defined(MT9V115_YUV)
    YUV_INFO(MT9V115_SENSOR_ID,SENSOR_DRVNAME_MT9V115_YUV,NULL),
#endif
/*GC*/
#if defined(GC2755_MIPI_RAW)
    RAW_INFO(GC2755_SENSOR_ID, SENSOR_DRVNAME_GC2755_MIPI_RAW,NULL),
#endif
#if defined(GC5024_MIPI_RAW)
    RAW_INFO(GC5024_SENSOR_ID, SENSOR_DRVNAME_GC5024_MIPI_RAW,NULL),
#endif
#if defined(GC2355_MIPI_RAW)
    RAW_INFO(GC2355_SENSOR_ID, SENSOR_DRVNAME_GC2355_MIPI_RAW,NULL),
#endif
#if defined(GC2235_RAW)
    RAW_INFO(GC2235_SENSOR_ID, SENSOR_DRVNAME_GC2235_RAW, NULL),
#endif
#if defined(GC2035_YUV)
    YUV_INFO(GC2035_SENSOR_ID, SENSOR_DRVNAME_GC2035_YUV, NULL),
#endif
#if defined(GC0330_YUV)
    YUV_INFO(GC0330_SENSOR_ID, SENSOR_DRVNAME_GC0330_YUV, NULL),
#endif
#if defined(GC0329_YUV)
    YUV_INFO(GC0329_SENSOR_ID, SENSOR_DRVNAME_GC0329_YUV, NULL),
#endif
#if defined(GC0313_MIPI_YUV)
    YUV_INFO(GC0313MIPI_YUV_SENSOR_ID, SENSOR_DRVNAME_GC0313MIPI_YUV, NULL),
#endif
#if defined(GC0310_MIPI_YUV)
    YUV_INFO(GC0310_SENSOR_ID, SENSOR_DRVNAME_GC0310_MIPI_YUV,NULL),
#endif
#if defined(GC0310_YUV)
    YUV_INFO(GC0310_SENSOR_ID, SENSOR_DRVNAME_GC0310_YUV,NULL),
#endif
/*SP*/
#if defined(SP0A19_YUV)
    YUV_INFO(SP0A19_YUV_SENSOR_ID, SENSOR_DRVNAME_SP0A19_YUV, NULL),
#endif
#if defined(SP2518_YUV)
    YUV_INFO(SP2518_YUV_SENSOR_ID, SENSOR_DRVNAME_SP2518_YUV, NULL),
#endif
#if defined(SP2509_MIPI_RAW)
    RAW_INFO(SP2509_SENSOR_ID, SENSOR_DRVNAME_SP2509_MIPI_RAW,NULL),
#endif
#if defined(SP5509_MIPI_RAW)
    RAW_INFO(HI556_SENSOR_ID, SENSOR_DRVNAME_HI556_MIPI_RAW,NULL),
#endif
#if defined(SP5506_MIPI_RAW)
    RAW_INFO(OV5675MIPI_SENSOR_ID, SENSOR_DRVNAME_OV5675_MIPI_RAW,NULL),
#endif
/*A*/
#if defined(A5141_MIPI_RAW)
    RAW_INFO(A5141MIPI_SENSOR_ID, SENSOR_DRVNAME_A5141_MIPI_RAW,NULL),
#endif
#if defined(A5142_MIPI_RAW)
    RAW_INFO(A5142MIPI_SENSOR_ID, SENSOR_DRVNAME_A5142_MIPI_RAW,NULL),
#endif
/*HM*/
#if defined(HM3451_RAW)
    RAW_INFO(HM3451_SENSOR_ID, SENSOR_DRVNAME_HM3451_RAW, NULL),
#endif
/*AR*/
#if defined(AR0833_MIPI_RAW)
  RAW_INFO(AR0833_SENSOR_ID, SENSOR_DRVNAME_AR0833_MIPI_RAW,NULL),
#endif
/*SIV*/
#if defined(SIV120B_YUV)
    YUV_INFO(SIV120B_SENSOR_ID, SENSOR_DRVNAME_SIV120B_YUV, NULL),
#endif
#if defined(SIV121D_YUV)
    YUV_INFO(SIV121D_SENSOR_ID, SENSOR_DRVNAME_SIV121D_YUV, NULL),
#endif
/*PAS (PixArt Image)*/
#if defined(PAS6180_SERIAL_YUV)
    YUV_INFO(PAS6180_SENSOR_ID, SENSOR_DRVNAME_PAS6180_SERIAL_YUV, NULL),
#endif
/*Panasoic*/
#if defined(MN34152_MIPI_RAW)
    RAW_INFO(MN34152_SENSOR_ID, SENSOR_DRVNAME_MN34152_MIPI_RAW, NULL),
#endif
/*Toshiba*/
#if defined(T4K28_YUV)
    YUV_INFO(T4K28_SENSOR_ID, SENSOR_DRVNAME_T4K28_YUV, T4K28_YUV_SensorInit),
#endif
#if defined(T4KA7_MIPI_RAW)
    RAW_INFO(T4KA7_SENSOR_ID, SENSOR_DRVNAME_T4KA7_MIPI_RAW, NULL),
#endif
/*Others*/
#if defined(ISX012_MIPI_YUV)
    YUV_INFO(ISX012MIPI_SENSOR_ID, SENSOR_DRVNAME_ISX012_MIPI_YUV, ISX012_MIPI_YUV_SensorInit),
#endif
#if defined(T8EV5_YUV)
    YUV_INFO(T8EV5_SENSOR_ID, SENSOR_DRVNAME_T8EV5_YUV, NULL),
#endif
/*LCA Test*/
#if defined(IMX135_MIPI_RAW_5MP)
    RAW_INFO(IMX135_SENSOR_ID, SENSOR_DRVNAME_IMX135_MIPI_RAW_5MP,NULL),
#endif
/*  ADD sensor driver before this line */
    {0,{0},NULL, NULL, NULL}//end of list
};

UINT32 GetSensorInitFuncList(MSDK_SENSOR_INIT_FUNCTION_STRUCT **ppSensorList)
{
    if (NULL == ppSensorList) {
        ALOGE("ERROR: NULL pSensorList\n");
        return MHAL_UNKNOWN_ERROR;
    }
    *ppSensorList = &SensorList[0];
	return MHAL_NO_ERROR;
} // GetSensorInitFuncList()


