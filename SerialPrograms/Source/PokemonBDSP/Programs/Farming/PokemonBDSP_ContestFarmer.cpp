/*  Contest Farmer
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "CommonFramework/Tools/StatsTracking.h"
#include "CommonFramework/ImageTools/ImageStats.h"
#include "CommonFramework/ImageTools/ImageBoxes.h"
#include "CommonFramework/ImageTools/SolidColorTest.h"
#include "CommonFramework/VideoPipeline/VideoFeed.h"
#include "CommonFramework/Notifications/ProgramNotifications.h"
#include "NintendoSwitch/Commands/NintendoSwitch_Commands_PushButtons.h"
#include "Pokemon/Pokemon_Strings.h"
#include "PokemonBDSP/PokemonBDSP_Settings.h"
#include "PokemonBDSP_ContestFarmer.h"



namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonBDSP{
    using namespace Pokemon;


ContestFarmer_Descriptor::ContestFarmer_Descriptor()
    : SingleSwitchProgramDescriptor(
        "PokemonBDSP:ContestFarmer",
        STRING_POKEMON + " BDSP", "Contest Farmer",
        "ComputerControl/blob/master/Wiki/Programs/PokemonBDSP/ContestFarmer.md",
        "End game goal is to automate all contests, with all dificulty levels. We will eventually see if it's doable.",
        FeedbackType::REQUIRED,
        AllowCommandsWhenRunning::DISABLE_COMMANDS,
        PABotBaseLevel::PABOTBASE_12KB
    )
{}
struct ContestFarmer_Descriptor::Stats : public StatsTracker{
    Stats()
        : m_attempts(m_stats["Contests won"])
    {
        m_display_order.emplace_back("Contests won");
    }
    std::atomic<uint64_t>& m_attempts;
};
std::unique_ptr<StatsTracker> ContestFarmer_Descriptor::make_stats() const{
    return std::unique_ptr<StatsTracker>(new Stats());
}

ContestFarmer::ContestFarmer()
    : GO_HOME_WHEN_DONE(false)
    , MAX_COOK_ATTEMPTS(
        "to be changed",
        LockWhileRunning::LOCKED,
        5
    )

{
    PA_ADD_OPTION(GO_HOME_WHEN_DONE);
    PA_ADD_OPTION(MAX_COOK_ATTEMPTS);
}


//ImageFloatBox box0(0.386, 0.79, 0.05, 0.1); 
ImageFloatBox box1(0.342, 0.84, 0.001, 0.001); // Most optimal one so far. box0 is obsolete 
ImageFloatBox boxPink(0.016, 0.702, 0.005, 0.005); 

// This switch is on by default and is turned off once you use your move for the contest
int onoff = 1;

void ContestFarmer::program(SingleSwitchProgramEnvironment& env, BotBaseContext& context){
    ContestFarmer_Descriptor::Stats& stats = env.current_stats<ContestFarmer_Descriptor::Stats>();
    env.update_stats();

    //  Connect the controller.
    //pbf_move_right_joystick(context, 0, 255, 10, 0);

    while(true){
        // Capture the image on the screen
        context.wait_for_all_requests();
        VideoSnapshot screen = env.console.video().snapshot();
        // Get the stats of the screen's sub-image
        //ImageStats IMGstats0 = image_stats(extract_box_reference(screen, box0));
        ImageStats IMGstats1 = image_stats(extract_box_reference(screen, box1));        

        /*// If the pokeball symbol is in the sub-image, the RGB avg should be around [212, 133, 137]. If not, RGB avg should be around [122, 108, 85].
        if (IMGstats0.average.r > 180 && IMGstats0.average.g > 110 && IMGstats0.average.b > 110){
            pbf_wait(context, 27);
            pbf_press_button(context, BUTTON_A, 5, 0);
        }*/

        if (IMGstats1.average.r > 240 && IMGstats1.average.g > 240 && IMGstats1.average.b > 240){
            pbf_wait(context, 10);
            pbf_press_button(context, BUTTON_A, 5, 0);
        }
        if (onoff != 0){
            ImageStats IMGstatsPink = image_stats(extract_box_reference(screen, boxPink));
            if (IMGstatsPink.average.r > 240 && IMGstatsPink.average.g > 120 && IMGstatsPink.average.g < 140 && IMGstatsPink.average.b > 230){
                pbf_wait(context, 125);
                pbf_press_button(context, BUTTON_X, 5, 0);
                onoff = 0;
            }
        }
    }
        stats.m_attempts++;
    

    env.update_stats();
    GO_HOME_WHEN_DONE.run_end_of_program(context);
}





}
}
}