class Particle {
  PVector pos;
  PVector vel;
  PVector acc;
  float lifespan;
  PImage img;
  Particle(PVector l,PImage img_) {
    acc = new PVector(0,0);
    float vx = randomGaussian()*0.1;
    float vy = randomGaussian()*0.1 ;
    vel = new PVector(vx,vy);
    pos = l.get();
    lifespan = 100.0;
    img = img_;
  }
  void run() {
    update();
    render();
  }
  void applyForce(PVector f) {
    acc.add(f);
  }  
  void update() {
    vel.add(acc);
    pos.add(vel);
    lifespan -= 10;
    acc.mult(0); // clear Acceleration
  }
  void render() {
    imageMode(CENTER);
    tint(255,lifespan);
    image(img,pos.x,pos.y);
  }
  boolean isDead() {
    if (lifespan <= 0.0) {
      return true;
    } else {
      return false;
    }
  }
}
