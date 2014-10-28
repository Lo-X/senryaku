#pragma once

const unsigned short ServerPort = 27012;

namespace Server
{
    enum PacketType
    {
        Pong,
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
