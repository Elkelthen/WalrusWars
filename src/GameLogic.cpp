#include <iostream>
#include <cmath>
#include <Definitions.h>
#include "GameLogic.h"
#include "Player.h"
#include <memory>
#include <list>
#include <vector>

void GameLogic::init() {

    playerList.push_back(walrus1);
    playerList.push_back(walrus2);
    playerList.push_back(walrus3);
    playerList.push_back(walrus4);

    posList.push_back(walrus1->getPos());
    posList.push_back(walrus1->getPos());
    posList.push_back(walrus1->getPos());
    posList.push_back(walrus1->getPos());

    massList.push_back(0);
    massList.push_back(0);
    massList.push_back(0);
    massList.push_back(0);

    state = mainMenu;
    walrus1->resetStats();
    walrus2->resetStats();
    stage->generateMap();
    progression = 0;
    accumulator = 0;
    fish_accumulator = 0.0f;
    sfx_volume = SFX_VOLUME_BASE;
    music_volume = MUSIC_VOLUME_BASE;
    walrus1->setColor(sf::Color(255,255,255,255));
    walrus2->setColor(sf::Color(155,155,155,255));
    walrus1->setName(DEFAULT_NAME_1);
    walrus2->setName(DEFAULT_NAME_2);
    walrus3->setName(DEFAULT_NAME_3);
    walrus4->setName(DEFAULT_NAME_4);

}

void GameLogic::update(float dSec) {
    if (state == playing) {

        // fish power-up generation
        // fish will be generated in water flopping (sometimes landing on ice)
        fish_accumulator += dSec;
        if (fish_list.size() < MAX_NUM_OF_FISH && fish_accumulator > 3.0) {
            fish_accumulator = 0;

            sf::Vector2f rand_spawn = sf::Vector2f(rand() % ((int)(7 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8), rand() % ((int)(5 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8));
            sf::Vector2f rand_target = sf::Vector2f(rand() % 160 - 80, rand() % 160 - 80);
            // make sure first jump is from water onto ice
            while ((stage->getTileDura((int)(rand_spawn.x / ICE_BLOCKS_SIZE_X), (int)(rand_spawn.y / ICE_BLOCKS_SIZE_Y), progression) > 0) ||
                (stage->getTileDura((int)((rand_spawn.x + rand_target.x) / ICE_BLOCKS_SIZE_X), (int)((rand_spawn.y + rand_target.y) / ICE_BLOCKS_SIZE_Y), progression) <= 0)) {
                rand_spawn = sf::Vector2f(rand() % ((int)(7 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8), rand() % ((int)(5 * WINDOW_WIDTH / 8)) + (WINDOW_WIDTH / 8));
                rand_target = sf::Vector2f(rand() % 160 - 80, rand() % 160 - 80);
            }

            fish_list.push_back(std::unique_ptr<Fish>(new Fish(rand_spawn, rand_target)));
        }

        //Handle all of this crap in one main loop.            //////////////////////////////////////////////////////////////////////////////////////////////////////////
        float dist;
        sf::Vector2f posDiff;
        
        for (int i = 0; i < playerList.size(); i++) {

            //Movement
            if (!playerList[i]->isDead()) {
                playerList[i]->tickUpdate(dSec);
                playerList[i]->applyPassiveForce(dSec);
            }

            //update positions and masses
            posList[i] = playerList[i]->getPos();
            massList[i] = playerList[i]->getMass();

            //Water Collision
            if (stage->getTileDura((posList[i].x) / ICE_BLOCKS_SIZE_X, (posList[i].y) / ICE_BLOCKS_SIZE_Y, progression) <= 0) {
                if (!playerList[i]->isDead()) {
                    handlePlayerDeath(i);
                    splash = sfx_volume;
                }
            }

            //Boundary Collision
            if (posList[i].x >= WINDOW_WIDTH || posList[i].x <= 0) {
                handleBoundaryCollision(i, posList[i].x);
            }
        }

        bool collision = false;
        //Player Collision. Loops through one by one and makes a table holding each difference to check.
        for (int i = 0; i < playerList.size(); i++) {
            for (int j = 0; j < playerList.size(); j++) {
                if (i != j) {
                    sf::Vector2f posDiff = posList[i] - posList[j];
                    dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
                    if (dist < PLAYER_HITBOX_SCALE * (massList[i] + massList[j]) && !(playerList[i]->isDead() || playerList[j]->isDead())) {
                        if (!collision) {
                            handlePlayerCollision(i, j);
                            collision = true;
                        }
                    }
                }
            }
        }

            // melt stage
        accumulator += dSec;
            if (accumulator >= .6) {
                stage->tickMelt(progression);
                accumulator -= .6;
            }

            // *check collisions* //
            sf::Vector2f w1_pos = walrus1->getPos();
            sf::Vector2f w2_pos = walrus2->getPos();
            sf::Vector2f w3_pos = walrus3->getPos();
            sf::Vector2f w4_pos = walrus4->getPos();
            float w1_mass = walrus1->getMass();
            float w2_mass = walrus2->getMass();
            float w3_mass = walrus2->getMass();
            float w4_mass = walrus2->getMass();

                                                                         //Attacking gives a speed boost, Defending poops out a wall for a certain time/distance
            // player1 attack - player 2 collision
            if (walrus1->getState() == Player::attacking) {
                //determine direction of attack
                p1AttackPoint = w1_pos + walrus1->getFacingDir() * (w1_mass / 3);

                posDiff = w2_pos - p1AttackPoint;
                dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
                if (!p1_attack_handling_in_progress && dist <= PLAYER_HITBOX_SCALE * (w2_mass + w1_mass)) {
                    // use the unit vector between attack and player to direct knockback
                    handlePlayerAttack(1, posDiff / dist);
                }
                else if (dist > PLAYER_HITBOX_SCALE* (w2_mass + w1_mass)) {
                    p1_attack_handling_in_progress = false;
                }
            }
            else {
                p1_attack_handling_in_progress = false;
            }

            // player2 attack - player 1 collision
            if (walrus2->getState() == Player::attacking) {
                //determine direction of attack
                p2AttackPoint = w2_pos + walrus2->getFacingDir() * (w2_mass / 3);

                posDiff = w1_pos - p2AttackPoint;
                dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
                if (!p2_attack_handling_in_progress && dist <= PLAYER_HITBOX_SCALE * (w1_mass + w2_mass)) {
                    //std::cout<<"attack begun!"<<std::endl;
                    // use the unit vector between attack and player to direct knockback
                    handlePlayerAttack(2, posDiff / dist);
                }
                else if (dist > PLAYER_HITBOX_SCALE* (w1_mass + w2_mass)) {
                    p2_attack_handling_in_progress = false;
                }
            }
            else {
                p2_attack_handling_in_progress = false;
            }

            // fish collisions
            std::list<std::unique_ptr<Fish>>::iterator fish;
            for (fish = fish_list.begin(); fish != fish_list.end(); fish++) {
                sf::Vector2f fish_pos = (*fish)->getPosition();
                // fish - player1 collision
                posDiff = w1_pos - fish_pos;
                dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
                if (dist < PLAYER_HITBOX_SCALE * w1_mass + FISH_SIZE && !walrus1->isDead()) {
                    handleFishCollision(1, *fish);
                    break;
                }
                // fish - player 2 collision
                posDiff = w2_pos - fish_pos;
                dist = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
                if (dist < PLAYER_HITBOX_SCALE * w2_mass + FISH_SIZE && !walrus2->isDead()) {
                    handleFishCollision(2, *fish);
                    break;
                }
                // fish - water collision
                if (stage->getTileDura(fish_pos.x / ICE_BLOCKS_SIZE_X, fish_pos.y / ICE_BLOCKS_SIZE_Y, progression) <= 0 && !(*fish)->flop_progress_timer) {
                    handleFishCollision(0, *fish);
                    break;
                }

                // tick update for living fish
                (*fish)->flop(dSec);
            }
            //std::cout << "end\n";
    }
}

void GameLogic::handleBoundaryCollision(int walrus, float xpos) {

    if (walrus < playerList.size() / 2) {

        //Check to see if other team is dead
        bool winner = true;
        for (int i = playerList.size() / 2; i < playerList.size(); i++) {
            if (!playerList[i]->isDead()) {
                winner = false;
            }
        }
        
        //If they are both dead
        if (winner == true && xpos >= WINDOW_WIDTH) {
            progression++;
            round += 1;
            fish_list.clear();
            if (sprites.size() == 2) {
                resetGame();
            }
            else {
                begin2v2();
            }
        }
        //at least one is still alive
        else {
            sf::Vector2f newVel = playerList[walrus]->getVel();
            newVel.x *= -1;
            playerList[walrus]->setVel(newVel);
            playerList[walrus]->tickUpdate(COLLISION_KNOCKBACK_TIME);
            border_bump = sfx_volume * BUMP_VOL_SCALE;
        }
    }
    else {
        bool winner = true;
        for (int i = 0; i < playerList.size() / 2; i++) {
            if (!playerList[i]->isDead()) {
                winner = false;
            }
        }

        //If they are both dead
        if (winner == true && xpos <= 0) {
            progression--;
            round += 1;
            fish_list.clear();
            if (sprites.size() == 2) {
                resetGame();
            }
            else {
                begin2v2();
            }
        }
        //at least one is still alive
        else {
            sf::Vector2f newVel = playerList[walrus]->getVel();
            newVel.x *= -1;
            playerList[walrus]->setVel(newVel);
            playerList[walrus]->tickUpdate(COLLISION_KNOCKBACK_TIME);
            border_bump = sfx_volume * BUMP_VOL_SCALE;
        }

    }

}

void GameLogic::handleFishCollision(int player, std::unique_ptr<Fish> &fish) {

    if (player == 1) {
        walrus1->handlePowerUp(fish->getColor());
        powerup = sfx_volume;
    } else if (player == 2) {
        walrus2->handlePowerUp(fish->getColor());
        powerup = sfx_volume;
    }

    fish_list.remove(fish);

}

void GameLogic::handlePlayerCollision(int i, int j) {

  //find the velocity of collision along the line of collision
  sf::Vector2f w1_vel = playerList[i]->getVel();
  sf::Vector2f w2_vel = playerList[j]->getVel();
  sf::Vector2f w1_pos = posList[i];
  sf::Vector2f w2_pos = posList[j];
  float w1_mass = massList[i];
  float w2_mass = massList[j];


  // calculate point of collision for potentially adding a collision animation later
  playerCollisionPoint = sf::Vector2f(((w1_pos.x * w2_mass) + (w2_pos.x * w1_mass)) / (w1_mass + w2_mass), ((w1_pos.y * w2_mass) + (w2_pos.y * w1_mass)) / (w1_mass + w2_mass));

  // Elastic Collision handling algorithm implemented from:
  // http://cobweb.cs.uga.edu/~maria/classes/4070-Spring-2017/Adam%20Brookes%20Elastic%20collision%20Code.pdf

  // calculate the difference in positions and normalize into a unit vector
  sf::Vector2f posDiff = w1_pos - w2_pos;
  float length = sqrt((posDiff.x * posDiff.x) + (posDiff.y * posDiff.y));
  sf::Vector2f normal = sf::Vector2f(posDiff.x / length, posDiff.y / length);
  // calculate the tangent unit vector
  sf::Vector2f tangent = sf::Vector2f(normal.y * -1, normal.x);
  // dot product of normal and velocities
  float walrus1ScalarNorm = (normal.x * w1_vel.x) + (normal.y * w1_vel.y);
  float walrus2ScalarNorm = (normal.x * w2_vel.x) + (normal.y * w2_vel.y);
  // dot product of tangent and velocities
  float walrus1ScalarTan = (tangent.x * w1_vel.x) + (tangent.y * w1_vel.y);
  float walrus2ScalarTan = (tangent.x * w2_vel.x) + (tangent.y * w2_vel.y);
  // calculate elastic collision
  float walrus1NewScalarNorm = (walrus1ScalarNorm * (w1_mass - w2_mass) + 2 * w2_mass * walrus2ScalarNorm) / (w1_mass + w2_mass);
  float walrus2NewScalarNorm = (walrus2ScalarNorm * (w2_mass - w1_mass) + 2 * w1_mass * walrus1ScalarNorm) / (w1_mass + w2_mass);

  sf::Vector2f walrus1NewVecNorm = normal * walrus1NewScalarNorm;
  sf::Vector2f walrus2NewVecNorm = normal * walrus2NewScalarNorm;
  sf::Vector2f walrus1NewVecTan = tangent * walrus1ScalarTan;
  sf::Vector2f walrus2NewVecTan = tangent * walrus2ScalarTan;

  playerList[i]->setVel(walrus1NewVecTan + walrus1NewVecNorm);
  playerList[j]->setVel(walrus2NewVecTan + walrus2NewVecNorm);
  // avoid walrus sticking together occasionally
  playerList[i]->tickUpdate(COLLISION_KNOCKBACK_TIME);
  playerList[j]->tickUpdate(COLLISION_KNOCKBACK_TIME);

  // power of collision
  sf::Vector2f velDiff = playerList[i]->getVel() - playerList[j]->getVel();
  float magnitude = sqrt((velDiff.x * velDiff.x) + (velDiff.y * velDiff.y));
  player_bump = magnitude * BUMP_VOL_SCALE * (sfx_volume / 100);
}

void GameLogic::handlePlayerAttack(int attacker, sf::Vector2f dir) {
    float attack_charge;
    if (attacker == 2) {
        p2_attack_handling_in_progress = true;
        attack_charge = walrus2->getAttackCharge();
        walrus1->setVel(walrus1->getVel() + dir * SLASH_ATTACK_POWER * attack_charge);
        walrus1->setStamina(walrus1->getStamina() - ATTACKED_STAMINA_LOST * attack_charge);
        player_hit = sfx_volume * attack_charge;
    } else if (attacker == 1) {
        p1_attack_handling_in_progress = true;
        attack_charge = walrus1->getAttackCharge();
        walrus2->setVel(walrus2->getVel() + dir * SLASH_ATTACK_POWER * attack_charge);
        walrus2->setStamina(walrus2->getStamina() - ATTACKED_STAMINA_LOST * attack_charge);
        player_hit = sfx_volume * attack_charge;
    }
}

void GameLogic::returnToMenu() {
    state = mainMenu;
}

void GameLogic::setSFXVolume(float vol) {
    float tmp = SFX_VOLUME_MAX;
    if (vol > tmp)
        vol = tmp;
    else if (vol <= 0.0)
        vol = 0;
    sfx_volume = vol;

}
void GameLogic::setMusicVolume(float vol) {
    float tmp = MUSIC_VOLUME_MAX;
    if (vol > tmp)
        vol = tmp;
    else if (vol <= 0.0)
        vol = 0;
    music_volume = vol;
}
float GameLogic::getSFXVolume() {
    return sfx_volume;
}
float GameLogic::getMusicVolume() {
    return music_volume;
}
/*
 *1 param: walrus1 died
 * 2 param: walrus2 died
 * */
void GameLogic::handlePlayerDeath(int walrus) {

    //Kill the current walrus
    playerList[walrus]->kill();
    
    //First check to see if everyone is dead. If so then we just reset where we are.
    bool allDead = true;
    for (int i = 0; i < sprites.size(); i++) {
        if (!playerList[i]->isDead()) {
            allDead = false;
        }
    }
    if (allDead) {
        if (sprites.size() == 2) {
            resetGame();
        }
        else {
            begin2v2();
        }
    }

    //check to see if the entire team is dead.
    bool winner = true;
    if (walrus < sprites.size() / 2) {
        for (int i = 0; i < sprites.size() / 2 + 1; i++) {
            if (!playerList[i]->isDead()) {
                winner = false;
            }
        }
    }
    else {
        for (int i = sprites.size() / 2; i < playerList.size(); i++) {
            if (!playerList[i]->isDead()) {
                winner = false;
            }
        }
    }

    if (winner == true) {
        if (progression == 2 || progression == -2) {
            winner1 = false;
            state = gameOverMenu;
        }
    }

    splash = 1.0f;

}

void GameLogic::togglePause() {
  if (state == pauseMenu) {
      state = playing;
  } else if (state == playing) {
      state = pauseMenu;
  }
}

void GameLogic::resetGame() {

    state = playing;
    walrus1->spawn(sf::Vector2f(3 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2));
    walrus2->spawn(sf::Vector2f(5 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2));
    sprites.clear();
    sprites.push_back(walrus1);
    sprites.push_back(walrus1);

    // balance difficulty curve
    if (progression == -1) {
        walrus2->handlePowerUp(1);
    } else if (progression == 1) {
        walrus1->handlePowerUp(1);
    }

}

void GameLogic::begin2v2() {
    state = playing;

    walrus1->spawn(sf::Vector2f(3 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2 - 50));
    walrus2->spawn(sf::Vector2f(3 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2 + 50));
    walrus3->spawn(sf::Vector2f(5 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2 - 50));
    walrus4->spawn(sf::Vector2f(5 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2 + 50));
    sprites.clear();
    sprites.push_back(walrus1);
    sprites.push_back(walrus2);
    sprites.push_back(walrus3);
    sprites.push_back(walrus4);

    if (progression == -1) {
        for (int i = 0; i != playerList.size() / 2; i++) {
            playerList[i]->handlePowerUp(1);
        }
    }
    else if (progression == 1) {
        for (int i = playerList.size() / 2; i < playerList.size(); i++) {
            playerList[i]->handlePowerUp(1);
        }
    }
}

void GameLogic::handleOptionsMenu() {
    state = optionsMenu;
}
void GameLogic::handleStatsMenu() {
    state = statsMenu;
}

void GameLogic::handleHelpMenu() {
  state = helpMenu;
}
void GameLogic::handlePlayerSelectMenu() {
    state = playerSelectMenu;
    //reset stats
    walrus1->resetStats();
    walrus2->resetStats();
    stage->generateMap();
    //reset progression
    progression = 0;
    //reset rounds
    round = 1;
}

void GameLogic::handlePlayerNumberMenu() {
	state = playerNumberMenu;
}

void GameLogic::handleNameTextSubMenu() {
    state = nameTextSubMenu;
}
void GameLogic::handleColorSelectSubMenu() {
    state = colorSelectSubMenu;
}
GameLogic::GameState GameLogic::getState() {
    return state;
}
int GameLogic::getStageProgression() {
    return progression;
}
int GameLogic::getRound(){
    return round;
}
