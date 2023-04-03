#include<reg51.h>
#define uChar unsigned char
#define uInt unsigned int
uChar a[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
uChar b[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 
uChar second=50,minute=59,hour=16,year=22,month=12,day=25,count;
sbit Key1 = P3^0; 
sbit Key2 = P3^1; 
sbit Key3 = P3^2; 
sbit Key4 = P3^3;  
sbit Buzzer=P1^1;

void Delay(uInt t)
{
	while(t)
	{
		t--;
	}
}
 
void Dispaly1(uChar second,uChar minute,uChar hour)
{
	
	P2=b[0];
	P0=a[hour/10];
	Delay(10);
	
	P2=b[1];
	P0=a[hour%10];
	Delay(10);

	P2=b[2]; 
	P0=0x40; 
	Delay(10);

	P2=b[3]; 
	P0=a[minute/10]; 
	Delay(10);

	P2=b[4];
	P0=a[minute%10]; 
	Delay(10);

	P2=b[5]; 
	P0=0x40; 
	Delay(10);

	P2=b[6]; 
	P0=a[second/10]; 
	Delay(10);

	P2=b[7];; 
	P0=a[second%10]; 
	Delay(10);
}

void Dispaly2(uChar year,uChar month,uChar day)
{
 
		P2=b[0]; 
		P0=a[year/10]; 
		Delay(10);
 
		P2=b[1]; 
		P0=a[year%10]; 
		Delay(10);
 
		P2=b[2]; 
		P0=0x40; 
		Delay(10);
 
		P2=b[3]; 
		P0=a[month/10]; 
		Delay(10);
 
		P2=b[4]; 
		P0=a[month%10]; 
		Delay(10);
 
		P2=b[5]; 
		P0=0x40; 
		Delay(10);
			
		P2=b[6];
		P0=a[day/10];
		Delay(10);
 
		P2=b[7];
		P0=a[day%10];
		Delay(10);
}

void Keyscan1()
{
	static uChar i=0,j=0; 
	
	if(Key2==0) 
	{
		Delay(10); 
		if(Key2==0)
		while(!Key2);
		i++;
		j++; 
	}
	
	
	if(j%4==1)
	{
		if(Key3==0)
		{
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			second++;
			if(second==60)
			{
				second=00;
				minute++;
			}
		}
	}
	if(j%4==2)
	{	
		if(Key3==0)
		{
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			minute++;
			if(minute==60)
			{
				minute=00;
				hour++;
			} 
		}
	}
	if(j%4==3)
	{
		if(Key3==0)
		{ 
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			hour++;
			if(hour==24)
			{
				hour=00; 
				day++;
			}
		}
	}
	
	if(i%4==1)
	{
		if(Key1==0)
		{
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			second--;
			if(second==0)
			{
				second=60;
				minute--;
			}
		}
	}
	if(i%4==2)
	{	
		if(Key1==0)
		{
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			minute--;
			if(minute==0)
			{
				minute=0;
				hour--;
			}
		}
	}
	if(i%4==3)
	{
		if(Key1==0)
		{ 
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			hour--;
			if(hour==0)
			{
				hour=0;
				day--;
			}
		}
	}	
}

void Keyscan2()
{
	static uChar n=0,m=0; 
	/*????????*/
	
	if(Key2==0) 
	{
		Delay(10); 
		if(Key2==0)
		while(!Key2);
		n++;
		m++; 
	}

	if(n%4==1)
	{
		if(Key3==0)
		{
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			day++;
			if(day==30)
			{
				day=0;
				month++;
			}
		}
	}
	if(n%4==2)
	{
		if(Key3==0)
		{ 
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			month++;
			if(month==12)
			{
				month=1;
				year++;
			}				
		}
	}
	if(n%4==3)
	{
		if(Key3==0)
		{ 
			Delay(10); 
			if(Key3==0)
			while(!Key3);
			year++;
			if(year==99)
			year=0; 
		}
	}
	
	if(m%4==1)
	{
		if(Key1==0)
		{
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			day--;
			if(day==0)
			{
				day=30;
				month--;
			}
		}
	}
	if(m%4==2)
	{
		if(Key1==0)
		{ 
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			month--;
			if(month==0)
			{
				month=12;
				year--;	
			}		
		}
	}
	if(m%4==3)
	{
		if(Key1==0)
		{ 
			Delay(10); 
			if(Key1==0)
			while(!Key1);
			year--;
			if(year==0)
			year=1; 
		}
	}
}

void main()
{						
		TMOD=0x01; 	 
		TH0=(65536-10000)/256;
		TL0=(65536-10000)%256;
		EA=1;
		ET0=1;
		TR0=1;
		while(1)
		{
			static uChar h=0;
			if(Key4==0) 
			{
				Delay(10); 
				if(Key4==0)
				while(!Key4);
				h++;
			}
			if(h%2==0)
			{
				Dispaly1(second,minute,hour);
				Keyscan1(); 
			}
 
			if(h%2==1)
			{
				Dispaly2(year,month,day);
				Keyscan2();
			}
		}
}


void time0_int(void) interrupt 1
{
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;
	count++;
	if(count==100)
	{
		count=0;
		second++;
		if(second==60)
		{
			second=0;
			minute++;
			if(minute==60)
			{
				minute=0;
				hour++;
				if(hour==24)
				{
					hour=0;
					day++;
					if(day==30)
					{
						day=0;
						month++;
						if(month==12)
						{
							month=0;
							year++;
							if(year==99)
							{
							year=0;
							}
						}
					}
				}
			}
		}
	}
	
	if(second==00&&minute==00)								   
	Buzzer=1;
	else
	Buzzer=0;
}
