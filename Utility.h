// Utility.h
#ifndef UTILITY_H
#define UTILITY_H

class PointI;

class PointF {
public:
   PointF();
   PointF( const float x, const float y );
   PointF( const PointI &point); // conversion

   PointF operator+(const PointF& point) const;
   PointF operator-(const PointF& point) const;
   PointF& operator+=(const PointF& rhs);
   bool operator==(const PointF& point) const;

public:
    float x_;
    float y_;
};

class PointI {
public:
    PointI();
    PointI( const int x, const int y );
    PointI( const PointI &point );
    PointI( const PointF &point ); // conversion

    PointI operator=( const PointI& point );
    PointI operator+( const PointI& point ) const;
    PointI operator-( const PointI& point ) const;

    bool operator==( const PointI& point ) const;

public:
    int x_;
    int y_;
};

class RegionF{
public:
    RegionF();
    RegionF( float left, float top, float width, float height );
    RegionF( PointF pt, float width, float height );

    PointF Position() const;
    void SetPosition( const PointF &pos);

    float left_, top_, width_, height_;
};

//#include <windows.h>
//#include <gdiplus.h>
//
//
//template <typename T>
//static bool deleteAll( T* theElement )
// { delete theElement; return true; }
//
bool PointInsideRegionF(const PointF& clickPoint,
                   const PointF& regionStart,
                   const float regionWidth, const float regionHeight);


bool PointInsideRegionF( const PointF &clickPoint, const RegionF &region );

bool PointInsideRegion(const PointI& clickPoint,
                   const PointI& regionStart,
                   const int regionWidth, const int regionHeight);

bool PointInsideRegion(const PointI& clickPoint, const RegionF &region );

bool PointInsideCircle(const PointF& clickPoint, const PointF& circleCentre, const float& radius );

// generic functions
int Largest( const int num1, const int num2 ); // will return num2 if both numbers are equal.
int NumNonZeroDigits( const int num ); //returns number of non-zero digits in a number. Will return 0 if number is <= 0.

int NumDigits( const int num );
#endif
