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

godot::Vector2 Utils::getCenteredPosition(godot::Vector2 objectSize)
{
    return Vector2(real_t(int(SCREEN_WIDTH / 2 - objectSize.x / 2)), real_t(int(SCREEN_HEIGHT / 2 - objectSize.y / 2)));
}
