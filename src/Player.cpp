//
// Created by elias on 02/02/2023.
//

#include "Player.h"

Player &Player::instance() {
    static Player instance;
    return instance;
}

void Player::init(int hp) {
    Player& p = Player::instance();
    p.max_hp = hp;
    p.hp = hp;
    rlFPCameraInit(&p.cam,45.0f,{1.0f,0.0f,0.0f});
    p.cam.MoveSpeed.z = 5;
    p.cam.MoveSpeed.x = 5;
    p.cam.MoveSpeed.y = 5;
    p.cam.FarPlane = 5000; // render distance
    p.cam.ControlsKeys[4] = KEY_SPACE;
    p.cam.ControlsKeys[5] = KEY_LEFT_CONTROL;
    p.cam.ControlsKeys[6] = KEY_RIGHT;
    p.cam.ControlsKeys[7] = KEY_LEFT;
    p.cam.ControlsKeys[8] = KEY_DOWN;
    p.cam.ControlsKeys[9] = KEY_UP;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    return os << "hp:{" << player.hp << "/" <<player.max_hp << "}\n"
    << "pos:{" << player.cam.CameraPosition.x << ";" << player.cam.CameraPosition.y << ";" << player.cam.CameraPosition.z << "}\n"
    << "speed: {sidestep:" << player.cam.MoveSpeed.x << ";vertical:" << player.cam.MoveSpeed.y << ";horizontal:" << player.cam.MoveSpeed.z << "}";
}

