struct Command
{
    enum Actions
    {
        deposit,
        withdraw
    } action;
    int amount{0};
    bool success{false};

    Command(Actions action, int amount) : action(action), amount(amount) {}
};

struct Account
{
    int balance{0};
    void process(Command &cmd)
    {
        switch (cmd.action)
        {
        case Command::deposit:
            cmd.success = deposit(cmd.amount);
            break;
        case Command::withdraw:
            cmd.success = withdraw(cmd.amount);
            break;
        }
    };

    bool deposit(int amount)
    {
        balance += amount;
        return true;
    }

    bool withdraw(int amount) {
        if(amount > balance) return false;
        balance -= amount;
        return true;
    }
};