float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}

Vector2 lerp(Vector2 a, Vector2 b, float f)
{
    return Vector2(lerp(a.x, b.x, f), lerp(a.y, b.y, f));
}

Vector3 lerp(Vector3 a, Vector3 b, float f)
{
    return Vector3(lerp(a.x, b.x, f), lerp(a.y, b.y, f), lerp(a.z, b.z, f));
}

float calculateHypotenuse(float x, float y) {
  float result = sqrt(pow(x, 2) + pow(y, 2));
  return result;
}


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define every(interval)\
  static uint32_t __every__##interval = millis();\
  if(millis() - __every__##interval >= interval && (__every__##interval = millis()))