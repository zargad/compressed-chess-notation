#ifndef UTILS_H
#define UTILS_H

struct Range {
    int min;
    int max;
};

struct Range range_from_max(int max);


struct Region {
    struct Range x;
    struct Range y;
};

struct Region region_from_max(int x, int y);

struct Region horizontal_region(int y, struct Range x);

struct Region vertical_region(int x, struct Range y);

#endif /* UTILS_H */

