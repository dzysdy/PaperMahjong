#include "MahjongSocreRecorder.h"

void MahjongSocreRecorder::setScore(const vector<unsigned> &value)
{
    mahjongScore = value;
}

bool MahjongSocreRecorder::updateScore(unsigned priority, unsigned score)
{
    if (mahjongScore.size() > priority) {
        mahjongScore[priority] = score;
        return true;
    }
    return false;
}

void MahjongSocreRecorder::appendScore(unsigned score)
{
    mahjongScore.push_back(score);
}

void MahjongSocreRecorder::clearSocre()
{
    mahjongScore.clear();
}
