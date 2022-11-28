#include "assist/assist.h"

void AssistRun()
{
    enable_icp = 1;
    static uint8_t prev_;
    static uint8_t prev_prep;
    // obs[1] = 3;
    // obs[2] = 3;
    // obs[0] = 3;
    // printf("game_status: %d\n", game_status * robot_base_action);
    // printf("robot-action: %d\n", robot_action);
    // printf("robot_action kawan: %d\n", robot_data[2].state);
    // printf("style: %d\n", style);
    // printf("data ball: %.2f || %.2f || %d\n", ball_on_field[0], ball_on_field[1], ball_status);
    switch (game_status * robot_base_action)
    {
    case 0:
        // game_status = 0;
        // printf("Robot stop\n");
        ManualMotion(0, 0, 0, 3);
        break;

    case status_iddle_2:
        ManualMotion(0, 0, 0, 3);
        break;

    case keyboard_forward:
        ManualMotion(0, 5, 0, 3);
        break;

    case keyboard_backward:
        ManualMotion(0, -5, 0, 3);
        break;

    case keyboard_left:
        ManualMotion(-5, 0, 0, 3);
        break;

    case keyboard_right:
        ManualMotion(5, 0, 0, 3);
        break;

    case keyboard_left_rotation:
        ManualMotion(0, 0, 2, 3);
        break;

    case keyboard_right_rotation:
        ManualMotion(0, 0, -2, 3);
        break;

    case status_preparation_kickoff_home:
        switch (style)
        {
        case 'A':
            GamePreparationChallengeA();
            break;
        case 'B':
            GamePreparationChallengeB();
            break;
        case 'C':
            GamePreparationChallengeC();
            break;
        default:
            break;
        }
        break;
    case status_preparation_freekick_home:
        switch (n_active_robot)
        {
        case 1:
            PrepFreekickHomeSingleDef();
            break;
        case 2:
            PrepFreekickHomeDoubleDef();
            break;
        case 3:
            PrepFreekickHomeTripleDef();
            break;
        case 4:
            PrepFreekickHomeQuadrupleDef();
            break;
        default:
            PrepFreekickHomeSingleDef();
            break;
        }
        break;

    case game_kickoff_home:
        switch (style)
        {
        case 'A':
            GamePassingChallengeA();
            break;
        case 'B':
            GamePassingChallengeB();
            break;
        case 'C':
            GamePassingChallengeC();
            break;
        default:
            break;
        }
        break;

    case game_freekick_home:
        switch (n_active_robot)
        {
        case 1:
            GameMainSingleDef();
            break;
        case 2:
            GameMainDoubleDef();
            break;
        case 3:
            GameMainTripleDef();
            break;
        case 4:
            GameMainQuadrupleDef();
            break;
        default:
            GameMainSingleDef();
            break;
        }
        break;
    case 34:
        GamePassingChallengeA();
        break;
    case 35:
        GamePreparationChallengeA();
        break;
    case 36:
        GamePassingChallengeB();
        break;
    case 37:
        GamePreparationChallengeB();
        break;
    case 38:
        // CatchBallMotion(30, 12);
        // PassBall(2);
        RecieveBall(2);
        // PivotMotion(90, 22);
        // Kick(69, 10, 900);
        break;
    case 39:
        GamePassingChallengeC();
        break;
    case 40:
        GamePreparationChallengeC();
        break;
    }

    // printf("asdasd %d %d\n",game_status,robot_base_action);

    // Reset state every new set piece
    // if (robot_base_action == 0)
    // {
    //     if (ball_status == 2)
    //     {
    //         Kick(10, 50);
    //     }
    // }

    // game_sub_status *= robot_base_action;
    // state_prep_b.value *= robot_base_action;
    // curr_stat.value *= robot_base_action;
    // printf("%d %d %d\n", game_status, robot_base_action, curr_stat.value);
    // printf("curr_stat: %d\n", curr_stat.value);

    if (prev_ != game_status || prev_prep != style)
    {
        printf("asu: %d %d %d %d\n", prev_, game_status, prev_prep, style);
        curr_stat.value = 0;
        state_prep_b.value = 0;
    }

    // Level 0 EN_ICP
    if (Pythagoras(pos_robot[0], pos_robot[1], -270, 220) < 90)
        enable_icp = 0;
    if (pos_robot[1] < 15)
        enable_icp = 0;
    prev_ = game_status;
    prev_prep = style;
}

void PrepKickoffHomeSingleDef()
{
    if (ball_status && Pythagoras(ball_on_field[0], ball_on_field[1], FIELD_X_1_2, FIELD_Y_1_2) < 70)
        game_sub_status = 100;
    switch (game_sub_status)
    {
    case 0:
        printf("prep kickoff home 1 def (0)\n");
        if (MotionToPoint(FIELD_X_1_2, FIELD_Y_1_5, 90, 40, 13))
            game_sub_status = 10;
        break;
    case 10:
        printf("prep kickoff home 1 def (10)\n");
        if (ball_status && Pythagoras(ball_on_field[0], ball_on_field[1], FIELD_X_1_2, FIELD_Y_1_2) < 70)
            game_sub_status = 100;
        else
            game_sub_status = 110;
        break;
    case 100:
        MotionAroundBall(300, 165, 40, 13);
        break;
    case 110:
        MotionAroundPoint(FIELD_X_1_2, FIELD_Y_1_2, 300, 165, 40, 13);
        break;
    }
}
void PrepKickoffHomeDoubleDef()
{
    if (ball_status && Pythagoras(ball_on_field[0], ball_on_field[1], FIELD_X_1_2, FIELD_Y_1_2) < 70)
        game_sub_status = 100;
    switch (game_sub_status)
    {
    case 0:
        printf("prep kickoff home 1 def (0)\n");
        if (MotionToPoint(FIELD_X_1_2, FIELD_Y_1_5, 90, 40, 13))
            game_sub_status = 10;
        break;
    case 10:
        printf("prep kickoff home 1 def (10)\n");
        if (ball_status && Pythagoras(ball_on_field[0], ball_on_field[1], FIELD_X_1_2, FIELD_Y_1_2) < 70)
            game_sub_status = 100;
        else
            game_sub_status = 110;
        break;
    case 100:
        MotionAroundBall(300, 165, 40, 13);
        break;
    case 110:
        MotionAroundPoint(FIELD_X_1_2, FIELD_Y_1_2, 300, 165, 40, 13);
        break;
    }
}
void PrepKickoffHomeTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep kickoff home 3 def\n");
        break;
    }
}
void PrepKickoffHomeQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep kickoff home 4 def\n");
        break;
    }
}

void PrepFreekickHomeSingleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep freekick home 1 def\n");
        break;
    }
}
void PrepFreekickHomeDoubleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep freekick home 2 def\n");
        break;
    }
}
void PrepFreekickHomeTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep freekick home 3 def\n");
        break;
    }
}
void PrepFreekickHomeQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep freekick home 4 def\n");
        break;
    }
}

void PrepGoalkickHomeSingleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Goalkick home 1 def\n");
        break;
    }
}
void PrepGoalkickHomeDoubleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Goalkick home 2 def\n");
        break;
    }
}
void PrepGoalkickHomeTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Goalkick home 3 def\n");
        break;
    }
}
void PrepGoalkickHomeQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Goalkick home 4 def\n");
        break;
    }
}

void PrepCornerHomeSingleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Corner home 1 def\n");
        break;
    }
}
void PrepCornerHomeDoubleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Corner home 2 def\n");
        break;
    }
}
void PrepCornerHomeTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Corner home 3 def\n");
        break;
    }
}
void PrepCornerHomeQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Corner home 4 def\n");
        break;
    }
}

void PrepThrowinHomeSingleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Throwin home 1 def\n");
        break;
    }
}
void PrepThrowinHomeDoubleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Throwin home 2 def\n");
        break;
    }
}
void PrepThrowinHomeTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Throwin home 3 def\n");
        break;
    }
}
void PrepThrowinHomeQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("prep Throwin home 4 def\n");
        break;
    }
}

void GameMainSingleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("game home 1 def (0)\n");
        game_sub_status = 100;
        break;

    case 100:
        printf("game home 1 def (100)\n");
        break;
    }
}

void GameMainDoubleDef()
{
    switch (game_sub_status)
    {
    case 0:
        switch (style)
        {
        case 'A':
            game_sub_status = 100;
            break;
        case 'B':
            game_sub_status = 200;
            break;
        }
        break;

    case 100:
        if (RecieveBall(n_robot_att))
        {
            robot_action = reset_action;
            game_sub_status = 99;
        }
        break;

    case 99:
        GeneralGame();
        break;
    }
}

void GameMainTripleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("game home 3 def\n");

        break;

    case 10:
        printf("masuk Def\n");
        break;
    }
}

void GameMainQuadrupleDef()
{
    switch (game_sub_status)
    {
    case 0:
        printf("game home 4 def\n");

        break;

    case 10:
        printf("masuk Def\n");
        break;
    }
}

void GeneralGame()
{
    printf("Game general\n");
}

bool PreparationKickOffAssist()
{
    switch (game_sub_status)
    {
    case 0:
        if (n_active_robot)
            break;

    case 1:
        printf("aku assist\n");
        break;
    }
}

void GameMainSingleAssist()
{
    printf("%d %d\n", game_sub_status, style);
    switch (game_sub_status)
    {
    case 0:
        switch (style)
        {
        case 0:
            game_sub_status = 10;
            break;
        case 1:
            game_sub_status = 20;
            break;
        }
        break;

    case 10:
        printf("masuk assist\n");
        break;
    }
}

void GameMainDoubleAssist()
{
    switch (game_status)
    {
    case game_kickoff_home:
        printf("masuk game kickoff home\n");
        break;
    }
}

void GameMainTripleAssist()
{
    switch (game_status)
    {
    case game_kickoff_home:
        printf("masuk game kickoff home\n");
        break;
    }
}

void GameMainQuadrupleAssist()
{
    printf("Halo banh Quadruple\n");
}

void GamePreparationChallengeA()
{
    if (ball_status == 2)
    {
        Kick(10, 50);
    }

    // note: 100-10x untuk kasus obs1
    // note: 1000-100x untuk kasus dekat pusat
    // note: 200-20x untuk kasus obs2

    // 175
    const float obs1_7x = 175 + target_offset_x;
    const float obs1_7y = target_offset_y - 20;

    static float l_tol = 0;

    static float buffer_offset_x;
    static float buffer_offset_y;
    static float buffer_distance;

    static float buffer_pos_robot[3];

    printf("prep A curr_stat: %d || obs[1]: %d || obs[2]: %d\n", curr_stat.value, obs[1], obs[2]);
    // printf("Ball pos: %.2f %.2f\n", ball_on_field[0], ball_on_field[1]);

    printf("pos robot: %.2f || %.2f || %.2f\n", pos_robot[0], pos_robot[1], pos_robot[2]);

    state_debugger = curr_stat.value;
    // switch (curr_stat.value)
    // {
    // case 0:
    //     // static float pos_x_offset;
    //     // static float pos_y_offset;

    //     // pos_x_offset = ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
    //     // pos_y_offset = ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

    //     // printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
    //     // printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
    //     // if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 35)
    //     // {
    //     //     printf("Aktif offsettt\n");
    //     //     // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
    //     //     SetPosXoffset(pos_x_offset);
    //     //     SetPosYoffset(pos_y_offset);
    //     //     buzzer2(10, 10);
    //     // }

    //     if ((obs[1] == 1 || obs[2] == 1) && (obs[1] == 2 || obs[2] == 2))
    //     {
    //         curr_stat.value = 1234; // case untuk obstacle di posisi 2
    //     }
    //     // apabila obstacle di posisi 1 true jalankan perintah dibawah
    //     // obs1 = true;
    //     else if (obs[1] == 1 || obs[2] == 1)
    //     {
    //         if (Pythagoras(pos_robot[0], pos_robot[2], 0, 0) < 30)
    //         { // apabila posisi robot dekat dengan titik start challenge
    //             curr_stat.value = 5000;
    //         }
    //         else
    //         {
    //             curr_stat.value = 500; // case untuk obstacle di posisi 1
    //         }
    //     }
    //     // apabila obstacle di posisi 2 true jalankan perintah dibawah
    //     // obs2 = true;
    //     else if (obs[1] == 2 || obs[2] == 2)
    //     {
    //         // if(Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100){ // apabila posisi robot dekat dengan titik start challenge
    //         //     curr_stat.value = 1000
    //         l_tol = Pythagoras(pos_robot[0], pos_robot[1], obs2_posx, obs2_posy) * 0.62;
    //         curr_stat.value = 600; // case untuk obstacle di posisi 2
    //     }
    //     // if(Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 100){
    //     //     curr_stat.value = 101;
    //     // }

    //     // curr_stat.value = 101;

    //     else if ((obs[2] == 7 && obs[1] == 3) || (obs[2] == 7 && obs[1] == 4) || (obs[2] == 7 && obs[1] == 5))
    //     {
    //         printf("masuk case 501 soko kene\n");
    //         curr_stat.value = 501;
    //     }
    //     else if (pos_robot[0] < -130)
    //     {
    //         curr_stat.value = 601;
    //     }
    //     else
    //     {
    //         printf("masuk case 501 soko else\n");
    //         curr_stat.value = 501;
    //     }

    //     if (pos_robot[1] < 100)
    //     {
    //         printf("mosok gk melbu\n");
    //         curr_stat.value = 700;
    //     }

    //     if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 100)
    //     {
    //         curr_stat.value = 601;
    //     }

    //     // if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 50)
    //     // {
    //     //     curr_stat.value = 99;
    //     // }

    //     // curr_stat.value = 600;

    //     break;
    // case 500:
    //     if (Pythagoras(pos_robot[0], pos_robot[1], obs1_posx, obs1_posy) < 30)
    //     { // saat robot terlalu dekat dengan obstacle 1
    //         curr_stat.value = 6000;
    //     }
    //     else
    //     { // apabila robot tidak dekat dengan obstacle 1 maka nge L ke titik obstacle 2
    //         if (MotionToPoint(-260 + 175, 230, target_theta_offset, vel_trans + 10, vel_rot))
    //         {
    //             curr_stat.value = 501;
    //         }
    //         if (Pythagoras(pos_robot[0], pos_robot[1], -260 + 190, 210) < 50)
    //         {
    //             curr_stat.value = 501;
    //         }
    //     }

    //     break;
    // case 501:
    //     if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
    //     { // apabila sudah nge L dan sampai pada posisi maka return true
    //         curr_stat.value = 99;
    //     }
    //     break;
    // case 5000:
    //     if ((obs[1] == 1 || obs[2] == 1))
    //     { // apabila obs1 true dan jarak terlalu dekat dengannya maka
    //         curr_stat.value = 5001;
    //     }
    //     else
    //     { // apabila robot dekat titik start tapi tidak dekat obs 1 dan obs1 tidak ada maka lanjut case 1002
    //         curr_stat.value = 5002;
    //     }
    //     break;
    // case 5001:
    //     if (MotionToPoint(-240, 0 - 20, target_theta_offset, vel_trans + 10, vel_rot))
    //     { // apabila dekat obs1 maka gerak menuju ke tiitk tersebut dan kemudian nge L masuk case 1003
    //         curr_stat.value = 5003;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -220, 0) < 40)
    //     {
    //         curr_stat.value = 5003;
    //     }
    //     break;
    // case 5002:
    //     if (MotionToPoint(-150 + 20, 100, target_theta_offset, vel_trans + 10, vel_rot))
    //     {
    //         curr_stat.value = 5002;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -110, 80) < 50)
    //     {
    //         curr_stat.value = 5002;
    //     }
    // case 5003:
    //     if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
    //     {
    //         curr_stat.value = 99;
    //     }
    //     break;
    // case 5004:
    //     if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
    //     {
    //         curr_stat.value = 99;
    //     }
    //     break;
    // // lanjutan dari case 100 jika pos robot dekat obstacle 1
    // case 6000:
    //     if (MotionToPoint(-100, 160, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
    //     { // lakukan nge L dan menuju posisi -150 dan 200
    //         curr_stat.value = 6001;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -100, 160) < 30)
    //     {
    //         curr_stat.value = 6001;
    //     }
    //     break;
    // case 6001:
    //     if (MotionToPoint(-150, 200, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
    //     { // persiapan nge L menuju target offset
    //         curr_stat.value = 501;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -150, 200) < 30)
    //     {
    //         curr_stat.value = 501;
    //     }
    //     break;
    // case 600:
    //     if (MotionToPoint(-100, 50, target_theta_offset, vel_trans + 10, vel_rot))
    //     {
    //         curr_stat.value = 601;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -120, 60) < l_tol)
    //     {
    //         curr_stat.value = 601;
    //     }
    //     break;
    // case 601:
    //     if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
    //     {
    //         curr_stat.value = 99;
    //     }
    //     break;
    // case 602:
    //     break;
    // case 1234:
    //     if (MotionToPoint(-150, 320, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
    //     {
    //         curr_stat.value = 601;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -150, 320) < l_tol + 50)
    //     {
    //         curr_stat.value = 601;
    //     }
    //     break;
    // case 700:
    //     if (MotionToPoint(-150, 0, 0, vel_trans, vel_rot))
    //     {
    //         curr_stat.value = 701;
    //     }
    //     break;
    // case 701:
    //     if (MotionToPoint(-240, 20, 0, vel_prep_trans, vel_rot))
    //     {
    //         curr_stat.value = 702;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -230, 10) < 40)
    //     {
    //         curr_stat.value = 702;
    //     }
    //     break;
    // case 702:
    //     if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_prep_trans, vel_rot))
    //     {
    //         curr_stat.value = 99;
    //     }
    //     break;
    // }

    // if (curr_stat.value == 99)
    // {
    //     ManualMotion(0, 0, 0, 3);
    //     // curr_stat.value = 0;
    // }

    switch (curr_stat.value)
    {

    case 0:
        // Tak gae dadi else if
        // if (ball_status == 2)
        // {
        //     Kick(10, 50);
        // }

        // apabila ada obs di 1 dan 2, muter lewat bawah
        if ((obs[1] == 1 || obs[2] == 1) && (obs[1] == 2 || obs[2] == 2))
        {
            curr_stat.value = 321;
        }
        // else if ((obs[1] == 1 || obs[2] == 1) && (obs[1] == 3 || obs[2] == 3))
        // {
        //     buffer_pos_x = pos_robot[0];
        //     curr_stat.value = 432;
        // }
        // apabila obstacle di posisi 1 true jalankan perintah dibawah
        // obs1 = true;
        else if ((obs[1] == 1 || obs[2] == 1))
        {
            // if(Pythagoras(pos_robot[0], pos_robot[2], 0, 0) < 30){ // apabila posisi robot dekat dengan titik start challenge
            //     curr_stat.value = 5000;
            // }else{
            curr_stat.value = 500; // case untuk obstacle di posisi 1
            // }
        }
        // apabila obstacle di posisi 2 true jalankan perintah dibawah
        // obs2 = true;, muter lewat atas
        else if (obs[1] == 2 || obs[2] == 2 && pos_robot[1] < 220)
        {
            // if(Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100){ // apabila posisi robot dekat dengan titik start challenge
            //     curr_stat.value = 1000
            l_tol = Pythagoras(pos_robot[0], pos_robot[1], obs2_posx, obs2_posy) * 0.62;
            buffer_pos_robot[0] = pos_robot[0];
            buffer_pos_robot[1] = pos_robot[1];
            curr_stat.value = 600; // case untuk obstacle di posisi 2
        }
        // if(Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 100){
        //     curr_stat.value = 101;
        // }

        // curr_stat.value = 101;

        // if((obs[2] == 7 && obs[1] == 3) || (obs[2] == 7 && obs[1] == 4) || (obs[2] == 7 && obs[1] == 5)){
        //     printf("masuk case 501 soko kene\n");
        //     curr_stat.value = 501;
        // }

        // asdasd

        // langsung
        else if ((obs[1] != 1 && obs[2] != 1 && obs[1] != 2 && obs[1] != 2) && pos_robot[1] < 250)
        {
            curr_stat.value = 601;
        }
        else if ((obs[1] == 2 || obs[2] == 2) && pos_robot[1] < 190)
        {
            buffer_pos_robot[0] = pos_robot[0];
            buffer_pos_robot[1] = pos_robot[1];
            curr_stat.value = 800;
        }
        else if (obs[1] == 3 || obs[2] == 3)
        {
            buffer_pos_robot[0] = pos_robot[0];
            curr_stat.value = 300;
        }
        else if ((obs[1] == 2 || obs[2] == 2) && pos_robot[1] > 220)
        {
            buffer_pos_robot[0] = pos_robot[0];
            curr_stat.value = 220;
        }

        // Safety, digawe langsung ae
        else
        {
            curr_stat.value = 601;
        }

        // iki nggo misal keadaan robot nde endi endi
        // else {
        //     curr_stat.value = 501;
        // }

        if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 120)
        {
            curr_stat.value = 601;
        }
        // if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 110)
        // {
        //     curr_stat.value = 999;
        // }

        if (pos_robot[1] < 100 && (obs[1] == 1 || obs[2] == 1))
        {
            buffer_pos_robot[0] = pos_robot[0];
            curr_stat.value = 700;
        }

        break;
    case 220:
        if (MotionToPoint(buffer_pos_robot[0], 300, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 221;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 300) < 50)
        {
            curr_stat.value = 221;
        }
        break;
    case 221:
        if (MotionToPoint(-220, 270, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 270) < 50)
        {
            curr_stat.value = 501;
        }
        break;
    case 300:
        if (MotionToPoint(buffer_pos_robot[0], 180, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 180) < 70)
        {
            curr_stat.value = 601;
        }
        break;
    case 500:
        // if(Pythagoras(pos_robot[0], pos_robot[1], obs1_posx, obs1_posy) < 30){ // saat robot terlalu dekat dengan obstacle 1
        //     curr_stat.value = 6000;
        // }
        // else{ // apabila robot tidak dekat dengan obstacle 1 maka nge L ke titik obstacle 2
        if (MotionToPoint(-260 + 165, 230 - 30, target_theta_offset, vel_trans, vel_rot))
        {
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -260 + 165, 230 - 30) < 50)
        {
            curr_stat.value = 501;
        }
        // }

        break;
    case 501:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        { // apabila sudah nge L dan sampai pada posisi maka return true
            curr_stat.value = 999;
        }
        break;
    case 5000:
        if ((obs[1] == 1 || obs[2] == 1))
        { // apabila obs1 true dan jarak terlalu dekat dengannya maka
            curr_stat.value = 5001;
        }
        else
        { // apabila robot dekat titik start tapi tidak dekat obs 1 dan obs1 tidak ada maka lanjut case 1002
            curr_stat.value = 5002;
        }
        break;
    case 5001:
        if (MotionToPoint(-240, 0 - 20, target_theta_offset, vel_trans + 10, vel_rot))
        { // apabila dekat obs1 maka gerak menuju ke tiitk tersebut dan kemudian nge L masuk case 1003
            curr_stat.value = 5003;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 0) < 40)
        {
            curr_stat.value = 5003;
        }
        break;
    case 5002:
        if (MotionToPoint(-150 + 20, 100, target_theta_offset, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 5002;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -110, 80) < 50)
        {
            curr_stat.value = 5002;
        }
    case 5003:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    case 5004:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    // lanjutan dari case 100 jika pos robot dekat obstacle 1
    case 6000:
        if (MotionToPoint(-100, 160, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
        { // lakukan nge L dan menuju posisi -150 dan 200
            curr_stat.value = 6001;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -100, 160) < 30)
        {
            curr_stat.value = 6001;
        }
        break;
    case 6001:
        if (MotionToPoint(-150, 200, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
        { // persiapan nge L menuju target offset
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -150, 200) < 30)
        {
            curr_stat.value = 501;
        }
        break;
    case 600:
        // if (MotionToPoint(-250, point_k_y, target_theta_offset, vel_trans + 10, vel_rot))
        // {
        //     curr_stat.value = 601;
        // }
        // if (Pythagoras(pos_robot[0], pos_robot[1], -230, point_k_y-10) < l_tol)
        // {
        //     curr_stat.value = 601;
        // }
        if (MotionToPoint(buffer_pos_robot[0], 100, 0, vel_prep_trans, vel_rot - 4))
        {
            buffer_pos_robot[1] = pos_robot[1];
            curr_stat.value = 601;
        }
        // if (pos_robot[1] < 85)
        // {
        //     curr_stat.value = 601;
        // }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 100) < 70)
        {
            buffer_pos_robot[1] = pos_robot[1];
            curr_stat.value = 601;
        }
        break;
    case 601:
        if (MotionToPoint(-240, pos_robot[1], 0, vel_trans, vel_rot))
        {
            curr_stat.value = 6020;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -240, pos_robot[1]) < 70)
        {
            curr_stat.value = 6020;
        }
        break;
    case 6020:
        // buffer_theta = pos_robot[2];
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans - 10, vel_rot))
        {
            // SetOffsetRobot(pos_robot[0], pos_robot[1], pos_robot[2] + 2);
            curr_stat.value = 999;
        }
        break;
    case 321:
        if (MotionToPoint(-77, 190, 0, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 322;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -77, 190) < 110)
        {
            curr_stat.value = 322;
        }
        break;
    case 322:
        // if (pos_robot[0] < -120)
        // {
        //     curr_stat.value = 601;
        // }
        // if (MotionAroundPointAngle(-150, 150, 50, -45, 0, vel_trans, vel_rot))
        // {
        //     curr_stat.value = 601;
        // }
        if (MotionToPoint(-120, 320, target_theta_offset, vel_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -120, 300) < 100)
        {
            curr_stat.value = 601;
        }
        break;
    case 432:
        if (MotionToPoint(pos_robot[0], 200, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        break;
    case 543:
        if (MotionToPoint(-180, 350, 90, vel_prep_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 601;
        }
        if (pos_robot[0] < -170)
        {
            curr_stat.value = 601;
        }
        break;
    case 5431:
        break;
    case 700:
        if (MotionToPoint(buffer_pos_robot[0], 15, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 701;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 20) < 50)
        {
            curr_stat.value = 701;
        }
        break;
    case 701:
        if (MotionToPoint(-220, 30, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 702;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 30) < 70)
        {
            curr_stat.value = 702;
        }
        break;
    case 702:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            curr_stat.value = 999;
        }
        break;
    case 800:
        if (MotionToPoint(buffer_pos_robot[0], 70, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 801;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 70) < 50)
        {
            curr_stat.value = 801;
        }
        break;
    case 801:
        if (MotionToPoint(-220, 80, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 702;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 80) < 50)
        {
            curr_stat.value = 702;
        }
        break;
    }

    if (curr_stat.value == 999)
    {
        ManualMotion(0, 0, 0, 3);
    }
}

void GamePassingChallengeA()
{
    // point robot sendiri
    float point_i_x = -60;
    float point_i_y = -15;
    float point_k_x = -60 + 10;
    float point_k_y = 100 - 10;
    float center_x = 0;
    float center_y = 0;

    // point robot kawan
    float point_j_x = 100 + 20;
    float point_j_y = 60 - 30;
    float point_l_x = 100;
    float point_l_y = 160;

    int target = 2;

    curr_stat.reentry(0, 1);
    // robot_data[2].state = is_receiving;
    // robot_data[2].pos_x = 100;
    // robot_data[2].pos_y = 60;

    const float obs1_7x = 175 + target_offset_x;
    const float obs1_7y = target_offset_y - 20;

    static float l_tol = 0;

    static float buffer_offset_x;
    static float buffer_offset_y;
    static float buffer_distance;

    int16_t friend_robot_x = robot_data[target].pos_x;
    int16_t friend_robot_y = robot_data[target].pos_y;

    static float buffer_theta;
    static float buffer_pos_x;
    static float buffer_pos_y;
    // safety_pass_ball.SafetyInit(&curr_stat);

    // obssss
    static obs_t obs_1_real;
    static obs_t obs_2_real;

    obs_1_real = ObstacleChecking(RobotAngletoPoint(-150, 100), 10, 150);
    obs_2_real = ObstacleChecking(RobotAngletoPoint(-150, 200), 10, 150);

    printf("curr_status game style A: %d || obs: %d %d\n", curr_stat.value, obs[1], obs[2]);
    printf("status kawan: %d\n", robot_data[2].state);
    printf("status saya: %d\n", robot_action);
    printf("STATUS BOLA: %d\n", ball_status);
    printf("posisi: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
    printf("real_obs: %.2f %.2f | %.2f %.2f\n", obs_1_real.pos_x, obs_1_real.pos_y, obs_2_real.pos_x, obs_2_real.pos_y);

    state_debugger = curr_stat.value;

    switch (curr_stat.value)
    {
    case 0:
        // static float offset_ball_x_start_a = 13;
        // static float offset_ball_y_start_a = -11;

        // if(Pythagoras(ball_on_field[0],ball_on_field[1],offset_ball_x_start_a,offset_ball_y_start_a)< 30){
        //     printf("offset bola: %.2f %.2f\n",ball_on_field[0],ball_on_field[1]);
        //     buzzer2(10, 10);
        //     SetOffsetRobot(offset_ball_x_start_a - ball_on_field[0] + pos_robot[0],offset_ball_y_start_a - ball_on_field[1]   + pos_robot[1],pos_robot[2]);
        // }
        // it has to be kalibration
        robot_action = 0; // tidak siap untuk mengumpan maupun menerima umpan
        // SetOffsetRobot(target_offset_x, target_offset_y, target_theta_offset);

        // iki tak comment
        if (obs[1] == 1 || obs[2] == 1)
        {
            curr_stat.value = 100;
        }
        else
        {
            curr_stat.value = 1;
        }

        // curr_stat.value = 99;

        // safety_pass_ball.Timeout(123,3);

        break;
    case 1:
        // / motion L
        if (MotionToPoint(-200, 50, 0, vel_trans + 20, vel_rot))
        {
            curr_stat.value = 101;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -240, 70) < 115) // asline 100, tak ganti
        {
            curr_stat.value = 101;
        }
        break;
    case 100:
        // motion L obs 1
        if (MotionToPoint(-240, 20, 0, vel_trans + 20, vel_rot))
        {
            curr_stat.value = 1011;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -260, 40) < 140) // asline 70, tak ganti
        {
            curr_stat.value = 1011;
        }
        break;
    case 101:
        // apabila sudah sampai ke titik siap umpan maka berhenti terlebih dahulu
        if (MotionToPoint(point_i_x, point_i_y, 0, vel_trans + 10, vel_rot + 4))
        {
            // robot_action = is_passing;
            // ManualMotion(0, 0, 0, 3);
            // curr_stat.value = 103;
            // curr_stat.value = 1011;
            curr_stat.value = 104;
        }
        // printf("sudut target: %.2f\n", atan2(60-0,100-0)*RAD2DEG);

        //         // apabila sudah sampai ke titik siap umpan maka berhenti terlebih dahulu
        // if(MotionAroundPoint(0,0,30,atan2(60-0,100-0)*RAD2DEG,vel_trans,vel_rot)){
        //     robot_action = is_passing;
        //     // ManualMotion(0, 0, 0, 3);
        //     curr_stat.value = 103;
        // }
        if (Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100)
        {
            // robot_action = is_passing;
            // curr_stat.value = 103;
            // curr_stat.value = 1011;
            curr_stat.value = 104;
        }
        break;
    case 1011:
        // apabila sudah sampai ke titik siap umpan maka berhenti terlebih dahulu
        if (MotionToPoint(point_i_x, point_i_y + 10, RobotAngletoPoint(0, 0), vel_trans + 5, vel_rot + 5))
        {
            // curr_stat.value = 103;
            curr_stat.value = 104;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100)
        {
            // curr_stat.value = 103;
            curr_stat.value = 104;
        }
        break;
    case 103:
        // static int8_t ball_x_offset = 19;
        // static int8_t ball_y_offset = 5;

        // static int8_t ball_x_offset = 0;
        // static int8_t ball_y_offset = -1;
        // if (Pythagoras(ball_on_field[0], ball_on_field[1], ball_x_offset, ball_y_offset) < 60)
        // {
        //     printf("offset bola: %.2f %.2f\n", ball_on_field[0], ball_on_field[1]);
        //     buzzer2(10, 10);
        //     SetOffsetRobot(ball_x_offset - ball_on_field[0] + pos_robot[0], ball_y_offset - ball_on_field[1] + pos_robot[1], pos_robot[2]);
        // }
        static float pos_x_offset;
        static float pos_y_offset;

        pos_x_offset = 0 + ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        pos_y_offset = -1 + ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 80)
        {
            printf("Aktif offsettt\n");
            // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
            SetPosXoffset(pos_x_offset);
            SetPosYoffset(pos_y_offset);
            buzzer2(10, 10);
        }

        curr_stat.value = 1040;

        break;
    case 1040:
        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, 18);
        if (robot_data[2].state == is_receiving)
        {
            //     // safety_pass_ball.ResetUptimeTimeout();
            //     curr_stat.resetUptimeTimeout();
            //     // CatchBallMotion(vel_trans-5, vel_rot);
            //     // LeadBallMotion(vel_trans-5, vel_rot); // misal pada pass ball tidak terdapat motion kejar bola

            curr_stat.value = 104;
        }

        // curr_stat.value = 104;
        break;
    case 104:
        // robot_action = is_passing;
        if (PassBall(2, 6, 0))
        {
            robot_action = 0;
            // ManualMotion(0,0,0,3);
            // robot_data[2].state = is_passing; //  iki nggo nyoba dewe
            if (obs[1] == 4 || obs[2] == 4)
            {
                curr_stat.value = 144;
            }
            else
            {
                curr_stat.value = 105;
            }
        }
        // printf("ball: %.2f || %.2f\n", ball_on_field[0], ball_on_field[1]);
        // if(MotionToPoint(center_x, center_y, RobotAngletoPoint(100, 60), vel_trans, vel_rot)){
        //     curr_stat.value = 300;
        // }
        // safety_pass_ball.Timeout(1000, 5);

        break;
    // case 300:
    //     // if(ball_status == 2){
    //         Kick(69, 8, 800);
    //         curr_stat.value = 105;
    //     // }
    //     break;
    case 144:
        if (MotionToPoint(point_k_x - 45, point_k_y + 20, RobotAngletoPoint(point_j_x, point_j_y), vel_trans, vel_rot))
        {
            curr_stat.resetUptimeTimeout();
            // robot_action = is_receiving;
            // curr_stat.value = 107;
            curr_stat.value = 106;
            // curr_stat.value = 99;
        }

        if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 45, point_k_y + 20) < 20)
        {
            // robot_action = is_receiving;
            curr_stat.value = 106;
        }

        if (robot_data[2].state == is_passing)
        {
            curr_stat.value = 107;
        }
        break;
    case 105:
        // if (n_has_ball == 2)
        // {
        //     robot_action = 0;
        // }
        // robot_data[2].state = is_passing; // iki nggo nyoba dewe
        if (MotionToPoint(point_k_x - 35, point_k_y + 20, RobotAngletoPoint(point_j_x, point_j_y), vel_trans, vel_rot))
        {
            curr_stat.resetUptimeTimeout();
            // robot_action = is_receiving;
            // curr_stat.value = 107;
            curr_stat.value = 106;
            // curr_stat.value = 99;
        }

        if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 35, point_k_y + 20) < 20)
        {
            // robot_action = is_receiving;
            curr_stat.value = 106;
        }

        if (robot_data[2].state == is_passing)
        {
            curr_stat.value = 107;
        }
        break;
    case 106:
        // robot_action = is_receiving;
        // if(robot_data[2].state == is_passing && ball_status){
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), vel_trans, vel_rot)){
        //         // safety_pass_ball.ResetUptimeTimeout();
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 107;
        //     }
        // }
        // else if(robot_data[2].state == is_passing && !ball_status){
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoRobot(2), vel_trans, vel_rot)){
        //         // safety_pass_ball.ResetUptimeTimeout();
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 107;
        //     }
        // }
        // else{
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoRobot(2), vel_trans, vel_rot)){
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 107;
        //     }
        // }

        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, vel_rot);

        // || n_has_ball == 0 -> sebelume ada case ini
        // if (robot_data[2].state == is_passing)
        // {
        //     robot_action = is_receiving;
        //     curr_stat.value = 107;
        // }

        // Males gawe status status an
        if (n_has_ball == 0 && robot_data[2].state == is_passing)
        {
            // robot_action = is_receiving;
            curr_stat.value = 107;
        }
        break;
    case 107:
        // robot_action = 0;
        if (RecieveBall(2))
        {
            // robot_action = 0;
            // curr_stat.value = 99;

            if (obs[1] == 4 || obs[2] == 4)
            {
                if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 45, point_k_y + 20) > 45 || (Pythagoras(pos_robot[0], pos_robot[1], robot_data[2].pos_x, robot_data[2].pos_y) < 100))
                {
                    curr_stat.value = 1231;
                }
                else
                {
                    curr_stat.value = 109;
                }
            }
            else
            {
                if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 35, point_k_y + 20) > 45 || (Pythagoras(pos_robot[0], pos_robot[1], robot_data[2].pos_x, robot_data[2].pos_y) < 100))
                {
                    curr_stat.value = 123;
                }
                else
                {
                    curr_stat.value = 110;
                }
            }

            // else
            // {
            //     // curr_stat.value = 109;
            //     if (obs[1] == 4 || obs[2] == 4)
            //     {
            //         // robot_action = is_passing;
            //         curr_stat.value = 109;
            //     }
            //     else
            //     {
            //         curr_stat.value = 110;
            //     }
            // }
        }
        // safety_pass_ball.Timeout(2000, 5);
        // curr_stat.timeout(106, 8); // Opo 106?, tak komen
        break;
    case 108:
        // robot_action = 0;
        if (obs[1] == 1 || obs[2] == 1)
        {
            curr_stat.value = 123;
        }
        if (MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(point_l_x, point_l_y), vel_trans, vel_rot, normal_obstacle))
        {
            // robot_action = is_passing;
            curr_stat.resetUptimeTimeout();
            curr_stat.value = 110;
            // curr_stat.value = 109;
        }
        break;
    case 1231:
        if (MotionToPoint(point_k_x - 35, point_k_y + 20, RobotAngletoRobot(2) - 2, vel_trans - 20, vel_rot))
        {
            curr_stat.resetUptimeTimeout();
            // curr_stat.value = 109;
            // robot_action = is_passing;
            curr_stat.value = 110;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 35, point_k_x + 20) < 40)
        {
            curr_stat.value = 110;
            // curr_stat.value = 109;
        }
        break;
    case 123:
        // if (MotionToPoint(point_k_x - 50, point_k_y, RobotAngletoPoint(point_l_x, point_l_x), vel_trans, vel_rot))
        // {
        //     // curr_stat.resetUptimeTimeout();
        //     curr_stat.value = 109;
        //     robot_action = is_passing;
        //     // curr_stat.value = 110;
        // }

        // tak ganti iki
        // robotangletorobot(2)-2 -> awale sudute iki
        if (MotionToPoint(point_k_x - 35, point_k_y + 20, RobotAngletoRobot(2) - 2, vel_trans - 20, vel_rot))
        {
            curr_stat.resetUptimeTimeout();
            // curr_stat.value = 109;
            // robot_action = is_passing;
            curr_stat.value = 110;
        }
        // coba
        if (Pythagoras(pos_robot[0], pos_robot[1], point_k_x - 35, point_k_x + 10) < 40)
        {
            curr_stat.value = 110;
            // curr_stat.value = 109;
        }
        break;
    case 109:
        PivotMotion(RobotAngletoRobot(2), 20);
        if (robot_data[2].state == is_receiving)
        {
            robot_action = is_passing;
            //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoRobot(2), vel_trans, vel_rot)){
            curr_stat.value = 110;
            //     }
        }
        // curr_stat.timeout(1090, 4);
        break;
    case 1090:
        if (ball_status == 2)
        {
            Kick(69, 6, 900);
            curr_stat.value = 99;
        }
        break;
    case 110:
        if (PassBall(2, 6, -2))
        {
            if (obs[1] != 4 && obs[2] != 4)
            {
                // robot_action = 10;
                // ga lapo-lapo soale gasido resete kecepeten cok
            }
            // robot_action = 10;
            curr_stat.value = 99;
        }
        // curr_stat.timeout(123, 10);
        break;
    case 1000:
        // bola terlepas dari robot
        if (ball_status == 1)
        {
            // robot_action = 0;
            LeadBallMotion(vel_trans - 5, vel_rot);
            curr_stat.value = 1001;
        }
        break;
    case 1001:
        if (MotionToPoint(point_i_x, point_i_y, RobotAngletoRobot(2), vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 104;
        }
        break;
    case 2000:
        // ketika bola terlepas dari robot
        if (ball_status == 1)
        {
            // robot_action = 0;
            LeadBallMotion(vel_trans - 5, vel_rot);
            curr_stat.value = 2001;
        }
        break;
    case 2001:
        if (MotionToPoint(point_k_x, point_k_y, RobotAngletoRobot(2), vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 108;
        }
        break;

        // case 99:
        //     // GamePreparationChallengeA();
        //     if(MotionToPoint(target_offset_x, target_offset_y, 0, vel_trans, vel_rot, normal_obstacle)){
        //         curr_stat.value = 999;
        //     }
        //     break;

    case 99:

        if (ball_status == 2)
        {
            curr_stat.value = 110;
        }
        // Tak gae dadi else if

        if ((obs[1] == 4 || obs[2] == 4))
        {
            robot_action = 0;
        }
        // apabila ada obs di 1 dan 2, muter lewat bawah
        if ((obs[1] == 1 || obs[2] == 1) && (obs[1] == 2 || obs[2] == 2))
        {
            curr_stat.value = 321;
        }
        // else if ((obs[1] == 1 || obs[2] == 1) && (obs[1] == 3 || obs[2] == 3))
        // {
        //     buffer_pos_x = pos_robot[0];
        //     curr_stat.value = 432;
        // }
        // apabila obstacle di posisi 1 true jalankan perintah dibawah
        // obs1 = true;
        else if ((obs[1] == 1 || obs[2] == 1))
        {
            // if(Pythagoras(pos_robot[0], pos_robot[2], 0, 0) < 30){ // apabila posisi robot dekat dengan titik start challenge
            //     curr_stat.value = 5000;
            // }else{
            curr_stat.value = 500; // case untuk obstacle di posisi 1
            // }
        }
        // apabila obstacle di posisi 2 true jalankan perintah dibawah
        // obs2 = true;, muter lewat atas
        else if (obs[1] == 2 || obs[2] == 2)
        {
            // if(Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100){ // apabila posisi robot dekat dengan titik start challenge
            //     curr_stat.value = 1000
            l_tol = Pythagoras(pos_robot[0], pos_robot[1], obs2_posx, obs2_posy) * 0.62;
            buffer_pos_x = pos_robot[0];
            buffer_pos_y = pos_robot[1];
            curr_stat.value = 600; // case untuk obstacle di posisi 2
        }
        // if(Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 100){
        //     curr_stat.value = 101;
        // }

        // curr_stat.value = 101;

        // if((obs[2] == 7 && obs[1] == 3) || (obs[2] == 7 && obs[1] == 4) || (obs[2] == 7 && obs[1] == 5)){
        //     printf("masuk case 501 soko kene\n");
        //     curr_stat.value = 501;
        // }

        // langsung
        else if ((obs[1] != 1 && obs[1] != 2 && obs[1] != 3) || obs[1] == 3)
        {
            curr_stat.value = 601;
        }

        // Safety, digawe langsung ae
        else
        {
            curr_stat.value = 601;
        }
        // coba nde kene

        // iki nggo misal keadaan robot nde endi endi
        // else {
        //     curr_stat.value = 501;
        // }

        if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 120)
        {
            curr_stat.value = 601;
        }
        // if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 110)
        // {
        //     curr_stat.value = 999;
        // }

        break;
    case 500:
        // if(Pythagoras(pos_robot[0], pos_robot[1], obs1_posx, obs1_posy) < 30){ // saat robot terlalu dekat dengan obstacle 1
        //     curr_stat.value = 6000;
        // }
        // else{ // apabila robot tidak dekat dengan obstacle 1 maka nge L ke titik obstacle 2
        if (MotionToPoint(-260 + 165, 200, target_theta_offset, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -260 + 175, 220) < 70)
        {
            curr_stat.value = 501;
        }
        // }

        break;
    case 501:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        { // apabila sudah nge L dan sampai pada posisi maka return true
            curr_stat.value = 999;
        }
        break;
    case 5000:
        if ((obs[1] == 1 || obs[2] == 1))
        { // apabila obs1 true dan jarak terlalu dekat dengannya maka
            curr_stat.value = 5001;
        }
        else
        { // apabila robot dekat titik start tapi tidak dekat obs 1 dan obs1 tidak ada maka lanjut case 1002
            curr_stat.value = 5002;
        }
        break;
    case 5001:
        if (MotionToPoint(-240, 0 - 20, target_theta_offset, vel_trans + 10, vel_rot))
        { // apabila dekat obs1 maka gerak menuju ke tiitk tersebut dan kemudian nge L masuk case 1003
            curr_stat.value = 5003;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 0) < 40)
        {
            curr_stat.value = 5003;
        }
        break;
    case 5002:
        if (MotionToPoint(-150 + 20, 100, target_theta_offset, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 5002;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -110, 80) < 50)
        {
            curr_stat.value = 5002;
        }
    case 5003:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    case 5004:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    // lanjutan dari case 100 jika pos robot dekat obstacle 1
    case 6000:
        if (MotionToPoint(-100, 160, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
        { // lakukan nge L dan menuju posisi -150 dan 200
            curr_stat.value = 6001;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -100, 160) < 30)
        {
            curr_stat.value = 6001;
        }
        break;
    case 6001:
        if (MotionToPoint(-150, 200, target_theta_offset, vel_trans + 10, vel_rot, normal_obstacle))
        { // persiapan nge L menuju target offset
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -150, 200) < 30)
        {
            curr_stat.value = 501;
        }
        break;
    case 600:
        // if (MotionToPoint(-250, point_k_y, target_theta_offset, vel_trans + 10, vel_rot))
        // {
        //     curr_stat.value = 601;
        // }
        // if (Pythagoras(pos_robot[0], pos_robot[1], -230, point_k_y-10) < l_tol)
        // {
        //     curr_stat.value = 601;
        // }
        if (MotionToPoint(buffer_pos_x, 100, 0, vel_prep_trans, vel_rot - 4, normal_obstacle))
        {
            buffer_pos_y = pos_robot[1];
            curr_stat.value = 601;
        }
        // if (pos_robot[1] < 85)
        // {
        //     curr_stat.value = 601;
        // }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_x, 100) < 70)
        {
            buffer_pos_y = pos_robot[1];
            curr_stat.value = 601;
        }
        break;
    case 601:
        if (MotionToPoint(-240, pos_robot[1], 0, vel_trans, vel_rot))
        {
            curr_stat.value = 6020;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -240, pos_robot[1]) < 70)
        {
            curr_stat.value = 6020;
        }
        break;
    case 6020:
        // buffer_theta = pos_robot[2];
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans - 10, vel_rot))
        {
            // SetOffsetRobot(pos_robot[0], pos_robot[1], pos_robot[2] + 2);
            curr_stat.value = 999;
        }
        break;
    case 602:
        break;
    case 321:
        if (MotionToPoint(-77, 190, 0, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 322;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -77, 190) < 110)
        {
            curr_stat.value = 322;
        }
        break;
    case 322:
        // if (pos_robot[0] < -120)
        // {
        //     curr_stat.value = 601;
        // }
        // if (MotionAroundPointAngle(-150, 150, 50, -45, 0, vel_trans, vel_rot))
        // {
        //     curr_stat.value = 601;
        // }
        if (MotionToPoint(-120, 320, target_theta_offset, vel_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -120, 300) < 100)
        {
            curr_stat.value = 601;
        }
        break;
    case 432:
        if (MotionToPoint(pos_robot[0], 200, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        break;
    case 543:
        if (MotionToPoint(-180, 350, 90, vel_prep_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 601;
        }
        if (pos_robot[0] < -170)
        {
            curr_stat.value = 601;
        }
        break;
    case 5431:
        break;
    }

    if (curr_stat.value == 999)
    {

        // curr_stat.value = 0;
        ManualMotion(0, 0, 0, 3);
    }
}

void GamePreparationChallengeB()
{

    printf("prep style b cur_stat: %d\n", state_prep_b.value);
    printf("pos robot: %.2f || %.2f\n", pos_robot[0], pos_robot[1]);

    state_debugger = state_prep_b.value;
    static float buffer_pos_robot[3];

    if (ball_status == 2)
    {
        Kick(10, 50);
    }

    switch (state_prep_b.value)
    {
    case 0:
        robot_action = 0; // tidak siap untuk mengumpan maupun menerima umpan

        // static float pos_x_offset;
        // static float pos_y_offset;

        // pos_x_offset = ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        // pos_y_offset = ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        // printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        // printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        // if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 35)
        // {
        //     printf("Aktif offsettt\n");
        //     // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
        //     SetPosXoffset(pos_x_offset);
        //     SetPosYoffset(pos_y_offset);
        //     buzzer2(10, 10);
        // }

        // apabila terdapat obstacle di posisi 3
        if (obs[1] == 3 || obs[2] == 3)
        {
            buffer_pos_robot[0] = pos_robot[0];
            state_prep_b.value = 600;
        }
        else if (pos_robot[1] < 150 && (obs[1] == 2 || obs[2] == 2))
        {
            buffer_pos_robot[0] = pos_robot[0];
            state_prep_b.value = 100;
        }
        else if (pos_robot[1] < 150 && (obs[1] == 1 || obs[2] == 1))
        {
            buffer_pos_robot[0] = pos_robot[0];
            state_prep_b.value = 200;
        }
        else if (pos_robot[1] > 360)
        {
            state_prep_b.value = 310;
        }
        else if (pos_robot[1] < 300 && (obs[1] == 2 || obs[2] == 2))
        {
            buffer_pos_robot[0] = pos_robot[0];
            state_prep_b.value = 100;
        }
        else if ((obs[1] != 3 && obs[2] != 3))
        {
            buffer_pos_robot[1] = pos_robot[1];
            state_prep_b.value = 130;
        }
        else
        {
            state_prep_b.value = 500;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 70)
        {
            printf("masuk kenne\n");
            state_prep_b.value = 702;
        }

        if (Pythagoras(pos_robot[0], pos_robot[1], 0, 0) < 100 && pos_robot[1] < 50)
        {
            state_prep_b.value = 700;
        }
        // printf("masukkkk\n")
        if (pos_robot[1] < 100 && (obs[1] == 1 || obs[2] == 1))
        {
            state_prep_b.value = 800;
        }
        break;
    case 130:
        if (MotionToPoint(-220, buffer_pos_robot[1], 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, buffer_pos_robot[1]) < 70)
        {
            state_prep_b.value = 501;
        }
        break;
    case 310:
        if (MotionToPoint(pos_robot[0], 280, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 0;
        }
        break;
    case 500:
        // printf("masukkkk 501\n");
        if (MotionToPoint(-220, 333, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -200, 300) < 70)
        {
            state_prep_b.value = 501;
        }
        break;
    case 501:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    case 600:
        if (MotionToPoint(buffer_pos_robot[0], 180, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 602;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 180) < 70)
        {
            state_prep_b.value = 602;
        }
        // if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 200) < 100)
        // {
        //     state_prep_b.value = 603;
        // }
        break;
    case 603:
        if (pos_robot[0] < -160)
        {
            state_prep_b.value = 602;
        }
        if (MotionAroundPointAngle(-150, 300, 50, 0, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 602;
        }
    case 601:
        if (MotionToPoint(-220, pos_robot[1], 90, vel_trans, vel_rot))
        {
            state_prep_b.value = 602;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, pos_robot[1]) < 70)
        {
            state_prep_b.value = 602;
        }
        break;
    case 602:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    case 700:
        if (MotionToPoint(-150, 0, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 701;
        }
        break;
    case 701:
        if (MotionToPoint(-240, 20, 0, vel_prep_trans, vel_rot))
        {
            state_prep_b.value = 702;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -230, 10) < 40)
        {
            state_prep_b.value = 702;
        }
        break;
    case 702:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_prep_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    case 800:
        if (MotionToPoint(-150, 10, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 801;
        }
        break;
    case 801:
        if (MotionToPoint(-240, 30, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 802;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -230, 10) < 70)
        {
            state_prep_b.value = 802;
        }
        break;
    case 802:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    case 100:
        if (MotionToPoint(buffer_pos_robot[0], 85, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 101;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 70) < 50)
        {
            state_prep_b.value = 101;
        }
        break;
    case 101:
        if (MotionToPoint(-220, 85, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 102;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, 85) < 70)
        {
            state_prep_b.value = 102;
        }
        break;
    case 102:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    case 200:
        if (MotionToPoint(buffer_pos_robot[0], 210, 0, vel_trans, vel_rot))
        {
            state_prep_b.value = 202;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], buffer_pos_robot[0], 210) < 50)
        {
            state_prep_b.value = 202;
        }
        break;
    // case 201:
    //     if (MotionToPoint(-220, 30, 0, vel_trans, vel_rot))
    //     {
    //         state_prep_b.value = 202;
    //     }
    //     if (Pythagoras(pos_robot[0], pos_robot[1], -220, 30) < 70)
    //     {
    //         state_prep_b.value = 202;
    //     }
    //     break;
    case 202:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            state_prep_b.value = 999;
        }
        break;
    }

    if (state_prep_b.value == 999)
    {
        ManualMotion(0, 0, 0, 3);
    }
}

void GamePassingChallengeB()
{

    // case 100-10x : untuk case mulus
    // case 1000-100x: untuk case bercabang
    // case 2000-200x: untuk case bercabang 2;

    // safety_pass_ball.SafetyInit(&curr_stat.value);

    // friend robot point
    // printf("aku masik b\n");
    float point_i_x = 60;
    float point_i_y = -20;
    float point_k_x = 60;
    float point_k_y = 100;
    float center_x = 0;
    float center_y = 0;

    // my robot point
    float point_j_x = -100;
    float point_j_y = 30;
    float point_l_x = -100;
    float point_l_y = 130 + 40;
    float point_m_x = -80;
    float point_m_y = 300;

    //     // point robot sendiri style a
    // float point_i_x = -60;
    // float point_i_y = -20;
    // float point_k_x = -60 + 10;
    // float point_k_y = 100 -10;
    // float center_x = 0;
    // float center_y = 0;

    // // point robot kawan style a
    // float point_j_x = 100 + 20;
    // float point_j_y = 60 - 30;
    // float point_l_x = 100;
    // float point_l_y = 160;

    // angle target friend robot
    float target_first_recieve = RobotAngletoPoint(0.0, 0.0);
    float target_first_pass = RobotAngletoPoint(point_k_x, point_k_y);
    float target_second_recieve = RobotAngletoPoint(point_k_x, point_k_y);

    static float buffer_pos_x;
    static float buffer_pos_y;
    static float buffer_theta;

    // angle target goal obstacle
    // untuk sekarang karena obs kiper belum ditentukan maka menggunakan target_normal
    float target_normal = RobotAngletoPoint(0, 450);

    float target_kiri = RobotAngletoPoint(-50, 450);
    float target_kanan = RobotAngletoPoint(50, 450);

    // obssss
    static obs_t obs_1_real;
    static obs_t obs_2_real;
    static obs_t obs_kiper;

    obs_1_real = ObstacleChecking(RobotAngletoPoint(-150, 100), 10, 150);
    obs_2_real = ObstacleChecking(RobotAngletoPoint(-150, 200), 10, 150);

    if (obs[0] == 1)
        obs_kiper = ObstacleChecking(RobotAngletoPoint(50, 450), 5, Pythagoras(pos_robot[0], pos_robot[1], 50, 450) + 50);
    else if (obs[0] == 2)
        obs_kiper = ObstacleChecking(RobotAngletoPoint(0, 450), 5, Pythagoras(pos_robot[0], pos_robot[1], 0, 450) + 50);
    else if (obs[0] == 3)
        obs_kiper = ObstacleChecking(RobotAngletoPoint(-50, 450), 5, Pythagoras(pos_robot[0], pos_robot[1], -50, 450) + 50);

    printf("passing challenge B cur_status: %d || ball_stat: %d\n", curr_stat.value, ball_status);
    printf("stat ball: %d ||ball pos: %.2f || %.2f\n", ball_status, ball_on_field[0], ball_on_field[1]);
    printf("status kawan: %d|| status saya: %d\n", robot_data[2].state, robot_action);
    printf("obs: %d || %d\n", obs[1], obs[2]);
    printf("robot pos: %.2f || %.2f || %.2f\n", pos_robot[0], pos_robot[1], pos_robot[2]);
    // printf("real_obs: %.2f %.2f | %.2f %.2f\n", obs_1_real.pos_x, obs_1_real.pos_y, obs_2_real.pos_x, obs_2_real.pos_y);
    // printf("counter: %d || theta_counter: %d\n", prog_counter, theta_counter);

    state_debugger = curr_stat.value;

    switch (curr_stat.value)
    {
    case 0:
        // if((prog_counter & 1)==1)
        //     IncOffsetTh(1);

        // prog_counter++;
        // theta_counter += 10;
        // if (prog_counter == 3)
        // {
        //     prog_counter = 0;
        //     theta_counter = 0;
        // }
        // static float offset_ball_x_start_b = 13;
        // static float offset_ball_y_start_b = -11;

        // if(Pythagoras(ball_on_field[0],ball_on_field[1],offset_ball_x_start_b,offset_ball_y_start_b)< 30){
        //     printf("offset bola: %.2f %.2f\n",ball_on_field[0],ball_on_field[1]);
        //     buzzer2(10, 10);
        //     SetOffsetRobot(offset_ball_x_start_b - ball_on_field[0] + pos_robot[0],offset_ball_y_start_b - ball_on_field[1]   + pos_robot[1],pos_robot[2]);
        // }
        robot_action = 0;
        // SetOffsetRobot(target_offset_x, target_offset_y, target_theta_offset);

        // tak comment sek
        if (obs[1] == 1 || obs[2] == 1)
        {
            curr_stat.value = 1;
        }
        else
        {
            curr_stat.value = 100;
        }
        // curr_stat.value = 99;.
        break;
    case 1:
        if (MotionToPoint(-220, 30, 0, vel_trans + 20, vel_rot))
        {
            curr_stat.value = 101;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -230, 50) < 70)
        {
            curr_stat.value = 101;
        }
        break;
    case 100:
        // motion L baik ada obstacle di 1 maupun tidak
        if (MotionToPoint(-220, 60, 0, vel_trans + 20, vel_rot))
        {
            curr_stat.value = 101;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -240, 80) < 70)
        {
            curr_stat.value = 101;
        }
        break;
    case 101:
        // +15
        if (MotionToPoint(point_j_x - 60, point_j_y + 20, RobotAngletoPoint(0, 0), vel_trans + 10, vel_rot))
        {
            robot_action = is_receiving;
            // ManualMotion(0, 0, 0, 3);
            // curr_stat.value = 1020;
            curr_stat.value = 102;
            // curr_stat.value = 99;
        }
        break;
    case 1020:
        // static int8_t ball_x_offset = 10 + 1;
        // static int8_t ball_y_offset = 3;
        // if(Pythagoras(ball_on_field[0],ball_on_field[1],ball_x_offset,ball_y_offset)< 80){
        //     printf("offset bola: %.2f %.2f\n",ball_on_field[0],ball_on_field[1]);
        //     buzzer2(10, 10);
        //     SetOffsetRobot(ball_x_offset - ball_on_field[0] + pos_robot[0],ball_y_offset - ball_on_field[1]   + pos_robot[1],pos_robot[2]);
        // }
        static int8_t ball_x_offset = 0;
        static int8_t ball_y_offset = -1;
        // if (Pythagoras(ball_on_field[0], ball_on_field[1], ball_x_offset, ball_y_offset) < 60)
        // {
        //     printf("offset bola: %.2f %.2f\n", ball_on_field[0], ball_on_field[1]);
        //     buzzer2(10, 10);
        //     SetOffsetRobot(ball_x_offset - ball_on_field[0] + pos_robot[0], ball_y_offset - ball_on_field[1] + pos_robot[1], pos_robot[2]);
        // }
        // curr_stat.value = 102;
        // curr_stat.value = 1021;

        // Cobak
        static float pos_x_offset;
        static float pos_y_offset;

        pos_x_offset = ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        pos_y_offset = ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 80 && Pythagoras(0, 0, ball_on_field[0], ball_on_field[1]) < 30)
        {
            printf("Aktif offsettt\n");
            // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
            SetPosXoffset(pos_x_offset);
            SetPosYoffset(pos_y_offset);
        }

        // static float theta_offset;
        // theta_offset =  atan2(ball_y_offset - pos_robot[1], ball_x_offset - pos_robot[0]) * RAD2DEG;
        // printf("theta offset: %.2f\n", theta_offset);
        // if(fabs(pos_robot[2] - theta_offset) > 12){
        //     SetOffsetRobot(pos_robot[0], pos_robot[1], theta_offset);
        //     printf("pos robot: %.2f || %.2f || %.2f\n", pos_robot[0], pos_robot[1], pos_robot[2]);
        // }

        // pos_x_offset = ball_distance * cos((RobotAngletoBall()-180) * DEG2RAD);
        // pos_y_offset = ball_distance * sin((RobotAngletoBall()-180) * DEG2RAD);
        // if(Pythagoras(pos_robot[0],pos_robot[1],pos_x_offset,pos_y_offset)< 125){
        //     printf("Aktif offsettt\n");
        //     SetOffsetRobot(pos_x_offset,pos_y_offset,pos_robot[2]);
        // }

        curr_stat.resetUptimeTimeout();
        curr_stat.value = 102;
        // curr_stat.value = 103; // percobaan

        break;
    // case 1021:
    //     static float theta_offset;
    //     theta_offset =  atan2(ball_y_offset - pos_robot[1], ball_x_offset - pos_robot[0]) * RAD2DEG;
    //     printf("theta offset: %.2f\n", theta_offset);
    //     if(fabs(pos_robot[2] - theta_offset) > 12){
    //         SetOffsetRobot(pos_robot[0], pos_robot[1], theta_offset);
    //         printf("pos robot: %.2f || %.2f || %.2f\n", pos_robot[0], pos_robot[1], pos_robot[2]);
    //     }
    //     curr_stat.value = 1022;
    //     break;
    case 1022:
        static int8_t ball_x_offset_2 = 1;
        static int8_t ball_y_offset_2 = 4;
        if (Pythagoras(ball_on_field[0], ball_on_field[1], ball_x_offset_2, ball_y_offset_2) < 60)
        {
            printf("offset bola: %.2f %.2f\n", ball_on_field[0], ball_on_field[1]);
            buzzer2(10, 10);
            SetPosXoffset(pos_x_offset);
            SetPosYoffset(pos_y_offset);
            // SetOffsetRobot(ball_x_offset_2 - ball_on_field[0] + pos_robot[0], ball_y_offset_2 - ball_on_field[1] + pos_robot[1], pos_robot[2]);
        }
        // curr_stat.value = 102;
        curr_stat.value = 103; // percobaan
        break;
    case 102:
        // if(robot_data[2].state == is_passing && ball_status == 1){
        //     target_first_recieve = RobotAngletoBall();
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], target_first_recieve, vel_trans, vel_rot)){
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 103;
        //     }
        // }
        // if(robot_data[2].state != is_passing){
        //     target_first_recieve = RobotAngletoPoint(0, 0);
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], target_first_recieve, vel_trans, vel_rot)){
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 103;
        //     }
        // }
        // if(robot_data[2].state = is_passing && !ball_status){
        //     target_first_recieve = RobotAngletoRobot(2);
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], target_first_pass, vel_trans, vel_rot)){
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 103;
        //     }
        // }
        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, vel_rot);
        if (robot_data[2].state == is_passing)
        {
            curr_stat.resetUptimeTimeout();
            curr_stat.value = 103;
        }
        break;
    case 103:
        // if(ball_status == 2){
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(point_k_x, point_k_y), vel_trans, vel_rot)){
        //         robot_action = is_passing;
        //         safety_pass_ball.ResetUptimeTimeout();
        //         curr_stat.value = 104;
        //     }
        // }else{
        //     CatchBallMotion(vel_trans, vel_rot);
        //     curr_stat.value = 1000;
        // }
        // robot_data[2].state = is_passing; // percobaan
        if (RecieveBall(2))
        {
            robot_action = 0;
            // curr_stat.value = 104;
            if (Pythagoras(pos_robot[0], pos_robot[1], point_j_x - 60, point_j_y) > 40 || Pythagoras(pos_robot[0], pos_robot[1], robot_data[2].pos_x, robot_data[2].pos_y) < 100)
            {
                curr_stat.value = 150;
            }
            else
            {
                curr_stat.value = 105;
            }

            // curr_stat.value = 99;
        }
        curr_stat.timeout(1000, 100);
        break;
    case 150:
        if (MotionToPoint(point_j_x - 50, point_j_y + 20, 0, vel_trans - 10, vel_rot))
        {
            curr_stat.value = 105;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], point_j_x - 40, point_j_y + 30) < 70)
        {
            curr_stat.value = 105;
        }
        break;
    case 104:
        // if(robot_data[2].state = is_receiving){
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoRobot(2), vel_trans, vel_rot)){
        //         safety_pass_ball.ResetUptimeTimeout();
        //         curr_stat.value = 105;
        //     }
        // }
        // safety_pass_ball.Timeout(2000, 5);
        if (MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(point_k_x, point_k_y), vel_trans + 10, vel_rot))
        {
            robot_action = is_passing;
            curr_stat.value = 105;
            // curr_stat.value = 106; // percobaan
        }
        break;
    case 105:
        // if(PassBall(2)){
        //     robot_action = 0;
        //     curr_stat.value = 106;
        // }
        // safety_pass_ball.Timeout(2001, 5);
        // robot_data[2].state = is_receiving;
        // if(robot_data[2].state = is_receiving){
        //     if(MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoRobot(2), vel_trans, vel_rot)){
        //         curr_stat.resetUptimeTimeout();
        //         curr_stat.value = 106;
        //     }
        // }
        // robot_data[2].state = is_receiving;

        PivotMotion(RobotAngletoRobot(2), 20);
        // if (fabs(pos_robot[2] - RobotAngletoRobot(2)) < 3)
        // robot_action = is_passing;
        if (robot_data[2].state == is_receiving && ball_status == 2)
        {
            // curr_stat.resetUptimeTimeout();
            curr_stat.value = 106;
        }
        if (Pythagoras(robot_data[2].pos_x, robot_data[2].pos_y, pos_robot[0], pos_robot[1]) < 70)
        {
            curr_stat.value = 1060;
        }
        // if(Pythagoras(pos_robot[0], pos_robot[1], ))
        break;
    case 1060:
        if (MotionToPoint(point_j_x - 40, point_j_y + 30, RobotAngletoRobot(2), vel_trans + 10, vel_rot))
        {
            curr_stat.value = 106;
        }
        if (Pythagoras(robot_data[2].pos_x, robot_data[2].pos_y, pos_robot[0], pos_robot[1]) > 100)
        {
            curr_stat.value = 106;
        }
        break;
    case 106:
        // robot_action = is_passing;
        if (PassBall(2, 7))
        {
            // robot_action = 0;
            curr_stat.value = 1070;
        }
        // safety_pass_ball.Timeout(2000, 5);
        // curr_stat.timeout(2000, 100);
        break;
    case 1070:
        if (obs[1] == 1 || obs[2] == 1)
        {
            curr_stat.value = 107;
        }
        else
        {
            curr_stat.value = 108;
        }
        break;
    case 107:
        if (MotionToPoint(point_j_x + 50, point_j_y, 0, vel_trans + 10, vel_rot))
        {
            curr_stat.value = 108;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], point_j_x + 40, point_j_y) < 40)
        {
            curr_stat.value = 108;
        }
        break;
    case 108:
        // asline x + 0
        // sudut robot ke teman tak ganti ke bola
        if (MotionToPoint(point_l_x + 20, point_l_y - 50, RobotAngletoBall(), vel_trans + 10, vel_rot))
        {
            robot_action = is_receiving;
            // robot_data[2].state = is_passing;
            curr_stat.value = 1090;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], point_l_x + 20, point_l_y - 50) < 15)
        {
            robot_action = is_receiving;
            // robot_data[2].state = is_passing;
            curr_stat.value = 1090;
            // curr_stat.value = 109; // percobaan
        }
        if (robot_data[2].state == is_passing && n_has_ball == 0)
        {
            robot_action = is_receiving;

            curr_stat.value = 109;
        }
        break;
    case 1090:
        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, vel_rot);
        if (robot_data[2].state == is_passing)
        {
            curr_stat.value = 109;
        }
        break;
    case 109:
        // robot_data[2].state = is_passing; // percobaan
        if (RecieveBall(2))
        {
            curr_stat.value = 1100;
            // robot_action = 0;
            // curr_stat.value = 1100;
            // curr_stat.value = 1111;
        }
        break;
    case 1099:
        if (MotionToPoint(point_l_x + 20, point_l_y - 50, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 1100;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], point_l_x + 20, point_l_y - 50) < 70)
        {
            curr_stat.value = 1100;
        }
        break;
    case 1111:
        buffer_pos_x = pos_robot[0];
        if (obs[1] == 2)
        {
            if (MotionToPoint(buffer_pos_x - 20, pos_robot[1], pos_robot[2], vel_trans + 10, vel_rot))
            {
                curr_stat.value = 1100;
            }
        }
        else
        {
            curr_stat.value = 1100;
        }

        break;

    // Jangkrek kejarbola
    case 543:
        CatchBallMotion(40, 13);
        if (ball_status == 2)
            curr_stat.value = 1100;
        break;
    case 1100:

        // if ((obs[2] == 7 || obs[2] == 8) && (obs[1] == 2 || obs[1] == 3))
        // {
        //     curr_stat.value = 1102;
        // }
        // else
        // {
        //     curr_stat.value = 110;
        // }

        if (((obs[1] == 2 || obs[2] == 2) || (obs[1] == 3 || obs[2] == 3)) &&
            ((obs[1] == 7 || obs[2] == 7) || (obs[1] == 8 || obs[2] == 8)))
        {
            // if (pos_robot[0] < -120)
            //     curr_stat.value = 1102; // eksekusi
            // else
            curr_stat.value = 1105; // gerak sek ke antara 2 obstacle
        }
        else
        {
            curr_stat.value = 110;
        }

        // Lek gorong entok bal
        if (ball_status != 2)
            curr_stat.value = 543;
        break;
    case 1105:
        // if (fabs(pos_robot[2] - 90) < 40)
        // {
        //     // curr_stat.value = 1102;
        //     curr_stat.value = 110;
        // }
        if (Pythagoras(pos_robot[0], pos_robot[1], -70, 50 + 80) < 70)
        {
            // curr_stat.value = 1102; // eksekusi
            curr_stat.value = 110;
        }
        if (MotionToPoint(-70, 130, pos_robot[2], vel_trans, vel_rot + 3))
        {
            // curr_stat.value = 1102; // eksekusi
            curr_stat.value = 110;
        }
        break;
    case 1101:
        buffer_pos_x = pos_robot[0];
        if (fabs(buffer_pos_x + 20) < 20)
        {
            curr_stat.value = 1102;
        }
        break;
    case 1102:
        static obs_t obs_depan;
        static obs_t obs_belakang;

        obs_depan = ObstacleChecking(0, 80, 200);
        obs_belakang = ObstacleChecking(180, 80, 200);

        static float safety_x;

        safety_x = (obs_depan.pos_x + obs_belakang.pos_x) * 0.5;
        printf("obs depan: %.2f || %.2f\n", obs_depan.pos_x, obs_depan.pos_y);
        printf("obs belakang: %.2f || %.2f\n", obs_belakang.pos_x, obs_belakang.pos_y);
        printf("safety_x: %.2f\n", safety_x);

        if (pos_robot[0] > -80)
        {
            if (MotionToPoint(safety_x, pos_robot[1], pos_robot[2], vel_trans - 5, vel_rot))
            {
                curr_stat.value = 110;
            }
            if (ball_status != 2)
            {
                curr_stat.value = 1110;
            }
        }
        else
        {
            if (MotionToPoint(-50, pos_robot[1], pos_robot[2], vel_trans - 5, vel_rot))
            {
                curr_stat.value = 110;
            }
        }

        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }

        // buffer_pos_x = pos_robot[0];
        break;
    case 110:
        if (ball_status == 2)
        {
            curr_stat.value = 1240;
        }
        else
        {
            curr_stat.value = 1110;
        }

        // curr_stat.value = 123;
        break;
    case 1240:
        if (MotionToPoint(pos_robot[0], pos_robot[1], 90, 0, vel_rot - 3))
        {
            curr_stat.value = 124;
        }
        if (fabs(pos_robot[2] - 90) < 30)
        {
            curr_stat.value = 124;
        }
        break;
    // case obstacle
    case 124:
        // if (obs[1] == 3 && obs[2] == 8)
        // {
        //     curr_stat.value = 125;
        // }
        // if (obs[1] == 3 && obs[2] != 8)
        // {
        //     curr_stat.value = 126;
        // }
        // if (obs[1] != 3 && obs[2] == 8)
        // {
        //     curr_stat.value = 127;
        // }
        // if (obs[1] != 3 && obs[2] != 8)
        // {
        //     curr_stat.value = 126;
        // }
        // if (obs[2] == 7 && (obs[1] != 2 || obs[1] != 1 || obs[1] != 3))
        // {
        //     curr_stat.value = 128;
        // }

        // Tak genti
        if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 8 || obs[2] == 8)) // 3, 8
        {
            curr_stat.value = 125;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] != 8 && obs[2] != 8)) // 3, !8
        {
            curr_stat.value = 126;
        }
        else if ((obs[1] != 3 && obs[2] != 3) && (obs[1] == 8 || obs[2] == 8)) // !3, 8
        {
            curr_stat.value = 127;
        }
        else if ((obs[1] != 3 && obs[2] != 3) && (obs[1] != 8 && obs[2] != 8)) // !3, !8
        {
            curr_stat.value = 126;
        }
        // 7, !(1,2,3)
        else if ((obs[1] == 7 || obs[2] == 7) && ((obs[1] != 2 && obs[2] != 2) || (obs[1] != 1 && obs[2] != 1) || (obs[1] != 3 && obs[2] != 3)))
        {
            curr_stat.value = 128;
        }
        // safety
        else
        {
            curr_stat.value = 125;
        }
        break;
    case 125:
        // enable_icp = 0;
        buffer_pos_x = pos_robot[0];
        buffer_pos_y = pos_robot[1];
        if (obs[0] == 1 || obs[0] == 2)
        {
            curr_stat.value = 1251;
        }
        if (obs[0] == 3)
        {
            curr_stat.value = 1252;
        }
        break;
    case 1251:
        // buffer_pos_x = pos_robot[0];
        // buffer_pos_y = pos_robot[1];
        // if (obs_kiper.status)
        // {
        enable_icp = 0;
        if (MotionToPoint(point_m_x, point_m_y - 40, RobotAngletoPoint(-45, 450), vel_trans + 22, vel_rot + 2))
        {
            curr_stat.value = 111;
        }
        // }
        // else
        // {
        // if (MotionToPoint(point_m_x, point_m_y - 40, RobotAngletoPoint(-45, 1000), vel_trans + 20, vel_rot + 3))
        // {
        //     curr_stat.value = 111;
        // }
        // }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-45, 450)) < 6.8 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 1252:
        enable_icp = 0;
        if (MotionToPoint(point_m_x + 3, point_m_y - 30, RobotAngletoPoint(55, 450), vel_trans + 22, vel_rot + 2))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(55, 450)) < 6.8 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 126:
        // enable_icp = 0;
        buffer_pos_x = pos_robot[0];
        buffer_pos_y = pos_robot[1];
        if (obs[0] == 1 || obs[0] == 2)
        {
            curr_stat.value = 1261;
        }
        if (obs[0] == 3)
        {
            curr_stat.value = 1262;
        }
        break;
    case 1261:
        enable_icp = 0;
        if (MotionToPoint(point_m_x + 30, point_m_y - 20, RobotAngletoPoint(-50, 500), vel_trans + 20, vel_rot + 3, normal_obstacle))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-50, 500)) < 7 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        // if (pos_robot[1] > point_m_y - 40)
        // {
        //     enable_icp = 1;
        // }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 1262:
        // buffer_pos_x = pos_robot[0];
        // buffer_pos_y = pos_robot[1];
        enable_icp = 0;
        if (MotionToPoint(point_m_x + 30, point_m_y - 20, RobotAngletoPoint(55, 500), vel_trans + 22, vel_rot + 2, normal_obstacle))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(55, 500)) < 7 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        // if (pos_robot[1] > point_m_y - 40)
        // {
        //     enable_icp = 1;
        // }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 127:
        // enable_icp = 0;
        buffer_pos_x = pos_robot[0];
        buffer_pos_y = pos_robot[1];
        if (obs[0] == 1 || obs[0] == 2)
        {
            curr_stat.value = 1271;
        }
        if (obs[0] == 3)
        {
            curr_stat.value = 1272;
        }
        break;
    case 1271:
        enable_icp = 0;
        if (MotionToPoint(point_m_x - 15, point_m_y - 20, RobotAngletoPoint(-50, 500), vel_trans + 22, vel_rot + 2, normal_obstacle))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-50, 500)) < 5.5 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        // if (pos_robot[1] > point_m_y - 40)
        // {
        //     enable_icp = 1;
        // }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 1272:
        enable_icp = 0;
        if (MotionToPoint(point_m_x - 13, point_m_y - 20, RobotAngletoPoint(55, 500), vel_trans + 22, vel_rot + 2, normal_obstacle))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(55, 500)) < 5 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        // if (pos_robot[1] > point_m_y - 40)
        // {
        //     enable_icp = 1;
        // }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 128:
        // enable_icp = 0;
        buffer_pos_x = pos_robot[0];
        buffer_pos_y = pos_robot[1];
        if (obs[0] == 1 || obs[0] == 2)
        {
            curr_stat.value = 1281;
        }
        else if (obs[0] == 3)
        {
            curr_stat.value = 1282;
        }
        break;
    case 1281:
        enable_icp = 0;
        if (MotionToPoint(point_m_x - 30, point_m_y, RobotAngletoPoint(-45, 450), vel_trans + 22, vel_rot + 2))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-45, 450)) < 5 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 1282:
        enable_icp = 0;
        if (MotionToPoint(point_m_x - 30, point_m_y, RobotAngletoPoint(50, 500), vel_trans + 22, vel_rot + 2))
        {
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(50, 500)) < 5 && (Pythagoras(buffer_pos_x, buffer_pos_y, pos_robot[0], pos_robot[1]) > 132))
        {
            curr_stat.value = 111;
        }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 123:
        enable_icp = 0;
        if (MotionToPoint(point_m_x, point_m_y, RobotAngletoPoint(0, 450), vel_trans + 22, vel_rot + 2))
        {
            // Kick(69, 8, 800);
            curr_stat.value = 111;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(0, 450)) < 5)
        {
            curr_stat.value = 111;
        }
        if (ball_status != 2)
        {
            curr_stat.value = 1110;
        }
        break;
    case 111:
        // ManualMotion(0, 0, 0); // jangkrek males aku...
        if (ball_status == 2)
        {
            Kick(69, 12, 800);
            // curr_stat.value = 99;
        }
        else if (ball_status != 2 && ball_distance > 30)
        {
            curr_stat.value = 99;
        }
        else
        {
            curr_stat.value = 1110;
        }
        break;
    case 1110:
        CatchBallMotion(vel_trans - 10, vel_rot);
        if (ball_status == 2)
        {
            curr_stat.value = 124;
        }
        break;
    case 99:
        buffer_pos_x = pos_robot[0];
        // apabila terdapat obstacle di posisi 3
        if ((obs[1] == 3 || obs[2] == 3) && (obs[1] != 2 && obs[2] != 2))
        {
            curr_stat.value = 600;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 1 || obs[2] == 1))
        {
            curr_stat.value = 600;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 2 || obs[2] == 2))
        {
            buffer_pos_x = pos_robot[0];
            curr_stat.value = 321;
        }
        // else if(((obs[1] == 1 || obs[2] == 1) && (obs[1] != 2 || obs[2] !=2)) && ((obs[1] == 1 || obs[2] == 1) && (obs[1] != 3 || obs[2] !=3))){
        //     curr_stat.value = 600;
        // }
        else
        {
            curr_stat.value = 500;
            // }else if(obs[1] !=2 && obs[1] != 3 && py){
            //     curr_stat.value = 700;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 100)
        {
            curr_stat.value = 999;
        }
        break;
    case 500:
        if (MotionToPoint(-220, 270, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 501;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220 + 20, 250) < 30 + 40)
        {
            curr_stat.value = 501;
        }
        break;
    case 321:
        if (MotionToPoint(-80, 90, 0, vel_prep_trans, vel_rot - 9, normal_obstacle))
        {
            curr_stat.value = 3210;
        }
        if (pos_robot[1] < 150)
        {
            curr_stat.value = 3210;
        }
        break;
    case 3210:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans - 10, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    // case 700:
    //     if(MotionToPoint())
    case 501:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            curr_stat.value = 999;
        }
        break;
    case 600:
        // if (MotionToPoint(pos_robot[0], 380, 90, vel_trans, vel_rot, normal_obstacle))
        // {
        //     curr_stat.value = 601;
        // }
        // if (Pythagoras(pos_robot[0], pos_robot[1], pos_robot[0], 350) < 50)
        // {
        //     curr_stat.value = 601;
        // }
        // if (MotionToPoint(pos_robot[0], 250, 90, vel_trans, vel_rot))
        // {
        //     curr_stat.value = 6001;
        // }
        // if (Pythagoras(pos_robot[0], pos_robot[1], pos_robot[0], 250) < 70)
        // {
        //     curr_stat.value = 6001;
        // }
        if (MotionToPoint(buffer_pos_x, 200, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 602;
        }
        if (pos_robot[1] < 220)
        {
            curr_stat.value = 602;
        }
        break;
    case 6001:
        if (pos_robot[0] < -170)
        {
            curr_stat.value = 602;
        }
        if (MotionAroundPointAngle(-150, 285, 30, -90, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 602;
        }
        break;
    case 601:
        if (MotionToPoint(-220, pos_robot[1], 90, vel_trans, vel_rot, normal_obstacle))
        {
            curr_stat.value = 6020;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, pos_robot[1]) < 30)
        {
            curr_stat.value = 6020;
        }
        break;
    case 6020:
        // buffer_theta = pos_robot[2];
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans - 10, vel_rot - 5))
        {
            // SetOffsetRobot(pos_robot[0], pos_robot[1], pos_robot[2] + 2);
            curr_stat.value = 999;
        }
        break;
    case 602:
        // buffer_theta = pos_robot[2];
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans, vel_rot))
        {
            // SetOffsetRobot(pos_robot[0], pos_robot[1], pos_robot[2] + 2);
            curr_stat.value = 999;
        }
        break;
    }

    if (curr_stat.value == 999)
    {
        ManualMotion(0, 0, 0, 3);
        // curr_stat.value = 0;
    }
}

void GamePreparationChallengeC()
{
    printf("curr status prep C: %d\n", curr_stat.value);
    printf("obs pos: %d || %d || %d\n", obs[0], obs[1], obs[2]);

    static float buffer_posx;
    static float buffer_posy;
    static float buffer_theta;

    if (ball_status == 2)
    {
        Kick(10, 50);
    }

    state_debugger = curr_stat.value;
    switch (curr_stat.value)
    {
    case 0:

        // if (ball_status == 2)
        // {
        //     Kick(10, 50);
        // }
        robot_action = 0; // tidak siap untuk mengumpan maupun menerima umpan

        // if ((prog_counter & 1) == 1)
        //     IncOffsetTh(1);
        // prog_counter++;

        // if(Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 50){
        //     curr_stat.value = 99;
        // }
        // ingat obstacle di 2 dan di 7
        if (pos_robot[0] > -260)
        {
            curr_stat.value = 1000;
        }
        else if (pos_robot[1] > 340)
        {
            curr_stat.value = 310;
        }
        else
        {
            curr_stat.value = 100;
        }
        break;
    case 310:
        if (MotionToPoint(pos_robot[0], 280, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 0;
        }
        break;
    case 1000:
        if ((obs[1] == 3 || obs[2] == 3) && (obs[1] != 2 && obs[2] != 2))
        {
            printf("melbu kene\n");
            curr_stat.value = 11;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 2 || obs[2] == 2))
        {
            curr_stat.value = 200;
        }
        else if ((obs[1] != 3 && obs[2] != 3) && (obs[1] != 2 && obs[2] != 2))
        {
            curr_stat.value = 100;
        }
        else if (obs[1] == 2 || obs[2] == 2)
        {
            buffer_posy = pos_robot[1];
            buffer_posx = pos_robot[0];
            curr_stat.value = 400;
        }
        else
        {
            curr_stat.value = 300;
        }
        break;
    case 11:
        buffer_posx = pos_robot[0];
        if (pos_robot[1] < -220)
        {
            curr_stat.value = 100;
        }
        else
        {
            curr_stat.value = 1;
        }
        break;
    case 1:
        if (MotionToPoint(buffer_posx - 10, 190, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 100;
        }
        break;
    case 300:
        if (MotionToPoint(-240, 300, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 100;
        }
        break;
    case 200:
        if (pos_robot[0] > -150)
        {
            curr_stat.value = 201;
        }
        else
        {
            curr_stat.value = 100;
        }
        break;
    case 201:
        // if(MotionToPoint(-100, 100, 90 ,vel_trans, vel_rot)){
        //     curr_stat.value = 202;
        // }
        // // buffer_posy = pos_robot[1];
        // if(Pythagoras(pos_robot[0], pos_robot[1], -80, 130) < 70){
        //     curr_stat.value = 202;
        // }
        if (MotionToPoint(-80, 90, 0, vel_trans, vel_rot - 9, normal_obstacle))
        {
            curr_stat.value = 100;
        }
        if (pos_robot[1] < 150)
        {
            curr_stat.value = 100;
        }
        break;
    case 202:
        if (pos_robot[0] < -220)
        {
            curr_stat.value = 100;
        }
        if (MotionToPoint(-240, 150, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 100;
        }
        break;
    case 100:
        if (MotionToPoint(target_offset_x, target_offset_y, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 99;
        }
        break;
    case 400:
        if (MotionToPoint(-260, 300, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 100;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -260, 300) < 40)
        {
            curr_stat.value = 100;
        }
        break;
    case 990:
        static float pos_x_offset;
        static float pos_y_offset;
        static float ball_y_offset = 450 - 15;
        static float ball_x_offset = -300 + 15;

        pos_x_offset = ball_x_offset + ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        pos_y_offset = ball_y_offset + ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 40)
        {
            printf("Aktif offsettt\n");
            // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
            SetPosXoffset(pos_x_offset);
            SetPosYoffset(pos_y_offset);
        }

        curr_stat.value = 99;

        break;

    default:
        if (MotionToPoint(target_offset_x, target_offset_y, target_theta_offset, vel_trans - 10, vel_rot))
        {
            curr_stat.value = 99;
        }
        break;
    }

    if (curr_stat.value == 99)
    {
        ManualMotion(0, 0, 0, 3);
    }
    // return true;
}

void GamePassingChallengeC()
{

    printf("curr status game passing C: %d\n", curr_stat.value);
    printf("status kawan: %d || status saya: %d\n", robot_data[2].state, robot_action);
    printf("obs 0 : %d\n", obs[0]);

    static float buffer_theta;
    static float buffer_posx;
    static float buffer_posy;

    curr_stat.reentry(0, 1);

    state_debugger = curr_stat.value;

    switch (curr_stat.value)
    {
    case 0:
        robot_action = 0;

        // static float pos_x_offset;
        // static float pos_y_offset;
        // static float ball_y_offset = 450 - 15;
        // static float ball_x_offset = -300 + 15;

        // pos_x_offset = ball_x_offset + ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        // pos_y_offset = ball_y_offset + ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        // printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        // printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        // if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 40)
        // {
        //     printf("Aktif offsettt\n");
        //     // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
        //     SetPosXoffset(pos_x_offset);
        //     SetPosYoffset(pos_y_offset);
        // }

        if (obs[1] == 3 || obs[2] == 3)
        {
            curr_stat.value = 1;
        }
        else if (obs[1] == 2 || obs[2] == 2)
        {
            curr_stat.value = 1;
        }
        else
        {
            curr_stat.value = 100;
        }
        break;
    case 1:
        if (MotionToPoint(target_offset_x, target_offset_y + 50, 90, vel_trans - 10, vel_rot))
        {
            // robot_action = is_receiving;
            curr_stat.value = 101;
            // curr_stat.value = 1010;
        }
        break;
    case 100:
        if (MotionToPoint(target_offset_x + 40, target_offset_y + 20, 90, vel_trans - 10, vel_rot))
        {
            // robot_action = is_receiving;
            curr_stat.value = 101;
            // curr_stat.value = 1010;
        }
        break;
        // case percobaan cuy
    case 1010:
        // static float pos_x_offset;
        // static float pos_y_offset;
        // static float ball_y_offset = 450 - 15;
        // static float ball_x_offset = -300 + 15;

        // pos_x_offset = ball_x_offset + ball_distance * cos((RobotAngletoBall() - 180) * DEG2RAD);
        // pos_y_offset = ball_y_offset + ball_distance * sin((RobotAngletoBall() - 180) * DEG2RAD);

        // printf("odom: %.2f %.2f\n", pos_robot[0], pos_robot[1]);
        // printf("real: %.2f %.2f\n", pos_x_offset, pos_y_offset);
        // if (Pythagoras(pos_robot[0], pos_robot[1], pos_x_offset, pos_y_offset) < 70)
        // {
        //     printf("Aktif offsettt\n");
        //     // SetOffsetRobot(pos_x_offset, pos_y_offset, pos_robot[2]);
        //     SetPosXoffset(pos_x_offset);
        //     SetPosYoffset(pos_y_offset);
        //     buzzer2(10, 10);
        // }
        robot_action = is_receiving;
        curr_stat.value = 101;
        break;
    case 101:
        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, vel_rot);
        if (robot_data[2].state == is_passing)
        {
            robot_action = is_receiving;
            curr_stat.value = 102;
        }
        break;
    case 1020:
        // MotionToPoint(pos_robot[0],pos_robot[1], RobotAngletoBall(), 0, vel_rot);
        // if(robo)
        break;
    case 102:
        if (RecieveBall(2))
        {
            curr_stat.value = 104;
        }
        break;
    // apabila ada obstacle di titik 3
    case 103:
        if (MotionToPoint(pos_robot[0], pos_robot[1], atan2(380, -120) * RAD2DEG, 0, vel_rot + 3))
        {
            // robot_action = is_passing;
            curr_stat.value = 104;
        }
        if (fabs(pos_robot[2] - (atan2(380, -120) * RAD2DEG)) < 5)
        {
            // robot_action = is_passing;
            curr_stat.value = 104;
        }
        break;
    case 104:
        PivotMotion(RobotAngletoRobot(2) - 10, 16);
        // if (robot_data[2].state == is_receiving && Pythagoras(robot_data[2].pos_x, robot_data[2].pos_y, -120, 380) < 20)
        // {
        //     curr_stat.value = 105;
        // }
        // if (MotionToPoint(target_offset_x + 40, target_offset_y + 20, RobotAngletoRobot(2) - 2, 10, vel_trans - 10, vel_rot))
        // {
        //     curr_stat.value = 105;
        // }
        // tak ganti iki
        if (robot_data[2].state == is_receiving)
        {
            // robot_action = is_passing;
            if (obs[1] == 3 || obs[2] == 3)
            {
                if (pos_robot[0] > target_offset_x + 10)
                {
                    curr_stat.value = 110;
                }
                else
                {
                    curr_stat.resetUptimeTimeout();
                    curr_stat.value = 1103;
                }
            }
            else
            {
                if (pos_robot[0] > target_offset_x + 10)
                {
                    curr_stat.value = 110;
                }
                else
                {
                    curr_stat.resetUptimeTimeout();
                    curr_stat.value = 105;
                }
            }
        }

        break;
    case 1103:
        if (PassBall(2, 6, -2))
        {
            curr_stat.value = 99;
        }
        buffer_theta = pos_robot[2];
        break;
    case 105:
        // robot_action = is_passing;
        // robot_data[2].state = is_receiving;
        if (PassBall(2, 6, -10))
        {
            curr_stat.value = 99;
        }
        buffer_theta = pos_robot[2];
        break;
    case 1050:
        if (ball_status == 2)
        {
            if (MotionToPoint(pos_robot[0], pos_robot[1], buffer_theta - 3, 0, vel_rot))
            {
                Kick(69, 5, 900);
            }
            // curr_stat.value = 99;
        }
        else if (ball_status != 2 && ball_distance > 20)
        {
            curr_stat.value = 99;
        }
        break;
    case 110:
        if (MotionToPoint(target_offset_x, target_offset_y + 70, RobotAngletoRobot(2), vel_trans - 10, vel_rot))
        {
            // robot_action = is_receiving;
            // curr_stat.value = 101;
            curr_stat.resetUptimeTimeout();
            curr_stat.value = 105;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], robot_data[2].pos_x, robot_data[2].pos_y) >= 100)
        {
            curr_stat.value = 105;
        }

        if (Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y + 70) < 20)
        {
            curr_stat.value = 105;
        }

        break;
    case 1060:
        MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoBall(), 0, vel_rot);
        robot_action = is_receiving;
        if (robot_data[2].state == is_passing && n_has_ball == 0)
        {
            curr_stat.value = 106;
        }
        break;
    case 1061:
        if (obs[1] == 3)
        {
            curr_stat.value = 1071;
        }
        else
        {
            curr_stat.value = 106;
        }
        break;
    case 106:
        // robot_action = is_receiving;
        if (RecieveBall(2))
        {
            curr_stat.value = 107;
        }
        break;
    case 1071:
        if (MotionToPoint(target_offset_x + 10, 190, 90, vel_trans - 20, vel_rot + 3))
        {
            curr_stat.value = 1072;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], pos_robot[0], 200) < 30)
        {
            curr_stat.value = 1072;
        }
        break;
    case 1072:
        if (MotionToPoint(-100, 180, RobotAngletoPoint(70, 450), vel_trans - 10, vel_rot + 3))
        {
            // robot_action = is_receiving;
            curr_stat.value = 109;
        }
        break;
    case 10733:
        if (MotionToPoint(pos_robot[0], 240, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 108;
        }
        if (pos_robot[1] < 250)
        {
            curr_stat.value = 108;
        }
        break;
    // iki case brutal cokkkk
    case 123:
        if (MotionToPoint(pos_robot[0], 300, 90, vel_trans - 5, vel_rot + 3))
        {
            curr_stat.value = 108;
        }
        break;
    case 1085:
        static obs_t obs_depan;
        static obs_t obs_belakang;

        obs_depan = ObstacleChecking(0, 80, 200);
        obs_belakang = ObstacleChecking(180, 80, 200);

        static float safety_x;
        safety_x = (obs_depan.pos_x + obs_belakang.pos_x) * 0.5;
        // printf("safety: %.2f\n", safety_x);
        printf("obs depan: %.2f || %.2f\n", obs_depan.pos_x, obs_depan.pos_y);
        printf("obs belakang: %.2f || %.2f\n", obs_belakang.pos_x, obs_belakang.pos_y);
        printf("safety_x: %.2f\n", safety_x);

        if (pos_robot[0] > -60)
        {
            if (MotionToPoint(safety_x - 10, pos_robot[1], pos_robot[2], vel_trans - 5, vel_rot))
            {
                curr_stat.value = 108;
            }
        }
        break;
    case 1073:
        if (RecieveBall(2))
        {
            curr_stat.value = 108;
        }
        break;
    // case mulai siap siap ngegolne
    case 107:
        // if (MotionToPoint(pos_robot[0], pos_robot[1], atan2(target_offset_y + 120 - pos_robot[1], target_offset_x + 140 - pos_robot[0]) * RAD2DEG, vel_trans, vel_rot))
        // {
        //     curr_stat.value = 108;
        // }
        // RobotAngletoPoint(-100, 450)

        // tak komen sek
        buffer_posx = pos_robot[0];
        if ((obs[1] == 3 || obs[2] == 3) && (obs[1] != 2 && obs[2] != 2) && obs[0] == 3) //
        {
            curr_stat.value = 1071;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 2 || obs[2] == 2))
        {
            curr_stat.value = 3142;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 8 || obs[2] == 8))
        {
            curr_stat.value = 1200;
        }
        else
        {
            curr_stat.value = 1088;
        }

        // if (obs[1] != 3 && obs[2] != 3)
        // {
        //     curr_stat.value = 1701;
        // }
        // else if ((obs[1] != 2 && obs[2] != 2) && (obs[1] == 3 || obs[2] == 3))
        // {
        //     curr_stat.value = 1071;
        // }
        // else if ((obs[1] == 2 || obs[2] == 2) && (obs[1] == 3 || obs[2] == 3))
        // {
        //     curr_stat.value = 3142;
        // }
        // else
        // {
        //     curr_stat.value = 1701;
        // }

        break;
    case 1200:
        if (MotionToPoint(target_offset_x + 10, 190, 90, vel_trans - 10, vel_rot))
        {
            curr_stat.value = 1201;
        }
        if (pos_robot[1] < 200)
        {
            curr_stat.value = 1201;
        }
        break;
    case 1201:
        if (MotionToPoint(-80, 240, RobotAngletoPoint(50, 450), vel_trans - 10, vel_rot))
        {
            curr_stat.value = 109;
        }
        break;
    case 1701:
        if (obs[0] == 1)
        {
            if (MotionToPoint(-60, 300, RobotAngletoPoint(-20, 450), vel_trans, vel_rot))
            {
                curr_stat.value = 109;
            }
            if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-20, 450)) < 3)
            {
                curr_stat.value = 109;
            }
        }
        else if (obs[0] == 2)
        {
            if (MotionToPoint(-60, 300, RobotAngletoPoint(-60, 450), vel_trans, vel_rot))
            {
                curr_stat.value = 109;
            }
            if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-60, 450)) < 3)
            {
                curr_stat.value = 109;
            }
        }
        else if (obs[0] == 3)
        {
            if (MotionToPoint(-60, 300, RobotAngletoPoint(30, 450), vel_trans, vel_rot))
            {
                curr_stat.value = 109;
            }
            if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(30, 450)) < 3)
            {
                curr_stat.value = 109;
            }
        }
        break;
    case 3142:
        // bingung aku kape digae opo
        if (MotionToPoint(pos_robot[0], 350, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 3141;
        }
        // if(Pythagoras(pos_robot[0], pos_robot[1], pos_robot[0], 330) < 30){
        //     curr_stat.value = 3141;
        // }
        break;
    case 3141:
        if (MotionToPoint(-80, pos_robot[1], 90, vel_trans, vel_rot))
        {
            curr_stat.value = 3140;
        }
        if (pos_robot[0] > -100)
        {
            curr_stat.value = 3140;
        }
        break;
    case 3140:
        if (MotionToPoint(-80, 280, 90, vel_trans, vel_rot))
        {
            curr_stat.value = 108;
        }
        break;
    case 1088:
        if (MotionToPoint(-220, pos_robot[1], pos_robot[2], vel_trans, vel_rot))
        {
            curr_stat.value = 108;
        }
        if (Pythagoras(pos_robot[0], pos_robot[1], -220, pos_robot[1]) < 15)
            curr_stat.value = 108;
        break;
    case 108:
        if (obs[0] == 1)
        {
            curr_stat.value = 1080;
        }
        if (obs[0] == 2)
        {
            curr_stat.value = 1081;
        }
        if (obs[0] == 3 && obs[1] != 3)
        {
            curr_stat.value = 1082;
        }
        break;
    case 1080:
        if (MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(-60, 450), vel_trans, vel_rot))
        {
            curr_stat.value = 109;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-60, 450)) < 3)
        {
            curr_stat.value = 109;
        }
        break;
    case 1081:
        if (MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(-35, 450), vel_trans, vel_rot))
        {
            curr_stat.value = 109;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(-35, 450)) < 3)
        {
            curr_stat.value = 109;
        }
        break;
    case 1082:
        if (MotionToPoint(pos_robot[0], pos_robot[1], RobotAngletoPoint(90, 450), vel_trans, vel_rot))
        {
            curr_stat.value = 109;
        }
        if (ball_status == 2 && fabs(pos_robot[2] - RobotAngletoPoint(90, 450)) < 3)
        {
            curr_stat.value = 109;
        }
        break;
    case 109:
        if (ball_status == 2)
        {
            Kick(69, 10, 800);
            // curr_stat.value = 99;
        }
        else if (ball_status != 2 && ball_distance > 30)
        {
            curr_stat.value = 99;
        }
        else
        {
            curr_stat.value = 1110;
        }
        break;
    case 990:
        if (obs[1] == 3)
        {
            curr_stat.value = 99;
        }
        break;
    case 991:
        if (MotionAroundPointAngle(-130, 300, 70, 0, 0, vel_trans, vel_rot))
        {
            curr_stat.value = 99;
        }
        if (pos_robot[0] > -200)
        {
            curr_stat.value = 99;
        }
        break;
    case 1110:
        CatchBallMotion(vel_trans, vel_rot);
        if (ball_status == 2)
        {
            curr_stat.value = 108;
        }
        break;
    case 99:
        robot_action = 10; // tidak siap untuk mengumpan maupun menerima umpan

        // if ((prog_counter & 1) == 1)
        //     IncOffsetTh(1);
        // prog_counter++;

        // if(Pythagoras(pos_robot[0], pos_robot[1], target_offset_x, target_offset_y) < 50){
        //     curr_stat.value = 99;
        // }
        if (pos_robot[0] > -100)
        {
            curr_stat.value = 1000;
        }
        else
        {
            curr_stat.value = 601;
        }
        break;
    case 1000:
        if ((obs[1] == 3 || obs[2] == 3) && (obs[1] != 2 || obs[2] != 2))
        {
            curr_stat.value = 600;
        }
        else if ((obs[1] == 3 || obs[2] == 3) && (obs[1] == 2 || obs[2] == 2))
        {
            curr_stat.value = 200;
        }
        else if (obs[1] != 3 || obs[2] != 3)
        {
            curr_stat.value = 300;
        }
        else
        {
            curr_stat.value = 100;
        }
        break;
    case 600:
        if (MotionToPoint(-80, 200, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        break;
    case 300:
        if (MotionToPoint(-240, 300, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        break;
    case 200:
        if (pos_robot[0] > -150)
        {
            curr_stat.value = 201;
        }
        else
        {
            curr_stat.value = 601;
        }
        break;
    case 201:
        if (MotionToPoint(-80, 100, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 202;
        }
        // buffer_posy = pos_robot[1];
        if (Pythagoras(pos_robot[0], pos_robot[1], -80, 130) < 70)
        {
            curr_stat.value = 202;
        }
        break;
    case 202:
        if (pos_robot[0] < -220)
        {
            curr_stat.value = 601;
        }
        if (MotionToPoint(-240, 150, 0, vel_prep_trans, vel_rot))
        {
            curr_stat.value = 601;
        }
        break;
    case 601:
        if (MotionToPoint(target_offset_x, target_offset_y, 0, vel_trans - 10, vel_rot, normal_obstacle))
        {
            curr_stat.value = 999;
        }
        break;
    }

    if (curr_stat.value == 999)
    {
        ManualMotion(0, 0, 0, 3);
    }
}
