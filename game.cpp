#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale.h>

void openLuckyBlock();
void riskyBattle();

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50;  // Деньги / Мана / Патроны / Крышки
int score = 0;       // Очки выживания (цель — рекорд)
int turn = 1;

void printHUD() {
    std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score
        << "] ================\n";
    std::cout << "♥ Здоровье: " << hp << "/100  |  ▫ Ресурсы: "
        << resources << "\n";
    std::cout << "--------------------------------------------------------\n";
}

// -------------------------------------------------------------
// [МЕСТО ДЛЯ ФУНКЦИЙ РАЗРАБОТЧИКОВ ИЗ PULL REQUEST'ОВ]
// -------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int choice = 0;

    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД MINECRAFT EDITION <<<\n";

    while (hp > 0) {
        printHUD();
        std::cout << "1. Рискованная битва с мобами (Высокая награда / Высокий риск)\n";
        std::cout << "2. Поспать на кровати / Отдохнуть дома (Лечение и обмен ресурсов)\n";
        std::cout << "3. Особое событие / Открытие Lucky Block'а\n";
        std::cout << "0. Погибнуть и зафиксировать счет\n";
        std::cout << "Выберите действие > ";

        if (!(std::cin >> choice)) break;

        switch (choice) {
        case 1:
            // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
            riskyBattle();
            break;

	case 2: {
            // [РАЗРАБОТЧИК 2: МОДУЛЬ ОТХИЛА (ISSUE #2)]
            std::cout << "\n[ КРОВАТЬ / ДОМ ] Вы ложитесь спать...\n";
            
            if (hp >= 100) {
                std::cout << "-> Вы полностью здоровы! Отдых не требуется.\n";
            } 
            else if (resources >= 15) {
                // Платный/ресурсный качественный отдых
                resources -= 15;
                int heal = 40 + (rand() % 21); // Лечение от 40 до 60 HP
                hp += heal;
                if (hp > 100) hp = 100;
                
                std::cout << "-> Вы отлично выспались в безопасности!\n";
                std::cout << "   Потрачено ресурсов: 15\n";
                std::cout << "   Восстановлено здоровья: +" << heal << " HP\n";
            } 
            else {
                // Ресурсов мало — сон тревожный и лечит слабо
                int badHeal = 5 + (rand() % 6); // Лечение от 5 до 10 HP
                hp += badHeal;
                if (hp > 100) hp = 100;
                
                std::cout << "-> У вас не хватает ресурсов (нужно 15) на обустройство безопасного ночлега.\n";
                std::cout << "   Сон на сырой земле был тревожным... Восстановлено всего: +" << badHeal << " HP\n";
            }
            break;
        }


        case 3:
            // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/БОССА (ISSUE #3)]
			openLuckyBlock();
            break;

        case 0:
            hp = 0;
            break;

        default:
            std::cout << "\nНеизвестная команда!\n";
            break;
        }

        // Каждый успешный ход дает очки выживания
        if (hp > 0) {
            turn++;
            score += 10;
        }
    }

    std::cout << "\n▫ ИГРА ОКОНЧЕНА, ВЫ МЕРТВЫ. Ваш итоговый рекорд: " << score << " очков!\n";
    return 0;
}

void openLuckyBlock() {
    int roll = rand() % 20 + 1;

    std::cout << "\n[?] Вы разбиваете загадочный Лаки-блок...\n";
    std::cout << "Бросок D20: " << roll << "!\n";

    if (roll == 1) {
        // Критический провал — 5%
        hp -= 50;
        if (hp < 0) hp = 0;

        resources /= 2;
        score /= 2;

        std::cout << "[!!!] КРИТИЧЕСКОЕ ПРОКЛЯТИЕ!\n";
        std::cout << "Из блока вырвался Иссушитель!\n";
        std::cout << "-50 HP, потеря половины ресурсов и очков.\n";

        if (hp == 0) {
            std::cout << "Проклятие оказалось смертельным...\n";
        }
    }
    else if (roll <= 5) {
        // Неудача — 20%
        int damage = rand() % 16 + 15;
        hp -= damage;
        if (hp < 0) hp = 0;

        std::cout << "[!] Ловушка! Рядом появился заряженный крипер!\n";
        std::cout << "Вы потеряли " << damage << " HP.\n";

        if (hp == 0) {
            std::cout << "Вы не пережили взрыв...\n";
        }
    }
    else if (roll <= 10) {
        // Ресурсы — 25%
        int reward = rand() % 31 + 20;
        resources += reward;

        std::cout << "[+] Из блока выпал сундук с припасами!\n";
        std::cout << "Вы получили " << reward << " ресурсов.\n";
    }
    else if (roll <= 15) {
        // Случайный множитель — 25%
        int multiplier = rand() % 2 + 2;
        int bonus = 200 * multiplier;
        score += bonus;

        std::cout << "[+] Алмазная находка! Множитель награды: x"
            << multiplier << "!\n";
        std::cout << "Вы получили " << bonus << " очков.\n";
    }
    else if (roll <= 19) {
        // Удвоение накопленных очков — 20%
        int bonus = score;
        score += bonus;

        std::cout << "[++] Благословение тотема! Ваши очки удвоены!\n";
        std::cout << "Вы получили " << bonus << " очков.\n";
    }
    else {
        // Натуральная двадцатка — 5%
        score += 2000;
        resources += 100;
        hp = 100;

        std::cout << "[!!!] ДЖЕКПОТ! Натуральная двадцатка!\n";
        std::cout << "Лаки-блок открыл сокровищницу древнего города!\n";
        std::cout << "+2000 очков, +100 ресурсов, полное восстановление HP!\n";
    }
}

void riskyBattle() {
    struct Mob {
        const char* name;
        int minDamage;
        int maxDamage;
        int rewardScore;
        int rewardResources;
    };

    const Mob mobs[] = {
        { "Зомби",    30, 35,  500, 20 },
        { "Скелет",   35, 40,  650, 30 },
        { "Крипер",   40, 45,  800, 40 },
        { "Эндермэн", 45, 50, 1100, 50 }
    };

    const Mob& mob = mobs[rand() % 4];

    std::cout << "\n[!] На вашем пути появился " << mob.name << "!\n";

    if (rand() % 100 < 50) {
        score += mob.rewardScore;
        resources += mob.rewardResources;

        std::cout << "Победа! Вы получили "
            << mob.rewardScore << " очков и "
            << mob.rewardResources << " ресурсов!\n";
    }
    else {
        int damage = mob.minDamage
            + rand() % (mob.maxDamage - mob.minDamage + 1);

        hp -= damage;
        if (hp < 0) hp = 0;

        std::cout << "Моб оказался сильнее! Вы потеряли "
            << damage << " HP.\n";

        if (hp == 0) {
            std::cout << "Вы погибли в бою...\n";
        }
    }
}