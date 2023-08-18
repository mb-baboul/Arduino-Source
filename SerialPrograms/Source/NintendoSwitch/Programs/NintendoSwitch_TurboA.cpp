/*  Turbo A
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "NintendoSwitch/Commands/NintendoSwitch_Commands_PushButtons.h"
#include "NintendoSwitch/NintendoSwitch_Settings.h"
#include "PokemonSwSh/Programs/PokemonSwSh_GameEntry.h"
#include "NintendoSwitch_TurboA.h"

namespace PokemonAutomation{
namespace NintendoSwitch{


TurboA_Descriptor::TurboA_Descriptor()
    : SingleSwitchProgramDescriptor(
        "PokemonSwSh:TurboA",
        "Nintendo Switch", "Turbo A",
        "ComputerControl/blob/master/Wiki/Programs/NintendoSwitch/TurboA.md",
        "Modified script that will endlessly farm the TableTurf minigame in Splatoon3. Starts it with the minigame opened, you'll need at least 3 diferents card sets for it to work.",
        FeedbackType::NONE,
        AllowCommandsWhenRunning::DISABLE_COMMANDS,
        PABotBaseLevel::PABOTBASE_12KB
    )
{}



TurboA::TurboA(){
    PA_ADD_OPTION(START_LOCATION);
}
void TurboA::program(SingleSwitchProgramEnvironment& env, BotBaseContext& context){
    if (START_LOCATION.start_in_grip_menu()){
        grip_menu_connect_go_home(context);
        PokemonSwSh::resume_game_back_out(env.console, context, ConsoleSettings::instance().TOLERATE_SYSTEM_UPDATE_MENU_FAST, 200);
    }

    while (true){
        pbf_press_dpad(context, DPAD_DOWN, 5, 20);
        pbf_press_dpad(context, DPAD_DOWN, 5, 20);
        pbf_press_button(context, BUTTON_A, 5, 20);
        pbf_press_button(context, BUTTON_A, 5, 1250);
    }
}




}
}

