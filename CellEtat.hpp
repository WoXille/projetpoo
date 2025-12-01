#ifndef CELLETAT_HPP
#define CELLETAT_HPP

class CellEtat {
    public:
    virtual ~CellEtat() = default;
    virtual bool estVivante() const = 0;
    virtual bool estObstacle() const = 0;
    virtual CellEtat* clone() const = 0;
};

#endif