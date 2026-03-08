#include <string>
#include <vector>
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
    
    // 0 for white, 1 for black
    bool turn_ = 0;
    bool bkingcastle_ = true;
    bool bqueencastle_ = true;
    bool wkingcastle_ = true;
    bool wqueencastle_ = true;
    char epf_ = '-';
    int epr_ = 0; 
};