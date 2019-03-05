class Spinner{
  float originX;
  float originY;
  float endX;
  float endY;
  float length;
  float angle = 0;
  float speed;
  float lengthFactor;
  float speedFactor;
  float bright;
  Spinner child = null;
  
  Spinner(float x, float y, float length, float lengthFactor, float speed, float speedFactor, float bright){
    originX = x;
    originY = y;
    this.length = length;
    this.lengthFactor = lengthFactor;
    this.speed = speed;
    this.speedFactor = speedFactor;
    endX = x + length;
    endY = y;
    this.bright = bright;
  }
  
  // update endpoint and child's start point
  void update(){
    angle += speed;
    endX = originX + length * cos(angle);
    endY = originY - length * sin(angle);
    if(child != null){
      child.originX = endX;
      child.originY = endY;
    }
  }
  
  // create child Spinner attached to this one
  Spinner spawnChild(){
    float l = lengthFactor * length / (lengthFactor + 2 * length);
    float s = speed + 2 * speedFactor;
    child = new Spinner(endX, endY, l, lengthFactor, s, speedFactor, bright + 2.0/n);
    return child;
  }
}