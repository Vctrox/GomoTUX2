

#include <gomotux_eval.h>
#include <utils.h>
#include <globals.h>
#include <board.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include <cstring>

GomoTuxEval::DirectionPattern *GomoTuxEval::preset_patterns = nullptr;
int *GomoTuxEval::preset_scores = nullptr;
int preset_patterns_size = 0;
int preset_patterns_skip[6] = {0};

int GomoTuxEval::evalState(const char *gs, int player) {
    if (gs == nullptr ||
        player < 1 || player > 2) return 0;

    int score = 0;
    for (int r = 0; r < g_board_size; ++r) {
        for (int c = 0; c < g_board_size; ++c) {
            score += evalMove(gs, r, c, player);
        }
    }
    return score;
}

int GomoTuxEval::evalMove(const char *gs, int r, int c, int player) {
    if (gs == nullptr ||
        player < 1 || player > 2) return 0;

    ++g_eval_count;

    if (preset_patterns == nullptr) {
        generatePresetPatterns(&preset_patterns, &preset_scores, &preset_patterns_size, preset_patterns_skip);
    }

    DirectionMeasurement adm[4];

    int max_score = 0;
    for (bool consecutive = false;; consecutive = true) {
        measureAllDirections(gs, r, c, player, consecutive, adm);

        int score = evalADM(adm);
        max_score = std::max(max_score, score);

        if (consecutive) break;
    }
    return max_score;
}

int GomoTuxEval::evalADM(DirectionMeasurement *all_direction_measurement) {
    int score = 0;
    int size = preset_patterns_size;
    int max_measured_len = 0;
    for (int i = 0; i < 4; i++) {
        int len = all_direction_measurement[i].length;
        max_measured_len = len > max_measured_len ? len : max_measured_len;
        score += len - 1;
    }
    int start_pattern = preset_patterns_skip[max_measured_len];

    for (int i = start_pattern; i < size; ++i) {
        score += matchPattern(all_direction_measurement, &preset_patterns[2 * i]) * preset_scores[i];

        if (score >= kGomoTuxEvalThreateningScore) break;
    }

    return score;
}

int GomoTuxEval::matchPattern(DirectionMeasurement *all_direction_measurement,
                              DirectionPattern *patterns) {
    if (all_direction_measurement == nullptr) return -1;
    if (patterns == nullptr) return -1;

    g_pm_count++;

    int match_count = INT_MAX, single_pattern_match = 0;

    for (int i = 0; i < 2; ++i) {
        auto p = patterns[i];
        if (p.length == 0) break;

        single_pattern_match = 0;

        for (int j = 0; j < 4; ++j) {
            auto dm = all_direction_measurement[j];

            if (dm.length == p.length &&
                (p.block_count == -1 || dm.block_count == p.block_count) &&
                (p.space_count == -1 || dm.space_count == p.space_count)) {
                single_pattern_match++;
            }
        }

        single_pattern_match /= p.min_occurrence;

        match_count = match_count >= single_pattern_match ? single_pattern_match : match_count;
    }
    return match_count;
}

void GomoTuxEval::measureAllDirections(const char *gs,
                                       int r,
                                       int c,
                                       int player,
                                       bool consecutive,
                                       GomoTuxEval::DirectionMeasurement *adm) {
    if (gs == nullptr) return;
    if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size) return;

    measureDirection(gs, r, c, 0,  1, player, consecutive, &adm[0]);
    measureDirection(gs, r, c, 1,  1, player, consecutive, &adm[1]);
    measureDirection(gs, r, c, 1,  0, player, consecutive, &adm[2]);
    measureDirection(gs, r, c, 1, -1, player, consecutive, &adm[3]);
}

void GomoTuxEval::measureDirection(const char *gs,
                                   int r, int c,
                                   int dr, int dc,
                                   int player,
                                   bool consecutive,
                                   GomoTuxEval::DirectionMeasurement *result) {
    if (gs == nullptr) return;
    if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size) return;
    if (dr == 0 && dc == 0) return;

    int cr = r, cc = c;
    result->length = 1, result->block_count = 2, result->space_count = 0;

    int space_allowance = 1;
    if (consecutive) space_allowance = 0;

    for (bool reversed = false;; reversed = true) {
        while (true) {
            cr += dr; cc += dc;

            if (cr < 0 || cr >= g_board_size || cc < 0 || cc >= g_board_size) break;

            int cell = gs[g_board_size * cr + cc];

            if (cell == 0) {
                if (space_allowance > 0 && Board::getCell(gs, cr + dr, cc + dc) == player) {
                    space_allowance--; result->space_count++;
                    continue;
                } else {
                    result->block_count--;
                    break;
                }
            }

            if (cell != player) break;

            result->length++;
        }

        if (reversed) break;
        cr = r; cc = c;
        dr = -dr; dc = -dc;
    }

    if (result->length >= 5) {
        if (result->space_count == 0) {
            result->length = 5;
            result->block_count = 0;
        } else {
            result->length = 4;
            result->block_count = 1;
        }
    }
}

void GomoTuxEval::generatePresetPatterns(DirectionPattern **preset_patterns,
                                         int **preset_scores,
                                         int *preset_patterns_size,
                                         int *preset_patterns_skip) {
    const int _size = 11;
    preset_patterns_skip[5] = 0;
    preset_patterns_skip[4] = 1;
    preset_patterns_skip[3] = 7;
    preset_patterns_skip[2] = 10;

    preset_patterns_skip[1] = _size;
    preset_patterns_skip[0] = _size;

    DirectionPattern patterns[_size * 2] = {
        {1, 5,  0,  0}, {0, 0,  0,  0},  // 10000
        {1, 4,  0,  0}, {0, 0,  0,  0},  // 700
        {2, 4,  1,  0}, {0, 0,  0,  0},  // 700
        {2, 4, -1,  1}, {0, 0,  0,  0},  // 700
        {1, 4,  1,  0}, {1, 4, -1,  1},  // 700
        {1, 4,  1,  0}, {1, 3,  0, -1},  // 500
        {1, 4, -1,  1}, {1, 3,  0, -1},  // 500
        {2, 3,  0, -1}, {0, 0,  0,  0},  // 300
        // {1, 4,  1,  0}, {0, 0,  0,  0},  // 1
        // {1, 4, -1,  1}, {0, 0,  0,  0},  // 1
        {3, 2,  0, -1}, {0, 0,  0,  0},  // 50
        {1, 3,  0, -1}, {0, 0,  0,  0},  // 20
        {1, 2,  0, -1}, {0, 0,  0,  0}   // 9
    };

    int scores[_size] = {
        10000,
        700,
        700,
        700,
        700,
        500,
        500,
        300,
        // 1,
        // 1,
        50,
        20,
        9
    };

    *preset_patterns = new DirectionPattern[_size * 2];
    *preset_scores   = new int[_size];

    memcpy(*preset_patterns, patterns, sizeof(DirectionPattern) * _size * 2);
    memcpy(*preset_scores, scores, sizeof(int) * _size);

    *preset_patterns_size = _size;
}

int GomoTuxEval::winningPlayer(const char *gs) {
    if (gs == nullptr) return 0;
    for (int r = 0; r < g_board_size; ++r) {
        for (int c = 0; c < g_board_size; ++c) {
            int cell = gs[g_board_size * r + c];
            if (cell == 0) continue;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc <= 0) continue;
                    DirectionMeasurement dm;
                    measureDirection(gs, r, c, dr, dc, cell, 1, &dm);
                    if (dm.length >= 5) return cell;
                }
            }
        }
    }
    return 0;
}

