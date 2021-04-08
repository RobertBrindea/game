#include <bits/stdc++.h>

using namespace std;

struct entity{
    char name[50];
    int hp=100, shield=50, potions=3;
};

void heal(entity &p) {
    if(p.potions > 0) {
        p.potions--;
        p.hp += 50;
        if(p.hp > 100)
            p.hp = 100;
        cout << p.name << " healed and now has " << p.hp << " health";
    }
    else {
        cout << "You have no potions";
    }
}

void attack(entity &a, entity &b) {
    int damage=10;
    damage = (damage * b.shield) / 100;
    b.shield -= 1;
    b.hp -= damage;
    cout << a.name << " attacked " << b.name << " for " << damage << " damage" << endl;
    cout << b.name << " now has " << b.hp << " health";
}

int checkAlive(entity &a, entity &b) {
    if(a.hp <= 0)
        return 1;
    else if(b.hp <= 0)
        return 2;
    return 0;
}

void bossMove(entity &a, entity &b) {
    if(b.hp < 50 && rand()%100 > 30+(50-b.hp)) {
        heal(b);
        return;
    }
    attack(b, a);
}

int main()
{
    
	return 0;
}
