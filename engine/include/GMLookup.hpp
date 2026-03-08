#include <string>
#include <cstdint>

struct PolyglotEntry {
    uint64_t key; // position zobrist hash
    uint16_t move; // encoded move
    uint16_t weight; // move weight
    /**
     * TODO:
     * implement move learning later to improve lookup moves.
     * however not quite necessary right now.
     */
    uint32_t learn; // move learning. 
};

class GMLookup {
    GMLookup(std::string path) {
        path_ = path;
    }

    uint16_t find_move() {

    }
    
private:
    std::string path_;
};