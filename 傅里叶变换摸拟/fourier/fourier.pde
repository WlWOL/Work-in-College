import java.util.*; //<>//

int n = 5;
int f = 200;
float l = 90;
int w, h,time=0;
Spinner[] spinners;
LinkedList<Trail> trails;
LinkedList<Trail> trails_2;
//int slider;
float speed = TWO_PI / (f);

void setup() {
  //slider = createSlider(0, 255, 100);
  w = 500;
  h = 300;
  size(1500, 280);
  frameRate(30);
  
  trails =  new LinkedList<Trail>();
  trails_2 =  new LinkedList<Trail>();
  // create list of spinners
  spinners = new Spinner[n];
  spinners[0] = new Spinner(w/2, h/2, l, l, speed, speed, 0);
  for (int i=1; i<n; i++) spinners[i] = spinners[i-1].spawnChild();
}

void draw() {
  background(255);

  time=time+2;
 
if(time>600)
{
trails_2.clear();
time=0;
}

fill(100);
textSize(50); 
text("n="+n,400,50); 
text("UP+1,DOWN-1,RIGHT+10,LEFT-10",600,50); 
  // update and draw trails
  addTrail(spinners[n-1].endX, spinners[n-1].endY);
  
  for (Trail trail : trails) {
    if (trail.finished) trail.draw();
  }
  
  for (Trail trail : trails_2) {
    if (trail.finished) trail.draw();
  }

 // addTrail(spinners[n-1].endX, spinners[n-1].endY);
 // for (Trail trail : trails) {
  //  if (trail.finished) trail.draw();
 // }
  
  
  // draw spinners
  strokeWeight(5);
  for (int i=0; i<n; i++) {
    float b = spinners[i].bright;
    if (b < 1) {
      stroke(0, 0, 255*b);
    } else {
      stroke(0, 255*(b-1), 255);
    }
    line(spinners[i].originX, spinners[i].originY, spinners[i].endX, spinners[i].endY);
    if(i==n-1)
    {
      //line(550, spinners[i].originY, 550, spinners[i].endY);
      ellipse(550, spinners[i].endY, 5, 5);
    }
    
    
  }
  
  // update spinner positions
  for (int i=0; i<n; i++) spinners[i].update();
  
  // save frames the second time around
  //  if(frameCount >= 2*f) exit();
  //  if(frameCount >= f && frameCount % 4 == 0) saveFrame("../robo/fourier/##.png");
}

void addTrail(float x, float y) {
  // finish most recently started trail
  if (trails.size() > 0) 
{
  trails.peekFirst().finish(x, y);
}

  if (trails_2.size() > 0) 
{ 
  trails_2.peekFirst().finish(550+time, y);
}
  // start new trail
  trails.addFirst(new Trail(x, y));
  trails_2.addFirst(new Trail(550+time, y));
  
  if (trails.size() >= 100) 
{
  trails.removeLast();
}

  if (trails_2.size() >= 100) 
{
  trails_2.removeLast();
}
}

void keyPressed()
{
  
    if (keyCode == UP) 
    {
      n++;
      Reset();
    } 
    
    else if (keyCode == DOWN)
    {
      n--;
      Reset();
    } 
 
  else if (keyCode == RIGHT)
  {
    n= n+10;
    Reset();
  }
  else if (keyCode == LEFT){
    n= n-10;
    Reset();
}
}

void Reset()
{
  trails.clear();
  trails_2.clear();
  //spinners[0] = new Spinner(w/2, h/2, l, l, speed, speed, 0);
  //for (int i=1; i<n; i++) spinners[i] = spinners[i-1].spawnChild();
  spinners = new Spinner[n];
  spinners[0] = new Spinner(w/2, h/2, l, l, speed, speed, 0);
  for (int i=1; i<n; i++) spinners[i] = spinners[i-1].spawnChild();
  time=0;
}
