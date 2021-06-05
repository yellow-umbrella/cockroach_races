#ifndef _COMPETITION_HPP_
#define _COMPETITION_HPP_

#include "player.hpp"
#include "cockroach.hpp"
#include "utilities.hpp"
#include <vector>

using namespace std;

enum RaceState {
    WINNER_FOUND, 
    IN_PROGRESS,
    NOBODY_LEFT
};

class Competition {
public:
    Competition() = default;
    void init(MainPlayer player);

    MainPlayer run();
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

    MainPlayer main_player;

    int num_players;
    int num_cockroaches;
    int num_races;
    int prize;
    int winner;

    vector<Player> players;
    vector<Cockroach> cockroaches;
};

#endif

