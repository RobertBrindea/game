/// very advanced fight game made by a chad and a furry

#include <bits/stdc++.h>

using namespace std;

struct entity{
    char name[50];
    int hp=100, shield=50, potions=3, stamina=100;
};

entity Player, Boss;
int chargePercent=0;

void heal(entity &p) {
    if(p.potions > 0) {
        p.stamina = 100;
        p.potions--;
        p.hp += 40;
        if(p.hp > 100)
            p.hp = 100;
        cout << p.name << " healed and now has " << p.hp << " health" << endl;
    }
    else {
        cout << "You have no potions" << endl;
    }
}

bool parry(entity &a, entity &b, int bossChance)
{
    cout << a.name << " is trying to attack " << b.name << "\n";
    if(strcmp(b.name, Player.name) == 0)
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
        if(expected == value)
        {
            cout << "You parried.\n";
            return 1;
        }
        cout << "You failed to parry.\n";
        return 0;
    }
    else if(strcmp(b.name, Boss.name) == 0)
    {
        int chance = rand()%3;
        if(chance == bossChance)
        {
            cout << "Boss parried.\n";
            return 1;
        }
        cout << "Boss failed to parry.\n";
        return 0;
    }
}

void attack(entity &a, entity &b, int chargeDamage) {
    a.stamina -= 20;
    int damage=40, nr=rand()%51+50, bossChance=1;
    damage = (damage * nr) / 100;
    if(chargeDamage != 0) {
        damage = chargeDamage;
        chargePercent = -10;
        bossChance = 5;
    }
    damage = damage - (damage * b.shield) / 100;
    if(strcmp(a.name, Player.name) == 0 && parry(Player, Boss, 0)) return;
    if(strcmp(a.name, Boss.name) == 0 && parry(Boss, Player, bossChance)) return;
    if(strcmp(b.name, Boss.name) == 0)
    {
        chargePercent += 10;
        if(chargePercent > 100) chargePercent = 100;
    }
    b.shield -= 2;
    b.hp -= damage;
    cout << a.name << " attacked " << b.name << " for " << damage << " damage" << endl;
    cout << b.name << " now has " << b.hp << " health" << endl;
}

int chargeWeapon(int chargePercent) {
    chargePercent = 0;
    int damage = 15;
    cout << "Current attack damage charge at " << damage << ". Initiating power modules\n";
    for(int i=1; damage < 75; i++) {
        int nr = rand()%15 + 1, nrinput;
        cout << "Powering up module " << i << ". Complete following sequence for full charge:\n";
        for(int k=1; k<=7; k++)
            cout << nr*k << " ";
        cin >> nrinput;
        if(nrinput == nr*8) {
            damage += 15;
            cout << "Module " << i << " at full power. Current charge at " << damage << " damage\n";
        }
        else {
            cout << "Module " << i << " startup failed. Current charge at " << damage << " damage\n";
            return damage;
        }
    }
    cout << "Weapon fully charged, engaging attack\n";
    return damage;
}

void addStamina(entity &p) {
    p.stamina += 50;
    cout << p.name << " waited and raised their stamina to " << p.stamina << endl;
}

void lookForPotions(entity &p) {
    int chance = rand()%100;
    p.stamina += 20;
    if(chance < 40) {
        p.potions++;
        cout << p.name << " has found 1 potion\n";
    }
    else
        cout << p.name << " looked for potions, but didn't find any\n";
}

int checkAlive(entity &a, entity &b) {
    if(a.hp <= 0)
        return 1;
    else if(b.hp <= 0)
        return 2;
    return 0;
}

void bossMove(entity &a, entity &b) {
    if(rand()%100 < 15) {
        lookForPotions(b);
        return;
    }
    if(b.hp < 50 && rand()%100 < 30+(50-b.hp)) {
        if(b.potions == 0) {
            lookForPotions(b);
            return;
        }
        heal(b);
        return;
    }
    if(b.stamina < 20 || (b.stamina < 60 && rand()%100 < 20)) {
        addStamina(b);
        return;
    }
    attack(b, a, 0);
}

void showHealthAndPotions(entity &a, entity &b) {
    cout << a.name << " has " << a.hp << " health and " << a.potions << " potions | stamina at " << a.stamina << " | charge " << chargePercent << "%" << endl;
    cout << b.name << " has " << b.hp << " health and " << b.potions << " potions | stamina at " << b.stamina << endl;
}

void newBossFight(entity &Player, entity &Boss, int &act) {
    Boss.hp = 50*act;
    Boss.potions = act;
    Boss.shield = 50;
    Boss.stamina = 100;
    Player.potions = act+1;
    Player.hp = 100;
    Player.shield = 50+(10*(act-2));
    Player.stamina = 100;
    while(1) {
        showHealthAndPotions(Player, Boss);
        cout << "Enter your action: (attack/heal/wait/charge/search)\n";
        string action;
        cin >> action;
        if(action == "attack") {
            if(Player.stamina >= 20)
                attack(Player, Boss, 0);
            else {
                cout << "No stamina\n";
                continue;
            }
        }
        else if(action == "heal")
            heal(Player);
        else if(action == "wait")
            addStamina(Player);
        else if(action == "charge") {
            if(chargePercent == 100)
                attack(Player, Boss, chargeWeapon(chargePercent));
            else {
                cout << "Insufficient charge\n";
                continue;
            }
        }
        else if(action == "search")
            lookForPotions(Player);
        else {
            cout << "Invalid action\n";
            continue;
        }
        if(Boss.hp > 0)
            bossMove(Player, Boss);
        system("PAUSE");
        system("CLS");
        int state = checkAlive(Player, Boss);
        if(state) {
            if(state == 1) {
                cout << "You lost!\n";
                return;
            }
            else cout << "You won!\n";
            break;
        }
    }
    act++;
    if(act < 6) {
        int newGame;
        cout << "If you want to go to the next stage, press 1. If not, press anything else: ";
        cin >> newGame;
        if(newGame == 1)
            newBossFight(Player, Boss, act);
    }
    else
        cout << "There are no more bosses, you won!\n";
}

int main()
{
    srand(time(0));
    cout << "Enter your name: ";
    cin.getline(Player.name, 50);
	strcpy(Boss.name, "Boss");
	int nrofbosses = 2;
	newBossFight(Player, Boss, nrofbosses);

    cout << "Game over, play again if you want to suffer once more\n";
    cout << "In the end, you beat up " << nrofbosses-1 << " bosses!\n";
    if(nrofbosses == 6)
        cout << "Pretty impressive!\n";
    system("PAUSE");
	return 0;
}
