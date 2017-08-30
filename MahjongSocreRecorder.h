#ifndef MAHJONGSOCRERECORDER_H
#define MAHJONGSOCRERECORDER_H

#include <vector>

using std::vector;

enum ScorePriority {
    SP_MELDSNUM,    // melds and chows count
    SP_FIRSTTILE,   // the count of tiles whitch can increase the count of SP_MELDSNUM.
    SP_SECONDTILE,  // ditto.
    SP_THIRDTILE
};

class MahjongSocreRecorder
{
public:
    MahjongSocreRecorder() = default;

    bool operator < (const MahjongSocreRecorder& that) const {
        for (unsigned i = 0, j = 0; i < mahjongScore.size() && j < that.mahjongScore.size(); ++i, ++j) {
            if (mahjongScore[i] != that.mahjongScore[j])
                return mahjongScore[i] < that.mahjongScore[j];
        }
        return mahjongScore.size() < that.mahjongScore.size();
    }

    bool operator > (const MahjongSocreRecorder& that) {
        return that < (*this);
    }

    bool operator == (const MahjongSocreRecorder& that) {
        return (*this < that) == (that < *this);
    }

    void setScore(const vector<unsigned> &value);

    bool updateScore(unsigned priority, unsigned score);

    void appendScore(unsigned score);

    void clearSocre();

private:
    vector<unsigned> mahjongScore;
};

#endif // MAHJONGSOCRERECORDER_H
