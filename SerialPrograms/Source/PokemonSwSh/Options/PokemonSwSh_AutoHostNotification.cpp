/*  Auto-Host Notification
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "PokemonSwSh_AutoHostNotification.h"

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonSwSh{


AutoHostNotificationOption::AutoHostNotificationOption(std::string label, bool max_lair)
    : GroupOption(std::move(label), LockWhileRunning::LOCKED, true, false)
    , DESCRIPTION(
        "<b>Description:</b>",
        LockWhileRunning::LOCKED,
        "",
        max_lair
            ? "Auto-Hosting Lugia\nCode: Random"
            : "Den 123: Square Shiny\nIGN: Kimberly\nCode: 1234-5678\nFC: SW-1234-5678-9012"
    )
    , SHOW_STATS(
        "<b>Show Stats:</b> Show program stats for this session.",
        LockWhileRunning::LOCKED,
        true
    )
//    , SCREENSHOT("<b>Notification Screenshot:</b><br>Attach screenshot of the den to notifications.")
    , NOTIFICATION("Hosting Announcements", true, false, ImageAttachmentMode::JPG, {"LiveHost"})
{
    PA_ADD_OPTION(DESCRIPTION);
    PA_ADD_OPTION(SHOW_STATS);
//    PA_ADD_OPTION(SCREENSHOT);
}



}
}
}
