#include "Cloudy/Entity/entity.h"
#include "Cloudy/Input/input_man.h"
#include "Cloudy/Ext/misc.h"
#include "Cloudy/Events/events.h"
#include "Cloudy/Render/simple_window.h"
#include "Cloudy/Render/drawing.h"
#include "Cloudy/Physics/physics.h"
#include "Cloudy/UI/ui.h"

int gameScreenWidth = 640;
int gameScreenHeight = 480;

int main(void) {
    /* ENGINE INSTANCES */
    CDY_Simple_Window *simple_window = CDY_SimpleWindowCreate("Pong Game Demo", gameScreenWidth, gameScreenHeight);
    CDY_InputManager *input_manager = CDY_InputManagerCreate();
    CDY_EntityManager *entity_manager = CDY_EntityManagerCreate();
    CDY_FPSManager *fps = CDY_FPSManagerCreate(60);

    /* USER VARIABLES */
    CDY_Entity *paddle1 = CDY_EntityCreate(entity_manager);
    paddle1->posX = 50;
    paddle1->posY = 50;
    paddle1->scaleX = 25;
    paddle1->scaleY = 100;

    CDY_Entity *paddle2 = CDY_EntityCreate(entity_manager);
    paddle2->posX = 590;
    paddle2->posY = 330;
    paddle2->scaleX = 25;
    paddle2->scaleY = 100;

    CDY_Entity *ball = CDY_EntityCreate(entity_manager);
    ball->posX = 320;
    ball->posY = 240;
    ball->scaleX = 15;
    ball->scaleY = 15;
    float ballMoveSpeedX = 2.0f;
    float ballMoveSpeedY = 2.0f;
    int score1 = 0, score2 = 0;





    CDY_Font *fontmain = CDY_FontLoadDefault(32);

    int running = 1;
    while (running)
    {
        CDY_FPSBegin(fps);
        /* GAME LOOP START */

        char score1_text[16];
        char score2_text[16];
        sprintf(score1_text, "%d", score1);
        sprintf(score2_text, "%d", score2);

        CDY_Event event;
        while (CDY_PollEvent(&event)) {
                if (event.type == CDY_EVENT_QUIT) running = 0; // quit game
        }



        CDY_ColorRenderer(simple_window, 0, 0, 0, 255); //BG colour
        CDY_WipeRenderer(simple_window);

        CDY_DrawText(simple_window, fontmain, "Pong Game", 150, 10, 255, 255, 255);
        CDY_DrawText(simple_window, fontmain, score1_text, 100, 10, 255, 255, 255);
        CDY_DrawText(simple_window, fontmain, score2_text, 500, 10, 255, 255, 255);

        CDY_ColorRenderer(simple_window, 255, 255, 255, 255); // paddle1 colour
        CDY_DrawEntity(simple_window, paddle1);
        CDY_ColorRenderer(simple_window, 255, 255, 255, 255); // paddle2 colour
        CDY_DrawEntity(simple_window, paddle2);
        CDY_ColorRenderer(simple_window, 255, 255, 255, 255); // ball colour
        CDY_DrawEntity(simple_window, ball);

        /* Move paddles if W or S (Up arrow or Down arrow) is touched */
        CDY_UpdateInput(input_manager);
        if (CDY_IsKeyHeld(input_manager, CDY_KEY_W))
        {
            CDY_TranslateEntity(paddle1, 0, -10);
        }

        if (CDY_IsKeyHeld(input_manager, CDY_KEY_S))
        {
            CDY_TranslateEntity(paddle1, 0, 10);
        }

        if (CDY_IsKeyHeld(input_manager, CDY_KEY_UP))
        {
            CDY_TranslateEntity(paddle2, 0, -10);
        }

        if (CDY_IsKeyHeld(input_manager, CDY_KEY_DOWN))
        {
            CDY_TranslateEntity(paddle2, 0, 10);
        }

        /* Detect if ball misses paddles and then reset ball pos + speed */
        if (ball->posX > gameScreenWidth) {
            score1 += 1;
            ball->posX = 320;
            ball->posY = 240;
            ballMoveSpeedX = -2;
            ballMoveSpeedY = 2;
        }
        if (ball->posX < 0) {
            score2 += 1;
            ball->posX = 320;
            ball->posY = 240;
            ballMoveSpeedX = 2;
            ballMoveSpeedY = 2;
        }
        /* Move the ball in a classic pong fashion */
        // We can multiply the ballMoveSpeedX/Y
        // by -1 to invert the direction so if
        // the ball detects it hits a wall
        // we then flip the y or smth like that
        CDY_TranslateEntity(ball, ballMoveSpeedX, ballMoveSpeedY);

        if (ball->posY + ball->scaleY >= gameScreenHeight || ball->posY <= 0)
        {
            ballMoveSpeedY *= -1;
        }

        if (CDY_AABBCollide(paddle1, ball))
        {
            ball->posX = paddle1->posX + paddle1->scaleX;
            ballMoveSpeedX *= -1.1;
            // reflect ball off paddle depending on where it hits paddle
            float hitPos = (ball->posY + ball->scaleY / 2) - (paddle1->posY + paddle1->scaleY / 2);
            float normalised = hitPos / (paddle1->scaleY / 2);
            ballMoveSpeedY = (int)(normalised * 5); // 5 is max bounce speed
        }
        if (CDY_AABBCollide(paddle2, ball))
        {
            ball->posX = paddle2->posX - ball->scaleX;
            ballMoveSpeedX *= -1.1;
            // reflect ball off paddle depending on where it hits paddle
            float hitPos = (ball->posY + ball->scaleY / 2) - (paddle2->posY + paddle2->scaleY / 2);
            float normalised = hitPos / (paddle2->scaleY / 2);
            ballMoveSpeedY = (int)(normalised * 5); // 5 is max bounce speed
        }

        CDY_ArmRenderer(simple_window);


        /* GAME LOOP END */
        CDY_FPSEnd(fps);
    }
    CDY_Close();
}
