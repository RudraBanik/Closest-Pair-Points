#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct Point
{
    double x, y;
    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
} points[N];

double dist(Point a, Point b)
{
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double closestPair(int l, int r)
{
    if (l >= r)
        return 1e9;
    if (l + 1 == r)
        return dist(points[l], points[r]);

    int mid = l + r >> 1;
    double d = min(closestPair(l, mid), closestPair(mid + 1, r));

    int i = l, j = mid + 1, k = 0;
    Point strip[r - l + 1];
    while (i <= mid && j <= r)
    {
        if (points[i] < points[j])
            strip[k++] = points[i++];
        else
            strip[k++] = points[j++];
    }
    while (i <= mid)
        strip[k++] = points[i++];
    while (j <= r)
        strip[k++] = points[j++];
    for (int i = 0; i < k; i++)
        points[l + i] = strip[i];

    i = 0;
    for (int j = l; j <= r; j++)
    {
        if (abs(points[j].x - points[mid].x) >= d)
            continue;
        while (i < k - 1 && points[l + i + 1].y < points[j].y)
            i++;
        for (int t = i; t < k && points[l + t].y - points[j].y < d; t++)
        {
            if (mid - l >= 1 && r - mid >= 1)
            {
                d = min(d, dist(points[mid - 1], points[mid]));
                d = min(d, dist(points[mid], points[mid + 1]));
            }
        }
    }

    return d;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    sort(points, points + n);
    cout << closestPair(0, n - 1) << endl;
    return 0;
}
