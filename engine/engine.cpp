#include<iostream>
#include"chess.hpp"
#include<utility>
#include<vector>
#include<map>
#include<string>
#include<cmath>
#include<chrono>
#include<cstdint>
#include<fstream>

using namespace chess;
using namespace std;

typedef struct {
    uint64_t key;
    uint16_t move;
    uint16_t weight;
    uint32_t learn;
} poly_book_entry;

int opening_entries_count = 0;
poly_book_entry * entries;

void init_book()
{
    std::ifstream open_file("Titans.bin",std::ios::binary);
    if (!open_file)
    {
        exit(1);
    }
    else
    {
        open_file.seekg(0,open_file.end);
        long long position = open_file.tellg();

        if (position < sizeof(poly_book_entry))
        {
            cout << "Error: Opening book is too small\n";
            exit(1);
        }
        opening_entries_count = position/sizeof(poly_book_entry);
        cout << "Opening book has " << opening_entries_count << " entries\n";

        entries = (poly_book_entry *)malloc(opening_entries_count*sizeof(poly_book_entry));
        open_file.seekg(0,open_file.beg);

        open_file.read((char *)entries,opening_entries_count*sizeof(poly_book_entry));
        cout << "Opening book loaded successfully\n" << "It has " << opening_entries_count << " entries\n";
    }
}
uint64_t decode_key(uint64_t key)
{
    // copied from Chat-GPT 😅
    return ((key >> 56)) |          // move byte 7 to byte 0
           ((key >> 40) & 0xFF00) |        // move byte 6 to byte 1
           ((key >> 24) & 0xFF0000) |      // move byte 5 to byte 2
           ((key >> 8) & 0xFF000000) |     // move byte 4 to byte 3
           ((key << 8) & 0xFF00000000) |   // move byte 3 to byte 4
           ((key << 24) & 0xFF0000000000) |// move byte 2 to byte 5
           ((key << 40) & 0xFF000000000000)|// move byte 1 to byte 6
           ((key << 56)); // move byte 0 to byte 7
}
uint16_t bigEndianToLittleEndian16(uint16_t key) {
    return ((key >> 8)) | ((key << 8));
}
string get_uci_from_polyglot_move(uint16_t move)
{
    string uci = "";
    uci += 'a' + ((move >> 6) & 7);
    uci += '1' + ((move >> 9) & 7);
    uci += 'a' + (move & 7);
    uci += '1' + ((move >> 3) & 7);
    return uci;
}
// void search(int l , int r , const Board &board, uint64_t key, int &count,uint16_t *poly_moves, uint16_t *weights)
// {
//     if (count == 100) return;
//     while (l < r)
//     {
//         int mid = (l+r)/2;
//         uint64_t book_key = decode_key(entries[mid].key);
//         if (book_key == key)
//         {
//             cout << l << " " << mid << " " << r << "\n";
//             poly_moves[count] = bigEndianToLittleEndian16( entries[mid].move ) ;
//             weights[count++] = bigEndianToLittleEndian16( entries[mid].weight );
//             search(l,mid-1,board,key,count,poly_moves,weights);
//             search(mid+1,r,board,key,count,poly_moves,weights);

//             return;
//         }
//         else if (book_key < key)
//         {
//             l = mid+1;
//         }
//         else
//         {
//             r = mid-1;
//         }
//     }
//     if (entries[l].key == key)
//     {
//         poly_moves[count] = bigEndianToLittleEndian16(entries[l].move);
//         weights[count++] = bigEndianToLittleEndian16( entries[l].weight );
//     }
//     if (l!=r && entries[r].key == key)
//     {
//         poly_moves[count] = bigEndianToLittleEndian16(entries[r].move);
//         weights[count++] = bigEndianToLittleEndian16( entries[r].weight );
//     }
//     return;
// }
int get_move_from_book(Board &board)
{
    uint64_t key = board.zobrist();

    int left = 0 , right = opening_entries_count-1;

    while (left < right)
    {
        int mid = (left+right)/2;
        uint64_t book_key = decode_key(entries[mid].key);
        if (book_key >= key)
        {
           right = mid;
        }
        else 
        {
            left = mid+1;
        }
        
    }
    if (decode_key(entries[left].key) == key)
    {
       return left;
    }
    return -1;
    
}
void free_book()
{
    delete[] entries;
}

bool game_ends(const Board &board)
{
    return board.isGameOver().second != GameResult::NONE;
}
void print_result(const Board &board, bool engine_move)
{
    auto result = board.isGameOver();
    if (result.second == GameResult::DRAW)
    {
        cout << "Game is a draw\n";
    }
    else if (result.second == GameResult::LOSE)
    {
        cout << "Congratulations!!! You Won\n";
    }
    else
    {
        cout << "Sorry, you lost\n";
    }
    return;
}
void play(Board &board)
{
    bool engine_move;
    cout << "Do you want to play the first move (Enter y/n): ";
    char choice;
    cin >> choice;
    engine_move = (choice == 'n');
    cout << "Enter your moves in UCI Notation\n";

    while (!game_ends(board))
    {
        if (engine_move)
        {
            Movelist moves;
            movegen::legalmoves(moves, board);
            
            Move best_move = *(moves.begin());
            board.makeMove(best_move);

            cout << uci::moveToUci(best_move) << "\n";
        }
        else
        {
            cout << "Enter your move: ";
            string move;
            cin >> move;

            Movelist moves;
            movegen::legalmoves(moves, board);
            
            while (true)
            {
                bool found = false;
                auto uci_move = uci::uciToMove(board,move);
                for (auto &it:moves)
                {
                    if (it == uci_move)
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
                cout << "Invalid Move\nEnter move again: ";
                cin >> move;
                continue;
            }
            board.makeMove(uci::uciToMove(board,move));
        }
        engine_move = !engine_move;
    }
    print_result(board,engine_move);
}
int main()
{
    chess::Board board = Board();
    board.makeMove(uci::uciToMove(board,"e2e4"));
    init_book();
    get_move_from_book(board);
    // play(board);
    
    free_book();
    
}