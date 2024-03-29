#include "PlayerController.h"
#include <iostream>

void PlayerController::update(sf::RenderWindow &window, GameLogic &logic, float dSec, int playerNum) {

    sf::Vector2f dir = sf::Vector2f(0,0);


    if (playerNum == 0) {
        //process keyboard input for player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && logic.walrus1->getStamina() >= 30) {
            logic.walrus1->boost(0);
        }
        if (sf::Joystick::isConnected(0)) {
            if (sf::Joystick::isButtonPressed(0, 0)) {
                logic.walrus1->raiseTusks(dSec);
            }
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            if (x > 50) {
                dir.x += 1;
            }
            if (x < -50) {
                dir.x -= 1;
            }
            if (y > 50) {
                dir.y += 1;
            }
            if (y < -50) {
                dir.y -= 1;
            }
        }
        logic.playerList[playerNum]->applyActiveForce(dir, dSec);

    }


    else if (playerNum == 1) {
        //process keyboard input for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && logic.walrus2->getStamina() >= 30) {
			logic.walrus2->boost(0);
        }
        if (sf::Joystick::isConnected(1)) {
            if (sf::Joystick::isButtonPressed(1, 0)) {
                //logic.walrus2->raiseTusks(dSec);
            }
            float x = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
            if (x > 50) {
                dir.x += 1;
            }
            if (x < -50) {
                dir.x -= 1;
            }
            if (y > 50) {
                dir.y += 1;
            }
            if (y < -50) {
                dir.y -= 1;
            }
        }
        logic.playerList[playerNum]->applyActiveForce(dir, dSec);

    } else if (playerNum == 2) {
        //process keyboard input for player 3
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && logic.walrus3->getStamina() >= 30) {
			logic.walrus3->boost(0);
        }
        if(sf::Joystick::isConnected(2)){
          if(sf::Joystick::isButtonPressed(1, 0)){
            //logic.walrus2->raiseTusks(dSec);
          }
          float x = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
          float y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
          if(x>50){
            dir.x+=1;
          }
          if(x<-50){
            dir.x-=1;
          }
          if(y>50){
            dir.y+=1;
          }
          if(y<-50){
            dir.y-=1;
          }
        }
        logic.playerList[playerNum]->applyActiveForce(dir, dSec);
    }

    else if (playerNum == 3) {
        //process keyboard input for player 4
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            dir.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            dir.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && logic.walrus4->getStamina() >= 30) {
			logic.walrus4->boost(0);
        }
        if (sf::Joystick::isConnected(3)) {
            if (sf::Joystick::isButtonPressed(0, 0)) {
                //logic.walrus1->raiseTusks(dSec);
            }
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            if (x > 50) {
                dir.x += 1;
            }
            if (x < -50) {
                dir.x -= 1;
            }
            if (y > 50) {
                dir.y += 1;
            }
            if (y < -50) {
                dir.y -= 1;
            }
        }
        logic.playerList[playerNum]->applyActiveForce(dir, dSec);

    }

    // process events
    sf::Event Event;
    while (window.pollEvent(Event)) {
        switch (Event.type) {
            //window closed
            case sf::Event::Closed:
                window.close();
                break;
            //window out of focus
            case sf::Event::LostFocus:
                logic.togglePause();
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::P) {
                    logic.togglePause();
                }
                break;
        }
    }
};
