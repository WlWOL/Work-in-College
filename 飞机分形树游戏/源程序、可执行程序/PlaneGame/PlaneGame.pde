import java.util.*;

//int Width = 720,Height=900;//already have width and height
int score = 0,level=0;
int enemy_speed = 2;  //temp
int bullet_speed = 5;  //temp
boolean game_start=false;
boolean game_over=false;
int creat_enemy_fluence=1000;
int creat_bullet_fluence=400;

int temp_score;
int ceng=0;
int num=2;
//ArrayList<Particle> particles;


float start_time;
float end_time=0;
float current_time_1=0;
float current_time_2=0;

LinkedList<Enemy> enemys;
LinkedList<Bullet> bullets;
Plane player=new Plane((int)0.5*width,(int)0.5*height);
ParticleSystem ps_l;
ParticleSystem ps_r;


void setup() {
 size(720,900);
 frameRate(60);
   enemys=  new LinkedList<Enemy>();
   bullets=  new LinkedList<Bullet>();
   //particles = new ArrayList<Particle>();
   PImage img = loadImage("texture3.png");
   img.resize(10,10);
   ps_l = new ParticleSystem(0,new PVector(0.5*width,0.5*height),img);
   ps_r = new ParticleSystem(0,new PVector(0.5*width,0.5*height),img);
}

 void draw() 
{  //x++
start_time=millis();
game_setting_and_start();
draw_tree();
level_setting();
shoot_addbullet();
add_enemy();
draw_enemys();
draw_bullets();
draw_plane(mouseX,mouseY);
collision();
replay();
  current_time_1=current_time_1+(start_time-end_time);
  current_time_2=current_time_2+(start_time-end_time);
  end_time=millis();
  current_time_1=current_time_1+(end_time-start_time);
  current_time_2=current_time_2+(end_time-start_time);
}


void draw_tree()
{
  if(temp_score>0)
  {
ceng=(int)log_num(temp_score);
  }
  else
  {
    ceng=-1;
  }

text("ceng:"+ceng, 0, 60);
if(ceng>=0)
{
pushMatrix();
translate(width/2, height);
branch(height*0.28);
popMatrix();
}
}


float log_num (int x) {
  return (log(x) / log(num));
}


void branch(float len) {
  float sw = map(len,2,120,1,20);
  strokeWeight(sw);
  
    if (len >8)
      stroke(128,64,0);
      else
      stroke(33,204,52);     
  line(0, 0, 0, -len);
  translate(0, -len);
  len *= 0.618;
  if (len >=height*0.28*pow(0.618,ceng)) {
    pushMatrix();    // Save the current state of transformation (i.e. where are we now)
    rotate(PI*0.3);   // Rotate by theta
    branch(len);       // Ok, now call myself to draw two new branches!!
    popMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state
    pushMatrix();
    rotate(-PI*0.3);
    branch(len);
    popMatrix();
  }
}

 
 
