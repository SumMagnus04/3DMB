#include "bullet.h"

Bullet initBullet(vec2 position, vec2 direction, float speed, int lifeTime)
{
	Bullet bullet;
	glm_vec2_copy(position, bullet.position);
	glm_vec2_copy(direction, bullet.direction);
	bullet.speed = speed;
	bullet.lifeTime = lifeTime;
	return bullet;
}

void drawBullet(Bullet* bullet, SpriteBatch* spriteBatch, GLuint textureId)
{
	vec4 position;
	position[0] = bullet->position[0];
	position[1] = bullet->position[1];
	position[2] = 30.0f;
	position[3] = 30.0f;
	vec4 uv;
	uv[0] = 0.0f;
	uv[1] = 0.0f;
	uv[2] = 1.0f;
	uv[3] = 1.0f;
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	drawSpriteBatch(spriteBatch, position, uv, textureId, 0.0f, &color);
}

void updateBullet(Bullet* bullet)
{
	bullet->position[0] += bullet->direction[0] * bullet->speed;
	bullet->position[1] += bullet->direction[1] * bullet->speed;
	bullet->lifeTime--;
}