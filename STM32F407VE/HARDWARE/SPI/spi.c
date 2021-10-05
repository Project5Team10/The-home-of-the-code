#include "spi.h"

SPI_HandleTypeDef SPI1_Handler;  
SPI_HandleTypeDef SPI2_Handler;  
void SPI1_Init(void)
{
	    SPI1_Handler.Instance=SPI1;                         //SPI1
	    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;             //设置SPI工作模式，设置为主模式
	    SPI1_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //设置SPI单向或者双向的数据模式:SPI设置为双线模式
	    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //设置SPI的数据大小:SPI发送接收8位帧结构
	    SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //串行同步时钟的空闲状态为高电平
	    SPI1_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	    SPI1_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//定义波特率预分频的值:波特率预分频值为256
	    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //关闭TI模式
	    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//关闭硬件CRC校验
	    SPI1_Handler.Init.CRCPolynomial=7;                  //CRC值计算的多项式
	    HAL_SPI_Init(&SPI1_Handler);//初始化

	    __HAL_SPI_ENABLE(&SPI1_Handler);                    //使能SPI1

	    SPI1_ReadWriteByte(0Xff);                           //启动传输
}
void SPI2_Init(void)
{
	    SPI2_Handler.Instance=SPI2;                         //SPI1
	    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //设置SPI工作模式，设置为主模式
	    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //设置SPI单向或者双向的数据模式:SPI设置为双线模式
	    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //设置SPI的数据大小:SPI发送接收8位帧结构
	    SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //串行同步时钟的空闲状态为高电平
	    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	    SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//定义波特率预分频的值:波特率预分频值为256
	    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //关闭TI模式
	    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//关闭硬件CRC校验
	    SPI2_Handler.Init.CRCPolynomial=7;                  //CRC值计算的多项式
	    HAL_SPI_Init(&SPI2_Handler);//初始化

	    __HAL_SPI_ENABLE(&SPI2_Handler);                    //使能SPI1

	    SPI2_ReadWriteByte(0Xff);                           //启动传输
}


/*void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();       //使能GPIOB时钟
    __HAL_RCC_SPI1_CLK_ENABLE();        //使能SPI1时钟
	__HAL_RCC_SPI2_CLK_ENABLE();        //使能SPI2时钟
    
   //PB3,4,5
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //快速
    GPIO_Initure.Alternate=GPIO_AF5_SPI1;           //复用为SPI1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //快速
    GPIO_Initure.Alternate=GPIO_AF5_SPI2;           //复用为SPI1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);	
	
}*/
//void HAL_SPI2_MspInit(SPI_HandleTypeDef *hspi)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    
//    __HAL_RCC_GPIOB_CLK_ENABLE();       //使能GPIOB时钟
//    __HAL_RCC_SPI2_CLK_ENABLE();        //使能SPI2时钟
//    
//    //PB3,4,5
//    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //快速
//    GPIO_Initure.Alternate=GPIO_AF5_SPI1;           //复用为SPI1
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//}


void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	    __HAL_SPI_DISABLE(&SPI1_Handler);            //关闭SPI
	    SPI1_Handler.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
	    SPI1_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
	    __HAL_SPI_ENABLE(&SPI1_Handler);             //使能SPI
    
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&SPI2_Handler);            //关闭SPI
    SPI2_Handler.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
    __HAL_SPI_ENABLE(&SPI2_Handler);             //使能SPI
    
}

u8 SPI1_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 1000);       
 	return Rxdata;          		    //返回收到的数据
}
u8 SPI2_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 1000);       
 	return Rxdata;          		   		
}
