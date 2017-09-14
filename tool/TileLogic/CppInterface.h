#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include <QQuickItem>
#include <vector>
using std::vector;

struct Melds {
    enum MeldsType {
        MT_PAIR,
        MT_MELD,
        MT_CHOW,
        MT_UNDEFINED
    };
    Melds(unsigned b, MeldsType t, int id):
        base_(b),
        type_(t),
        id_(id){}

    bool operator <(const Melds& that) {
        return id_ < that.id_;
    }

    unsigned base_;
    MeldsType type_;
    int id_;
};

class CppInterface : public QQuickItem
{
    Q_OBJECT
public:
    CppInterface();

signals:
    void tileModelUpdated(QString tileModelData);
    void lonelyTilesUpdated(QString lonelyTiles);
    void readyStepsUpdated(int steps);

public slots:
    void analysisTiles(QString tileString);

private:
    void analysisTiles(vector<unsigned> nums);
    vector<unsigned> takeLonelyTiles(vector<unsigned>& nums);
    void calcAdjacentTiles(const vector<unsigned> &srcNums, vector<unsigned> &adjacentNums);
    bool apendIfNotContain(unsigned i, vector<unsigned>& srcNums);
};

#endif // CPPINTERFACE_H
