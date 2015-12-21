#include <Servo.h>   //调用舵机的函数库
#define LED 7   // light
#define KEY 12  // key press

int KEY_NUM = 0;      //按键键值存放变量，不等于1说明有按键按下

#define p1 2    //红外传感器的引脚2,3,4,5脚
#define p2 3
#define p3 4
#define p4 5

#define PWM_pin 6    //舵机的信号引脚
int pulsewidth = 0;      //定义变量，舵机的脉冲宽度的
Servo myservo;          //定义一个舵机伺服电机对象

#define  Pin0 8     //定义四个步进电机的相位引脚，8,9,10,11
#define  Pin1 9
#define  Pin2 10
#define  Pin3 11
int _step = 0;      //步数
boolean dir;         //布尔变量，确定步进电机是正转还是反转
int stepperSpeed = 5;     //电机转速,5ms一步
int iCurrentAngle = 45; 
int iDebugAngle = 45;
int iDeltaSpeed = 1; // speed per 1 frequence
int s1=0,s2=0,s3=0,s4=0;    //定义4个存储红外传感器数值的量
void setup()
{
pinMode(p1,INPUT);      //初始化红外传感器的端口
pinMode(p2,INPUT);
pinMode(p3,INPUT);
pinMode(p4,INPUT); 
myservo.attach(6);     //6号引脚输出舵机电机控制信号
Serial.begin(9600);    

pinMode(Pin0, OUTPUT);   //初始化步进电机的端口
pinMode(Pin1, OUTPUT);
pinMode(Pin2, OUTPUT);
pinMode(Pin3, OUTPUT);

myservo.write(iCurrentAngle);

  pinMode(LED,OUTPUT);          //定义LED为输出引脚
  pinMode(KEY,INPUT_PULLUP);    //定义KEY为带上拉输入引脚
  digitalWrite(LED,HIGH);
}

void judgeDir()
{
int i=0;          
s1=digitalRead(p1);   // up数字读红外传感器的数值
s2=digitalRead(p2);  //   down
s3=digitalRead(p3);  // left
s4=digitalRead(p4);  // down

//pulse(90);  //初始化舵机的角度90°

if(s1 == HIGH && s2 == LOW)
{
   // turn down
   if(iCurrentAngle <70)
   {
        iDebugAngle = iCurrentAngle;
    iCurrentAngle += iDeltaSpeed;
    myservo.write(iCurrentAngle);
    delay(15);
  }   
}
else if(s1 == LOW && s2 == HIGH)
{
  // turn up
  if(iCurrentAngle > 25)
  {
        iDebugAngle = iCurrentAngle;
    iCurrentAngle -= iDeltaSpeed;
    myservo.write(iCurrentAngle);
    delay(15);
  }   
}
else 
{
    // do nothing
}

if(s3 == HIGH && s4 == LOW)
{
   // turn right
       for(int i = 0; i<20; ++i)
    {
        stepper( false);  
    }
}
else  if(s3 == LOW && s4 == HIGH)
{
  // turn left
   for(int i = 0; i<20; ++i)
    {
        stepper( true);
    }
}
else 
{
    // do nothing
}
Serial.print(iDebugAngle);
Serial.print("  ; ");
Serial.print(s1);
Serial.print("  ; ");
Serial.print(s2);
Serial.print("  ; ");
Serial.print(s3);
Serial.print("  ; ");
Serial.print(s4);
Serial.println(" ----------------------------");

//////////////////////////////////////////
 
//delay(150);
}
void loop()
{
  //stepper( true);
  judgeDir();
 ScanKey();
  /*
int i=0;          
s1=digitalRead(p1);   // up数字读红外传感器的数值
s2=digitalRead(p2);   // down
s3=digitalRead(p3);   // left
s4=digitalRead(p4);   // r ightmmmmmmmmmmmmmmm,,,

//pulse(90);  //初始化舵机的角度90°


if(HIGH==s1)           //判断第一个红外传感器是否是1，
{
  for(i=90;i>0;i--)     //i从90变到0
  {
    myservo.write(i);       //舵机转到i角度
    delay(15); 
    if(LOW==s1)
{
break;
}    //如果s1是低电平，就跳出循环
  }
}

if(HIGH==s2)
{
  for(i=90;i<180;i++)
  {
    myservo.write(i);
    delay(15); 
    if(LOW==s2)
{
break;
}
  }
}
 

if(HIGH==s3)      //判断第三红外传感器是否高电平
{
  dir=true;       //是的话就赋dir为真，即步进电机反转
stepper(dir);  //将dir传递到stepper函数，stepper为让步进电机转动函数
}
if(HIGH==s4)
{
  dir=false;
stepper( dir);
}
*/
}
//*******************************舵机的初始化函数
void pulse(int angle)     //设置舵机角度为angle
{
  pulsewidth=int ((angle*11)+500);  //计算高电平时间
  digitalWrite(PWM_pin,HIGH);       //设置高电平
  delayMicroseconds(pulsewidth);    //延时pulsewidth （us）
  digitalWrite(PWM_pin,LOW);        //设置低电平
  delay(20-pulsewidth/1000);        //延时20-pulsewidth/1000 （ms）
}
//************************************步进电机转动函数
void stepper(boolean dir)
{
 switch(_step){
    case 0:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    case 1:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
    break;
    case 2:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 3:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
    break;
    case 4:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
    case 5:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
      case 6:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
    case 7:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
    break;
    default:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
    break;
  }
  if(dir){
    _step++;
  }else{
    _step--;
  }
  if(_step>7){
    _step=0;
  }
  if(_step<0){
    _step=7;
  }
  delay(stepperSpeed);

}
//*******************************************************************///
int iKeyState = 0;
void ScanKey()            //按键扫描程序
{ 
  int curState = digitalRead(KEY);
  Serial.println(curState); 
   if( curState == LOW)
    {
      
       if(iKeyState == 1)
       {
         //delay(20); 
         digitalWrite(LED,HIGH);    //LED的状态翻转
         iKeyState =  0;
       }
       else
       {
         //delay(20); 
         digitalWrite(LED,LOW);   //LED的状态翻转
         iKeyState =  1;
       } 
       delay(300);
    } 
}  
