#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

class Libro;
class Film;
class Vinile;

class ItemVisitor{
public:
    ~ItemVisitor() = default;

    virtual void visit(Libro* libro) = 0;
    virtual void visit(Film* film) = 0;
    virtual void visit(Vinile* vinile) = 0;
};

#endif // ITEMVISITOR_H
