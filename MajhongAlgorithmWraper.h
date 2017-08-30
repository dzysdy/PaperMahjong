#ifndef MAJHONGALGORITHMWRAPER_H
#define MAJHONGALGORITHMWRAPER_H

#include <QObject>
#include <vector>

using std::vector;

class PaperCard;
class MajhongAlgorithm;
class MajhongAlgorithmWraper
{
public:
    static MajhongAlgorithmWraper* instance();

    bool isChow(const QList<PaperCard*>& cards);
    bool isPair(const QList<PaperCard*>& cards);
    bool isMelds(const QList<PaperCard*>& cards);
    bool isHappyGroup(const QList<PaperCard*>& cards);
    bool isWinningHand(const QList<PaperCard*>& cards);

    int calcCurrentScore(const QList<PaperCard*>& cards);
    QList<QList<PaperCard*>> scanHappyGroups(QList<PaperCard*> cards);
    PaperCard* scanDiscard(QList<PaperCard*> cards);

private:
    MajhongAlgorithmWraper();
    vector<unsigned> cards2Numbers(const QList<PaperCard*>& cards);

    static MajhongAlgorithmWraper* me;
    MajhongAlgorithm* algorithm;
};

#endif // MAJHONGALGORITHMWRAPER_H
