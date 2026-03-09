#include <string>
#include <cstdint>
#include <fstream>
#include <vector>

typedef struct polyglot_entry {
    uint64_t key; // position zobrist hash
    uint16_t move; // encoded move
    uint16_t weight; // move weight
    /**
     * TODO:
     * implement move learning later to improve lookup moves.
     * however not quite necessary right now.
     */
    uint32_t learn; // move learning. 
} PolyglotEntry;

class GMLookup {
    GMLookup(std::string path) {
        file_ = std::ifstream(path);
    }

    uint16_t pick_move(std::vector<PolyglotEntry> &moves) {

        int total = 0;
        for (auto &m : moves)
            total += m.weight;

        int r = rand() % total;

        for (auto &m : moves) {
            if (r < m.weight)
                return m.move;

            r -= m.weight;
        }

        return moves[0].move;
    }

    std::vector<PolyglotEntry> find_book_moves(uint64_t key) {

        file_.seekg(0, std::ios::end);
        size_t size = file_.tellg() / 16;

        size_t lo = 0;
        size_t hi = size;

        std::vector<PolyglotEntry> moves;

        while (lo < hi) {
            size_t mid = (lo + hi) / 2;

            file_.seekg(mid * 16);
            PolyglotEntry e = read_entry();

            if (e.key < key)
                lo = mid + 1;
            else
                hi = mid;
        }

        for (size_t i = lo; i < size; i++) {
            file_.seekg(i * 16);
            PolyglotEntry e = read_entry();

            if (e.key != key)
                break;

            moves.push_back(e);
        }

        return moves;
    }
    
private:
    std::ifstream file_;

    uint64_t read_u64_be() {
        uint8_t b[8];
        file_.read((char*)b, 8);

        return (uint64_t)b[0] << 56 |
            (uint64_t)b[1] << 48 |
            (uint64_t)b[2] << 40 |
            (uint64_t)b[3] << 32 |
            (uint64_t)b[4] << 24 |
            (uint64_t)b[5] << 16 |
            (uint64_t)b[6] << 8  |
            (uint64_t)b[7];
    }

    uint16_t read_u16_be() {
        uint8_t b[2];
        file_.read((char*)b, 2);
        return (b[0] << 8) | b[1];
    }

    uint32_t read_u32_be() {
        uint8_t b[4];
        file_.read((char*)b, 4);

        return (uint32_t)b[0] << 24 |
            (uint32_t)b[1] << 16 |
            (uint32_t)b[2] << 8  |
            (uint32_t)b[3];
    }

    PolyglotEntry read_entry() {
        PolyglotEntry e;

        e.key = read_u64_be();
        e.move = read_u16_be();
        e.weight = read_u16_be();
        e.learn = read_u32_be();

        return e;
    }
};