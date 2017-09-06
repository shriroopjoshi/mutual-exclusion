class bakery {
    static bool instance;
    static bakery *m;
    bool *choosing;
    int *token;
    int n;

    bakery(int i);
    int max(int *);

public:

    static bakery* getLock(int);
    void lock(int);
    void unlock(int);
    ~bakery();
};
