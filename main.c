#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	float HealthPoint;
	float AttackDamage;
	float Defense;
	float Speed;
	int Level;
	int Exp;
	int StatusPoint;
} User;


typedef struct {
	float HealthPoint;
	float AttackDamage;
	float Defense;
	float Speed;
	int giveExp;
} Enemy;

User seedUser();
void debugUser(User*);
Enemy seedEnemy(int);
void debugEnemy(Enemy*);


int main()
{
	/*
	 * Init
	 */
	srand(time(NULL));
	
	/*
	 * Debug
	 */
	//User user = seedUser();
	//debugUser(&user);
	for (int i = 1; i < 5; ++i)
	{
		Enemy enemy = seedEnemy(100);
		debugEnemy(&enemy);
	}

	/*
	 * End
	 */
	return 0;
}

User seedUser(){
	User u = {
		10.0, // HealthPoint
		3.0,  // AttackDamage
		2.0,  // Defense
		1.0,  // Speed
		1,  // Level
		0,  // Exp
		0   // StatusPoint
	};
	return u;
}

void debugUser(User *user){
	printf("[Debug]:  User - ");
	printf("HealthPoint: %.1f / ", user -> HealthPoint);
	printf("AttackDamage: %.1f / ", user -> AttackDamage);
	printf("Defense: %.1f / ", user -> Defense);
	printf("Speed: %.1f / ", user -> Speed);
	printf("StatusPoint: %d\n", user -> StatusPoint);
}

Enemy seedEnemy(int level){
	float hp = level * 8.0 + (float)(rand() % (15 * level + 50)) / 10;
	float ad = level * 1.0 + (float)(rand() % (5 * level + 10)) / 10;
	float df = level * 2.0 + (float)(rand() % (5 * level + 20)) / 10;
	float sp = 1.0 + (float)(rand() % ((10 * level) / 10 + 5)) / 10;
	int xp = (hp / 3 + ad * 5 + df * 5 + sp * 10) / 2;
	Enemy e = {hp, ad, df, sp, xp};
	return e;
}

void debugEnemy(Enemy *enemy){
	printf("[Debug]: Enemy - ");
	printf("HealthPoint: %.1f / ", enemy -> HealthPoint);
	printf("AttackDamage: %.1f / ", enemy -> AttackDamage);
	printf("Defense: %.1f / ", enemy -> Defense);
	printf("Speed: %.1f / ", enemy -> Speed);
	printf("giveExp: %d\n", enemy -> giveExp);
}