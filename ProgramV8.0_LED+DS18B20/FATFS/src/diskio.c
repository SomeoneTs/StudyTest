
#include "diskio.h"			/* FatFs lower layer API */
#include "malloc.h"	 
#include "nand.h"	 
#include "ftl.h"	 


#define EX_NAND  	0			//外部nand flash,卷标为0
	
  
 
//获得磁盘状态
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{ 
	return RES_OK;
}  


//初始化磁盘
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	u8 res=0;	    
	if(pdrv==EX_NAND)		//外部NAND
		res=FTL_Init();	//NAND初始化	 
	if(res)
		return  STA_NOINIT;
	else 
		return 0; //初始化成功 
} 
//读扇区
//pdrv:磁盘编号0~9
//*buff:数据接收缓冲首地址
//sector:扇区地址
//count:需要读取的扇区数
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	u8 res=0; 
    if (!count)
		return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
	if(pdrv == EX_NAND)
	{
		res=FTL_ReadSectors(buff,sector,512,count);	//读取数据	
	}				 
    if(res==0x00)
		return RES_OK;	 
    else return 
		RES_ERROR;	   
}
//写扇区
//pdrv:磁盘编号0~9
//*buff:发送数据首地址
//sector:扇区地址
//count:需要写入的扇区数 
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	u8 res=0;  
    if (!count)
		return RES_PARERR;//count不能等于0，否则返回参数错误		 	 
	if(pdrv == EX_NAND)
	{
		res=FTL_WriteSectors((u8*)buff,sector,512,count);//写入数据 
	}
    if(res == 0x00)
		return RES_OK;	 
    else  
		return RES_ERROR;	
} 
//其他表参数的获得
//pdrv:磁盘编号0~9
//ctrl:控制代码
//*buff:发送/接收缓冲区指针 
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
DRESULT res;						  			     

	if(pdrv==EX_NAND)	//外部NAND FLASH
	{
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = 512;	//NAND FLASH扇区强制为512字节大小
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = nand_dev.page_mainsize/512;//block大小,定义成一个page的大小
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = nand_dev.valid_blocknum*nand_dev.block_pagenum*nand_dev.page_mainsize/512;//NAND FLASH的总扇区大小
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
	}else 
	res=RES_ERROR;//其他的不支持
    return 
		res;
} 
//获得时间
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}			 
//动态分配内存
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//释放内存
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}

