/*  Box Draw
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include <mutex>
#include "ClientSource/Connection/BotBase.h"
#include "CommonFramework/VideoPipeline/VideoOverlay.h"
#include "BoxDraw.h"

namespace PokemonAutomation{
namespace NintendoSwitch{



BoxDraw_Descriptor::BoxDraw_Descriptor()
    : SingleSwitchProgramDescriptor(
        "NintendoSwitch:BoxDraw",
        "Nintendo Switch", "Box Draw",
        "",
        "Test box coordinates for development.",
        FeedbackType::NONE, false, true,
        PABotBaseLevel::PABOTBASE_12KB
    )
{}

BoxDraw::BoxDraw()
    : X("<b>X Coordinate:</b>", 0.3, 0.0, 1.0)
    , Y("<b>Y Coordinate:</b>", 0.3, 0.0, 1.0)
    , WIDTH("<b>Width:</b>", 0.4, 0.0, 1.0)
    , HEIGHT("<b>Height:</b>", 0.4, 0.0, 1.0)
{
    PA_ADD_OPTION(X);
    PA_ADD_OPTION(Y);
    PA_ADD_OPTION(WIDTH);
    PA_ADD_OPTION(HEIGHT);
}

class BoxDraw::Overlay : public ConfigOption::Listener{
public:
    Overlay(BoxDraw& parent, VideoOverlay& overlay)
        : m_parent(parent)
        , m_overlay_set(overlay)
    {
        m_parent.X.add_listener(*this);
        m_parent.Y.add_listener(*this);
        m_parent.WIDTH.add_listener(*this);
        m_parent.HEIGHT.add_listener(*this);
    }
    virtual void value_changed() override{
        std::lock_guard<std::mutex> lg(m_lock);
        m_overlay_set.clear();
        m_overlay_set.add(COLOR_RED, {m_parent.X, m_parent.Y, m_parent.WIDTH, m_parent.HEIGHT});
    }

private:
    BoxDraw& m_parent;
    VideoOverlaySet m_overlay_set;
    std::mutex m_lock;
};

void BoxDraw::program(SingleSwitchProgramEnvironment& env, BotBaseContext& context){
    Overlay overlay(*this, env.console.overlay());
    overlay.value_changed();
    context.wait_until_cancel();
}




}
}