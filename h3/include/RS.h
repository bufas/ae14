#pragma once

class RS {

public:
    virtual ~RS() {}
    virtual int rank(const int x) const = 0;
    virtual int select(const int x) const = 0;

};