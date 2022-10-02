#include "minesweeper.h"

#include <ctime>
#include <random>

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    std::vector<Cell> cells_with_mines;
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            cells_with_mines.emplace_back(Cell{x, y});
        }
    }

    std::shuffle(cells_with_mines.begin(), cells_with_mines.end(), std::mt19937(std::random_device()()));
    cells_with_mines.resize(mines_count);

    NewGame(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    begin_time_ = std::time(NULL);

    width_ = width;
    height_ = height;

    should_open_ = width * height - cells_with_mines.size();
    opened_ = 0;

    field_ = std::vector<std::vector<CellStatus>>(height_, std::vector<CellStatus>(width_, CellStatus::CLOSED));
    has_mine_ = std::vector<std::vector<bool>>(height_, std::vector<bool>(width_, false));

    game_status_ = GameStatus::NOT_STARTED;

    for (const Cell& mine : cells_with_mines) {
        has_mine_[mine.y][mine.x] = true;
    }
}

void Minesweeper::GameLose() {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            field_[y][x] = CellStatus::OPEN;
        }
    }
    game_status_ = GameStatus::DEFEAT;
}

void Minesweeper::GameWin() {
    game_status_ = GameStatus::VICTORY;
}

void Minesweeper::OpenCell(const Minesweeper::Cell& cell) {
    if (game_status_ == GameStatus::DEFEAT || game_status_ == GameStatus::VICTORY) {
        return;
    }
    game_status_ = GameStatus::IN_PROGRESS;
    if (field_[cell.y][cell.x] == CellStatus::FLAG || field_[cell.y][cell.x] == CellStatus::OPEN) {
        return;
    }
    if (has_mine_[cell.y][cell.x]) {
        GameLose();
    }

    if (field_[cell.y][cell.x] == CellStatus::CLOSED) {
        field_[cell.y][cell.x] = CellStatus::OPEN;
        if (++opened_ == should_open_) {
            GameWin();
            return;
        }
    }
    if (CountAdjMines(cell) == 0) {
        for (const auto& next : GetAdjCells(cell)) {
            OpenCell(next);
        }
    }
}

void Minesweeper::MarkCell(const Minesweeper::Cell& cell) {
    if (game_status_ == GameStatus::DEFEAT || game_status_ == GameStatus::VICTORY) {
        return;
    }
    game_status_ = GameStatus::IN_PROGRESS;
    if (field_[cell.y][cell.x] == CellStatus::FLAG) {
        field_[cell.y][cell.x] = CellStatus::CLOSED;
    } else {
        field_[cell.y][cell.x] = CellStatus::FLAG;
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    return std::time(NULL) - begin_time_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField rendered_field(height_);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            switch (field_[y][x]) {
                case (CellStatus::CLOSED):
                    rendered_field[y] += '-';
                    break;
                case (CellStatus::FLAG):
                    rendered_field[y] += '?';
                    break;
                case (CellStatus::OPEN):
                    if (has_mine_[y][x]) {
                        rendered_field[y] += '*';
                    } else {
                        size_t cnt_adj_mines = CountAdjMines(Cell{x, y});
                        rendered_field[y] += cnt_adj_mines == 0 ? '.' : static_cast<char>(cnt_adj_mines + '0');
                    }
            }
        }
    }
    return rendered_field;
}

size_t Minesweeper::CountAdjMines(const Cell& cell) const {
    size_t cnt = 0;
    for (const auto& adj : GetAdjCells(cell)) {
        if (has_mine_[adj.y][adj.x]) {
            ++cnt;
        }
    }
    return cnt;
}

std::vector<Minesweeper::Cell> Minesweeper::GetAdjCells(const Minesweeper::Cell& cell) const {
    std::vector<Cell> adg_cells;
    for (int dx = cell.x == 0 ? 0 : -1; dx <= 1; ++dx) {
        for (int dy = cell.y == 0 ? 0 : -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            Cell cur{static_cast<size_t>(cell.x + dx), static_cast<size_t>(cell.y + dy)};
            if (InField(cur)) {
                adg_cells.emplace_back(cur);
            }
        }
    }
    return adg_cells;
}

bool Minesweeper::InField(const Cell& cell) const {
    return 0 <= cell.y && cell.y < height_ && 0 <= cell.x && cell.x < width_;
}
