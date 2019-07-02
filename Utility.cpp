#include "Utility.h"
#include <cmath>
#include <cstdlib>

// PointF
PointF::PointF()
:   x_(0.0f), y_(0.0f)
{}

PointF::PointF( const float x, const float y )
: x_(x), y_(y)
{}

PointF::PointF(const PointI &point){
    x_ = static_cast<float>(point.x_);
    y_ = static_cast<float>(point.y_);
}

PointF PointF::operator+( const PointF& point ) const{
   return PointF(x_ + point.x_,
                 y_ + point.y_ );
}

PointF PointF::operator-( const PointF& point ) const{
    return PointF(x_ - point.x_,
                  y_ - point.y_);
}

PointF& PointF::operator+=(const PointF& rhs){
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

bool PointF::operator == ( const PointF& point ) const{
    return (x_ == point.x_) &&
           (y_ == point.y_);
}

// PointI

PointI::PointI()
: x_(0), y_(0)
{}

PointI::PointI(const int x, const int y)
: x_(x), y_(y)
{}

PointI::PointI( const PointI &point )
: x_(point.x_), y_(point.y_)
{}

PointI::PointI(const PointF &point){
    x_ = static_cast<int>(point.x_);
    y_ = static_cast<int>(point.y_);
}

PointI PointI::operator=( const PointI& point){
    if( this != &point ){
        x_ = point.x_;
        y_ = point.y_;
    }
    return *this;
}

PointI PointI::operator+(const PointI &point) const{
    return PointI( x_ + point.x_,
                   y_ + point.y_ );
}

PointI PointI::operator-(const PointI &point) const{
    return PointI( x_ - point.x_,
                   y_ - point.y_ );
}

bool PointI::operator ==(const PointI &point) const{
    return ( x_ == point.x_ ) &&
           ( y_ == point.y_ );
}

RegionF::RegionF()
: left_(0.0f), top_(0.0f), width_(0.0f), height_(0.0f)
{}

RegionF::RegionF(float left, float top, float width, float height)
: left_(left), top_(top), width_(width), height_(height)
{}

RegionF::RegionF( PointF pt, float width, float height )
: left_(pt.x_), top_(pt.y_), width_(width), height_(height)
{}

PointF RegionF::Position() const{
    return PointF( left_, top_ );
}

void RegionF::SetPosition( const PointF &pos ){
    left_ = pos.x_;
    top_ = pos.y_;
}

//PointInsideRegion

bool PointInsideRegionF(const PointF& clickPoint,
                   const PointF& regionStart,
                   const float regionWidth, const float regionHeight){

    return( clickPoint.x_ >= regionStart.x_ &&
            clickPoint.y_ >= regionStart.y_ &&
            clickPoint.x_ <= regionStart.x_ + regionWidth &&
            clickPoint.y_ <= regionStart.y_ + regionHeight );
}

bool PointInsideRegionF( const PointF &clickPoint, const RegionF &region ){
    return  clickPoint.x_ >= region.left_ &&
            clickPoint.y_ >= region.top_  &&
            clickPoint.x_ <= region.left_ + region.width_ &&
            clickPoint.y_ <= region.top_  + region.height_;
}

bool PointInsideRegion(const PointI& clickPoint,
                   const PointI& regionStart,
                   const int regionWidth, const int regionHeight){

    return( clickPoint.x_ >= regionStart.x_ &&
            clickPoint.y_ >= regionStart.y_ &&
            clickPoint.x_ <= regionStart.x_ + regionWidth &&
            clickPoint.y_ <= regionStart.y_ + regionHeight );
}

bool PointInsideRegion(const PointI& clickPoint, const RegionF &region ){
    return  clickPoint.x_ >= region.left_ &&
            clickPoint.y_ >= region.top_ &&
            clickPoint.x_ <= region.left_ + region.width_ &&
            clickPoint.y_ <= region.top_ + region.height_;
}

bool PointInsideCircle( const PointF& clickPoint, const PointF& circleCentre, const float& radius ){
    float side1 = fabsf(clickPoint.x_ - circleCentre.x_);
    float side2 = fabsf(clickPoint.y_ - circleCentre.y_);
    return sqrtf( (side1 * side1) + (side2 * side2) ) <= radius;
}

// Random number functions
int Random(Range r)
{
	return r.mLow + rand() % ((r.mHigh + 1) - r.mLow);
}

// Returns a random number in [low, high].
int Random(int low, int high)
{
	return low + rand() % ((high + 1) - low);
}

bool PercentageChance(int percent) {
	return Random(1, percent) <= percent;
}

// generic number functions
int Largest( const int num1, const int num2 ){
    return num1 > num2 ? num1 : num2;
}

int NumNonZeroDigits( const int num ){
    if( num <= 0 ) return 0;// Special case

    int n = num;
    int count = 0;
    while( n > 0 ){
            if( n % 10 > 0) ++count;
            n /= 10;
    }
    return count;
}

int NumDigits( const int num ){
    if( num <= 0 ) return 0;

    int n = num;
    int count = 0;
    while( n > 0 ){
        ++count;
        n /= 10;
    }
    return count;
}
