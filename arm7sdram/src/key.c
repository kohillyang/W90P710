//KPIÖÐ¶Ï·þÎñ×Ó³ÌÐò

//¾ØÕó¼üÅÌÉ¨ÃèC´úÂë
#define u32     unsigned int 
#define REG_GPIO_CFG2  	0xFFF83020
#define REG_AIC_SCR29  		0xFFF82074
#define REG_AIC_MECR   		0xFFF82120
#define REG_KPICONF    		0xFFF88000
#define REG_KPISTATUS 		 0xFFF8800C
#define EBILED_ADDRESS    	 0x78000000
#define REG_EXT0CON		 0xFFF01018
#define EBI_EXT0_VALUE		 0xF0078003

#define WriteReg(Address,Value)  *(unsigned int volatile *)(Address) = Value
#define ReadReg(Address)       	 *(unsigned int volatile *)(Address)

void KPIInit(void);
void KPIInit(void){
     WriteReg(REG_EXT0CON, EBI_EXT0_VALUE);
	 WriteReg(REG_GPIO_CFG2, 0x000aaaaa);	  //½«GPIOÉèÖÃÎªKPIÄ£Ê½£¬2X8 
	 WriteReg(REG_AIC_SCR29, 0x00000045);     //½«KPI ÖÐ¶ÏÉèÖÃÎª¸ßµçÆ½ÓÐÐ§£¬ÓÅÏÈ¼¶Îª5
	 WriteReg(REG_AIC_MECR,  0x20000000);
	 WriteReg(REG_KPICONF,   0x00142fff);
}
int key_flag;// = 0
unsigned int  key_exec(void){

	 u32 KeyValue, temp;
	 temp = ReadReg(REG_KPISTATUS);
	 temp &= 0x0000000f;
	 key_flag = (1<<5)|temp;;
	 return KeyValue;
}
