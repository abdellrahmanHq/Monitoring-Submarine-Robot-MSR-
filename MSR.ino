#include <Servo.h>

// --- تعريف المواتير ---
Servo rightMotor;
Servo leftMotor;
Servo verticalMotor;

// --- البنات (تأكد من توصيلك) ---
const int RIGHT_PIN = 9;
const int LEFT_PIN = 10;
const int VERT_PIN = 11;

// --- إعدادات السرعة ---
const float HORZ_LIMIT = 0.5; // 50% سرعة للحركة الأفقية
const float VERT_LIMIT = 1.0; // 100% سرعة للحركة العمودية

String inputString = "";
bool stringComplete = false;
float surge = 0.0;
float yaw = 0.0;
float heave = 0.0;

void setup() {
  Serial.begin(115200); // لازم نفس سرعة الجيتسون
  
  rightMotor.attach(RIGHT_PIN);
  leftMotor.attach(LEFT_PIN);
  verticalMotor.attach(VERT_PIN);

  // Arming Sequence (تهيئة المواتير)
  // إرسال إشارة توقف لمدة 3 ثواني
  stopAll();
  delay(3000); 
}

void loop() {
  // استقبال البيانات
  if (stringComplete) {
    parseData(inputString);
    inputString = "";
    stringComplete = false;
    
    // حساب وتحريك المواتير
    updateMotors();
  }
}

// دالة التحريك والحساب
void updateMotors() {
  // تطبيق حدود السرعة
  float s = surge * HORZ_LIMIT;
  float y = yaw   * HORZ_LIMIT;
  float h = heave * VERT_LIMIT; // عامودي سرعة كاملة

  // معادلة الخلط (Mixing)
  // يمين = تقدم - دوران
  // يسار = تقدم + دوران
  float rightSpeed = s - y;
  float leftSpeed  = s + y;
  float vertSpeed  = h;

  writeMotor(rightMotor, rightSpeed);
  writeMotor(leftMotor, leftSpeed);
  writeMotor(verticalMotor, vertSpeed);
}

// دالة إرسال الإشارة للـ ESC
void writeMotor(Servo &motor, float val) {
  if (val > 1.0) val = 1.0;
  if (val < -1.0) val = -1.0;
  
  // تحويل لـ PWM (1500 +- 400)
  int pwm = 1500 + (val * 400);
  motor.writeMicroseconds(pwm);
}

// قراءة السيريال
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') stringComplete = true;
  }
}

// تفكيك النص
void parseData(String data) {
  int sInd = data.indexOf("S:");
  int yInd = data.indexOf("Y:");
  int hInd = data.indexOf("H:");
  
  if (sInd > -1 && yInd > -1 && hInd > -1) {
    surge = data.substring(sInd+2, data.indexOf(',', sInd)).toFloat();
    yaw   = data.substring(yInd+2, data.indexOf(',', yInd)).toFloat();
    heave = data.substring(hInd+2).toFloat();
  }
}

void stopAll() {
  rightMotor.writeMicroseconds(1500);
  leftMotor.writeMicroseconds(1500);
  verticalMotor.writeMicroseconds(1500);
}