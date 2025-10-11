#include <Wire.h>

// MPU-6050 register and helper definitions (from stabilizer_table_pid.ino)
#define MPU6050_AUX_VDDIO          0x01
#define MPU6050_SMPLRT_DIV         0x19
#define MPU6050_CONFIG             0x1A
#define MPU6050_GYRO_CONFIG        0x1B
#define MPU6050_ACCEL_CONFIG       0x1C
#define MPU6050_FF_THR             0x1D
#define MPU6050_FF_DUR             0x1E
#define MPU6050_MOT_THR            0x1F
#define MPU6050_MOT_DUR            0x20
#define MPU6050_ZRMOT_THR          0x21
#define MPU6050_ZRMOT_DUR          0x22
#define MPU6050_FIFO_EN            0x23
#define MPU6050_I2C_MST_CTRL       0x24
#define MPU6050_I2C_SLV0_ADDR      0x25
#define MPU6050_I2C_SLV0_REG       0x26
#define MPU6050_I2C_SLV0_CTRL      0x27
#define MPU6050_I2C_SLV1_ADDR      0x28
#define MPU6050_I2C_SLV1_REG       0x29
#define MPU6050_I2C_SLV1_CTRL      0x2A
#define MPU6050_I2C_SLV2_ADDR      0x2B
#define MPU6050_I2C_SLV2_REG       0x2C
#define MPU6050_I2C_SLV2_CTRL      0x2D
#define MPU6050_I2C_SLV3_ADDR      0x2E
#define MPU6050_I2C_SLV3_REG       0x2F
#define MPU6050_I2C_SLV3_CTRL      0x30
#define MPU6050_I2C_SLV4_ADDR      0x31
#define MPU6050_I2C_SLV4_REG       0x32
#define MPU6050_I2C_SLV4_DO        0x33
#define MPU6050_I2C_SLV4_CTRL      0x34
#define MPU6050_I2C_SLV4_DI        0x35
#define MPU6050_I2C_MST_STATUS     0x36
#define MPU6050_INT_PIN_CFG        0x37
#define MPU6050_INT_ENABLE         0x38
#define MPU6050_INT_STATUS         0x3A
#define MPU6050_ACCEL_XOUT_H       0x3B
#define MPU6050_ACCEL_XOUT_L       0x3C
#define MPU6050_ACCEL_YOUT_H       0x3D
#define MPU6050_ACCEL_YOUT_L       0x3E
#define MPU6050_ACCEL_ZOUT_H       0x3F
#define MPU6050_ACCEL_ZOUT_L       0x40
#define MPU6050_TEMP_OUT_H         0x41
#define MPU6050_TEMP_OUT_L         0x42
#define MPU6050_GYRO_XOUT_H        0x43
#define MPU6050_GYRO_XOUT_L        0x44
#define MPU6050_GYRO_YOUT_H        0x45
#define MPU6050_GYRO_YOUT_L        0x46
#define MPU6050_GYRO_ZOUT_H        0x47
#define MPU6050_GYRO_ZOUT_L        0x48
#define MPU6050_PWR_MGMT_1         0x6B
#define MPU6050_PWR_MGMT_2         0x6C
#define MPU6050_WHO_AM_I           0x75

#define MPU6050_D0 0
#define MPU6050_D1 1
#define MPU6050_D2 2
#define MPU6050_D3 3
#define MPU6050_D4 4
#define MPU6050_D5 5
#define MPU6050_D6 6
#define MPU6050_D7 7
#define MPU6050_I2C_ADDRESS       0x68

// Global sensor values
float angle_x, angle_y, angle_z;
float accel_x, accel_y, accel_z;

float init_angle_x = 0;
float init_angle_y = 0;

// Timing and filter state
unsigned long last_read_time;
float last_x_angle, last_y_angle, last_z_angle;
float last_gyro_x_angle, last_gyro_y_angle, last_gyro_z_angle;

// Calibration offsets
float base_x_accel, base_y_accel, base_z_accel;
float base_x_gyro, base_y_gyro, base_z_gyro;

// Helper to store last values
void set_last_read_angle_data(unsigned long t, float x, float y, float z, float gx, float gy, float gz) {
  last_read_time = t;
  last_x_angle   = x;
  last_y_angle   = y;
  last_z_angle   = z;
  last_gyro_x_angle = gx;
  last_gyro_y_angle = gy;
  last_gyro_z_angle = gz;
}
inline unsigned long get_last_time() { return last_read_time; }
inline float get_last_x_angle() { return last_x_angle; }
inline float get_last_y_angle() { return last_y_angle; }
inline float get_last_z_angle() { return last_z_angle; }
inline float get_last_gyro_x_angle() { return last_gyro_x_angle; }
inline float get_last_gyro_y_angle() { return last_gyro_y_angle; }
inline float get_last_gyro_z_angle() { return last_gyro_z_angle; }

// Union for raw read
typedef union {
  struct { uint8_t xh, xl, yh, yl, zh, zl, th, tl, gh, gl, ih, il, jh, jl; } reg;
  struct { int x_accel, y_accel, z_accel, temperature, x_gyro, y_gyro, z_gyro; } value;
} accel_t_gyro_union;

int MPU6050_read(int start, uint8_t *buf, int size) {
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  Wire.write(start);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
  int i=0;
  while (Wire.available() && i<size) buf[i++] = Wire.read();
  return (i==size) ? 0 : -1;
}
int MPU6050_write_reg(int reg, uint8_t data) {
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  Wire.write(reg);
  Wire.write(data);
  return Wire.endTransmission(true);
}

void calibrate_sensors() {
  accel_t_gyro_union d;
  MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t*)&d, sizeof(d));
  int N=10;
  float sx=0, sy=0, sz=0, gx=0, gy=0, gz=0;
  for(int i=0;i<N;i++) {
    MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t*)&d, sizeof(d));
    sx += d.value.x_accel; sy += d.value.y_accel; sz += d.value.z_accel;
    gx += d.value.x_gyro;  gy += d.value.y_gyro;  gz += d.value.z_gyro;
    delay(100);
  }
  base_x_accel = sx/N; base_y_accel = sy/N; base_z_accel = sz/N;
  base_x_gyro  = gx/N;  base_y_gyro  = gy/N;  base_z_gyro  = gz/N;
}

void MPU6050_setup() {
  uint8_t c;
  MPU6050_read(MPU6050_WHO_AM_I, &c, 1);
  MPU6050_write_reg(MPU6050_PWR_MGMT_1, 0);
  calibrate_sensors();
  set_last_read_angle_data(millis(), 0,0,0, 0,0,0);
}

void MPU6050_data_read() {
  accel_t_gyro_union d;
  MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t*)&d, sizeof(d));
  unsigned long t = millis();
  float dt = (t - get_last_time())/1000.0;
  
  // bytes swap on regs
  #define SWAP(x,y) { uint8_t tmp=x; x=y; y=tmp; }
  SWAP(d.reg.xh, d.reg.xl); SWAP(d.reg.yh, d.reg.yl); SWAP(d.reg.zh, d.reg.zl);
  SWAP(d.reg.gh, d.reg.gl); SWAP(d.reg.ih, d.reg.il); SWAP(d.reg.jh, d.reg.jl);
  #undef SWAP
  
  // accelerometer
  accel_x = d.value.x_accel; accel_y = d.value.y_accel; accel_z = d.value.z_accel;
  float ax = accel_x, ay = accel_y, az = accel_z;
  float accel_angle_x = atan(ay/sqrt(ax*ax+az*az))*57.2958;
  float accel_angle_y = atan(-ax/sqrt(ay*ay+az*az))*57.2958;
  
  // gyro 
  float gx = (d.value.x_gyro - base_x_gyro)/131.0;
  float gy = (d.value.y_gyro - base_y_gyro)/131.0;
  float gz = (d.value.z_gyro - base_z_gyro)/131.0;
  float gyro_angle_x = gx*dt + get_last_x_angle();
  float gyro_angle_y = gy*dt + get_last_y_angle();
  float gyro_angle_z = gz*dt + get_last_z_angle();
  
  float alpha = 0.96;
  angle_x = alpha*gyro_angle_x + (1-alpha)*accel_angle_x;
  angle_y = alpha*gyro_angle_y + (1-alpha)*accel_angle_y;
  angle_z = gyro_angle_z;
  
  set_last_read_angle_data(t, angle_x, angle_y, angle_z,
                            gyro_angle_x, gyro_angle_y, gyro_angle_z);
}

// PID & PWM control globals
int ocr1a, ocr1b;
float target_a, error_a, bef_error_a, def_error_a, error_sum_a;
float P_a,I_a,D_a;
float target_b, error_b, bef_error_b, def_error_b, error_sum_b;
float P_b,I_b,D_b;

void setup() {
  Serial.begin(19200);
  Wire.begin();
  MPU6050_setup();
  pinMode(9, OUTPUT);  // OC1A
  pinMode(10, OUTPUT);  // OC1B
  pinMode(8, INPUT);
  // Timer1: Fast PWM, TOP=ICR1, prescaler=8
  TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
  TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);
  ICR1 = 39999;  // 20ms

    // 1) 遺??吏곹썑 ?먰븯???쒕Ъ由ъ쟻???쒖옉 ?꾩튂濡???踰??대룞
  const int INITIAL_POS_A = 10000;  // ?? 以묐┰(??90째)
  const int INITIAL_POS_B =-14000;
  OCR1A = INITIAL_POS_A;
  OCR1B = INITIAL_POS_B;

  // 2) ?좎떆 ?湲???MPU-6050???덉젙??媛믪쓣 ?쎌쓣 ?쒓컙
  delay(3000);

  // 3) ?쇱꽌 媛믪쓣 ??踰??쎌뼱?? ?대븣??媛곷룄瑜??? 湲곗??앹쑝濡??쇰뒗??  MPU6050_data_read();
  init_angle_x = angle_x;
  init_angle_y = angle_y;

  // 4) PID ?꾩쟻 蹂?섎? 珥덇린??(?좏깮)
  error_sum_a = 0;
  error_sum_b = 0;
}

void loop() {
  MPU6050_data_read();

  // A-axis PID (roll)
  target_a    = 250 - 0.04*(accel_x + 580.0);
  bef_error_a = error_a;
  error_a     = target_a - (angle_y - 1.42);
  def_error_a = error_a - bef_error_a;
  error_sum_a += error_a;
  P_a = 2.0; I_a = 0; D_a = 0.0001;
  ocr1a = P_a*error_a + I_a*error_sum_a + D_a*def_error_a;
  
  // B-axis PID (pitch)
  target_b    = 1020 - 0.025*(accel_y + 520.0);
  bef_error_b = error_b;
  error_b     = target_b - (angle_x + 0.57);
  def_error_b = error_b - bef_error_b;
  error_sum_b += error_b;
  P_b = 3.0; I_b = 0; D_b = 0.0001;
  ocr1b = P_b*error_b + I_b*error_sum_b + D_b*def_error_b;

  // deadband
  if (ocr1a>2700 && ocr1a<3000) ocr1a = 2850;
  if (ocr1b>2900 && ocr1b<3220) ocr1b = 3110;

  Serial.print(ocr1a); Serial.print("\t");
  Serial.println(ocr1b);

  OCR1A = ocr1a;
  OCR1B = ocr1b;
  
  delay(50);
}


