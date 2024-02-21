#include <string>
#include <sstream>
using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
  virtual void accept(Value& value) = 0;
  virtual void accept(AdditionExpression& ae) = 0;
  virtual void accept(MultiplicationExpression& me) = 0;
};

struct Expression
{
  virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
  int value;

  Value(int value) : value(value) {}

  void visit(ExpressionVisitor &ev) override
  {
    ev.accept(*this);
  }
};

struct AdditionExpression : Expression
{
  Expression &lhs, &rhs;

  AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor &ev) override
  {
    ev.accept(*this);
  }
};

struct MultiplicationExpression : Expression
{
  Expression &lhs, &rhs;

  MultiplicationExpression(Expression &lhs, Expression &rhs)
    : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor &ev) override
  {
    ev.accept(*this);
  }
};

struct ExpressionPrinter : ExpressionVisitor
{
  void accept(Value &value) override
  {
    oss << value.value;
  }

  void accept(AdditionExpression &ae) override
  {
    oss << "(";
    ae.lhs.visit(*this);
    oss << "+";
    ae.rhs.visit(*this);
    oss << ")";
  }

  void accept(MultiplicationExpression &me) override
  {
    me.lhs.visit(*this);
    oss << "*";
    me.rhs.visit(*this);
  }

  string str() const { return oss.str(); }

private:
  ostringstream oss;
};
