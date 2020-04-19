/******************************************************
******************************************************/
#include <REG51.H>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
//延时子程序模块
//**********************************************
void mdelay(uint delay)
{
    uint i;
    for(; delay>0; delay--)
    {
        for(i=0; i<80; i++) //1ms延时.
        {
            ;
        }
    }
}

//************************************************

void show();   //液晶显示程序
//****************************************
//12864液晶显示部分子程序模块
//****************************************
sbit K8		= P0^4;
sbit K7  	= P0^3;
sbit K6		= P0^2;

sbit K5  	= P0^1;
sbit K4		= P0^0;

sbit K1  	= P1^0;

sbit K2		= P1^1;
sbit K3 	= P1^2;


sbit K11  	= P3^2;
sbit K12  	= P3^3;
sbit K13  	= P3^4;
sbit K14  	= P3^5;
sbit K15  	= P3^6;



sbit DJ=P1^4;

sbit rs		= P0^5;
sbit rw		= P0^6;
sbit e  	= P0^7;
sbit beep = P1^5;
#define lcddata P2

unsigned char count=0,m=30,n,nn,money=0,du;			//定义计数变量

uchar t1=0,t2=5,t3=5,t4=5,t5=0;

uchar Time[6];

uchar info[] = "hello world";

sbit busy=P0^7;   //lcd busy bit
void wr_d_lcd(uchar content);
void wr_i_lcd(uchar content);
void clrram_lcd (void);
void init_lcd(void);
void busy_lcd(void);
void rev_row_lcd(uchar row);
void rev_co_lcd(uchar row,uchar col,uchar mode);
void clr_lcd(void);
void wr_co_lcd(uchar row,uchar col,uchar lcddata1,uchar lcddtta2);
void wr_row_lcd(uchar row,char *p);
//*******************************************************************                                                                */
//因为引脚的定义DB0..DB7是从P1.7...P1.0排列的                                                    */
//所以顺序需要调换一下
//*******************************************************************
uchar swapbit(uchar udata)
{
    uchar ii,tmp=0;
    for(ii=0; ii<8; ii++)
    {
        tmp<<=1;
        if(udata&0x01)
        {
            tmp|=0x01;
        }
        udata>>=1;
    }
    return tmp;
}
//**********************************
//液晶初始化
//**********************************
void init_lcd(void)
{
    wr_i_lcd(0x06);  /*光标的移动方向*/
    wr_i_lcd(0x0c);  /*开显示，关游标*/
}
//***********************************
//填充液晶DDRAM全为空格
//**********************************
void clrram_lcd (void)
{
    wr_i_lcd(0x30);
    wr_i_lcd(0x01);
}
//***********************************
//对液晶写数据
//content为要写入的数据
//***********************************
void wr_d_lcd(uchar content)
{
//	busy_lcd();
    rs=1;
    rw=0;
    lcddata=swapbit(content);
    e=1;
    ;
    e=0;
}
//********************************
//对液晶写指令
//content为要写入的指令代码
//*****************************
void wr_i_lcd(uchar content)
{
//	busy_lcd();
    rs=0;
    rw=0;
    lcddata=swapbit(content);
    e=1;
    ;
    e=0;
}
//********************************
//液晶检测忙状态
//在写入之前必须执行
//********************************
void busy_lcd(void)
{
    lcddata=0xff;
    rs=0;
    rw=1;
    e =1;
    while(busy==1);
    e =0;
}
//********************************
//指定要显示字符的坐标
//*******************************
void gotoxy(unsigned char y, unsigned char x)
{
    if(y==1)
        wr_i_lcd(0x80|x);
    if(y==2)
        wr_i_lcd(0x90|x);
    if(y==3)
        wr_i_lcd((0x80|x)+8);
    if(y==4)
        wr_i_lcd((0x90|x)+8);
}
//**********************************
//液晶显示字符串程序
//**********************************
void print(uchar *str)
{
    while(*str!='\0')
    {
        wr_d_lcd(*str);
        str++;
    }
}

//***************************************
//液晶显示主程序模块
//***************************************
void show()
{	  
    if(nn<10)
    {
        gotoxy(1,0);
        print("按键选择货物：   ");
        mdelay(10);
		



        gotoxy(2,0);
        print("①矿泉水(1元)  ");
        mdelay(10); 

		Time[0]=t1+'0';
        Time[1]='\0';
        gotoxy(2,7);
		print(Time);
		
               




        gotoxy(3,0);
        print("②红茶(3元)   ");
        mdelay(10); 	//扫描延时

		Time[0]=t2+'0';
      
        Time[1]='\0';
        gotoxy(3,7);
		print(Time);


        gotoxy(4,0);
        print("③绿茶(4元)  ");
        mdelay(10);                 //扫描延时

		Time[0]=t3+'0';
        Time[1]='\0';
        gotoxy(4,7);
		print(Time);



    }
    if(nn==10)
	{ clrram_lcd ();}
    if(nn>=11)
    {

        gotoxy(1,0);
        print("④啤酒(5元)  ");
        mdelay(10);

		Time[0]=t4+'0';
        Time[1]='\0';
        gotoxy(1,7);
		print(Time);

        gotoxy(2,0);
        print("⑤红牛(6元)  ");
        mdelay(10);                 //扫描延时

		Time[0]=t5+'0';
        Time[1]='\0';
        gotoxy(2,7);
		print(Time);

        gotoxy(3,0);
        print("选定后投入硬币");
        mdelay(10); 	//扫描延时
    }

}

//***************************************
//按键选择货物
//***************************************

void key()
{
    
          if(K11==0)
            {
                while(K11==0);
                mdelay(10);
                t1=t1+1;
            }
			else if(K12==0)
            {
                while(K12==0);
                mdelay(10);
                t2=t2+1;
            }
				else if(K13==0)
            {
                while(K13==0);
                mdelay(10);
                t3=t3+1;
            }
				else if(K14==0)
            {
                while(K14==0);
                mdelay(10);
                t4=t4+1;
            }
				else if(K15==0)
            {
                while(K15==0);
                mdelay(10);
                t5=t5+1;
            }
			
				
	
	
	if(K4==0)//按键1
    {	
	    if(t1>0)
		{  t1--;
		m=30;
        clrram_lcd ();
        while(1)
        {
            if(m==6)beep=0;
            if(m==5)beep=1;
            if(m==0)
            {
                if(0<money)
                {
                    clrram_lcd ();
                    gotoxy(1,0);
                    print("投币不足购买失败");
                    mdelay(10);
                    gotoxy(2,0);
                    print("退钱：    元");
                    mdelay(10);
                    Time[0]=money/10+'0';
                    Time[1]='.';
                    Time[2]=money%10+'0';
                    Time[3]='\0';
                    gotoxy(2,3);
                    print(Time);
                    mdelay(6000);
                    money=0;
                }

                clrram_lcd ();
                break;
            }

            gotoxy(1,0);
            print("已选矿泉水");
            mdelay(10);

            gotoxy(2,0);
            print("货物价格:1元");
            mdelay(10);

            gotoxy(3,0);
            print("投币金额:     元");
            mdelay(10);

            gotoxy(4,0);
            print("规定时间：");
            mdelay(10);


            if(n==0)
            {
                gotoxy(3,5);
                print(Time);
                mdelay(100);
            }

            if(n==1)
            {
                gotoxy(4,7);
                print(Time);
                mdelay(10);
            }

            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(money>=10)
            {
                clrram_lcd ();
                gotoxy(1,0);
                print("矿泉水购买成功");
                mdelay(10);
                gotoxy(2,0);
                print("找钱：    元");
                mdelay(10);

                du=money-10;
                Time[0]=du/10+'0';
                Time[1]='.';
                Time[2]=du%10+'0';
                Time[3]='\0';
                gotoxy(2,3);
                print(Time);
				DJ=0;
                mdelay(6000);
				DJ=1;
                money=0;
                clrram_lcd ();
                break;

            }
        }
		}
    }


    if(K5==0)//按键2
    {	if(t2>0)
		{  t2--;
	
		m=30;
        clrram_lcd ();
        while(1)
        {
            if(m==6)beep=0;
            if(m==5)beep=1;
            if(m==0)
            {
                if(0<money<30)
                {
                    clrram_lcd ();
                    gotoxy(1,0);
                    print("投币不足购买失败");
                    mdelay(10);
                    gotoxy(2,0);
                    print("退钱：    元");
                    mdelay(10);
                    Time[0]=money/10+'0';
                    Time[1]='.';
                    Time[2]=money%10+'0';
                    Time[3]='\0';
                    gotoxy(2,3);
                    print(Time);
                    mdelay(6000);
                    money=0;
                }

                clrram_lcd ();
                break;
            }

            gotoxy(1,0);
            print("已选红茶");
            mdelay(10);

            gotoxy(2,0);
            print("货物价格:3元");
            mdelay(10);

            gotoxy(3,0);
            print("投币金额:     元");
            mdelay(10);

            gotoxy(4,0);
            print("规定时间：");
            mdelay(10);


            if(n==0)
            {
                gotoxy(3,5);
                print(Time);
                mdelay(100);
            }

            if(n==1)
            {
                gotoxy(4,7);
                print(Time);
                mdelay(10);
            }

            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(money>=30)
            {
                clrram_lcd ();
                gotoxy(1,0);
                print("红茶购买成功");
                mdelay(10);
                gotoxy(2,0);
                print("找钱：    元");
                mdelay(10);

                du=money-30;
                Time[0]=du/10+'0';
                Time[1]='.';
                Time[2]=du%10+'0';
                Time[3]='\0';
                gotoxy(2,3);
                print(Time);
				DJ=0;
                mdelay(6000);
				DJ=1;
              
                money=0;
                clrram_lcd ();
                break;

            }
        }
		}

    }



    if(K6==0)//按键3
    {	if(t3>0)
		{  t3--;
        m=30;
        clrram_lcd ();
		while(1)
        {
			if(m==6)beep=0;
            if(m==5)beep=1;
            if(m==0)
            {
                if(0<money<40)
                {
                    clrram_lcd ();
                    gotoxy(1,0);
                    print("投币不足购买失败");
                    mdelay(10);
                    gotoxy(2,0);
                    print("退钱：    元");
                    mdelay(10);
                    Time[0]=money/10+'0';
                    Time[1]='.';
                    Time[2]=money%10+'0';
                    Time[3]='\0';
                    gotoxy(2,3);
                    print(Time);
                    mdelay(6000);
                    money=0;
                }

                clrram_lcd ();
                break;
            }

            gotoxy(1,0);
            print("已选绿茶");
            mdelay(10);

            gotoxy(2,0);
            print("货物价格:4元");
            mdelay(10);

            gotoxy(3,0);
            print("投币金额:     元");
            mdelay(10);

            gotoxy(4,0);
            print("规定时间：");
            mdelay(10);


            if(n==0)
            {
                gotoxy(3,5);
                print(Time);
                mdelay(100);
            }

            if(n==1)
            {
                gotoxy(4,7);
                print(Time);
                mdelay(10);
            }

            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(money>=40)
            {
                clrram_lcd ();
                gotoxy(1,0);
                print("绿茶购买成功");
                mdelay(10);
                gotoxy(2,0);
                print("找钱：    元");
                mdelay(10);

                du=money-40;
                Time[0]=du/10+'0';
                Time[1]='.';
                Time[2]=du%10+'0';
                Time[3]='\0';
                gotoxy(2,3);
                print(Time);
				 DJ=0;
                mdelay(6000);
				DJ=1;
               
                money=0;
                clrram_lcd ();
                break;

            }
        }
		}

    }



    if(K7==0)//按键4
    {	if(t4>0)
		{	t4--;
        m=30;
        clrram_lcd ();
        while(1)
        {	
        if(m==6)beep=0;
        if(m==5)beep=1;
            if(m==0)
            {
                if(0<money<50)
                {
                    clrram_lcd ();
                    gotoxy(1,0);
                    print("投币不足购买失败");
                    mdelay(10);
                    gotoxy(2,0);
                    print("退钱：    元");
                    mdelay(10);
                    Time[0]=money/10+'0';
                    Time[1]='.';
                    Time[2]=money%10+'0';
                    Time[3]='\0';
                    gotoxy(2,3);
                    print(Time);
                    mdelay(6000);
                    money=0;
                }

                clrram_lcd ();
                break;
            }

            gotoxy(1,0);
            print("已选啤酒");
            mdelay(10);

            gotoxy(2,0);
            print("货物价格:5元");
            mdelay(10);

            gotoxy(3,0);
            print("投币金额:     元");
            mdelay(10);

            gotoxy(4,0);
            print("规定时间：");
            mdelay(10);


            if(n==0)
            {
                gotoxy(3,5);
                print(Time);
                mdelay(100);
            }

            if(n==1)
            {
                gotoxy(4,7);
                print(Time);
                mdelay(10);
            }

            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(money>=50)
            {
                clrram_lcd ();
                gotoxy(1,0);
                print("啤酒买成功");
                mdelay(10);
                gotoxy(2,0);
                print("找钱：    元");
                mdelay(10);

                du=money-50;
                Time[0]=du/10+'0';
                Time[1]='.';
                Time[2]=du%10+'0';
                Time[3]='\0';
                gotoxy(2,3);
                print(Time);
				DJ=0;
                mdelay(6000);
				DJ=1;
                money=0;
                clrram_lcd ();
                break;

            }
        }
		}
    }

    if(K8==0)//按键5
    {  if(t5>0)
		{
   		   t5--;
        m=30;
        clrram_lcd ();
        while(1)
        {

		   if(m==6)beep=0;
           if(m==5)beep=1;
            if(m==0)
            {
                if(0<money<60)
                {
                    clrram_lcd ();
                    gotoxy(1,0);
                    print("投币不足购买失败");
                    mdelay(10);
                    gotoxy(2,0);
                    print("退钱：    元");
                    mdelay(10);
                    Time[0]=money/10+'0';
                    Time[1]='.';
                    Time[2]=money%10+'0';
                    Time[3]='\0';
                    gotoxy(2,3);
                    print(Time);
					 mdelay(6000);
                    money=0;
                }

                clrram_lcd ();
                break;
            }

            gotoxy(1,0);
            print("已选红牛");
            mdelay(10);

            gotoxy(2,0);
            print("货物价格:6元");
            mdelay(10);

            gotoxy(3,0);
            print("投币金额:     元");
            mdelay(10);

            gotoxy(4,0);
            print("规定时间：");
            mdelay(10);


            if(n==0)
            {
                gotoxy(3,5);
                print(Time);
                mdelay(100);
            }

            if(n==1)
            {
                gotoxy(4,7);
                print(Time);
                mdelay(10);
            }

            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(K1==0)
            {
                while(K1==0);
                mdelay(10);
                money=money+100;
            }

            if(K2==0)
            {
                while(K2==0);
                mdelay(10);
                money=money+50;
            }

            if(K3==0)
            {
                while(K3==0);
                mdelay(10);
                money=money+10;
            }
            if(money>=60)
            {
                clrram_lcd ();
                gotoxy(1,0);
                print("红牛买成功");
                mdelay(10);
                gotoxy(2,0);
                print("找钱：    元");
                mdelay(10);

                du=money-60;
                Time[0]=du/10+'0';
                Time[1]='.';
                Time[2]=du%10+'0';
                Time[3]='\0';
                gotoxy(2,3);
                print(Time);
				DJ=0;
                mdelay(6000);
				DJ=1;
                money=0;
                clrram_lcd ();
                break;

            }
        }
		}
    }
}

void InitUART(void)
{
    
	TMOD = 0x21;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
}

void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

void sendData(char *str)
{
	int i =0;
	while(str[i] != '\0')
		SendOneByte(str[i++]);
}


void UARTInterrupt(void) interrupt 4
{
    if(RI)
    {
        RI = 0;
        //add your code here!
    }
}



//************************************
//主程序
//*************************************
main()
{
    TMOD=0x01;					//T0 工作在方式1 16位计数器
    TH0=(65536-50000)/256; 	//预先 设定定时器 初值,50毫秒
    TL0=(65536-50000)%256;
    EA=1;						//开启 总中断
    ET0=1;						//开启定时器 0 中断
    TR0=1;						//定时器 0 启动计数

    init_lcd();
    clrram_lcd();
	InitUART();
	

    while(1)
    {
	  
       key();
	   sendData(info);
	   show(); 

    }
}


void time0(void)  interrupt 1
{
    TH0=(65536-50000)/256;		//重新设置定时器 初值,产生50MS定时中断
    TL0=(65536-50000)%256;
    count++;					//50ms太短，闪烁频率太快

    if(count==10)
    {
        if(n==0)
        {
            Time[0]=m/10+'0';

            Time[1]=m%10+'0';
            Time[2]='\0';
        }
        if(n==1)
        {
            Time[0]=money/10+'0';
            Time[1]='.';
            Time[2]=money%10+'0';

        }
		

        Time[3]='\0';
        Time[4]='\0';

        count=0;

        if(m==0)m=30;

        n++;
        if(n==2)
        {
            m--;
            n=0;
        }
		
	   count=0;
        nn++;
        if(nn==20)
        {
            nn=0;
        }
    }

}
