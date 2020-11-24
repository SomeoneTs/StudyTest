
#include "diskio.h"			/* FatFs lower layer API */
#include "malloc.h"	 
#include "nand.h"	 
#include "ftl.h"	 


#define EX_NAND  	0			//�ⲿnand flash,���Ϊ0
	
  
 
//��ô���״̬
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{ 
	return RES_OK;
}  


//��ʼ������
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	u8 res=0;	    
	if(pdrv==EX_NAND)		//�ⲿNAND
		res=FTL_Init();	//NAND��ʼ��	 
	if(res)
		return  STA_NOINIT;
	else 
		return 0; //��ʼ���ɹ� 
} 
//������
//pdrv:���̱��0~9
//*buff:���ݽ��ջ����׵�ַ
//sector:������ַ
//count:��Ҫ��ȡ��������
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	u8 res=0; 
    if (!count)
		return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
	if(pdrv == EX_NAND)
	{
		res=FTL_ReadSectors(buff,sector,512,count);	//��ȡ����	
	}				 
    if(res==0x00)
		return RES_OK;	 
    else return 
		RES_ERROR;	   
}
//д����
//pdrv:���̱��0~9
//*buff:���������׵�ַ
//sector:������ַ
//count:��Ҫд��������� 
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	u8 res=0;  
    if (!count)
		return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
	if(pdrv == EX_NAND)
	{
		res=FTL_WriteSectors((u8*)buff,sector,512,count);//д������ 
	}
    if(res == 0x00)
		return RES_OK;	 
    else  
		return RES_ERROR;	
} 
//����������Ļ��
//pdrv:���̱��0~9
//ctrl:���ƴ���
//*buff:����/���ջ�����ָ�� 
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
DRESULT res;						  			     

	if(pdrv==EX_NAND)	//�ⲿNAND FLASH
	{
	    switch(cmd)
	    {
		    case CTRL_SYNC:
				res = RES_OK; 
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = 512;	//NAND FLASH����ǿ��Ϊ512�ֽڴ�С
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = nand_dev.page_mainsize/512;//block��С,�����һ��page�Ĵ�С
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = nand_dev.valid_blocknum*nand_dev.block_pagenum*nand_dev.page_mainsize/512;//NAND FLASH����������С
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }
	}else 
	res=RES_ERROR;//�����Ĳ�֧��
    return 
		res;
} 
//���ʱ��
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}			 
//��̬�����ڴ�
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}
//�ͷ��ڴ�
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}

