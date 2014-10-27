#pragma once

const unsigned short ServerPort = 7012;

namespace Server
{
    enum PacketType
    {
        PlayerJoined,
        PlayerEmote,
        PlayerForfait,
        PieceMoved,
        PieceSpawn,
        PieceEaten,
        PlayerQuit,
        GameOver
    };
}

namespace Client
{
    enum PacketType
    {
        MovePiece,
        Emote,
        Forfait,
        Quit
    };
}
