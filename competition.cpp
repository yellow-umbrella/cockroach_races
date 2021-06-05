#include <iostream>
#include "competition.hpp"

using namespace std;

void Competition::init(MainPlayer player) {
    num_races = input_int("Enter number of races", 1, MAX_NUM_RACES);
    num_players = input_int("Enter number of players", 1, MAX_NUM_PLAYERS);
    num_cockroaches = input_int("Enter number of cockroaches in one race", 2, MAX_NUM_COCKROACHES);
    clear_enter();

    for (int i = 0; i < num_players; i++) {
        players.push_back(Player(i, MAX_NUM_RACES));
    }
    cockroaches.resize(num_cockroaches);
    main_player = player;
    cout << "All players:\n";
    players_stats();
    clear_enter();
}


MainPlayer Competition::run() {
    for (int i = 0; i < num_races; i++) {
        if (!simulate_race(i)) {
            break;
        }
    }
    cout << "The end of competition!\n";
    return main_player;
}

bool Competition::simulate_race(int n) {
    cout << "Race №" << n + 1 << "\n";
    for (int i = 0; i < num_cockroaches; i++) {
        cockroaches[i] = Cockroach(i);
    }
    cockroaches_stats(0);
    if (!get_bets(num_cockroaches)) {
        return 0;
    }
    clear_enter();

    print_start();
    RaceState res = IN_PROGRESS;
    while (res == IN_PROGRESS) {
        for (int i = 0; i < num_cockroaches; i++) {
            cockroaches[i].print_track(TRACK_LENGTH);
        }
        cockroaches_stats(1);
        res = tick();
        clear_time(3);
    }

    cout << "The end of the race!\n";
    if (res == NOBODY_LEFT) {
        cout << "No cockroaches can race anymore.\n";
    } else {
        cout << "The winner is cockroach №" << winner << "!\n";
        give_prizes();
    }
    players_stats();
    clear_enter();
    
    return 1;
}

RaceState Competition::tick() {
    winner = -1;
    int mx = 0;
    for (int i = 0; i < num_cockroaches; i++) {
        cockroaches[i].randomize();
        cockroaches[i].move();
        int x = cockroaches[i].get_coord();
        if (x >= TRACK_LENGTH && x > mx) {
            mx = x;
            winner = i;
        }
    }
    int cnt = 0;
    for (int i = 0; i < num_cockroaches; i++) {
        if (!cockroaches[i].can_move()) cnt++;
    }
    if (cnt == num_cockroaches) return NOBODY_LEFT;
    return winner == -1 ? IN_PROGRESS : WINNER_FOUND;
}

bool Competition::get_bets(int n) {
    if (main_player.money == 0) {
        cout << "You have no money.\n";
        return 0;
    }
    prize = 0;
    for (int i = 0; i < num_players; i++) {
        prize += players[i].make_bet(n);
    }
    if (prize == 0) {
        cout << "All of other players don't have money.\n";
        return 0;
    }
    main_player.bet_for = input_int("Enter number of your cockroach", 0, num_cockroaches-1);
    main_player.bet_with = input_int("Enter amount of bet", 1, main_player.money);
    main_player.money -= main_player.bet_with;
    prize += main_player.bet_with;
    return 1;
}

void Competition::give_prizes() {
    int cnt = 0;
    int winner_bet = 0;
    for (int i = 0; i < num_players; i++) {
        if (players[i].get_bet_for() == winner) {
            winner_bet += players[i].get_bet_with();
        }
    }
    if (main_player.bet_for == winner) {
        winner_bet += main_player.bet_with;
        main_player.last_prize = main_player.bet_with*prize/winner_bet;
        main_player.money += main_player.last_prize;
        main_player.wins++;
    } else {
        main_player.last_prize = 0;
    }
    
    for (int i = 0; i < num_players; i++) {
        if (players[i].get_bet_for() == winner) {
            players[i].add_prize(players[i].get_bet_with()*prize/winner_bet);
        } else {
            players[i].add_prize(0);
        }
    }
}

void Competition::cockroaches_stats(bool is_racing) const {
    for (int i = 0; i < num_cockroaches; i++) {
        cockroaches[i].print_stats(is_racing);
    }
}

void Competition::players_stats() const {
    for (int i = 0; i < num_players; i++) {
        players[i].print_stats();
    }
    cout << "\nYou:\n";
    cout << "amount of money: " << main_player.money << 
        (main_player.last_prize > 0 ? "(+"+to_string(main_player.last_prize)+")" : "") << "\n";
    cout << "number of wins in races: " << main_player.wins << "\n";
    cout << "\n";
}