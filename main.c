#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define Key_Up 0x48
#define Key_Down 0x50
#define Key_Enter '\r'
#define WIN 1
#define LOSE 0
#define CONT -1

typedef struct {
	float HealthPoint;
	float AttackDamage;
	float Defense;
	float Speed;
	int Level;
	int Exp;
	int StatusPoint;
	int Win;
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
void calcLevel(User*user);
void selectStatus(User*user);
int attack(int speed, User *user, Enemy *enemy);
void attackToUser(User *user, Enemy *enemy);
void attackToEnemy(User *user, Enemy *enemy);
void AvoidAttack(User *user, Enemy *Enemy);
int Battle(User *user);

int debug = 0;

int main()
{
	/*
	 *  Init
	 */
	system("chcp 65001");
	srand(time(NULL));
	User user = seedUser();
	int cnt = 0; //cntは、WINした回数
	int res;
	system("cls");

	/*
	 *  Title
	 */
	printf("\n\n          Sign in Adventure\n\n\n");
	printf("         Press 's' to Start.\n\n");
	char i_key = 0;
	do {
		i_key = getch();
		if(i_key == 'd'){
			debug = 1;
			break;
		}
	} while(i_key != 's');
	system("cls");

	/*
	 *  Battle
	 */
	do {
		res = Battle(&user);
		if(res == WIN){
			user.Win ++;
		}
	} while(res == WIN);

	/*
	 * End
	 */
	system("cls");
	printf(">> 敗北しました <<\n");
	printf("勝利数: %d\n", user.Win);
	if(debug) debugUser(&user);
	return 0;
}

User seedUser(){
	User u = {
		20.0, // HealthPoint
		3.0,  // AttackDamage
		1.5,  // Defense
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
	printf("Exp: %d / ", user -> Exp);
	printf("Level: %d / ", user -> Level);
	printf("StatusPoint: %d\n", user -> StatusPoint);
}

Enemy seedEnemy(int level){
	float hp = level * 5.0 + (float)(rand() % (4 * level + 50)) / 10;
	float ad = level * 2.0 + (float)(rand() % (5 * level + 10)) / 10;
	float df = level * 0.5 + (float)(rand() % (level + 10)) / 10;
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

void calcLevel(User *user){
    int need_exp = (int)(0.04 * user -> Level * user -> Level * user -> Level + 0.8 * user -> Level * user -> Level + 5 * user -> Level + 10);
    int bef_level = user -> Level;
    while(need_exp <= user -> Exp){
        user -> Exp -= need_exp ;
        need_exp = (int)(0.04 * user -> Level * user -> Level * user -> Level + 0.8 * user -> Level * user -> Level + 2 * user -> Level);
        user -> Level ++ ;
    }
    int bet = user -> Level - bef_level;
    if(0 < bet){
        user -> StatusPoint += 2 * bet;
        printf("あなたは%dレベル上がりました\n", bet);
    }
    getchar();
    system("cls");
    selectStatus(user);
}

void selectStatus(User *user){
	while(0 < user -> StatusPoint){
        char* txt[] = {"体力を上げる", "攻撃力を上げる", "防御力を上げる", "瞬発力を上げる"};
        int sel_num = 4;
		char input = 0;
		int cnt = 0;
		int last_up = -1;
		float up;
		while(input != Key_Enter){
			printf("あなた Lv.%d\n", user -> Level);
			printf("  体力\t:  %.1f", user -> HealthPoint);
			printf("\n  攻撃力 : %.1f", user -> AttackDamage);
			printf("\n  防御力 : %.1f", user -> Defense);
			printf("\n  瞬発力 : %.1f", user -> Speed);
			printf("\n---------------------------------\n");
			printf(">> 上昇させるステータスを選択してください <<\n\n");
			for(int i = 0; i < sel_num; i++){
				if(i == cnt) printf("> ");
				else printf("    ");
				printf("%s\n", txt[i]);
			}
			printf("あと%d回ステータス上昇が出来ます\n", user -> StatusPoint);
			if(debug) debugUser(user);
			input = getch();
			system("cls");
			if(input == Key_Up && 0 < cnt){
				cnt --;
			}
			if(input == Key_Down && cnt < sel_num - 1){
				cnt ++;
			}
		}
        switch (cnt){
            case 0:
                up = 5 * user -> Level + 10.0 + (rand() % 20 - 10) / 10.0;
                user -> HealthPoint += up;
                last_up = 0;
                break;
            case 1:
                up = 3.0 + (rand() % 20 - 10) / 20.0;
                user -> AttackDamage += up;
                last_up = 1;
                break ;
            case 2:
                up = 1.0 + (rand() % 10 - 5) / 10.0;
                user -> Defense += up;
                last_up = 2;
                break ;
            case 3:
                up = 1.0 + (rand() % 10 - 5) / 10.0;
                user -> Speed += up;
                last_up = 3;
                break ;
        }
        user -> StatusPoint -- ;
        system("cls");
	}
}


int attack(int speed, User *user, Enemy *enemy){
	if(speed){
		attackToEnemy(user, enemy);
		if (enemy -> HealthPoint <= 0){	//勝ったときは
			return WIN;
		}
		attackToUser(user, enemy);
		if (user -> HealthPoint <= 0){	//負けたときは
			return LOSE;
		}			
	} else {
		attackToUser(user, enemy);
		if (user -> HealthPoint <= 0){	//負けたときは
			return LOSE;
		}
		attackToEnemy(user, enemy);
		if (enemy -> HealthPoint <= 0){	//勝ったときは
			return WIN;
		}
	}
	return CONT;
}

void attackToEnemy(User *user, Enemy *enemy){
	//ダメージを算出(アルテリオス計算式)
	//回避機能は未実装
	float damage;
	damage = user -> AttackDamage + (rand() %  (2 * user -> Level) - user -> Level) - enemy -> Defense;
	if (damage < 0){	//回復されないように
		damage = 0;
	}
	
	//ダメージ付与
	enemy -> HealthPoint -= damage;	
}


void attackToUser(User *user, Enemy *enemy){
	//ダメージを算出(アルテリオス計算式)
	//回避機能は未実装
	float damage;
	
	damage = enemy -> AttackDamage + (rand() %  (2 * user -> Level) - user -> Level) - user -> Defense;
	if (damage < 0){	//回復されないように
		damage = 0;
	}
	
	//ダメージ付与
	user -> HealthPoint -= damage;
}

int Battle(User *user)
{
    //モンスター出現から撃破までの関数。
    
	Enemy enemy = seedEnemy(user -> Level);	//Enemyをとりあえず召喚。

	printf(">> 戦闘を開始します <<\n");
	getch();
	system("cls");

	float ES = enemy.Speed;
	float US = user -> Speed;
	int turn = 1;

	float e_max_hp = enemy.HealthPoint;
	float u_max_hp = user -> HealthPoint;

	while(1){
		char* txt[] = {"攻撃する", "回避する", "逃避する"};
		int sel_num = 3;
		char input = 0;
		int cnt = 0;

		while(input != Key_Enter){
			if(debug) {
				debugEnemy(&enemy);
				debugUser(user);
			}
			printf("------ %d ターン目 ------\n", turn);
			printf("敵の体力     : ");
			for(int j = 0; j < 30; j++) {
				if(j < 30 * enemy.HealthPoint / e_max_hp){
					putchar('*');
				} else {
					putchar(' ');
				}
			}
			printf("  %.1f\n", enemy.HealthPoint);

			printf("あなたの体力 : ");
			for(int j = 0; j < 30; j++) {
				if(j < 30 * user -> HealthPoint / u_max_hp){
					putchar('*');
				} else {
					putchar(' ');
				}
			}
			printf("  %.1f\n", user -> HealthPoint);

			for(int i = 0; i < sel_num; i++){
				if(i == cnt) printf("> ");
				else printf("   ");
				printf("%s\n", txt[i]);
			}
			
			input = getch();
			system("cls");
			if(input == Key_Up && 0 < cnt){
				cnt --;
			}
			if(input == Key_Down && cnt < sel_num - 1){
				cnt ++;
			}
		}
		system("cls");
		if(cnt == 0){
			int res = attack(ES < US, user, &enemy);
			if(res == WIN){
				printf(">> 勝利しました <<\n");
				printf("%dの経験値を得ました\n", enemy.giveExp);
				getch();
				user -> Exp += enemy.giveExp;
				calcLevel(user);
				return WIN;
			} else if(res == LOSE){
				return LOSE;
			}
		} else if(cnt == 1){
			if(US + (rand() % user -> Level * 10) / (user -> Level * 10) < ES){
				attackToUser(user,&enemy);
				if (user -> HealthPoint <= 0){	//負けたときは
					return LOSE;
				}
			}
		} else {
			printf(">> あなたは、この場から逃げ出した！ <<\n");
			return LOSE;
		}
		turn++;
	}
}