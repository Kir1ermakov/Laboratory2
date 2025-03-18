#ifndef PLAYER_H
#define PLAYER_H

#include "Creation.h"
#include <string>

/**
 * @brief Класс игрока, наследуется от базового класса Creation
 */
class Player : public Creation {
private:
    std::string name;    ///< Имя игрока
    int level;          ///< Уровень игрока
    int experience;     ///< Опыт игрока
    int maxHealth;      ///< Максимальное здоровье

public:
    /**
     * @brief Конструктор класса Player
     * @param name Имя игрока
     * @param health Начальное здоровье
     */
    Player(const std::string& name = "Player", int health = 100);

    /**
     * @brief Получить имя игрока
     * @return Имя игрока
     */
    std::string getName() const;

    /**
     * @brief Установить имя игрока
     * @param newName Новое имя
     */
    void setName(const std::string& newName);

    /**
     * @brief Получить уровень игрока
     * @return Текущий уровень
     */
    int getLevel() const;

    /**
     * @brief Получить опыт игрока
     * @return Текущий опыт
     */
    int getExperience() const;

    /**
     * @brief Добавить опыт игроку
     * @param exp Количество опыта для добавления
     */
    void addExperience(int exp);

    /**
     * @brief Получить максимальное здоровье
     * @return Максимальное здоровье
     */
    int getMaxHealth() const;

    /**
     * @brief Установить здоровье (переопределение метода Creation)
     * @param newHealth Новое значение здоровья
     */
    void setHealth(int newHealth) override;
};

#endif // PLAYER_H 