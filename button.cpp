#include "button.h"

using namespace std;

bool nsButton::isPressed(nsEvent::EventManager &eventM, const Button &bt) {
    // On vérifie chaque évènement de la queue d'évènements

    for (size_t i=0; i<eventM.eventsCount(); ++i) {

        // Take a new event
        const nsEvent::Event_t event = eventM.pullEvent();
        nsEvent::MouseClickData_t data = event.eventData.clickData;
        nsGraphics::Vec2D eventPos(data.x, data.y);

        // If event type is a left click and mouse coordinates collide with the button
        if (event.eventType==nsEvent::EventType_t::MouseClick && !data.button && !data.state
         && eventPos.isColliding(bt.rect.getFirstPosition(), bt.rect.getSecondPosition()))
            return true;

        // Else, we put back event in buffer because it can be used for another interaction
        eventM.pushEvent(event);
    }

    // If we are here, we checked any event for this frame (and put back in buffer)
    return false;
} // events()

void nsButton::setPosition(Button &bt, const nsGraphics::Vec2D &position) {
    nsGraphics::Vec2D rectSize = bt.rect.getSecondPosition() - bt.rect.getFirstPosition();
    bt.rect.setFirstPosition(position-rectSize/2);
    bt.rect.setSecondPosition(position+rectSize/2);
    bt.text.setPosition(position);
}

void nsButton::placeBtns(vector<Button> &btns) {
    size_t nb_btns = btns.size();

    unsigned text_max_size = 0;
    for (const Button &btn : btns)
        if (btn.content.size() > text_max_size)
            text_max_size = btn.content.size();
    nsGraphics::Vec2D btnSize{9*text_max_size+64, 64};

    for(size_t i=0; i<nb_btns; ++i) {
        nsGraphics::Vec2D pos1 = {nsConsts::WINSIZE.getX()/2 - btnSize.getX()/2, i * nsConsts::WINSIZE.getY()/nb_btns + nsConsts::WINSIZE.getY()/(2*nb_btns) - btnSize.getY()/2};
        nsGraphics::Vec2D pos2 = pos1 + btnSize;
        nsGraphics::Vec2D textPos = pos1 + btnSize/2;

        btns[i].rect.setFirstPosition(pos1);
        btns[i].rect.setSecondPosition(pos2);
        btns[i].text.setPosition(textPos);
    }
} // placeBtns()

void nsButton::drawBtns(MinGL &window, const vector<Button> &btns) {
    for (const Button &btn : btns)
        window << btn.rect << btn.text;
} // drawBtns()

