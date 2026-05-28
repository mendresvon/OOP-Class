#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "MediaItem.h"

class Magazine : public MediaItem {
private:
    int issueNum;
    int month;

public:
    Magazine(const std::string& id, const std::string& title, bool isBorrowed,
             int issueNum, int month);

    int getIssueNum() const;
    int getMonth() const;

    // Polymorphic overrides
    double getFee(int days) const override;
    std::string serialize() const override;
};

#endif
