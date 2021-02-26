#include <iostream>
#include <ctime>
using namespace std;

class weapon {
public:
    weapon(int base_damage, int durability, int degradation, int cost, int weight); //все важные значения задаются в конструкторе
    int get_base_damage() const;
    int get_durability() const;
    int get_degradation() const;
    void set_cost(int new_cost);
    int get_cost() const;
    int get_weight() const;
    int hit(); //здесь высчитывается результирующая сила удара для данного оружия

private:
    int base_damage; //базовый урон
    int durability; //максимальная прочность
    int degradation; //степень износа оружия
    int cost; //цена
    int weight; //вес
};

weapon::weapon(int base_damage = 15, int durability = 100, int degradation = 0, int cost = 250, int weight = 5) :
    //все важные величины имеют значения по умолчанию
    base_damage(base_damage),
    durability(durability),
    degradation(degradation),
    cost(cost),
    weight(weight)
    //список инициализации: значения аргументов присваиваются членам класса, позволяя оставить тело конструктора пустым
{

}

int weapon::get_base_damage() const { //функция-геттер для базового урона
    return this->base_damage;
}

int weapon::get_durability() const { //функция-геттер для прочности
    return this->durability;
}

int weapon::get_degradation() const { //функция-геттер для степени износа
    return this->degradation;
}

void weapon::set_cost(int new_cost) { //функция-сеттер для цены
    this->cost = new_cost;
}

int weapon::get_cost() const { //функция-геттер для цены
    return this->cost;
}

int weapon::get_weight() const { //функция-геттер для веса
    return this->weight;
}

//все геттеры определены, как константные методы, что позволяет обезопасить члены класса от нежелательных изменений

int weapon::hit() {
    srand(time(0));
    int random_effect = rand() % 10; //генерируем случайную величину в пределах от нуля до базового урона - 1
    int critical_strike = rand() % 5;
    int damage = this->base_damage - random_effect + critical_strike; //меняем урон: теперь он варьируется от нуля до изначального базового
    this->degradation++; //повышаем износ на единицу с каждым нанесенным ударом
    this->cost -= this->cost / durability; //уменьшаем цену соответственно изношенности оружия
    return damage; //возвращаем урон во внешнюю программу
}

class staff :public weapon {
public:
    staff(int base_damage, int durability, int degradation, int cost, int weight);
    int get_base_damage() const;
    int get_durability() const;
    int get_degradation() const;
    void set_cost(int new_cost);
    int get_cost() const;
    int get_weight() const;
    int hit2();
private:
    int base_damage;
    int durability;
    int degradation;
    int cost; 
    int weight; 
};

staff::staff(int base_damage = 10, int durability = 60, int degradation = 0, int cost = 400, int weight = 2):
    base_damage(base_damage),
    durability(durability),
    degradation(degradation),
    cost(cost),
    weight(weight){
}

int staff::get_base_damage() const {
    return this->base_damage;
}

int staff::get_degradation() const {
    return this->degradation;
}

int staff::get_durability() const {
    return this->durability;
}

int staff::get_cost() const {
    return this->cost;
}

int staff::get_weight() const {
    return this->weight;
}

int staff::hit2(){
    srand(time(0));
    int magic_effect = rand() % 5;
    int burn_attack = rand() % 2;
    int damage = this->base_damage + magic_effect + burn_attack; 
    this->degradation += 3;
    this->cost -= this->cost / durability; 
    return damage;
}


int main() {
    weapon iron_sword;
    staff fire_staff;
    int thief_health = 100, player_health = 100;

    while (thief_health > 0 && player_health > 0) {
        player_health = player_health - iron_sword.hit();
        cin.get();
        thief_health = thief_health - fire_staff.hit2();
        cout << "Player's health: " << player_health << endl;
        cout << "Thief's health: " << thief_health << endl;
    }

    cout << "sword condition: " << iron_sword.get_durability() - iron_sword.get_degradation() << endl;
    cout << "staff condition: " << fire_staff.get_durability() - fire_staff.get_degradation() << endl;
    cout << "sword cost: " << iron_sword.get_cost() << endl;
    cout << "staff cost: " << fire_staff.get_cost() << endl;

    return 0;
} 
