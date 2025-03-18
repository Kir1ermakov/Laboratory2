class Creation {
private:
    int health;

public:
    int getHealth() const {
        return health;
    }

    void setHealth(int newHealth) {
        if (newHealth >= 0)
        {
        health = newHealth;
        }
        
        else
        {
            health = 0;
        }
            
    }
};
