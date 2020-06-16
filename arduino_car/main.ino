const int LeftAin1 = 1;
const int LeftAin2 = 7;
const int LeftPWM = 9;
const int RightAin1 = 8;
const int RightAin2 = 12;
const int RightPWM = 10;

const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;

void setup()
{
    pinMode(LeftAin1, OUTPUT);
    pinMode(LeftAin2, OUTPUT);
    pinMode(RightAin1, OUTPUT);
    pinMode(RightAin2, OUTPUT);
    Serial.begin(9600);
}

int readSensor(void)
{
    int sensor, error;
    sensor = digitalRead(S0);
    sensor <<= 1;
    sensor |= digitalRead(S1);
    sensor <<= 1;
    sensor |= digitalRead(S2);
    sensor <<= 1;
    sensor |= digitalRead(S3);
    switch (sensor)
    {
    case 0x06: //S0S1S2S3=0110 线上
        error = 0;
        break;
    case 0x04: //S0S1S2S3=0100 小偏左
        error = 5;
        break;
    case 0x0c: //S0S1S2S3=1100 中偏左
        error = 10;
        break;
    case 0x08: //S0S1S2S3=1000 大偏左
        error = 20;
        break;
    case 0x02: //S0S1S2S3=0010 小偏右
        error = -5;
        break;
    case 0x03: //S0S1S2S3=0011 中偏右
        error = -10;
        break;
    case 0x01: //S0S1S2S3=0001 大偏右
        error = -20;
        break;
    default: //其他，不在线上
        error = 0x200;
        break;
    }
    return error;
}

void followLine(int speed)
{
    int err, left, right, out;
    int Kp = 5;
    err = readSensor();

    if (err < 100) //判断的是传感器的误差值是不是在争取的范围内
    {
        out = Kp * err; //计算当前比例控制量
        left = speed + out;
        right = speed - out;                //处理，根据控制量计算左右电机的输出
        left = constrain(left, -100, +100); //对计算结果进行限幅处理
        right = constrain(right, -100, +100);
        Serial.print("left=");
        Serial.println(left);
        Serial.print("right=");
        Serial.println(right);

        if (left >= 0) //判断控制量的正负号，控制左电机的转向
        {
            digitalWrite(LeftAin1, HIGH); //正向
            digitalWrite(LeftAin2, LOW);
        }

        else
        {
            digitalWrite(LeftAin1, LOW); //反向
            digitalWrite(LeftAin2, HIGH);
            left = -left; //取绝对值
        }

        if (right >= 0) //正向驱动
        {
            digitalWrite(RightAin1, HIGH);
            digitalWrite(RightAin2, LOW);
        }

        else
        {
            digitalWrite(RightAin1, LOW);
            digitalWrite(RightAin2, HIGH);
            right = -right;
        }

        analogWrite(LeftPWM, left * 255 / 100);   //输出到左电机，将百分比转换成0~255的输出
        analogWrite(RightPWM, right * 255 / 100); //输出到右电机
    }

    else //电机不在线上
    {
        digitalWrite(RightAin1, LOW); //停止右电机
        digitalWrite(RightAin2, LOW);
        digitalWrite(LeftAin1, LOW); //停止左电机
        digitalWrite(LeftAin2, LOW);
    }

    delay(5); //调整控制周期对微分作用很重要！
}


void loop()
{
    followLine(75); //以PWM值=75(百分数）的速度寻线                    
}
