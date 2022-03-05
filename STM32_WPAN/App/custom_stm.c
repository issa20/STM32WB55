/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.c
  * @author  MCD Application Team
  * @brief   Custom Example Service.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "common_blesvc.h"
#include "custom_stm.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "ibeacon_service.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct{
  uint16_t  CustomMyserviceHdle;                    /**< MyService handle */
  uint16_t  CustomPowerHdle;                  /**< Power handle */
  uint16_t  CustomMajorHdle;                  /**< Major handle */
  uint16_t  CustomMinorHdle;                  /**< Minor handle */
  uint16_t  CustomValidateHdle;                  /**< Validate handle */
}CustomContext_t;

/* USER CODE BEGIN PTD */
//uint8_t Power[] = {
// 0x00,// -40 dBm		tx=-63
// 0x01,// -20.85 dBm	tx=-62
// 0x02,// -19.75 dBm	tx=-70
// 0x03,// -18.85 dBm	tx=-64
// 0x04,// -17.6 dBm	tx=-70
// 0x05,// -16.5 dBm	tx=-68
// 0x06,// -15.25 dBm	tx=-65
// 0x07,// -14.1 dBm	tx=-69
// 0x08,// -13.15 dBm	tx=-69
// 0x09,// -12.05 dBm	tx=-70
// 0x0A,// -10.9 dBm	tx=-69
// 0x0B,// -9.9 dBm		tx=-68
// 0x0C,// -8.85 dBm	tx=-61
// 0x0D,// -7.8 dBm		tx=-65
// 0x0E,// -6.9 dBm		tx=-64
// 0x0F,// -5.9 dBm		tx=-67
// 0x10,// -4.95 dBm	tx=-66
// 0x11,// -4 dBm		tx=-63
// 0x12,// -3.15 dBm	tx=-66
// 0x13,// -2.45 dBm	tx=-67
// 0x14,// -1.8 dBm		tx=-62
// 0x15,// -1.3 dBm		tx=-61
// 0x16,// -0.85 dBm	tx=-62
// 0x17,// -0.5 dBm		tx=-67
// 0x18,// -0.15 dBm	tx=-63
// 0x19,// 0 dBm		tx=-59
// 0x1A,// +1 dBm		tx=-65
// 0x1B,// +2 dBm		tx=-69
// 0x1C,// +3 dBm		tx=-61
// 0x1D,// +4 dBm		tx=-60
// 0x1E,// +5 dBm		tx=-57
// 0x1F,// +6 dBm		tx=-58
// } ;
uint8_t indexPower =0;
uint8_t major[2] ={0,0};
uint8_t minor[2] ={0,0};
uint16_t data_major = 0x0000;
uint16_t data_minor = 0x0000;
int8_t Power[] = {
 0x01,// -20.85 dBm tx=-62
 0x09,// -3.15 dBm  tx=-70
 0x12// +2 dBm		tx=-66
 } ;
uint8_t tx_power[] = {
-62,
-70,
-66
};

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
#define UUID_128_SUPPORTED  1

#if (UUID_128_SUPPORTED == 1)
#define BM_UUID_LENGTH  UUID_TYPE_128
#else
#define BM_UUID_LENGTH  UUID_TYPE_16
#endif

#define BM_REQ_CHAR_SIZE    (3)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET         2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static const uint8_t SizePower=1;
static const uint8_t SizeMajor=5;
static const uint8_t SizeMinor=5;
static const uint8_t SizeValidate=1;
/**
 * START of Section BLE_DRIVER_CONTEXT
 */
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") static CustomContext_t CustomContext;

/**
 * END of Section BLE_DRIVER_CONTEXT
 */

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *pckt);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
        uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
            uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
                uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

/* Hardware Characteristics Service */
/*
 The following 128bits UUIDs have been generated from the random UUID
 generator:
 D973F2E0-B19E-11E2-9E96-0800200C9A66: Service 128bits UUID
 D973F2E1-B19E-11E2-9E96-0800200C9A66: Characteristic_1 128bits UUID
 D973F2E2-B19E-11E2-9E96-0800200C9A66: Characteristic_2 128bits UUID
 */
#define COPY_MYSERVICE_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x00,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_POWER_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x01,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_MAJOR_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x02,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_MINOR_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x03,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_VALIDATE_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x04,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *event_pckt;
  evt_blecore_aci *blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *attribute_modified;
  Custom_STM_App_Notification_evt_t     Notification;
  /* USER CODE BEGIN Custom_STM_Event_Handler_1 */

  /* USER CODE END Custom_STM_Event_Handler_1 */

  return_value = SVCCTL_EvtNotAck;
  event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

  switch(event_pckt->evt)
  {
    case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
      blecore_evt = (evt_blecore_aci*)event_pckt->data;
      switch(blecore_evt->ecode)
      {
        case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
          attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
          if(attribute_modified->Attr_Handle == (CustomContext.CustomPowerHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            //HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
            indexPower = (attribute_modified->Attr_Data[0]) - 48;
            memset(attribute_modified->Attr_Data,0,sizeof(attribute_modified->Attr_Data));
            /* USER CODE END CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomPowerHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if(attribute_modified->Attr_Handle == (CustomContext.CustomMajorHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            //HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
            uint8_t length_major = 0;

            while(attribute_modified->Attr_Data[length_major]!=(uint8_t)0){
            	length_major++;
            }

            switch (length_major){
				case 1:
					major[1] = (attribute_modified->Attr_Data[0])-48;
					//major[0]=0x00;
					break;

				case 2:
					major[1] = (attribute_modified->Attr_Data[1])-48 + ((attribute_modified->Attr_Data[2])-48)*10;
					//major[0]=0x00;
					break;

				case 3:
					data_major = (attribute_modified->Attr_Data[2])-48 + ((attribute_modified->Attr_Data[1])-48)*10 + ((attribute_modified->Attr_Data[0])-48)*100;
					major[1]= data_major;
					major[0]=data_major>>8;

					break;

				case 4:
					data_major = (attribute_modified->Attr_Data[3])-48 + ((attribute_modified->Attr_Data[2])-48)*10 + ((attribute_modified->Attr_Data[1])-48)*100+((attribute_modified->Attr_Data[0])-48)*1000;
					major[1]= data_major;
					major[0]=data_major>>8;

					break;

				case 5:
					data_major = (attribute_modified->Attr_Data[4])-48 + ((attribute_modified->Attr_Data[3])-48)*10 + ((attribute_modified->Attr_Data[2])-48)*100+((attribute_modified->Attr_Data[1])-48)*1000+((attribute_modified->Attr_Data[0])-48)*10000;
					major[1]= data_major;
					major[0]=data_major>>8;

					break;
            }
            memset(attribute_modified->Attr_Data,0,sizeof(attribute_modified->Attr_Data));

            /* USER CODE END CUSTOM_STM_Service_1_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomMajorHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if(attribute_modified->Attr_Handle == (CustomContext.CustomMinorHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            //HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
            uint8_t length_minor = 0;

            while(attribute_modified->Attr_Data[length_minor]!=(uint8_t)0){
                  length_minor++;
			}

			switch (length_minor){
				case 1:
					minor[1] = (attribute_modified->Attr_Data[0])-48;
					//minor[0]=0x00;
					break;

				case 2:
					minor[1] = (attribute_modified->Attr_Data[1])-48 + ((attribute_modified->Attr_Data[0])-48)*10;
					//minor[0]=0x00;
					break;

				case 3:
					data_minor = (attribute_modified->Attr_Data[2])-48 + ((attribute_modified->Attr_Data[1])-48)*10 + ((attribute_modified->Attr_Data[0])-48)*100;
					minor[1]= data_minor;
					minor[0]=data_minor>>8;

					break;

				case 4:
					data_minor = (attribute_modified->Attr_Data[3])-48 + ((attribute_modified->Attr_Data[2])-48)*10 + ((attribute_modified->Attr_Data[1])-48)*100+((attribute_modified->Attr_Data[0])-48)*1000;
					minor[1]= data_minor;
					minor[0]=data_minor>>8;

					break;

				case 5:
					data_minor = (attribute_modified->Attr_Data[4])-48 + ((attribute_modified->Attr_Data[3])-48)*10 + ((attribute_modified->Attr_Data[2])-48)*100+((attribute_modified->Attr_Data[1])-48)*1000+((attribute_modified->Attr_Data[0])-48)*10000;
					minor[1]= data_minor;
					minor[0]=data_minor>>8;

					break;
			}
			memset(attribute_modified->Attr_Data,0,sizeof(attribute_modified->Attr_Data));

            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomMinorHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if(attribute_modified->Attr_Handle == (CustomContext.CustomValidateHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
			//HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
			IBeacon_Process();
			uint8_t service_data[] =
			  {
				26,                                                                      /*< Length. */
				AD_TYPE_MANUFACTURER_SPECIFIC_DATA,                                      /*< Manufacturer Specific Data data type value. */
				0x4C, 0x00, 0x02, 0x15,                                                  /*< 32-bit Manufacturer Data. */
				0, 1, 2, 3, 4, 5, 6, 7, //Location UUID
				8, 9, 10, 11, 12, 13, 14,15,
				major[0], major[1], // Major number
				minor[0], minor[1], // Minor number
				tx_power[indexPower] //2's complement of the Tx power (-56dB)};                                      /*< Ranging data. */
			  };

			aci_hal_set_tx_power_level(1, Power[indexPower]);
			aci_gap_update_adv_data(sizeof(service_data), service_data);
			memset(attribute_modified->Attr_Data,0,sizeof(attribute_modified->Attr_Data));

            /* USER CODE END CUSTOM_STM_Service_1_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomValidateHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
          break;

        case ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE :
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_END */
          break;

        case ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
          break;
        /* USER CODE BEGIN BLECORE_EVT */

        /* USER CODE END BLECORE_EVT */
        default:
          /* USER CODE BEGIN EVT_DEFAULT */

          /* USER CODE END EVT_DEFAULT */
          break;
      }
      /* USER CODE BEGIN EVT_VENDOR*/

      /* USER CODE END EVT_VENDOR*/
      break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

      /* USER CODE BEGIN EVENT_PCKT_CASES*/

      /* USER CODE END EVENT_PCKT_CASES*/

    default:
      /* USER CODE BEGIN EVENT_PCKT*/

      /* USER CODE END EVENT_PCKT*/
      break;
  }

  /* USER CODE BEGIN Custom_STM_Event_Handler_2 */

  /* USER CODE END Custom_STM_Event_Handler_2 */

  return(return_value);
}/* end Custom_STM_Event_Handler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void SVCCTL_InitCustomSvc(void)
{

  Char_UUID_t  uuid;
  /* USER CODE BEGIN SVCCTL_InitCustomSvc_1 */

  /* USER CODE END SVCCTL_InitCustomSvc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(Custom_STM_Event_Handler);

  /*
   *          MyService
   *
   * Max_Attribute_Records = 1 + 2*4 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for MyService +
   *                                2 for Power +
   *                                2 for Major +
   *                                2 for Minor +
   *                                2 for Validate +
   *                              = 9
   */

  COPY_MYSERVICE_UUID(uuid.Char_UUID_128);
  aci_gatt_add_service(UUID_TYPE_128,
                       (Service_UUID_t *) &uuid,
                       PRIMARY_SERVICE,
                       9,
                       &(CustomContext.CustomMyserviceHdle));

  /**
   *  Power
   */
  COPY_POWER_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMyserviceHdle,
                    UUID_TYPE_128, &uuid,
                    SizePower,
                    CHAR_PROP_WRITE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    0x10,
                    CHAR_VALUE_LEN_CONSTANT,
                    &(CustomContext.CustomPowerHdle));
  /**
   *  Major
   */
  COPY_MAJOR_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMyserviceHdle,
                    UUID_TYPE_128, &uuid,
                    SizeMajor,
                    CHAR_PROP_WRITE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomMajorHdle));
  /**
   *  Minor
   */
  COPY_MINOR_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMyserviceHdle,
                    UUID_TYPE_128, &uuid,
                    SizeMinor,
                    CHAR_PROP_WRITE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomMinorHdle));
  /**
   *  Validate
   */
  COPY_VALIDATE_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMyserviceHdle,
                    UUID_TYPE_128, &uuid,
                    SizeValidate,
                    CHAR_PROP_WRITE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    0x10,
                    CHAR_VALUE_LEN_CONSTANT,
                    &(CustomContext.CustomValidateHdle));

  /* USER CODE BEGIN SVCCTL_InitCustomSvc_2 */

  /* USER CODE END SVCCTL_InitCustomSvc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  Service_Instance: Instance of the service to which the characteristic belongs
 *
 */
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload)
{
  tBleStatus result = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_1 */

  /* USER CODE END Custom_STM_App_Update_Char_1 */

  switch(CharOpcode)
  {

    case CUSTOM_STM_POWER:
      result = aci_gatt_update_char_value(CustomContext.CustomMyserviceHdle,
                                          CustomContext.CustomPowerHdle,
                                          0, /* charValOffset */
                                          SizePower, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1*/

      /* USER CODE END CUSTOM_STM_Service_1_Char_1*/
      break;

    case CUSTOM_STM_MAJOR:
      result = aci_gatt_update_char_value(CustomContext.CustomMyserviceHdle,
                                          CustomContext.CustomMajorHdle,
                                          0, /* charValOffset */
                                          SizeMajor, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2*/

      /* USER CODE END CUSTOM_STM_Service_1_Char_2*/
      break;

    case CUSTOM_STM_MINOR:
      result = aci_gatt_update_char_value(CustomContext.CustomMyserviceHdle,
                                          CustomContext.CustomMinorHdle,
                                          0, /* charValOffset */
                                          SizeMinor, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3*/

      /* USER CODE END CUSTOM_STM_Service_1_Char_3*/
      break;

    case CUSTOM_STM_VALIDATE:
      result = aci_gatt_update_char_value(CustomContext.CustomMyserviceHdle,
                                          CustomContext.CustomValidateHdle,
                                          0, /* charValOffset */
                                          SizeValidate, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_4*/

      /* USER CODE END CUSTOM_STM_Service_1_Char_4*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_2 */

  /* USER CODE END Custom_STM_App_Update_Char_2 */

  return result;
}
