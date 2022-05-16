#include "gomotux_ai.h"
#include <globals.h>
#include <climits>
#include <gomotux_eval.h>
#include <board.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>


int GomoTuxAI::presetSearchBreadth[5] = {17, 7, 5, 3, 3};


#define kAvgBranchingFactor 3


#define kMaximumDepth 18



#define kScoreDecayFactor 0.95

using namespace std;

void GomoTuxAI::generateMove(const char *board_string, int player,
                            int search_depth, int time_limit,
                            int *current_depth, int *x, int *y, int *winner,
                            unsigned int *node_count, unsigned int *eval_count) {

    
    char *board = new char[g_gs_size];
    std::memcpy(board, board_string, g_gs_size);

    
    gsFromString(board_string, board);

    unsigned int pm_count;
    
    GomoTuxAI::getBestMove(board, player, search_depth, time_limit, current_depth,
                                    x, y, winner, node_count, eval_count);

    
    delete[] board;
}

void GomoTuxAI::gsFromString(const char *board_string, char *board) {
    if (strlen(board_string) != g_gs_size) return;
    for (int i = 0; i < static_cast<int>(g_gs_size); i++) {
        board[i] = board_string[i] - '0';
    }
}

void GomoTuxAI::getBestMove(const char *board, int player, int search_depth, int time_limit,
                           int *current_depth, int *x, int *y, int *winner,
                           unsigned int *node_count, unsigned int *eval_count) {

    
    g_eval_count = 0;
    g_pm_count = 0;

    
    *x = -1;
    *y = -1;
    int _winner = 0;
    if (current_depth != nullptr) *current_depth = 0;

    _winner = GomoTuxEval::winningPlayer(board);
    if (_winner != 0) {
        if (winner != nullptr) *winner = _winner;
        return;
    }


    char *_board = new char[g_gs_size];
    std::memcpy(_board, board, g_gs_size);

    minimaxAlphaBetaIterative(_board, player, search_depth, time_limit, current_depth, x, y);

    std::memcpy(_board, board, g_gs_size);
    Board::setCell(_board, *x, *y, static_cast<char>(player));


    _winner = GomoTuxEval::winningPlayer(_board);


    if (winner != nullptr) *winner = _winner;
    if (node_count != nullptr) *node_count = g_node_count;
    if (eval_count != nullptr) *eval_count = g_eval_count;

    delete[] _board;
}

void GomoTuxAI::minimaxAlphaBetaIterative(const char *board, int player, int depth, int time_limit,
                                      int *current_depth, int *x, int *y) {
    
    char *_board = new char[g_gs_size];
    memcpy(_board, board, g_gs_size);

    
    int _cnt = 0;
    for (int i = 0; i < static_cast<int>(g_gs_size); i++)
        if (_board[i] != 0) _cnt++;

    if (_cnt <= 2) depth = 6;

    
    if (depth > 0) {
        if (current_depth != nullptr) *current_depth = depth;
        GomoTuxAI::minimaxAlphaBeta(_board, player, true, depth, depth,
                         INT_MIN / 2, INT_MAX / 2, x, y);
    } else {
        
        std::clock_t c_start = std::clock();
        for (int d = 2;; d += 2) {
            cout << "current depth: " << d << endl;
            std::clock_t c_iteration_start = std::clock();
            
            memcpy(_board, board, g_gs_size);

            
            GomoTuxAI::minimaxAlphaBeta(_board, player, true, d, d,
                             INT_MIN / 2, INT_MAX / 2, x, y);

            
            std::clock_t c_iteration = (std::clock() - c_iteration_start) * 1000 / CLOCKS_PER_SEC;
            std::clock_t c_elapsed = (std::clock() - c_start) * 1000 / CLOCKS_PER_SEC;

            if (c_elapsed + (c_iteration * kAvgBranchingFactor * kAvgBranchingFactor) > time_limit || d > kMaximumDepth) {
                if (current_depth != nullptr) *current_depth = d;
                break;
            }
        }
    }
    delete[] _board;
}




int GomoTuxAI::minimaxAlphaBeta(char *board, int player, bool isMax, int initial_depth, int depth, int alpha, int beta,
                                     int *x, int *y) {
    
    ++g_node_count;

    int max_score = INT_MIN;
    int opponent = player == 1 ? 2 : 1;

    
    std::vector<Move> moves_player, moves_opponent, candidate_moves;
    searchMovesOrdered(board, player, &moves_player);
    searchMovesOrdered(board, opponent, &moves_opponent);

    
    if (moves_player.size() == 0) return 0;

    
    if (moves_player.size() == 1 || moves_player[0].heuristic_val >= kGomoTuxEvalWinningScore) {
        auto move = moves_player[0];
        if (x != nullptr) *x = move.x;
        if (y != nullptr) *y = move.y;
        return move.heuristic_val;
    }

    
    bool block_opponent = false;
    int tmp_size = std::min(static_cast<int>(moves_opponent.size()), 2);
    if (moves_opponent[0].heuristic_val >= kGomoTuxEvalThreateningScore) {
        block_opponent = true;
        for (int i = 0; i < tmp_size; ++i) {
            auto move = moves_opponent[i];

            move.heuristic_val = GomoTuxEval::evalMove(board, move.x, move.y, player);

            candidate_moves.push_back(move);
        }
    }

    int breadth = (initial_depth >> 1) - ((depth + 1) >> 1);
    if (breadth > 4) breadth = presetSearchBreadth[4];
    else             breadth = presetSearchBreadth[breadth];

    // Copy moves for current player
    tmp_size = std::min(static_cast<int>(moves_player.size()), breadth);
    for (int i = 0; i < tmp_size; ++i)
        candidate_moves.push_back(moves_player[i]);

      
    int size = static_cast<int>(candidate_moves.size());
    

        if (isMax) {
            int m = INT_MAX;
            for (int i = 0; i < size; ++i) {
            auto move = candidate_moves[i];

            // Execute move
            Board::setCell(board, move.x, move.y, static_cast<char>(player));
            
            int score = 0;
            if (depth > 1) score = minimaxAlphaBeta(board, opponent, false, initial_depth, depth - 1, beta, alpha, nullptr, nullptr);

           
            candidate_moves[i].actual_score = move.actual_score;

            
            Board::setCell(board, move.x, move.y, 0);

            
            if (move.actual_score < m) {
                m = move.actual_score;
                if (x != nullptr) *x = move.x;
                if (y != nullptr) *y = move.y;
            }

            
            if (beta > m) beta = m;
            if (alpha >= beta) break;
            }
            return m;
        } else {
            int M = INT_MIN;
            for (int i = 0; i < size; ++i) {
            auto move = candidate_moves[i];
            
            int value = 4;
            int score = 0;
            if (depth > 1) score = minimaxAlphaBeta(board, opponent, true, initial_depth, depth - 1, beta, alpha, nullptr, nullptr);

            
            candidate_moves[i].actual_score = move.actual_score;

            Board::setCell(board, move.x, move.y, 0);

            
            if (move.actual_score > M) {
                M = move.actual_score;
                if (x != nullptr) *x = move.x;
                if (y != nullptr) *y = move.y;
            }

           
            if (alpha < M) alpha = M;
            if (alpha >= beta) break;
            }
            return M;

        }
        return 0;
    }


void GomoTuxAI::searchMovesOrdered(const char *board, int player, std::vector<GomoTuxAI::Move> *result) {
    result->clear();

    // Moins s'acces à Board::remote
    int min_r = INT_MAX, min_c = INT_MAX, max_r = INT_MIN, max_c = INT_MIN;
    for (int r = 0; r < g_board_size; ++r) {
        for (int c = 0; c < g_board_size; ++c) {
            if (board[g_board_size * r + c] != 0) {
                if (r < min_r) min_r = r;
                if (c < min_c) min_c = c;
                if (r > max_r) max_r = r;
                if (c > max_c) max_c = c;
            }
        }
    }

    if (min_r - 2 < 0) min_r = 2;
    if (min_c - 2 < 0) min_c = 2;
    if (max_r + 2 >= g_board_size) max_r = g_board_size - 3;
    if (max_c + 2 >= g_board_size) max_c = g_board_size - 3;

    for (int r = min_r - 2; r <= max_r + 2; ++r) {
        for (int c = min_c - 2; c <= max_c + 2; ++c) {
            if (board[g_board_size * r + c] != 0) continue;

            if (Board::remoteCell(board, r, c)) continue;

            Move m;
            m.x = r;
            m.y = c;

            m.heuristic_val = GomoTuxEval::evalMove(board, r, c, player);

            result->push_back(m);
        }
    }
    std::sort(result->begin(), result->end());
}