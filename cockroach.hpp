#ifndef _COCKROACH_HPP_
#define _COCKROACH_HPP_

class Cockroach {
public:
    Cockroach(int id = -1);
    void randomize();
    void move();
    bool can_move() const;
    int get_coord();
    void print_stats(bool is_racing) const;
    void print_track(int track_length) const;
private:
    int num_legs;
    int num_eyes;
    int ticks_until_awake;
    int velocity;
    int xp;
    int x;
    int id;
    static const int MAX_XP = 4;
    static const int MAX_NUM_LEGS = 6;
    static const int MAX_NUM_EYES = 2;
};

#endif