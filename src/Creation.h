#ifndef CREATION_H
#define CREATION_H

/**
 * @brief Базовый класс для всех существ в игре
 */
class Creation {
private:
    int health; ///< Текущее здоровье существа

public:
    /**
     * @brief Виртуальный деструктор для корректного удаления объектов
     */
    virtual ~Creation() = default;

    /**
     * @brief Получить текущее здоровье
     * @return Значение здоровья
     */
    int getHealth() const;

    /**
     * @brief Установить новое значение здоровья      
     * @param newHealth Новое значение здоровья
     */
    virtual void setHealth(int newHealth);
};

#endif // CREATION_H 