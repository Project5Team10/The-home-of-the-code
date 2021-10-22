#include "can.h"
#include "main.h"
#include "stm32f4xx_hal_def.h"
CAN_HandleTypeDef CAN1_Handler; //CAN1 handle
CAN_TxHeaderTypeDef TxHeader; //send
CAN_RxHeaderTypeDef RxHeader; //Receive

CAN_HandleTypeDef CAN2_Handler; //CAN1 handle
CAN_TxHeaderTypeDef Tx2Header; //send
CAN_RxHeaderTypeDef Rx2Header; //Receive

////CAN initialization
//tsjw: Resynchronize the jump time unit. Range: CAN_SJW_1TQ~CAN_SJW_4TQ
//tbs2: Time unit of time period 2. Range: CAN_BS2_1TQ~CAN_BS2_8TQ;
//tbs1: Time unit of time period 1. Range: CAN_BS1_1TQ~CAN_BS1_16TQ
//brp: baud rate divider. Range: 1~1024; tq=(brp)*tpclk1
//Baud rate=Fpclk1/((tbs1+tbs2+1)*brp); Among them, tbs1 and tbs2 we only use the serial number marked on the identifier, such as CAN_BS2_1TQ, we think that tbs2=1 can be calculated.
//mode: CAN_MODE_NORMAL, normal mode; CAN_MODE_LOOPBACK, loopback mode;
//The clock of Fpclk1 is set to 42M during initialization, if CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_MODE_LOOPBACK) is set;
//The baud rate is: 42M/((6+7+1)*6)=500Kbps
//Return value: 0, initialization is OK;
// Other, initialization failed;

u8 CAN1_Mode_Init(u32 tsjw,u32 tbs2,u32 tbs1,u16 brp,u32 mode)
{
CAN_InitTypeDef CAN1_InitConf;
    
    CAN1_Handler.Instance=CAN1;

CAN1_Handler.Init = CAN1_InitConf;

CAN1_Handler.Init.Prescaler=brp; //The frequency division coefficient (Fdiv) is brp+1
CAN1_Handler.Init.Mode=mode; //Mode setting
CAN1_Handler.Init.SyncJumpWidth=tsjw; //The resynchronization jump width (Tsjw) is tsjw+1 time unit CAN_SJW_1TQ~CAN_SJW_4TQ
CAN1_Handler.Init.TimeSeg1=tbs1; //tbs1 range CAN_BS1_1TQ~CAN_BS1_16TQ
CAN1_Handler.Init.TimeSeg2=tbs2; //tbs2 range CAN_BS2_1TQ~CAN_BS2_8TQ
CAN1_Handler.Init.TimeTriggeredMode=DISABLE; //Non-time trigger communication mode
CAN1_Handler.Init.AutoBusOff=DISABLE; //Software automatic offline management
CAN1_Handler.Init.AutoWakeUp=DISABLE; //Sleep mode is awakened by software (clear the SLEEP bit of CAN->MCR)
CAN1_Handler.Init.AutoRetransmission=ENABLE; //Prohibit automatic message transmission
CAN1_Handler.Init.ReceiveFifoLocked=DISABLE; //The message is not locked, the new one overwrites the old one
CAN1_Handler.Init.TransmitFifoPriority=DISABLE; //Priority is determined by the message identifier

    if(HAL_CAN_Init(&CAN1_Handler)!=HAL_OK) //initialization
return 1;
    return 0;
}
u8 CAN2_Mode_Init(u32 tsjw,u32 tbs2,u32 tbs1,u16 brp,u32 mode)
{
CAN_InitTypeDef CAN2_InitConf;
    
    CAN2_Handler.Instance=CAN2;

CAN2_Handler.Init = CAN2_InitConf;

CAN2_Handler.Init.Prescaler=brp; //The frequency division coefficient (Fdiv) is brp+1
CAN2_Handler.Init.Mode=mode; //Mode setting
CAN2_Handler.Init.SyncJumpWidth=tsjw; //The resynchronization jump width (Tsjw) is tsjw+1 time unit CAN_SJW_1TQ~CAN_SJW_4TQ
CAN2_Handler.Init.TimeSeg1=tbs1; //tbs1 range CAN_BS1_1TQ~CAN_BS1_16TQ
CAN2_Handler.Init.TimeSeg2=tbs2; //tbs2 range CAN_BS2_1TQ~CAN_BS2_8TQ
CAN2_Handler.Init.TimeTriggeredMode=DISABLE; //Non-time trigger communication mode
CAN2_Handler.Init.AutoBusOff=DISABLE; //Software automatic offline management
CAN2_Handler.Init.AutoWakeUp=DISABLE; //Sleep mode is awakened by software (clear the SLEEP bit of CAN->MCR)
CAN2_Handler.Init.AutoRetransmission=ENABLE; //Prohibit automatic message transmission
CAN2_Handler.Init.ReceiveFifoLocked=DISABLE; //The message is not locked, the new one overwrites the old one
CAN2_Handler.Init.TransmitFifoPriority=DISABLE; //Priority is determined by the message identifier

    if(HAL_CAN_Init(&CAN2_Handler)!=HAL_OK) //initialization
return 1;
    return 0;
}
//CAN bottom layer driver, pin configuration, clock configuration, interrupt configuration
//This function will be called by HAL_CAN_Init()
//hcan: CAN handle
/*void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_CAN1_CLK_ENABLE(); //Enable CAN1 clock
__HAL_RCC_CAN2_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE(); //Enable GPIOA clock
__HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //PA11,12
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; //Push-pull multiplexing
    GPIO_Initure.Pull=GPIO_PULLUP; //Pull up
    GPIO_Initure.Speed=GPIO_SPEED_FAST; //Fast
    GPIO_Initure.Alternate=GPIO_AF9_CAN1; //Multiplexed as CAN1
    HAL_GPIO_Init(GPIOD,&GPIO_Initure); //initialization
    GPIO_Initure.Pin=GPIO_PIN_12|GPIO_PIN_6; //PA11,12
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; //Push-pull multiplexing
    GPIO_Initure.Pull=GPIO_PULLUP; //Pull up
    GPIO_Initure.Speed=GPIO_SPEED_FAST; //Fast
    GPIO_Initure.Alternate=GPIO_AF9_CAN2; //Multiplexed as CAN1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure); //initialization

}*/

void CAN_Config(void)
{
  CAN_FilterTypeDef sFilterConfig;

  /*##-2- Configure the CAN Filter ##################################### ####*/
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&CAN1_Handler, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    while(1)
{
}
  }
  /*##-3- Start the CAN peripheral #################################### ####*/
  if (HAL_CAN_Start(&CAN1_Handler) != HAL_OK)
  {
    /* Start Error */
    while(1)
{
}
  }
  /*##-4- Activate CAN RX notification ##################################### */
  if (HAL_CAN_ActivateNotification(&CAN1_Handler, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    while(1)
{
}
  }
  /*##-5- Configure Transmission process ###################################*/
  TxHeader.StdId = 0x321;
  TxHeader.ExtId = 0x01;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 2;
  TxHeader.TransmitGlobalTime = DISABLE;
}
void CAN2_Config(void)
{
  CAN_FilterTypeDef sFilterConfig;

  /*##-2- Configure the CAN Filter ##################################### ####*/
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 28;

  if (HAL_CAN_ConfigFilter(&CAN2_Handler, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    while(1)
{
}
  }
  /*##-3- Start the CAN peripheral #################################### ####*/
  if (HAL_CAN_Start(&CAN2_Handler) != HAL_OK)
  {
    /* Start Error */
    while(1)
{
}
  }
  /*##-4- Activate CAN RX notification ##################################### */
  if (HAL_CAN_ActivateNotification(&CAN2_Handler, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    while(1)
{
}
  }
  /*##-5- Configure Transmission process ###################################*/
  Tx2Header.StdId = 0x321;
  Tx2Header.ExtId = 0x01;
  Tx2Header.RTR = CAN_RTR_DATA;
  Tx2Header.IDE = CAN_ID_STD;
  Tx2Header.DLC = 2;
  Tx2Header.TransmitGlobalTime = DISABLE;
}
//can send a set of data (fixed format: ID is 0X12, standard frame, data frame)
//len: data length (maximum 8)
//msg: data pointer, the maximum is 8 bytes.
//Return value: 0, success;
// Other, failure;
u8 CAN1_Send_Msg(u8* msg,u8 len)
{
    u8 i=0;
u32 TxMailbox;
u8 message[8];
TxHeader.StdId=0X12; //Standard identifier
TxHeader.ExtId=0x12; //Extended identifier (29 bits)
TxHeader.IDE=CAN_ID_STD; //Use standard frame
TxHeader.RTR=CAN_RTR_DATA; //Data frame ֡
    TxHeader.DLC=len;
    for(i=0;i<len;i++)
    {
message[i]=msg[i];
}
    if(HAL_CAN_AddTxMessage(&CAN1_Handler, &TxHeader, message, &TxMailbox) != HAL_OK)//Send
{
return 1;
}
while(HAL_CAN_GetTxMailboxesFreeLevel(&CAN1_Handler) != 3) {}
    return 0;
}
u8 CAN2_Send_Msg(u8* msg,u8 len)
{
    u8 i=0;
u32 TxMailbox;
u8 message[8];
Tx2Header.StdId=0X12; //Standard identifier
Tx2Header.ExtId=0x12; //Extended identifier (29 bits)
Tx2Header.IDE=CAN_ID_STD; //Use standard frame
Tx2Header.RTR=CAN_RTR_DATA; //Data frame ֡
    Tx2Header.DLC=len;
    for(i=0;i<len;i++)
    {
message[i]=msg[i];
}
    if(HAL_CAN_AddTxMessage(&CAN2_Handler, &Tx2Header, message, &TxMailbox) != HAL_OK)//Send
{
return 1;
}
while(HAL_CAN_GetTxMailboxesFreeLevel(&CAN2_Handler) != 3) {}
    return 0;
}
//can port receive data query
//buf: data buffer area;
//Return value: 0, no data was received;
// Other, received data length;
u8 CAN1_Receive_Msg(u8 *buf)
{
 u32 i;
u8 RxData[8];

if(HAL_CAN_GetRxFifoFillLevel(&CAN1_Handler, CAN_RX_FIFO0) != 1)
{
return 0xF1;
}

if(HAL_CAN_GetRxMessage(&CAN1_Handler, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
{
return 0xF2;
}
    for(i=0;i<RxHeader.DLC;i++)
    buf[i]=RxData[i];
return RxHeader.DLC;
}
u8 CAN2_Receive_Msg(u8 *buf)
{
 u32 i;
u8 RxData[8];

if(HAL_CAN_GetRxFifoFillLevel(&CAN2_Handler, CAN_RX_FIFO0) != 1)
{
return 0xF1;
}

if(HAL_CAN_GetRxMessage(&CAN2_Handler, CAN_RX_FIFO0, &Rx2Header, RxData) != HAL_OK)
{
return 0xF2;
}
    for(i=0;i<Rx2Header.DLC;i++)
    buf[i]=RxData[i];
return Rx2Header.DLC;
}
