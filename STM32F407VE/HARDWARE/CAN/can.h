#ifndef __CAN_H
#define __CAN_H
#include "sys.h"

//CAN1 receive RX0 interrupt enable
#define CAN1_RX0_INT_ENABLE 0 //0, disable; 1, enable.
#define CAN2_RX0_INT_ENABLE 0 //0, disable; 1, enable.

u8 CAN1_Mode_Init(u32 tsjw,u32 tbs2,u32 tbs1,u16 brp,u32 mode);//CAN initialization
u8 CAN2_Mode_Init(u32 tsjw,u32 tbs2,u32 tbs1,u16 brp,u32 mode);//CAN initialization

void CAN_Config(void);
void CAN2_Config(void);
u8 CAN1_Send_Msg(u8* msg,u8 len); //Send data
u8 CAN1_Receive_Msg(u8 *buf); //Receive data

u8 CAN2_Send_Msg(u8* msg,u8 len); //Send data
u8 CAN2_Receive_Msg(u8 *buf); //Receive data
#endif
