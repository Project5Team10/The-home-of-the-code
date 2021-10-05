#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include "main.h"
extern SPI_HandleTypeDef SPI1_Handler;  
extern SPI_HandleTypeDef SPI2_Handler;  

void SPI1_Init(void);
void SPI2_Init(void);

void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);

u8 SPI1_ReadWriteByte(u8 TxData);
u8 SPI2_ReadWriteByte(u8 TxData);

#endif
