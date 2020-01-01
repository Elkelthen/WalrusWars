#ifndef _CameraView_H_
#define _CameraView_H_

#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "Controller.h"
#include "Animation.h"
#include "SoundManager.h"
#include <memory>

class CameraView {
  public:
    CameraView() = default;
    void init();
    void processInput(sf::RenderWindow &window, GameLogic &logic, float dSec);
    void draw(sf::RenderWindow &window, GameLogic &logic);

  private:
    //Main Menu Objects and Background
    sf::RectangleShape water_object;
    sf::RectangleShape bg;
    std::vector<sf::Text> Buttons;
    int Main_Menu_Index = 0;

    //Twos Menu Objects and Background
    sf::RectangleShape player1_portrait_frame = sf::RectangleShape(sf::Vector2f(325 * WINDOW_WIDTH / 800, 425 * WINDOW_HEIGHT / 800));
    sf::RectangleShape player2_portrait_frame = sf::RectangleShape(sf::Vector2f(325 * WINDOW_WIDTH / 800, 425 * WINDOW_HEIGHT / 800));
    std::vector<sf::Text> Twos_Buttons;
    std::vector<sf::Text> Twos_Players;
    std::vector<std::shared_ptr<Controller> > Twos_Controllers;
    int Twos_Menu_Index = 0;



    void createControllers(int players);

    // draw screen functions
    void drawGame(sf::RenderWindow &window, GameLogic &logic);
    void drawMainMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPauseMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawGameOverMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawOptionsMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawStatsMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawPlayerSelectMenu(sf::RenderWindow &window, GameLogic &logic);
    void drawHelpMenu(sf::RenderWindow &window, GameLogic &logic);
	void drawPlayerNumberMenu(sf::RenderWindow& window, GameLogic& logic);
    void createTwos();
    void menuUp(sf::RenderWindow &window, GameLogic &logic);
    void menuDown(sf::RenderWindow &window, GameLogic &logic);
    void menuLeft(sf::RenderWindow &window, GameLogic &logic);
    void menuRight(sf::RenderWindow &window, GameLogic &logic);
    void menuSelect(sf::RenderWindow &window, GameLogic &logic);

    sf::Font font;
    char main_menu_selection = 'P';
    char options_menu_selection = 'S';
    char game_over_menu_selection = 'P';
    char player1_menu_selection = 'P';
    char pause_menu_selection = 'R';
    char color_selection = '1';
    bool colorSelector = false;
    bool enteringNameText = false;
    //char player2_menu_selection = 'P';

    std::vector<int> playerType;
    std::vector<char*> playerName;

    int player1OrBot = -1; //-1 is bot, 1 is player
    int player2OrBot = -1; //-1 is bot, 1 is player

    // major InputManager classes
    std::shared_ptr<Controller> player1Controller;
    std::shared_ptr<Controller> player2Controller;
    std::shared_ptr<Controller> player3Controller;
    std::shared_ptr<Controller> player4Controller;

    //animations and art
    SoundManager soundManager;
    Animation walrus1_animation;
    Animation walrus2_animation;
	Animation walrus3_animation;
	Animation walrus4_animation;
    Animation roundCounter10_animation;
    Animation roundCounter20_animation;
    Animation walrusSplash_animation;
    Animation water_animation;
    std::list<std::unique_ptr<Animation>> fish_animation_list;
    sf::Texture spriteMapWalrus;
    sf::Texture spriteMapFish;
    sf::Texture menu_background;
    sf::Texture stage_progression;
    sf::Texture stage_progression_active;
    sf::Texture playerPortrait;
    sf::Texture player1Select;
    sf::Texture player2Select;
    sf::Texture playerPortraitFrame;
    sf::Texture nameFrame;
    sf::Texture colorIcon;
    sf::Texture playerNeutralSelect;
    sf::Texture roundCounter10;
    sf::Texture roundCounter20;
    sf::Texture roundCounter;
    sf::Texture walrusSplash;
    sf::Texture water;

    //player names
    std::string walrus1_name_str;
    std::string walrus2_name_str;
    sf::Text walrus1_name;
    sf::Text walrus2_name;
	sf::Text walrus3_name;
	sf::Text walrus4_name;
    sf::Text name;

    //player colors
    sf::Color player_color1 = sf::Color(255,255,255,255);
    sf::Color player_color2 = sf::Color(155,155,155,255);
    sf::Color player_color3 = sf::Color(255,155,155,255);
    sf::Color player_color4 = sf::Color(155,255,155,255);
    sf::Color player_color5 = sf::Color(155,155,255,255);

    sf::RectangleShape ice;
    sf::RectangleShape player1;
    sf::RectangleShape player2;
    sf::RectangleShape player3;
    sf::RectangleShape player4;

    std::vector<sf::RectangleShape> sprites;
	std::vector<Animation> animations;

    sf::CircleShape hitbox;
    sf::CircleShape collision_pt;
    sf::RectangleShape minimapbg;
    sf::CircleShape stage_veil;
    sf::CircleShape attackHitbox;


    //minimap individual stages
    sf::RectangleShape mmStage;
    sf::RectangleShape mmStageR;
    sf::RectangleShape mmStageR2;
    sf::RectangleShape mmStageL;
    sf::RectangleShape mmStageL2;

    sf::RectangleShape mmStagei;
    sf::RectangleShape mmStageRi;
    sf::RectangleShape mmStageR2i;
    sf::RectangleShape mmStageLi;
    sf::RectangleShape mmStageL2i;

    float screenshake_magnitude;
    float screenshake_timer;
    float splash_timer;

    bool debug_mode;
};


#endif
