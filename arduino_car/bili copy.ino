#define leftA_PIN 6
#define leftB_PIN 7
#define left_Pwm_PIN 9

#define rightA_PIN 8
#define rightB_PIN 12
#define right_Pwm_PIN 10

#define leftA_track_PIN 2
#define leftB_track_PIN 3
#define rightA_track_PIN 4
#define rightB_track_PIN 5

float Kp = 10, Ki = 0.5, Kd = 0;					 //pid弯道参数参数
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; //pid直道参数                                      //元素判断
float previous_error = 0, previous_I = 0;			 //误差值
int sensor[4] = {0, 0, 0, 0};						 //5个传感器数值的数组
static int initial_motor_speed = 80;				 //初始速度

void read_sensor_values(void); //读取初值
void calc_pid(void);		   //计算pid
void motor_control(void);	   //电机控制
void motor_pinint();		   //引脚初始化
void _stop();				   //停车

void setup()
{
	Serial.begin(9600); //串口波特率115200（PC端使用）
	track_pinint();		//循迹引脚初始化
	motor_pinint();		//电机引脚初始化
}
void loop()
{
	read_sensor_values(); //循迹小车
	calc_pid();
	motor_control();
}

/*循迹模块引脚初始化*/
void track_pinint()
{
	pinMode(leftA_track_PIN, INPUT);  //设置引脚为输入引脚
	pinMode(leftB_track_PIN, INPUT);  //设置引脚为输入引脚
	pinMode(rightA_track_PIN, INPUT); //设置引脚为输入引脚
	pinMode(rightB_track_PIN, INPUT); //设置引脚为输入引脚
}

/*电机引脚初始化*/
void motor_pinint()
{
	pinMode(leftA_PIN, OUTPUT);	   //设置引脚为输出引脚
	pinMode(leftB_PIN, OUTPUT);	   //设置引脚为输出引脚
	pinMode(left_Pwm_PIN, OUTPUT); //设置引脚为输出引脚

	pinMode(rightA_PIN, OUTPUT);	//设置引脚为输出引脚
	pinMode(rightB_PIN, OUTPUT);	//设置引脚为输出引脚
	pinMode(right_Pwm_PIN, OUTPUT); //设置引脚为输出引脚
}

//停车函数
void _stop()
{
	digitalWrite(leftA_PIN, LOW);
	digitalWrite(leftB_PIN, LOW);
	analogWrite(left_Pwm_PIN, 255); //左轮静止不动

	digitalWrite(rightA_PIN, LOW);
	digitalWrite(rightB_PIN, LOW);
	analogWrite(right_Pwm_PIN, 255); //右轮静止不动
}

//速度设定范围(-255,255)
void motorsWrite(int speedL, int speedR)
{

	if (speedR > 0)
	{
		digitalWrite(rightA_PIN, HIGH);
		digitalWrite(rightB_PIN, LOW);
		analogWrite(right_Pwm_PIN, speedR);
	}
	else
	{
		digitalWrite(rightA_PIN, LOW);
		digitalWrite(rightB_PIN, HIGH);
		analogWrite(right_Pwm_PIN, -speedR);
	}

	if (speedL > 0)
	{
		digitalWrite(leftA_PIN, HIGH);
		digitalWrite(leftB_PIN, LOW);
		analogWrite(left_Pwm_PIN, speedL);
	}
	else
	{
		digitalWrite(leftA_PIN, LOW);
		digitalWrite(leftB_PIN, HIGH);
		analogWrite(left_Pwm_PIN, -speedL);
	}
}

//速度设定范围(-100，100)
void motorsWritePct(int speedLpct, int speedRpct)
{
	motorsWrite(speedLpct * 2.55, speedRpct * 2.55);
}

void motorsStop()
{
	digitalWrite(leftA_PIN, LOW);
	digitalWrite(leftB_PIN, LOW);
	analogWrite(left_Pwm_PIN, 255); //左轮静止不动

	digitalWrite(rightA_PIN, LOW);
	digitalWrite(rightB_PIN, LOW);
	analogWrite(right_Pwm_PIN, 255); //右轮静止不动
}

void read_sensor_values()
{
	sensor[0] = digitalRead(leftA_track_PIN);
	sensor[1] = digitalRead(leftB_track_PIN);
	sensor[2] = digitalRead(rightA_track_PIN);
	sensor[3] = digitalRead(rightB_track_PIN);

	if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1))
	{
		error = -2; //          0 0 0 1
	}

	else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0))
	{
		error = -1; //          0 0 0 1
	}

	else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0))
	{
		error = 0; //          0 1 1 0
	}

	else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
	{
		error = 1; //         0 1 0 0
	}

	else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0))
	{
		error = 2; //         1 0 0 0
	}
}

void calc_pid()
{
	P = error;
	I = I + error;
	D = error - previous_error;

	PID_value = (Kp * P) + (Ki * I) + (Kd * D);

	previous_error = error;
}

void motor_control()
{
	int left_motor_speed = initial_motor_speed + PID_value;
	int right_motor_speed = initial_motor_speed + PID_value;

	if (left_motor_speed < -255)
	{
		left_motor_speed = -255;
	}

	if (left_motor_speed > 255)
	{
		left_motor_speed = 255;
	}

	motorsWrite(left_motor_speed, right_motor_speed);

	Serial.print("move_A: ");
	Serial.print(left_motor_speed, OCT);
	Serial.print(" move_B: ");
	Serial.print(right_motor_speed, OCT);
	Serial.print(" error: ");
	Serial.print(error, OCT);
	Serial.print(" P: ");
	Serial.print(Kp, OCT);
	Serial.print(" PID_value: ");
	Serial.print(PID_value, OCT);
	Serial.println();
}
