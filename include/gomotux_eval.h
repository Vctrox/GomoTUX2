#ifndef GOMOTUX_EVAL_H
#define GOMOTUX_EVAL_H

#define kGomoTuxEvalWinningScore 10000
#define kGomoTuxEvalThreateningScore 300

#include <globals.h>

class GomoTuxEval {
 public:
    GomoTuxEval();
    ~GomoTuxEval();

    static int evalState(const char *gs, int player);

    static int evalMove(const char *gs, int r, int c, int player);

    static int winningPlayer(const char *gs);


 private:
    
    struct DirectionMeasurement {
        char length;          
        char block_count;     
        char space_count;     
    };

    struct DirectionPattern {
        char min_occurrence;  
        char length;          
        char block_count;     
        char space_count;     
    };

    static DirectionPattern *preset_patterns;

    static int *preset_scores;

    
    static void generatePresetPatterns(DirectionPattern **preset_patterns,
                                       int **preset_scores,
                                       int *preset_patterns_size,
                                       int *preset_patterns_skip);

    static int evalADM(DirectionMeasurement *all_direction_measurement);

    static int matchPattern(DirectionMeasurement *all_direction_measurement,
                            DirectionPattern *patterns);

    static void measureAllDirections(const char *gs,
                                     int r,
                                     int c,
                                     int player,
                                     bool consecutive,
                                     GomoTuxEval::DirectionMeasurement *adm);

    static void measureDirection(const char *gs,
                                 int r, int c,
                                 int dr, int dc,
                                 int player,
                                 bool consecutive,
                                 GomoTuxEval::DirectionMeasurement *result);



};

#endif  
