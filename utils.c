

struct Range {
    int min;
    int max;
};

struct Range range_from_max(int max) 
{
    return (struct Range) {0, max};
}


struct Region {
    struct Range x;
    struct Range y;
};

struct Region region_from_max(int x, int y) 
{
    return (struct Region) {range_from_max(x), range_from_max(y)};
}

struct Region horizontal_region(int y, struct Range x)
{
    return (struct Region) {x, (struct Range) {y, y + 1}};
}

struct Region vertical_region(int x, struct Range y)
{
    return (struct Region) {(struct Range) {x, x + 1}, y};
}

