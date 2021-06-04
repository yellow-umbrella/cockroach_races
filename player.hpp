class Player {
public:
    Player(int id, int num_races);
    int make_bet(int n);
    int get_bet_for() const;
    int get_bet_with() const;
    void add_prize(int prize);
    void print_stats() const;
private:
    static const int max_bet = 200;
    static const int min_bet = 1;
    int money;
    int bet_for;
    int bet_with;
    int num_wins;
    int id;
    int last_prize;
};