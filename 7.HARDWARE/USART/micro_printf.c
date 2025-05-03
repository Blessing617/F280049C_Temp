#include "micro_printf.h"

const char MY_digits[] = "0123456789ABCDEF";

u32 Float_to_u32(float data)
{
	float_to_u32 temp;
	temp._float_=data;
	return temp._u32_;
}

void float_to_char(float num,uint8_t* str)
{
    int     high;//float_整数部分
    float   low;//float_小数部分
    int n=0;
    char ch[50];
    int i;
    high=(int)num;
    low=num-high;
    if(high == 0)
    {
        ch[n++]='0';
    }
    while(high>0)
    {
        ch[n++]='0'+high%10;
        high=high/10;
    }
    for(i=n-1;i>=0;i--)
    {
        *str++=ch[i];
    }
    num -= (int)num;
    *str++='.';
    for(n=0;n<3;n++)
    {
        *str++='0'+(int)(low*10);
        low=low*10.0-(int)(low*10);
    }
    *str='\0';
}

static void _micro_PutChar(char c)
{
    SCI_writeCharBlockingFIFO(SCIB_BASE,c);
}

static void _micro_PutStr(const char *str)
{
    while ( *str != '\0' )
    	_micro_PutChar(*str++);
}

static void _micro_PrintNum(long num, char base)
{
	char numStr[PRINTF_MAX_NUM_LEN];            /*数值字符串缓冲区---*/
	char i = 0;                          		/*for numStr---------*/

    if (base < 2 || base > 16)
    	return;
    while (num)                                 /*将数值转换成字符串--*/
    {
        numStr[i++] = MY_digits[num % base];    /*得到的是颠倒的串--*/
        num /= base;                            /*去掉最低位---------*/
    }
    while (i--)                                 /*反向打印----------*/
    {
    	_micro_PutChar(numStr[i]);
    }
}

static void _micro_Printint(long num)
{
    long temp;
    if(num<0)
    {
        _micro_PutChar('-');
        temp=-num;
    }
    else
        temp=num;
    _micro_PrintNum(temp,10);

}

static void _micro_Printfloat(unsigned long num)
{
    u16 j;
    float_to_u32 temp;
    temp._u32_=num;

    u32 data_int;
    u32 data_dot;
    if(temp._float_ >= 0)
    {
        data_int=temp._float_;
        data_dot=(temp._float_-(float)data_int)*100000.f;
    }
    else
    {
        data_int=-temp._float_;
        data_dot=(-temp._float_-(float)data_int)*100000.f;
    }

    u16 output_char[16];
    output_char[0]=data_int/10000%10;
    output_char[1]=data_int/1000%10;
    output_char[2]=data_int/100%10;
    output_char[3]=data_int/10%10;
    output_char[4]=data_int%10;
    output_char[5]='.';
    output_char[6]=data_dot/10000%10;
    output_char[7]=data_dot/1000%10;
    output_char[8]=data_dot/100%10;
    output_char[9]=data_dot/10%10;
    output_char[10]=data_dot%10;

    if(temp._float_ <= 0)
        _micro_PutChar('-');
    u16 flag=0;
    for(j=0;j<5;j++)
    {
        if(flag==0 && output_char[j]!=0)
            flag=1;
        if(flag)
            _micro_PutChar(MY_digits[output_char[j]]);
    }
    if(flag==0 && output_char[4]==0)
        _micro_PutChar('0');
    _micro_PutChar(output_char[5]);
    for(j=6;j<11;j++)
        _micro_PutChar(MY_digits[output_char[j]]);
}

void micro_print(const char *fmt, ...)
{
	char c;
    va_list var_arg;

    /**
    **@准备访问可变参数
    */
    va_start( var_arg, fmt );
    while ( (c = *fmt++) != '\0' )
    {
        if (c != '%')
        {
        	_micro_PutChar(c);
            continue;
        }
        switch (*fmt++)
        {
            case 'C':
            case 'c':                           /*字符型-----------------*/
            {
            	_micro_PutChar( va_arg(var_arg, int) );
            }
            break;
            case 'D':
            case 'd':                           /*整型-------------------*/
            {
                _micro_Printint(va_arg(var_arg, int));
            }break;
            case 'S':
            case 's':                           /*字符串型----------------*/
            {
            	_micro_PutStr(va_arg(var_arg, char *));
            }break;
            case 'X':                           /*十六进制----------------*/
            case 'x':
            {
            	_micro_PrintNum(va_arg(var_arg, int), 16);
            }break;
            case 'O':                           /*八进制-----------------*/
            case 'o':
            {
            	_micro_PrintNum(va_arg(var_arg, int), 8);
            }break;
            case 'B':
            case 'b':                           /*二进制------------------*/
            {
            	_micro_PrintNum(va_arg(var_arg, int), 2);
            }break;

            case 'F':
            case 'f':                           /*float------------------*/
            {
                _micro_Printfloat(va_arg(var_arg, unsigned long));
            }break;

            default:
            {
            	_micro_PutChar(c);              /*未定义，直接打印----------*/
            }

        }
    }
    /**
    **@完成处理可变参数
    */
    va_end ( var_arg );
}

