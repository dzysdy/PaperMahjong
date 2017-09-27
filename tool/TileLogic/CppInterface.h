#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include <QQuickItem>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include <string>
using std::vector;
using std::string;

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
        id_(id){
        //toStr();
    }

    bool operator <(const Melds& that) {
        if (id_ != that.id_) {
            return id_ < that.id_;
        }
        return type_ < that.type_;
    }

    const char* toStr() {
        if (str_.empty()) {
            switch (type_) {
            case MT_PAIR:
                str_ = "(" + std::to_string(base_) + ", " + std::to_string(base_) + ")";
                break;
            case MT_MELD:
                str_ = "(" + std::to_string(base_) + ", " + std::to_string(base_) + ", " + std::to_string(base_) + ")";
                break;
            case MT_CHOW:
                str_ = "(" + std::to_string(base_) + ", " + std::to_string(base_+1) + ", " + std::to_string(base_+2) + ")";
                break;
            default:
                break;
            }
        }
        return str_.c_str();
    }

    unsigned base_;
    MeldsType type_;
    int id_;
    string str_;
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
    void discardTilesUpdated(QJsonArray dataList);

public slots:
    void analysisTiles(QString tileString);

private:
    void analysisTiles(vector<unsigned> nums);
    vector<unsigned> takeLonelyTiles(vector<unsigned>& nums);
    void calcAdjacentTiles(const vector<unsigned> &srcNums, vector<unsigned> &adjacentNums);
    bool apendIfNotContain(unsigned i, vector<unsigned>& srcNums);
};

#endif // CPPINTERFACE_H
