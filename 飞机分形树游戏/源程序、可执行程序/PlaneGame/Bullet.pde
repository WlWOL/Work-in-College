
class Bullet {

  int x, y;

   Bullet(int X, int Y)
  {
    x = X;
    y = Y;
  }

}

void draw_bullet(int x,int y)
  {
  noStroke();
  fill(color(0, 51, 133));
  triangle(x-5, y-40, x+5, y-40, x, y-60);
  }
  


void draw_bullets()
{
for(int i=0;i<bullets.size();i++)
  {
    bullets.get(i).y=bullets.get(i).y-bullet_speed;
    draw_bullet(bullets.get(i).x,bullets.get(i).y);
    if(bullets.get(i).y<100)
    {
      
     bullets.remove(i);
      
    }
  }
}

void shoot_addbullet()          //发射子弹
{if(current_time_1>creat_bullet_fluence)
  {
    if (mousePressed&&!game_over) 
    {      
    bullets.addFirst(new Bullet(player.x, player.y));      
      }   
    current_time_1=current_time_1-creat_bullet_fluence;
  }
}
