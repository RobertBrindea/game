#include <bits/stdc++.h>

using namespace std;

struct entity{
    char name[50];
    int hp=100, shield=30, potions=3;
};

entity Player, Boss;


void heal(entity &p) {
    if(p.potions > 0) {
        p.potions--;
        p.hp += 50;
        if(p.hp > 100)
            p.hp = 100;
        cout << p.name << " healed and now has " << p.hp << " health" << endl;
    }
    else {
        cout << "You have no potions" << endl;
    }
}

bool parried()
{
    int value = rand()%2;
    int expected = -1;
    while(expected == -1)
    {
         string s;
        cout << "Where do you want to parry: (left/right)\n";
        cin >> s;
        if(s == "left") expected = 0;
        else if(s == "right") expected = 1;
        else cout << "Invalid parry. Try again!\n";
    }

    return (expected == value);
}

void attack(entity &a, entity &b) {
    int damage=50, nr = rand()%51 + 50;
    damage = (damage * nr) / 100;
    damage = damage - (damage * b.shield) / 100;
    damage += rand()%3;
    if(strcmp(b.name, Player.name) == 0)
    {
        cout << "The boss is attacking you.\n";
        if(parried())
        {
            cout << "You parried\n";
            return;
        }

        cout << "You failed to parry!\n";
    }
    if(strcmp(b.name, Boss.name) == 0)
    {
        int chance = rand()%2;
        if(chance == 1)
        {
            cout << "Boss parried.\n";
            return;
        }
        cout << "Boss failed to parry.\n";

    }
    b.shield -= 1;
    b.hp -= damage;
    cout << a.name << " attacked " << b.name << " for " << damage << " damage" << endl;
    cout << b.name << " now has " << b.hp << " health" << endl;
}

int checkAlive(entity &a, entity &b) {
    if(a.hp <= 0)
        return 1;
    else if(b.hp <= 0)
        return 2;
    return 0;
}

void bossMove(entity &a, entity &b) {
    if(b.hp < 50 && rand()%100 < 10+(50-b.hp)) {
        heal(b);
        return;
    }
    attack(b, a);
}

void showHealthAndPotions(entity &a, entity &b) {
    cout << a.name << " has " << a.hp << " health and " << a.potions << " potions\n";
    cout << b.name << " has " << b.hp << " health and " << b.potions << " potions\n";
}

int main()
{
    srand(time(0));
    cout << "Enter your name: ";
    cin >> Player.name;
	strcpy(Boss.name, "Boss");
	while(1)
    {
        showHealthAndPotions(Player, Boss);
        cout << "Enter your action: (attack/heal)\n";
        string action;
        cin >> action;
        if(action == "attack")
            attack(Player, Boss);
        else if(action == "heal")
            heal(Player);
        else
        {
            cout << "Invalid action\n";
            continue;
        }

        bossMove(Player, Boss);
        system("PAUSE");
        system("CLS");
        int state = checkAlive(Player, Boss);
        if(state)
        {
            if(state == 1) cout << "You lost!\n";
            else cout << "You won!\n";
            break;
        }

    }
    cout << "Game over";
	return 0;
}
