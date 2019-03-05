class Trail {
  boolean finished;
  float startX, startY;
  float endX, endY;
  float light;
  
  // set starting point of trail
  Trail(float x, float y) {
    startX = x;
    startY = y;
    light = 0;
  }
  
  // set end of trail
  void finish(float x, float y) {
    endX = x;
    endY = y;
    finished = true;
  }
  
  // draw trail and fade
  void draw(){
    if(!finished) return;
    stroke(255, 255*light, 255*light);
    strokeWeight(2);
    line(startX, startY, endX, endY);
    light = light + 0.01;
  }
}