/**
 * @cite Interpreter Pattern states that in order to process/interpret some textual information, the text has to be converted into tokens and then the tokens have to be parsed into something that can be operated on.
 *
 * @brief Interpreter Pattern can be exemplified by a Arithmetic Expression Interpreter that takes expressions as string input and produces the results/.
 */

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct Token
{
    enum TokenType
    {
        integer,
        plus,
        minus,
        lparen,
        rparen
    } type;
    std::string token;

    Token(TokenType type, std::string token) : type(type), token(token) {}

    friend std::ostream &operator<<(std::ostream &oss, Token &t)
    {
        return oss << "'" << t.token << "'";
    }
};

std::vector<Token> lexer(std::string input)
{
    std::vector<Token> res;
    for (int i = 0; i < input.size(); i++)
    {
        switch (input[i])
        {
        case '+':
        {
            res.push_back(Token(Token::plus, "+"));
            break;
        }
        case '-':
        {
            res.push_back(Token(Token::minus, "-"));
            break;
        }
        case '(':
        {
            res.push_back(Token(Token::lparen, "("));
            break;
        }
        case ')':
        {
            res.push_back(Token(Token::rparen, ")"));
            break;
        }
        default:
        {
            std::ostringstream oss;
            oss << input[i];
            for (int j = i + 1; j < input.size(); j++)
            {
                if (isdigit(input[j]))
                {
                    oss << input[j];
                    ++i;
                }
                else
                {
                    res.push_back(Token{Token::integer, oss.str()});
                    break;
                }
            }
        }
        }
    }
    return res;
}

struct Element
{
    virtual int eval() = 0;
};

struct Integer : Element
{
    int value{0};

    Integer(int val) : value(val) {}

    int eval() override
    {
        return value;
    }
};

struct BinaryOperation : Element
{
    Element *lhs, *rhs;
    enum Type
    {
        addition,
        subtraction
    } type;

    BinaryOperation() {}

    int eval() override
    {
        switch (type)
        {
        case addition:
            return lhs->eval() + rhs->eval();
        case subtraction:
            return lhs->eval() - rhs->eval();
        }

        return 0;
    }
};

Element *parse(std::vector<Token> &tokens)
{
    auto res = new BinaryOperation();
    auto have_lhs{false};
    for (int i = 0; i < tokens.size(); i++)
    {
        auto &token = tokens[i];
        switch (token.type)
        {
        case Token::integer:
        {
            int val = std::stoi(token.token);
            // std::cout << val << " ";
            auto integer = new Integer{val};
            if (!have_lhs)
            {
                res->lhs = integer;
                have_lhs = true;
            }
            else
            {
                res->rhs = integer;
            }
            break;
        }
        case Token::plus:
        {
            res->type = BinaryOperation::addition;
            break;
        }
        case Token::minus:
        {
            res->type = BinaryOperation::subtraction;
            break;
        }
        case Token::lparen:
        {
            int j = i;
            for (; j < tokens.size(); j++)
                if (tokens[j].type == Token::rparen)
                    break;

            std::vector<Token> sub_expr(&tokens[i + 1], &tokens[j]);
            auto sub_expr_parsed = parse(sub_expr);

            if (have_lhs)
            {
                res->rhs = sub_expr_parsed;
            }
            else
            {
                res->lhs = sub_expr_parsed;
                have_lhs = true;
            }
            i = j;
        }
        }
    }
    
    return res;
}

int main()
{
    std::string input("(13-(10-4))-(12-8)");
    auto tokens = lexer(input);

    for (auto token : tokens)
        std::cout << token << " ";

    auto parsed = parse(tokens);

    std::cout <<"\n" << input << "=" << parsed->eval();
    return 0;
}