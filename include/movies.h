#ifndef MOVIES_H
#define MOVIES_H
#include <string>

class movies
{
public:
    movies();
    virtual ~movies();
    int userid;
    int movieid;
    float rating;
    long int timestamp;

};

#endif // MOVIES_H
