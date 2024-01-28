struct Square
{
    int side{0};
    explicit Square(const int side) : side(side) {}
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle
{
    Square sq;
    SquareToRectangleAdapter(Square &sq) : sq(sq) {}
    int width() const { return sq.side; }
    int height() const { return sq.side; }
    int area() const { return sq.side * sq.side; }
};
