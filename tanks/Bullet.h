#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
  Bullet(int startX, int startY, int dir);
  void draw();
  void update();
  void impact(int tankX, int tankY);

private:
  int x, y, dir;
};

#endif  // BULLET_H