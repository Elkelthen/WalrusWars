#ifndef _Definitions_H_
#define _Definitions_H_
/* Contains all game variables for easy tweaking and balancing, and all text strings for easy translation */

// window
#define WINDOW_HEIGHT 900.0f //600
#define WINDOW_WIDTH 1200.0f //800
#define APP_TITLE "Walrus Wars"

// collision variables
#define SLASH_ATTACK_POWER 100.0f

#define COLLISION_KNOCKBACK_TIME 0.04f

// this comes from removing the drawing of mass*20 and hitbox of mass*6.5
// 6.5 / 20 == 0.325
#define PLAYER_HITBOX_SCALE 0.325

// basic movement forces
#define DECELERATE_STRENGTH 20.0f
#define ACCELERATE_STRENGTH 500.0f

#define DEAD_MOVEMENT_SCALEDOWN 0.0f
#define RESTING_MOVEMENT_SCALEDOWN 0.2f
#define RAISING_TUSKS_MOVEMENT_SCALEDOWN 0.0f
#define ATTACKING_MOVEMENT_SCALEDOWN 0.2f

// bot
#define NUM_OF_RAYS_CAST 16
#define PI 3.14159265

// powerups
#define FISH_SPEED_BOOST 0.1
#define FISH_MASS_BOOST 8

// stamina
#define MAX_STAMINA 100.0f
#define STAMINA_THRESHOLD (MAX_STAMINA / 4)
#define NORMAL_STAMINA_REGEN_RATE 10
#define RESTING_STAMINA_REGEN_RATE 20
#define FISH_STAMINA_GAINED 20.0f
#define ATTACK_STAMINA_COST 20.0f
#define ATTACKED_STAMINA_LOST 15.0f
#define MOVEMENT_STAMINA_COST_SCALE 30
#define MAX_ATTACK_CHARGE 5.0f

#define INIT_MASS 80.0f

// stage
#define ICE_BLOCKS_WIDTH 40
#define ICE_BLOCKS_HEIGHT 30
#define ICE_BLOCKS_SIZE_X (WINDOW_WIDTH / ICE_BLOCKS_WIDTH)
#define ICE_BLOCKS_SIZE_Y (WINDOW_HEIGHT / ICE_BLOCKS_HEIGHT)

// fish
#define FISH_SIZE 30.0f
#define MAX_NUM_OF_FISH 8

// animations
#define ATTACK_RELEASE_TIMER 0.30f
#define ATTACK_DURATION_TIMER 0.60f

//Abilities
#define BOOST_TIMER 0.25f   //these values are preliminary because I have no idea what they are. Probably hex milliseconds?
#define BOOST_COOLDOWN 3.0f


// text
#define UI_TEXT_SIZE 100

// strings
#define GO_RIGHT "GO ->"
#define GO_LEFT "<- GO"
#define OPTIONS_TITLE_STRING "OPTIONS:"
#define SFX_VOLUME_STRING "SFX Volume: "
#define MUSIC_VOLUME_STRING "Music Volume: "
#define PLAY_STRING "Play"
#define TWO_STRING "Play 2v2"
#define HELP_STRING "Help"
#define OPTIONS_STRING "Options"
#define QUIT_STRING "Quit"
#define REPLAY "Play Again"
#define STATS_TEXT "Stats"
#define MAIN_MENU "Return to Main Menu"
#define P1 "Player 1"
#define P2 "Player 2"
#define P3 "Player 3"
#define P4 "Player 4"
#define BOT "Bot"
#define WON " Won!"
#define KILLS "Kills: "
#define DEATHS "Deaths: "
#define POWERUPS "Powerups: "
#define SLASH_ATTACKS "Slash Attacks: "
#define DIST "Distance (m): "
#define PAUSED "Paused"
#define RESUME "Resume"
#define BACKGROUND_A "Throughout the Arctic, sea ice deteriorates at astonishing rates.\n Global warming poses the biggest threat to walruses in the Arctic\n - their habitat is vanishing!\n\nTwo walruses, "
#define BACKGROUND_B " must fight over scarce land\nand food to claim a suitable location for their families... they must\nforce their competitors off the ice!"
#define CONTROL_INSTRUCTIONS "Player 1 movement = WASD, Player 2 movement = Arrow Keys\n Player 1 attack = LSHIFT, Player 2 attack = RSHIFT"
#define GAME_RULES "Being efficient with your actions to maintain stamina is crucial!\nSlash your opponent to deplete their stamina & eat fish \nto recover your own stamina:\n - Red increases movement speed, Green increases flubber mass\nProgress to the next stage to continue! \nThe first walrus to reach the end wins!"
#define DEFAULT_NAME_1 "Wally"
#define DEFAULT_NAME_2 "Wahlberg"
#define DEFAULT_NAME_3 "Wallace"
#define DEFAULT_NAME_4 "Walter"
#define MAX_INPUT_SIZE 7

//volume
#define SFX_VOLUME_BASE 50.0f
#define MUSIC_VOLUME_BASE 50.0f
#define SFX_VOLUME_MAX 100.0f
#define MUSIC_VOLUME_MAX 100.0f
#define VOLUME_BAR_WIDTH 200.0f

// volume
#define BUMP_VOL_SCALE 0.2f

#endif /* _Definitions_H_ */
