class Plane {
  int x, y,move_speed;
   Plane(int X, int Y)
  {
    x = X;
    y = Y;
    move_speed=5;
  }
}
PVector delta;
void draw_plane(int X,int Y)        
{
  int delta_x=X-player.x;
  int delta_y=Y-player.y;
  delta=new PVector(delta_x,delta_y);
  delta.normalize();
  if((abs(delta_x)<player.move_speed)&&(abs(delta_y)<player.move_speed))
  { player.x=X;
    player.y=Y; }
  else
  { player.x+=player.move_speed*delta.x;
  player.y+=player.move_speed*delta.y;}
  int x=player.x;
  int y=player.y;
  y=y+10;
  int a=10;
 draw_particle(ps_l,x+a,y+7,delta.x,delta.y);
 draw_particle(ps_r,x-a,y+7,delta.x,delta.y);
  noStroke();
  fill(color(0, 102, 133));
  triangle(x-40, y, x+40, y, x, y-30);
  fill(color(0, 153, 133));
  triangle(x-20, y-15, x+20, y-15, x, y-50);
  fill(color(0, 51, 133));
  triangle(x-20, y-15, x, y-15, x-10, y+15);
  triangle(x+20, y-15, x, y-15, x+10, y+15); 
} 
void draw_particle(ParticleSystem ps,int x,int y,float delta_x,float delta_y)
{
  ps.origin=new PVector(x,y);
  float dx = map(delta_x,-1,1,-0.5,0.5);
  float dy = map(delta_y,-1,1,-0.2,-0.4);
  PVector wind = new PVector(-dx,-dy);
  ps.applyForce(wind);
  ps.run();
  for (int i = 0; i < 2; i++) {
    ps.addParticle();
  }
}
