/*  Pokedex Tasks Reader
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "PokemonLA_PokedexTasksReader.h"

#include "CommonFramework/ImageTools/ImageFilter.h"
#include "CommonFramework/Notifications/ProgramNotifications.h"
#include "CommonFramework/OCR/OCR_NumberReader.h"
#include "CommonFramework/VideoPipeline/VideoFeed.h"
#include "CommonFramework/VideoPipeline/VideoOverlay.h"
#include "NintendoSwitch/Commands/NintendoSwitch_Commands_PushButtons.h"

#include <array>
#include <fstream>

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonLA{


class PokemonTasksReader{
public:
    PokemonTasksReader(ConsoleHandle& console)
        : m_console(console)
        , m_tasksBox{
            InferenceBoxScope(console, 0.400, 0.190, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.244, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.298, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.353, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.406, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.460, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.514, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.568, 0.040, 0.045),
            InferenceBoxScope(console, 0.400, 0.622, 0.040, 0.045)
        }
    {}

    std::array<int, 9> read_tasks(const QImage& screen) const
    {
        std::array<int, 9> tasks{};
        for (size_t i = 0; i < m_tasksBox.size(); ++i)
        {
            QImage image = extract_box_copy(screen, m_tasksBox[i]);
            to_blackwhite_rgb32_range(image, 0xff808080, 0xffffffff, false);
            tasks[i] = OCR::read_number(m_console, image);
        }
        return tasks;
    }

private:
    ConsoleHandle& m_console;
    std::array<InferenceBoxScope, 9> m_tasksBox;
};

PokedexTasksReader_Descriptor::PokedexTasksReader_Descriptor()
    : RunnableSwitchProgramDescriptor(
        "PokemonLA:PokedexTasksReader",
        STRING_POKEMON + " LA", STRING_POKEDEX + " Tasks Reader",
        "ComputerControl/blob/master/Wiki/Programs/PokemonLA/PokedexTasksReader.md",
        "Read all the tasks in your " + STRING_POKEDEX + " and output a json with the tasks you did.",
        FeedbackType::REQUIRED, false,
        PABotBaseLevel::PABOTBASE_12KB
    )
{}


PokedexTasksReader::PokedexTasksReader(const PokedexTasksReader_Descriptor& descriptor)
    : SingleSwitchProgramInstance(descriptor)
{
}


void PokedexTasksReader::program(SingleSwitchProgramEnvironment& env, BotBaseContext& context){
    //  Connect the controller.
    pbf_press_button(context, BUTTON_LCLICK, 5, 5);

    std::ofstream outputFile("output.txt");

    for (int i = 0; i < 242; ++i)
    {
        PokemonTasksReader reader(env.console);
        std::array<int, 9> tasks = reader.read_tasks(env.console.video().snapshot());
        for (auto task : tasks)
        {
            if (task != -1)
            {
                outputFile << task << "\n";
            }
        }
        pbf_press_dpad(context, DPAD_DOWN, 10, TICKS_PER_SECOND);
        context.wait_for_all_requests();
    }

    send_program_finished_notification(
        env.logger(), NOTIFICATION_PROGRAM_FINISH,
        env.program_info(),
        "",
        ""
    );
}




}
}
}