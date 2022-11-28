#ifndef ASSIST_H
#define ASSIST_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "multirole/multirole.h"
#include "motion/motion.h"

//=-------Global-------=//
extern uint8_t game_status;
extern uint8_t n_active_robot;
static uint16_t game_sub_status;
extern uint8_t n_active_robot;
extern uint8_t style;

//=--------Prep--------=//
bool PreparationKickOffAssist();
//=--------Prep--------=//
void PrepKickoffHomeSingleDef();
void PrepKickoffHomeDoubleDef();
void PrepKickoffHomeTripleDef();
void PrepKickoffHomeQuadrupleDef();

void PrepFreekickHomeSingleDef();
void PrepFreekickHomeDoubleDef();
void PrepFreekickHomeTripleDef();
void PrepFreekickHomeQuadrupleDef();

void PrepGoalkickHomeSingleDef();
void PrepGoalkickHomeDoubleDef();
void PrepGoalkickHomeTripleDef();
void PrepGoalkickHomeQuadrupleDef();

void PrepCornerHomeSingleDef();
void PrepCornerHomeDoubleDef();
void PrepCornerHomeTripleDef();
void PrepCornerHomeQuadrupleDef();

void PrepThrowinHomeSingleDef();
void PrepThrowinHomeDoubleDef();
void PrepThrowinHomeTripleDef();
void PrepThrowinHomeQuadrupleDef();

//=--------Main--------=//
void GameMainSingleDef();
void GameMainDoubleDef();
void GameMainTripleDef();
void GameMainQuadrupleDef();

void GeneralGame();

// =---------Local--------=//
// uint16_t curr_stat;
const float obs1_posx = -260 + 130;
const float obs1_posy = 100;
const float obs2_posx = -150;
const float obs2_posy = 200;
const float obs3_posx = -150;
const float obs3_posy = 300;
// const int vel_trans = 40;
// const int vel_rot = 15;
const int vel_trans = 60 + 5;
const int vel_rot = 16 + 2;
const int vel_prep_trans = 35;
float target_theta_offset = 0;
float target_offset_x = -262;
float target_offset_y = 220;

MachineState curr_stat;
MachineState state_prep_b;

extern int robot_condition[3];
extern short int odometry_robot[3][3];
extern int16_t obs[3];

extern int16_t state_debugger;

bool obs1, obs2, obs3, obs4, obs5, obs6, obs7, obs8;

uint8_t prog_counter = 0;
int16_t theta_counter = 0;

//=--------Main--------=//
void GameMainSingleAssist();
void GameMainDoubleAssist();
void GameMainTripleAssist();
void GameMainQuadrupleAssist();

void GamePassingChallengeA();
void GamePreparationChallengeA();
void GamePassingChallengeB();
void GamePreparationChallengeB();
void GamePassingChallengeC();
void GamePreparationChallengeC();

#endif