#pragma once

#include <string>
#include <vector>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    enum class CellStatus {
        CLOSED,
        FLAG,
        OPEN,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    std::vector<std::vector<CellStatus>> field_;
    std::vector<std::vector<bool>> has_mine_;
    size_t width_;
    size_t height_;

    time_t begin_time_;
    GameStatus game_status_;

    size_t should_open_;
    size_t opened_;

    void GameLose();
    void GameWin();

    size_t CountAdjMines(const Cell& cell) const;

    std::vector<Cell> GetAdjCells(const Cell& cell) const;

    bool InField(const Cell& cell) const;
};
