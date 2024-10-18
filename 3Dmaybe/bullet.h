#ifndef BULLET_H
#define BULLET_H

#include <cglm/cglm.h>
#include <3dmb/spritebatch.h>
#include <3dmb/vec.h>

typedef struct Bullet
{
	float speed;
	vec2 direction;
	vec2 position;
	int lifeTime;
} Bullet;

Bullet initBullet(vec2 position, vec2 direction, float speed, int lifeTime);
void drawBullet(Bullet* bullet, SpriteBatch* spriteBatch, GLuint textureId);
void updateBullet(Bullet* bullet);

#endif
