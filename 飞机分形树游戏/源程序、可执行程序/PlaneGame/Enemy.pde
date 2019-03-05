
class Enemy {
  //boolean finished;
  int x, y;
 
  Enemy(int X, int Y)
  {
    x = X;
    y = Y;
  }

  
}

void draw_enemy(int x,int y){
  noStroke();
  fill(color(204, 102, 0));
  triangle(x-40, y, x+40, y, x, y+30);
  fill(color(204, 153, 0));
  triangle(x-20, y-15, x+20, y-15, x, y+50);
  fill(color(153, 51, 0));
  triangle(x-20, y-15, x, y-15, x-10, y-30);
  triangle(x+20, y-15, x, y-15, x+10, y-30);
  }
  
  void draw_enemys()
{  
  for(int i=0;i<enemys.size();i++)
  {
    enemys.get(i).y=enemys.get(i).y+enemy_speed;
    draw_enemy(enemys.get(i).x,enemys.get(i).y);
    
    if(enemys.get(i).y>height)
    {
      enemys.remove(i);
     //EnemyList.splice(i,1);
    }
  }
}

void add_enemy()
  {
    if(current_time_2>creat_enemy_fluence)
    {
    if(game_start&&!game_over)
    {
       enemys.addFirst(new Enemy((int)random(width),20)); 
    //EnemyList.push(draw_single_enemy(random(WIDTH),20));
    }
    current_time_2=current_time_2-creat_enemy_fluence;
    }
  }
  
  
