#include "24l01.h"
#include "spi.h"


const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //sending addressַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //sending addressַ

// Modify SPI1 driver for NRF24L01
void NRF24L01_SPI_Init(void)
{
__HAL_SPI_DISABLE (& SPI1_Handler);// Close SPI1 first
SPI1_Handler. Init. CLKPolarity = SPI_POLARITY_LOW;// The idle state of the serial clock is low
SPI1_Handler. Init. CLKPhase = SPI_PHASE_1EDGE;// The first jump edge (up or down) of the serial synchronized clock is sampled
HAL_SPI_Init (& SPI1_Handler);
__HAL_SPI_ENABLE (& SPI1_Handler);// can make SPI1
}
void NRF24L01_2_SPI_Init(void)
{
__HAL_SPI_DISABLE (& SPI2_Handler);// Close SPI1 first
SPI2_Handler. Init. CLKPolarity = SPI_POLARITY_LOW;// The idle state of the serial clock is low
SPI2_Handler. Init. CLKPhase = SPI_PHASE_1EDGE;// The first jump edge (up or down) of the serial synchronized clock is sampled
HAL_SPI_Init (& SPI2_Handler);
__HAL_SPI_ENABLE (& SPI2_Handler);// can make SPI1
}
// Initialize the I/O port of 24L01
void NRF24L01_Init(void)
{
GPIO_InitTypeDef GPIO_Initure;
__HAL_RCC_GPIOB_CLK_ENABLE();
__HAL_RCC_GPIOG_CLK_ENABLE ();// Start the GPIOG clock
GPIO_Initure. Pin = GPIO_PIN_14;
GPIO_Initure. Mode = GPIO_MODE_OUTPUT_PP;// push pull output
GPIO_Initure. Pull = GPIO_PULLUP;//
GPIO_Initure. Speed = GPIO_SPEED_HIGH;// the
HAL_GPIO_Init (GPIOB, & GPIO_Initure);// initialization
GPIO_Initure. Mode = GPIO_MODE_OUTPUT_PP;// push pull output
GPIO_Initure. Pull = GPIO_PULLUP;//
GPIO_Initure. Speed = GPIO_SPEED_HIGH;// the
GPIO_Initure. Pin = GPIO_PIN_5 | GPIO_PIN_6;// PG6, 7
HAL_GPIO_Init (GPIOD, & GPIO_Initure);// initialization
// gpiog.8 pull up input
GPIO_Initure. Pin = GPIO_PIN_7;//PG8
GPIO_Initure. Mode = GPIO_MODE_INPUT;// input
HAL_GPIO_Init (GPIOD, & GPIO_Initure);// initialization
HAL_GPIO_WritePin (GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//PB14 outputs 1 to prevent SPI FLASH from interfering with NRF communication
SPI1_Init ();// Initialize SPI1
NRF24L01_SPI_Init ();// Modify SPI Settings for NRF characteristics
NRF24L01_CE = 0;// can make 24 l01
NRF24L01_CSN = 1;// The SPI chip selection is cancelled
}
void NRF24L01_2_Init(void)
{
GPIO_InitTypeDef GPIO_Initure;
__HAL_RCC_GPIOC_CLK_ENABLE ();// Start the GPIOG clock
__HAL_RCC_GPIOD_CLK_ENABLE();
GPIO_Initure. Mode = GPIO_MODE_OUTPUT_PP;// push pull output
GPIO_Initure. Pull = GPIO_PULLUP;//
GPIO_Initure. Speed = GPIO_SPEED_HIGH;// the
GPIO_Initure. Pin = GPIO_PIN_8 | GPIO_PIN_9;// PG6, 7
HAL_GPIO_Init (GPIOD, & GPIO_Initure);// initialization
// gpiog.8 pull up input
GPIO_Initure.Pin=GPIO_PIN_10;	 //PG8
GPIO_Initure. Mode = GPIO_MODE_INPUT;// input
HAL_GPIO_Init (GPIOD, & GPIO_Initure);// initialization
SPI2_Init ();// Initialize SPI1
NRF24L01_2_SPI_Init ();// Modify SPI Settings for NRF characteristics
NRF24L01_2_CE = 0;// can make 24 l01
NRF24L01_2_CSN = 1;// The SPI chip selection is cancelled
}
// Check whether 24L01 exists
// Return value :0, success;1, failure
u8 NRF24L01_Check(void)
{
	 u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); // The spi speed is 10.5mhz ((the maximum SPI clock of 24L01 is 10Mhz, it doesn't matter if it is bigger)
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);// Write a 5-byte address.
	NRF24L01_Read_Buf(TX_ADDR,buf,5); // Read the address to be written
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;
	if(i!=5)return 1;// Check the 24L01 error
	return 0;	 // 24L01 detected
	}
	u8 NRF24L01_2_Check(void)
	{
	   u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8); // The spi speed is 10.5mhz ((the maximum SPI clock of 24L01 is 10Mhz, it doesn't matter if it is bigger)
	NRF24L01_2_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);// Write a 5-byte address.
	NRF24L01_2_Read_Buf(TX_ADDR,buf,5); // Read the address to be written
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;
	if(i!=5)return 1;// Check the 24L01 error
	return 0;	 // 24L01 detected
	}
	//SPI writes registers
	//reg: specifies the register address
	//value: indicates the written value ֵ
	u8 NRF24L01_Write_Reg(u8 reg,u8 value)
	{
	U8 status;
	NRF24L01_CSN = 0;// Enable SPI transmission
	Status = SPI1_ReadWriteByte (reg);// Send the register number
	SPI1_ReadWriteByte (value);// Write the value to the register
	NRF24L01_CSN = 1;// Disable SPI transmission
	Return (status);// Return the status value ״ֵ̬
	}
	u8 NRF24L01_2_Write_Reg(u8 reg,u8 value)
	{
	U8 status;
	NRF24L01_2_CSN = 0;// Enable SPI transmission
	Status = SPI2_ReadWriteByte (reg);// Send the register number
	SPI2_ReadWriteByte (value);// Write the value to the register
	NRF24L01_2_CSN = 1;// Disable SPI transmission
	Return (status);// Return the status value ״ֵ̬
	}
	// Read the SPI register value
	//reg: the register to read
	u8 NRF24L01_Read_Reg(u8 reg)
	{
	U8 reg_val;
	NRF24L01_CSN = 0;// Enable SPI transmission
	SPI1_ReadWriteByte (reg);// Send the register number
	reg_val=SPI1_ReadWriteByte(0XFF);//Read register contents
	NRF24L01_CSN = 1;// Disable SPI transmission
	Return (reg_val);// Return the status value ״ֵ̬
	}
	u8 NRF24L01_2_Read_Reg(u8 reg)
	{
	U8 reg_val;
	NRF24L01_2_CSN = 0;// Enable SPI transmission
	SPI2_ReadWriteByte (reg);// Send the register number
	reg_val=SPI2_ReadWriteByte(0XFF);//Read register contents
	NRF24L01_2_CSN = 1;// Disable SPI transmission
	Return (reg_val);// Return the status value ״ֵ̬
	}
	// Read the specified length of data at the specified position
	//reg: register (position)
	//*pBuf: data pointer
	//len: data length
	// Return value, the status register value read this time
	u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
	{
	U8 status, u8_ctr;
	NRF24L01_CSN = 0;// Enable SPI transmission
	Status = SPI1_ReadWriteByte (reg);// Send the register value (position) and read the status value
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI1_ReadWriteByte(0XFF);//Read the data
	NRF24L01_CSN = 1;// Close SPI transmission
	Return status;// Return the read status value ֵ̬
	}
	u8 NRF24L01_2_Read_Buf(u8 reg,u8 *pBuf,u8 len)
	{
	U8 status, u8_ctr;
	NRF24L01_2_CSN = 0;// Enable SPI transmission
	Status = SPI2_ReadWriteByte (reg);// Send the register value (position) and read the status value
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI2_ReadWriteByte(0XFF);//Read the data
	NRF24L01_2_CSN = 1;// Close SPI transmission
	Return status;// Returns the read status value
	}
	// Write the specified length of data at the specified location
	//reg: register (position)
	//*pBuf: data pointer
	//len: data length
	// Return value, this time read the status register value ֵ
	u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
	{
	U8 status, u8_ctr;
	NRF24L01_CSN = 0;// Enable SPI transmission
	Status = SPI1_ReadWriteByte (reg);// Send the register value (position) and read the status value
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI1_ReadWriteByte(*pBuf++); //Write data
  	NRF24L01_CSN = 1;// Close SPI transmission
  	Return status;// Returns the read status value
}
	u8 NRF24L01_2_Write_Buf(u8 reg, u8 *pBuf, u8 len)
	{
	U8 status, u8_ctr;
	NRF24L01_2_CSN = 0;// Enable SPI transmission
	Status = SPI2_ReadWriteByte (reg);// Send the register value (position) and read the status value
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); // Write data
  	NRF24L01_2_CSN = 1;// Close SPI transmission
  	Return status;// Return the read status value ֵ̬
  	}
  	// start NRF24L01 to send data
  	//txbuf: first address of data to be sent
  	// Return value: send complete status
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //Spi speed is 6.75mhz (24L01 maximum SPI clock is 10Mhz)
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//Write data to TX BUF 32 bytes
 	NRF24L01_CE=1;                         //Start sending
	while(NRF24L01_IRQ!=0);                 //Wait for sending to complete
	sta=NRF24L01_Read_Reg(STATUS);          //Reads the value of the status register
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flags
	if(sta&MAX_TX)                          //The maximum number of retransmissions was reached
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);  //Clear the TX FIFO register
		return MAX_TX; 
	}
	if(sta&TX_OK)                           //Send complete
	{
		return TX_OK;
	}
	return 0xff;//Failed to send for other reasons
}
u8 NRF24L01_2_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8); //Spi speed is 6.75mhz (24L01 maximum SPI clock is 10Mhz)
	NRF24L01_2_CE=0;
  	NRF24L01_2_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//Write data to TX BUF 32 bytes
 	NRF24L01_2_CE=1;                         //Start sending
	while(NRF24L01_2_IRQ!=0);                 //Wait for sending to complete
	sta=NRF24L01_2_Read_Reg(STATUS);          //Reads the value of the status register
	NRF24L01_2_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flags
	if(sta&MAX_TX)                          //The maximum number of retransmissions was reached
	{
		NRF24L01_2_Write_Reg(FLUSH_TX,0xff);  //Clear the TX FIFO register
		return MAX_TX; 
	}
	if(sta&TX_OK)                           //Send complete
	{
		return TX_OK;
	}
	return 0xff;//Failed to send for other reasons
}
// start NRF24L01 to send data
//txbuf: first address of data to be sent
// Return value :0, receive complete;Other, error code
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_8); //Spi speed is 6.75mhz (24L01 maximum SPI clock is 10Mhz)
	sta=NRF24L01_Read_Reg(STATUS);          //Reads the value of the status register
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flags
	if(sta&RX_OK)//Received data
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//Read the data
		NRF24L01_Write_Reg(FLUSH_RX,0xff);  //Clear the TX FIFO register
		return 0; 
	}	   
	return 1;//No data was received
}
u8 NRF24L01_2_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8); //Spi speed is 6.75mhz (24L01 maximum SPI clock is 10Mhz)
	sta=NRF24L01_2_Read_Reg(STATUS);          //Reads the value of the status register
	NRF24L01_2_Write_Reg(NRF_WRITE_REG+STATUS,sta); //Clear TX_DS or MAX_RT interrupt flags
	if(sta&RX_OK)//Received data
	{
		NRF24L01_2_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//Read the data
		NRF24L01_2_Write_Reg(FLUSH_RX,0xff);  //Clear the TX FIFO register
		return 0; 
	}	   
	return 1;//No data was received
}
// This function initializes NRF24L01 to RX mode
// Set RX address, write RX data width, select RF channel, baud rate and LNA HCURR
// When the CE becomes high, RX mode is entered and data can be received
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//Write the RX node address
	  
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);       //Enable the automatic answer function for channel 0
  	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);   //The receiving address of channel 0 was enabled
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	        //Set the RF communication frequency
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//Select the effective data width for channel 0
  	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);    //Set TX transmission parameters, 0dB gain,2Mbps, low noise gain on
  	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);     //Configure basic working mode parameters;PWR_UP,EN_CRC,16BIT_CRC, receive mode
  	NRF24L01_CE=1; //If the CE value is high, the device enters the receiving mode
}
void NRF24L01_2_RX_Mode(void)
{
	NRF24L01_2_CE=0;	  
  	NRF24L01_2_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//Write the RX node address
	  
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);       //Enable the automatic answer function for channel 0
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);   //The receiving address of channel 0 was enabled
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+RF_CH,40);	        //Set the RF communication frequency
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//Select the effective data width for channel 0
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);    //Set TX transmission parameters, 0dB gain,2Mbps, low noise gain on
  	NRF24L01_2_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);     //Configure basic working mode parameters;PWR_UP,EN_CRC,16BIT_CRC, receive mode
  	NRF24L01_2_CE=1; //If the CE value is high, the device enters the receiving mode
}
// This function initializes NRF24L01 to TX mode
// Set TX address, write TX data width, set RX auto answer address, fill TX send data, select RF channel, baud rate and LNA HCURR
// PWR_UP, CRC can make
// When the CE becomes high, RX mode is entered and data can be received
// If the CE value is higher than 10us, start sending.
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//Write the ADDRESS of the TX node
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //The ADDRESS of the TX node is set to enable ACK

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //Enable the automatic answer function for channel 0
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //The receiving address of channel 0 was enabled
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//Set automatic retransmission interval :500us + 86us;Maximum number of automatic retransmissions :10
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //Set the RF channel to 40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //Set TX transmission parameters, 0dB gain,2Mbps, low noise gain on
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //Configure basic working mode parameters;PWR_UP,EN_CRC,16BIT_CRC, receive mode, enable all interrupts
	NRF24L01_CE=1;//CE is high, and start sending after 10us
}
void NRF24L01_2_TX_Mode(void)
{
NRF24L01_2_CE=0;
NRF24L01_2_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//write TX node address
NRF24L01_2_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //Set the TX node address, mainly to enable ACK

NRF24L01_2_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); //Enable automatic response of channel 0
NRF24L01_2_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //Enable the receiving address of channel 0
NRF24L01_2_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//Set the automatic retransmission interval time: 500us + 86us; the maximum number of automatic retransmissions: 10 times
NRF24L01_2_Write_Reg(NRF_WRITE_REG+RF_CH,40); //Set the RF channel to 40
NRF24L01_2_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); //Set TX transmission parameters, 0db gain, 2Mbps, low noise gain on
NRF24L01_2_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e); //Configure the parameters of the basic working mode; PWR_UP, EN_CRC, 16BIT_CRC, receive mode, open all interrupts
NRF24L01_2_CE=1;//CE is high, start sending after 10us
}
