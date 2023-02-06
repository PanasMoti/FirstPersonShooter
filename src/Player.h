//
// Created by elias on 02/02/2023.
//

#ifndef FPS_PLAYER_H
#define FPS_PLAYER_H
#include "rlFP/rlFPCamera.h"
#include <ostream>

class Player {
public:
    int hp;
    int max_hp;
    rlFPCamera cam;
    static Player& instance();
    Player(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(const Player&) = delete;
    Player& operator=(Player&&) = delete;

    static void init(int);
    friend std::ostream& operator<<(std::ostream& os,const Player& player);
protected:
    Player() = default;
};


#endif //FPS_PLAYER_H
