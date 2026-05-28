#ifndef DVD_H
#define DVD_H

#include "MediaItem.h"

class Dvd : public MediaItem {
private:
    std::string director;
    int duration; // minutes

public:
    Dvd(const std::string& id, const std::string& title, bool isBorrowed,
        const std::string& director, int duration);

    std::string getDirector() const;
    int getDuration() const;

    // Polymorphic overrides
    double getFee(int days) const override;
    std::string serialize() const override;
};

#endif
