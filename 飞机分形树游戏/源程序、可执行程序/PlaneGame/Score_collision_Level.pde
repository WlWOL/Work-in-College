void collision()
{
  for(int i=0;i<enemys.size();i++)
  {  
    int  distance_to_plane_y=abs(enemys.get(i).y-player.y);
    int  distance_to_plane_x=abs(enemys.get(i).x-player.x);
    float  distance_to_plane=sqrt(pow(distance_to_plane_y, 2)+pow(distance_to_plane_x, 2));
    if(distance_to_plane<80)  //飞机间碰撞检测
    { 
       game_over=true;
    }
      else 
      {
          for(int j=0;j<bullets.size();j++)
      {
        int distance_to_bullet_y=abs(enemys.get(i).y-bullets.get(j).y);
        int distance_to_bullet_x=abs(enemys.get(i).x-bullets.get(j).x);
        float distance_to_bullet=sqrt(pow(distance_to_bullet_y, 2)+pow(distance_to_bullet_x, 2));    
                if(distance_to_bullet<50)  //飞机间碰撞检测
                    {                     
                        translate(width/2, height);                                       
                         enemys.remove(i);
                          bullets.remove(j);
                        score++;        //分数+1
                        temp_score=score;  
                      break;   
                    }
      }  
      }
  }
}
void level_setting()
{
  level=floor(score/10);
  if(score>0)
  {
  level=(int)log_num(score);
  }
    float para=0.5*level;
  if(level<8)
  {
    enemy_speed=2+(int)para;                  //
    creat_bullet_fluence=(int)(400/(1+para));
  }
  creat_enemy_fluence=(int)(1000/(1+2*para));
}
