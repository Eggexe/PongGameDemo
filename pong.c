#include "Cloudy/Entity/entity.h"
#include "Cloudy/Input/input_man.h"
#include "Cloudy/Ext/misc.h"
#include "Cloudy/Render/simple_window.h"
#include "Cloudy/Render/drawing.h"
#include "Cloudy/Physics/physics.h"

int main(void) {
    /* ENGINE INSTANCES */
    CDY_Simple_Window *simple_window = CDY_SimpleWindowCreate("Pong Game Demo", 640, 480);
    CDY_InputManager *input_manager = CDY_InputManagerCreate();
    CDY_EntityManager *entity_manager = CDY_EntityManagerCreate();
    CDY_FPSManager *fps = CDY_FPSManagerCreate(60);

    /* USER VARIABLES */
    CDY_Entity *paddle1 = CDY_EntityCreate(entity_manager);
    paddle1->posX = 100;
    paddle1->posY = 100;
    paddle1->scaleX = 50;
    paddle1->scaleY = 150;

    int running = 1;
    while (running)
    {
        CDY_FPSBegin(fps);
        /* GAME LOOP START */


        // Dont forget to add a quit event poll!
        CDY_ColorRenderer(simple_window, 0, 0, 0, 255); //BG colour
        CDY_WipeRenderer(simple_window);

        CDY_ColorRenderer(simple_window, 255, 255, 255, 255); // paddle colour
        CDY_DrawEntity(simple_window, paddle1);

        CDY_ArmRenderer(simple_window);


        /* GAME LOOP END */
        CDY_FPSEnd(fps);
    }

}
