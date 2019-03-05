void game_setting_and_start()
{
  background(225);
  fill(0, 102, 153);
  text("enemy_on_screen:"+enemys.size(), 280, 30);
  text("bullet_on_screen:"+bullets.size(), 150, 30);
  text("score:"+score, 0, 30);
  text("level:"+level, 80, 30);
 if(!game_start)
 {
  text("Plane Game", 170, 70);
  text("Use your mouse to move",140, 90);
  text("Press your mouse to shoot",140, 110);
  text("press any key to start",150, 150);
 }
  if(!game_start&&keyPressed)
  {
    game_start=true;  
    enemys.clear();
    bullets.clear();
  }
}



void replay()
{
  if(game_over)
  {
    text("game over", 170, 100);
    text("press any key to restart",150,130);
    score=0;
    enemys.clear();
    bullets.clear();
  }
  if(game_over&&keyPressed)
  {
    game_over=false;
    
  }
}
