#pragma once

const unsigned short ServerPort = 7012;

namespace Server
{
    enum PacketType
    {
        PlayerJoined,
        PlayerEmote,
        PlayerForfait,
        NextTurn,
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
        Ping,
        MovePiece,
        Emote,
        Forfait,
        Quit
    };
}
