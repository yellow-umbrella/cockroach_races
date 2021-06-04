#include "player.hpp"
#include "cockroach.hpp"
#include <vector>

enum RaceState {
    WINNER_FOUND, 
    IN_PROGRESS,
    NOBODY_LEFT
};

class Competition {
public:
    Competition();
    ~Competition();
    void init(int money);

    int run();
    bool simulate_race(int n);
    RaceState tick();

    bool get_bets(int n);
    void give_prizes();

    void cockroaches_stats(bool is_racing) const;
    void players_stats() const;
private:
    static const int TRACK_LENGTH = 100;
    static const int MAX_NUM_RACES = 10;
    static const int MAX_NUM_PLAYERS = 5;
    static const int MAX_NUM_COCKROACHES = 5;

    struct {
        int money;
        int wins;
        int bet_for;
        int bet_with;
        int last_prize;
    } main_player;

    int num_players;
    int num_cockroaches;
    int num_races;
    int prize;
    int winner;

    Player* players[MAX_NUM_PLAYERS];
    Cockroach* cockroaches[MAX_NUM_COCKROACHES];
};

