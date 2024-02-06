/**
 * @cite Command Pattern states that inn order to keep track of all the operations performed in a system, each operation should be stored as an object that contains all information about the operation.
 * Aims at increasing flexibility and Extensibility in how requests are handled by decoupling the request from the sender.
 *
 *
 * @brief Command Pattern can be exemplified by a Banking System that processes requests from its clients and makes changes to the database.
 * How to avoid providing the client with a direct API to the bank databse as it could be security threat ?
 * How to undo the command on the database if a malicious request gets executed ?
 * How to execute multiple commands required to perform a transfer transaction in a series ?
 * How to make the transfer commands atomic ?
 */

#include <iostream>
#include <vector>

/**
 * @brief Unsecured Bank Account that provides direct API to the client.
 *
 * !@warning This API Doesn't provide any rollback funtionality.
 */
class BankAccount
{
protected:
    int balance{0};
    std::string name;

public:
    BankAccount(std::string name) : name{name} {}
    void deposit(int amount)
    {
        balance += amount;
        // std::cout << amount;
        std::cout << "(" << name << ") " << amount << " Deposited, Balance : " << balance << "\n";
    }

    void withdraw(int amount)
    {
        if (balance < amount)
        {
            std::cout << "(" << name << ") "
                      << "Insufficient Balance.\n";
            return;
        }
        balance -= amount;
        std::cout << "(" << name << ") " << amount << " Withdrawn, Balance : " << balance << "\n";
    }
};

/**
 * @brief Secured Bank Account that doesn't let client interact with it directly.
 *
 * !@warning Use the Command API to use the Bank Account
 */
class BankAccountSecure : private BankAccount
{
    friend class Command;

public:
    BankAccountSecure(std::string name) : BankAccount(name) {}
};

class CommandBase
{
public:
    virtual void call() = 0;
    virtual void rollback() = 0;
};

/**
 * @brief Command API that allows users to record commands in an object-format.
 * * Contains db state before and after the command execution.
 * * Allows rollback functionality.
 */
class Command : public CommandBase
{
    // reference to the Bank Account being operated on.
    BankAccountSecure &ba;
    // store the amount to be withdrawn or deposited.
    int amount;
    // Stores account state before and after the transaction.

public:
    enum BankCommands
    {
        DEPOSIT,
        WITHDRAW
    } action;
    bool succeded{false};

    Command(BankAccountSecure &b, BankCommands action, int amount) : ba(b), action(action), amount(amount) {}

    /**
     * @brief Executes the command on the bank account.
     */
    void call() override
    {
        int balance_before = ba.balance;
        switch (action)
        {
        case DEPOSIT:
            ba.deposit(amount);
            break;
        case WITHDRAW:
            ba.withdraw(amount);
            break;
        }
        succeded = (ba.balance != balance_before);
    }

    // Rolls back the command on the bank account.
    void rollback() override
    {
        if (!succeded)
            return;
        switch (action)
        {
        case DEPOSIT:
            ba.withdraw(amount);
            break;
        case WITHDRAW:
            ba.deposit(amount);
            break;
        }
    }
};

/**
 * @brief Composite Commands allow user to execute multiple commands at once.
 * 
 * !@warning The Commands are not linked together i.e if one command fails then the execution doesn't stop.
 */
class CompositeCommand : public CommandBase
{
protected:
    std::vector<Command> commands;

public:
    CompositeCommand(std::initializer_list<Command> items) : commands(items) {}

    void call() override
    {
        for (auto &cmd : commands)
        {
            cmd.call();
        }
    }

    void rollback()
    {
        for (auto cmd = commands.rbegin(); cmd != commands.rend(); ++cmd)
        {
            cmd->rollback();
        }
    }
};

/**
 * @brief TransferCompositeCommand groups commands required to transfer money from sender to reciever.
 * 
 * !@warning Deposits money to the reciever evven if the sender doesn't have enoguh balance.
 */
class TransferCompositeCommad : public CompositeCommand
{

public:
    TransferCompositeCommad(
        BankAccountSecure &sender,
        BankAccountSecure &reciever,
        int amount) : CompositeCommand({Command{sender, Command::WITHDRAW, amount},
                                        Command{reciever, Command::DEPOSIT, amount}}) {}
};

/**
 * @brief Improves the previous Composite Commands by linking each command with the previous one.
 * * If one command fails then next commands are not executed, making the composite commands atomic.
 */
class DependentCompositeCommand : public CompositeCommand
{

public:
    DependentCompositeCommand(std::initializer_list<Command> items) : CompositeCommand(items) {}

    void call() override
    {
        bool success = true;
        for (auto &cmd : commands)
        {
            if (success)
            {
                cmd.call();
                success = cmd.succeded;
            }
            else
            {
                return;
            }
        }
    }
};

/**
 * @brief Dependent Transfer Command that executes atomic transfer commands.
 */
class TransferDependentCompositeCommad : public DependentCompositeCommand
{

public:
    TransferDependentCompositeCommad(
        BankAccountSecure &sender,
        BankAccountSecure &reciever,
        int amount) : DependentCompositeCommand({Command{sender, Command::WITHDRAW, amount},
                                                 Command{reciever, Command::DEPOSIT, amount}}) {}
};

int main()
{
    {
        // ! Unsecured code as the client directly handling the back account.
        BankAccount ba("Jason");
        ba.deposit(500);
        ba.withdraw(1000);
        std::cout << std::endl;
    }

    {
        BankAccountSecure ba_1("John");

        // *Commands can be stored in the order that they have to be performed.
        std::vector<Command> commands{
            Command{ba_1, Command::DEPOSIT, 500},
            Command{ba_1, Command::WITHDRAW, 1000}};

        for (auto &cmd : commands)
        {
            cmd.call();
        }

        commands[0].rollback();
        std::cout << std::endl;

        // !Transferring amount from one account to another can still be tedious.
        {
            BankAccountSecure ba_2("Jason");
            std::vector<Command> transfer{
                Command{ba_1, Command::WITHDRAW, 500},
                Command{ba_2, Command::DEPOSIT, 500}};

            for (auto &cmd : transfer)
            {
                cmd.call();
            }

            std::cout << std::endl;
            // !Rolling back the transfer is also tedious as well.
        }

        // * Using the Composite commands makes transfer and transfer rollbacks much simpler.
        {
            // ! The Commands are not linked i.e if one fails other one still executes.
            // ! If the sender doesn't have enough balance sender still recieves amount.
            BankAccountSecure ba_2("Jason");
            TransferCompositeCommad tc(ba_1, ba_2, 500);
            tc.call();
            tc.rollback();
            std::cout << std::endl;

            // * Dependent Commands solves the above problem by linking the commands together.
            // * If the doesn't have enough balance then the execution terminates.
            {
                BankAccountSecure ba_2("Jason");
                TransferDependentCompositeCommad tc(ba_1, ba_2, 500);
                tc.call();
                tc.rollback();
            }
        }
    }
    return 0;
}