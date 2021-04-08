#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct entity{
    char name[50];
    int hp=100, shield=50, potions=3;
};

void heal(entity &p)
{
    cout << p.name << " healed.\n";
}

void attack(entity &p, entity &b)
{
    cout << p.name << " attacked" << b.name << ".\n";
}

int checkAlive(entity &p, entity &b)
{
    return 1;
}

void bossMove(entity &p, entity &b)
{
    cout << "Boss random action";
}

int main()
{
    entity Player, Boss;
    cout << "Enter your name:";
    cin >> Player.name;
	strcpy(Boss.name, "Boss");
	while(1)
    {
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
