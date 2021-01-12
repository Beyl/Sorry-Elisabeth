#include "utils.h"

using namespace godot;

bool const Utils::isInsideRoom(const godot::Vector2 eltPosition)
{
    bool isInside = false;

    if (eltPosition.x >= ROOM_WIDTH_BEGINNING && eltPosition.x <= ROOM_WIDTH_ENDING) {
        if (eltPosition.y >= ROOM_HEIGHT_BEGINNING && eltPosition.y <= ROOM_HEIGHT_ENDING)
            isInside = true;
    }

    return isInside;
}

bool const Utils::isInsideRoomX(const int eltXPosition)
{
    bool isInside = false;

    if (eltXPosition >= ROOM_WIDTH_BEGINNING && eltXPosition <= ROOM_WIDTH_ENDING)
            isInside = true;

    return isInside;
}

bool const Utils::isInsideRoomY(const int eltYPosition)
{
    bool isInside = false;

    if (eltYPosition >= ROOM_HEIGHT_BEGINNING && eltYPosition <= ROOM_HEIGHT_ENDING)
        isInside = true;

    return isInside;
}