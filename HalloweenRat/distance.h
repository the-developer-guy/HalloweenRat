class Ultrasonic
{
  int echoPin;
  int triggerPin;
  int distance;
  unsigned long echoTime;
public:
  Ultrasonic();
  Ultrasonic(int echoPin, int triggerPin);
  void measure(void);
  int getDistance(void);
};


