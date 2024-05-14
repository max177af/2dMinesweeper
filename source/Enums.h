#pragma once
// состояние клеток
enum class CellState {
    Hidden,
    HiddenBomb,
    Revealed,
    Flagged,
    FlaggedBomb
};
// состояния игры
enum class GameState {
    Playing,
    Victory,
    Defeat
};
