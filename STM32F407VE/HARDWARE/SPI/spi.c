#include "spi.h"

SPI_HandleTypeDef SPI1_Handler;
SPI_HandleTypeDef SPI2_Handler;
void SPI1_Init(void)
{
SPI1_Handler.Instance=SPI1; //SPI1
SPI1_Handler.Init.Mode=SPI_MODE_MASTER; //Set SPI working mode, set as master mode
SPI1_Handler.Init.Direction=SPI_DIRECTION_2LINES; //Set SPI one-way or two-way data mode: SPI is set to two-wire mode
SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT; //Set the data size of SPI: SPI send and receive 8-bit frame structure
SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH; //The idle state of the serial synchronous clock is high
SPI1_Handler.Init.CLKPhase=SPI_PHASE_2EDGE; //The second transition edge (rising or falling) of the serial synchronous clock data is sampled
SPI1_Handler.Init.NSS=SPI_NSS_SOFT; //NSS signal is managed by hardware (NSS pin) or software (using SSI bit): the internal NSS signal is controlled by SSI bit
SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//Define the value of the baud rate prescaler: the baud rate prescaler value is 256
SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB; //Specify whether the data transmission starts from the MSB bit or the LSB bit: Data transmission starts from the MSB bit
SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE; //Close TI mode
SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//Turn off the hardware CRC check
SPI1_Handler.Init.CRCPolynomial=7; //The polynomial for CRC value calculation
HAL_SPI_Init(&SPI1_Handler);//initialization

__HAL_SPI_ENABLE(&SPI1_Handler); //Enable SPI1

SPI1_ReadWriteByte(0Xff); //Start transmission
}
void SPI2_Init(void)
{
SPI2_Handler.Instance=SPI2; //SPI1
SPI2_Handler.Init.Mode=SPI_MODE_MASTER; //Set the SPI working mode, set it as the master mode
SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES; //Set SPI one-way or two-way data mode: SPI is set to two-wire mode
SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT; //Set the data size of SPI: SPI send and receive 8-bit frame structure
SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH; //The idle state of the serial synchronous clock is high
SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE; //The second transition edge (rising or falling) of the serial synchronous clock data is sampled
SPI2_Handler.Init.NSS=SPI_NSS_SOFT; //NSS signal is managed by hardware (NSS pin) or software (using SSI bit): the internal NSS signal is controlled by SSI bit
SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//Define the value of the baud rate prescaler: the baud rate prescaler value is 256
SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB; //Specify whether the data transmission starts from the MSB bit or the LSB bit: Data transmission starts from the MSB bit
SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE; //Close TI mode
SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//Turn off the hardware CRC check
SPI2_Handler.Init.CRCPolynomial=7; //The polynomial for CRC value calculation
HAL_SPI_Init(&SPI2_Handler);//initialization

__HAL_SPI_ENABLE(&SPI2_Handler); //Enable SPI1

SPI2_ReadWriteByte(0Xff); //Start transmission
}


/*void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE(); //Enable GPIOB clock
    __HAL_RCC_SPI1_CLK_ENABLE(); //Enable SPI1 clock
__HAL_RCC_SPI2_CLK_ENABLE(); //Enable SPI2 clock
    
   //PB3,4,5
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; //Multiplex push-pull output
    GPIO_Initure.Pull=GPIO_PULLUP; //Pull up
    GPIO_Initure.Speed=GPIO_SPEED_FAST; //Fast
    GPIO_Initure.Alternate=GPIO_AF5_SPI1; //Multiplexed as SPI1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; //Multiplex push-pull output
    GPIO_Initure.Pull=GPIO_PULLUP; //Pull up
    GPIO_Initure.Speed=GPIO_SPEED_FAST; //Fast
    GPIO_Initure.Alternate=GPIO_AF5_SPI2; //Multiplexed as SPI1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

}*/
//void HAL_SPI2_MspInit(SPI_HandleTypeDef *hspi)
//{
// GPIO_InitTypeDef GPIO_Initure;
//
// __HAL_RCC_GPIOB_CLK_ENABLE(); //Enable GPIOB clock
// __HAL_RCC_SPI2_CLK_ENABLE(); //Enable SPI2 clock
//
// //PB3,4,5
// GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
// GPIO_Initure.Mode=GPIO_MODE_AF_PP; //Multiplex push-pull output
// GPIO_Initure.Pull=GPIO_PULLUP; //Pull up
// GPIO_Initure.Speed=GPIO_SPEED_FAST; //Fast
// GPIO_Initure.Alternate=GPIO_AF5_SPI1; //Multiplexed as SPI1
// HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//}


void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//Judging validity
__HAL_SPI_DISABLE(&SPI1_Handler); //Close SPI
SPI1_Handler.Instance->CR1&=0XFFC7; //bits 3-5 are cleared, used to set the baud rate
SPI1_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//Set SPI speed
__HAL_SPI_ENABLE(&SPI1_Handler); //Enable SPI
    
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//Judging validity
    __HAL_SPI_DISABLE(&SPI2_Handler); //Close SPI
    SPI2_Handler.Instance->CR1&=0XFFC7; //bits 3-5 are cleared, used to set the baud rate
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//Set SPI speed
    __HAL_SPI_ENABLE(&SPI2_Handler); //Enable SPI
    
}

u8 SPI1_ReadWriteByte(u8 TxData)
{
     u8 Rxdata;
     HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 1000);
  return Rxdata; //Return the received data
}
u8 SPI2_ReadWriteByte(u8 TxData)
{
     u8 Rxdata;
     HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 1000);
  return Rxdata;
}
