/*  Screen Watch Widget
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include <QPainter>
#include "CommonFramework/VideoPipeline/VideoFeed.h"
#include "ScreenWatchWidget.h"

namespace PokemonAutomation{


ConfigWidget* ScreenWatchDisplay::make_QtWidget(QWidget& parent){
    return new ScreenWatchWidget(*this, parent);
}


ScreenWatchDisplayWidget::ScreenWatchDisplayWidget(ScreenWatchOption& option, ScreenWatchWidget& parent)
    : QWidget(&parent)
    , m_holder(parent)
    , m_option(option)
    , m_stop(false)
    , m_updater(&ScreenWatchDisplayWidget::thread_loop, this)
{}
ScreenWatchDisplayWidget::~ScreenWatchDisplayWidget(){
    {
        std::lock_guard lg(m_lock);
        m_stop = true;
        m_cv.notify_all();
    }
    m_updater.join();
}
void ScreenWatchDisplayWidget::paintEvent(QPaintEvent* event){
//        cout << "asdf" << endl;
    QWidget::paintEvent(event);
    VideoSnapshot snapshot = m_option.screenshot();
    m_holder.set_aspect_ratio((double)snapshot.frame->width() / snapshot.frame->height());
    QRect rect(0, 0, this->width(), this->height());
    QPainter painter(this);
    painter.drawImage(rect, snapshot.frame->to_QImage_ref());
}


void ScreenWatchDisplayWidget::thread_loop(){
    std::unique_lock lg(m_lock);
    while (!m_stop){
        QMetaObject::invokeMethod(this, [&]{
            this->update();
        }, Qt::QueuedConnection);
        m_cv.wait_for(lg, std::chrono::milliseconds(100));
    }
}

ScreenWatchWidget::ScreenWatchWidget(ScreenWatchDisplay& option, QWidget& parent)
    : WidgetStackFixedAspectRatio(parent, ADJUST_HEIGHT_TO_WIDTH, option.m_option.aspect_ratio())
    , ConfigWidget(option, *this)
{
    m_widget = new ScreenWatchDisplayWidget(option.m_option, *this);
    add_widget(*m_widget);
}





}
