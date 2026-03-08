#include <string>
#include <vector>
#include <cstdint>
#include "types.hpp"
class Board {
public: 
    /**
     * Default constructor, creates a board with startpos
     */
    Board();

    /**
     * Create board by parsing moves.
     */
    Board(std::vector<move_t> moves);

    /**
     * Create board starting with fen and parsing moves.
     */
    Board(std::string fen, std::vector<move_t> moves);

    void set_startpos();
    void set_fen(std::string fen);
    void make_move();

private:
    uint64_t white_pieces_;
    uint64_t black_pieces_;
    uint64_t all_pieces_;
    int piece_list_[12][16];
    uint64_t bitboards_[12];

    // attack tables
    uint64_t knight_attacks_[64];
    uint64_t king_attacks_[64];

    // magic bitboards
    uint64_t rook_masks_[64];
    uint64_t bishop_masks_[64];

    uint64_t rook_magics_[64];
    uint64_t bishop_magics_[64];

    uint64_t rook_attacks_[64][4096];
    uint64_t bishop_attacks_[64][512];

    // 0 for white, 1 for black
    bool turn_ = 0;
    bool bkingcastle_ = true;
    bool bqueencastle_ = true;
    bool wkingcastle_ = true;
    bool wqueencastle_ = true;
    char epf_ = '-';
    int epr_ = 0; 
    int fullmove_ = 0;
    int halfmove_ = 0;
};