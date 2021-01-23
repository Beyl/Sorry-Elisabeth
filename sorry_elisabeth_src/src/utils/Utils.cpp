#include "utils.h"

using namespace godot;

bool const Utils::isInsideRoom(const godot::Vector2 eltPosition)
{
    return (isInsideRoomX(int(eltPosition.x)) && isInsideRoomY(int(eltPosition.y)));
}

bool const Utils::isInsideRoomX(const int eltXPosition)
{
    return(eltXPosition >= ROOM_WIDTH_BEGINNING && eltXPosition <= ROOM_WIDTH_ENDING);
}

bool const Utils::isInsideRoomY(const int eltYPosition)
{
    return(eltYPosition >= ROOM_HEIGHT_BEGINNING && eltYPosition <= ROOM_HEIGHT_ENDING);
}