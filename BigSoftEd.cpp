// BigSoftEd.cpp
#include "BigSoftEd.h"
#include <vector>
//#include "Renderer.h"
/*
	Class Colour - stores 4 ints for red, green, blue, alpha
	Also defines
*/
BSE::Colour::Colour(unsigned int r, unsigned int g, unsigned int b, unsigned int a )
: _r(r), _g(g), _b(b), _a(a)
{}


/*
Class ColourFader - fades a colour to another at a given speed
*/
BSE::ColourFader::ColourFader( BSE::Colour& colour, double speed )
: _speed( speed ), _target(colour),  _tweener(0.0)
{}


void BSE::ColourFader::SetNewColour( const BSE::Colour &col ){
    _to = col;
    _from = _target;  // Store current colour
    _tweener = 0.0;
}


void BSE::ColourFader::Update( const double time ){
	if( _tweener < 1.0 ){
		_tweener += (time / _speed);
		if( _tweener > 1.0 ) {
		    _tweener = 1.0;
		}
		UpdateColour();
	}
}

void BSE::ColourFader::UpdateColour(){
    // static_cast needed as colours are set to unsigned ints.
	_target._r = _from._r + static_cast<int>( _to._r - _from._r ) * _tweener;
	_target._g = _from._g + static_cast<int>( _to._g - _from._g ) * _tweener;
	_target._b = _from._b + static_cast<int>( _to._b - _from._b ) * _tweener;
	_target._a = _from._a + static_cast<int>( _to._a - _from._a ) * _tweener;
}

bool BSE::ColourFader::Finished() const{
    return ( _tweener >= 1.0 );
}

/*
Class Text - simple text display object, with a string, position
*/
BSE::Text::Text( std::string str,
                 BSE::Colour col,
                 PointF pos,
				 BSE::TextSize textSize )
: _str(str), _pos(pos), _size(textSize), _colour(col)
{}

BSE::Text::~Text(){}



PointF BSE::Text::GetPosition() const{
	return _pos;
}

void BSE::Text::SetPosition( const PointF& pos ){
	_pos = pos;
}

std::string BSE::Text::GetString() const{
	return _str;
}

void BSE::Text::SetString( const std::string& str ){
	_str = str;
}

BSE::TextSize BSE::Text::GetSize() const{
	return _size;
}

void BSE::Text::SetSize( const BSE::TextSize size ){
	_size = size;
}

BSE::Colour BSE::Text::GetColour() const{
    return _colour;
}

BSE::Colour& BSE::Text::GetColour(){
    return _colour;
}

void BSE::Text::SetColour( const BSE::Colour &col ) {
    _colour = col;
}

/*
class Line
*/
BSE::Line::Line(const PointF &start, const PointF &end,
          const float thickness,
          BSE::Colour col ):
          _startPos( start ), _endPos( end ), _thickness(thickness),
          _colour(col)
         {}

BSE::Line::~Line(){}

PointF BSE::Line::GetStartPosition() const{
    return _startPos;
}

void BSE::Line::SetStartPosition( const PointF& pos ){
    _startPos = pos;
}

PointF BSE::Line::GetEndPosition() const{
    return _endPos;
}

void BSE::Line::SetEndPosition( const PointF& pos ){
    _endPos = pos;
}

float BSE::Line::GetThickness() const{
    return _thickness;
}

void BSE::Line::SetThickness( const float thickness ){
    _thickness = thickness;
}

BSE::Colour BSE::Line::GetColour() const{
    return _colour;
}

BSE::Colour& BSE::Line::GetColour(){
    return _colour;
}

void BSE::Line::SetColour(const BSE::Colour &col){
    _colour = col;
}


void BSE::Line::Update( double time ){

}

// Display Grid
BSE::DisplayGrid::DisplayGrid(unsigned int rows, unsigned int cols, float rowWidth, float colWidth, const PointF& position )
: numRows_(rows), numCols_(cols), rowWidth_(rowWidth), colWidth_(colWidth), position_(position)
{
    if( numRows_ < 1 ) numRows_ = 1;
    if( numCols_ < 1 ) numCols_ = 1;
    if( rowWidth_ < 0.0f ) rowWidth_ = 0.0f;
    if( colWidth_ < 0.0f ) colWidth_ = 0.0f;
}

void BSE::DisplayGrid::AddColumn(unsigned int num){
    numCols_ += num;
}

void BSE::DisplayGrid::AddRow(unsigned int num){
    numRows_ += num;
}

void BSE::DisplayGrid::RemoveRow(){
    if( numRows_ > 1 )
        --numRows_;
}

void BSE::DisplayGrid::RemoveColumn(){
    if( numCols_ > 1 )
        --numCols_;
}

float BSE::DisplayGrid::RowWidth() const{
    return rowWidth_;
}

float BSE::DisplayGrid::ColWidth() const{
    return colWidth_;
}

unsigned int BSE::DisplayGrid::NumRows() const{
    return numRows_;
}

unsigned int BSE::DisplayGrid::NumCols() const{
    return numCols_;
}

PointF BSE::DisplayGrid::Position() const{
    return position_;
}

RegionF BSE::DisplayGrid::Region() const{
    return RegionF( position_, colWidth_ * numCols_, rowWidth_ * numRows_ );
}

void BSE::DisplayGrid::SetRows( const int rows ){
    if( rows > 0 ) numRows_ = rows;
}

void BSE::DisplayGrid::SetColumns( const int cols ){
    if( cols > 0 ) numCols_ = cols;
}

void BSE::DisplayGrid::SetPosition( const PointF& position ){
    position_ = position;
}

void BSE::DisplayGrid::SetPosition( const float posX, const float posY ){
    SetPosition( PointF(posX, posY));
}

void BSE::DisplayGrid::SetRowWidth( const float width ){
    if( width > 0.0f ) rowWidth_ = width;
}

void BSE::DisplayGrid::SetColumnWidth( const float width ){
    if( width > 0.0f) colWidth_ = width;
}

PointF BSE::DisplayGrid::PrintPosition(const int row, const int col) const {
    return PointF( position_.x_ + colWidth_ * (col),
                   position_.y_ + rowWidth_ * (row) );
}

void BSE::DisplayGrid::RowColFromPoint( const PointF &point, int &row, int &col ) const{
    row = col = -1;
    PointF p = position_;
    // Find Row
    while( p.y_ <= point.y_){
        ++row;
        p.y_ += rowWidth_;
    }
    if( row > numRows_) row = -1; // Off grid
    while( p.x_ <= point.x_){
        ++col;
        p.x_ += colWidth_;
    }
    if( col > numCols_) col = -1; // Off grid
}

bool BSE::DisplayGrid::CellsOverlap(const int row1, const int col1, const int size1,
                                    const int row2, const int col2, const int size2 ) const{
    if( row1 != row2 ) return false;

    if( col1 == col2 ) return true;

    if( ( col1 > col2 && col1 - size1 >= col2 ) ||
        col2 - size2 >= col1 )
            return false;

    return true;
}


void BSE::DisplayGrid::PrintGrid( Renderer &renderer ) const{

    PrintGridInterior(renderer);
    PrintGridLines(renderer);
}

void BSE::DisplayGrid::PrintGridInterior( Renderer &renderer )const{
   // renderer.DisplayFilledRectangle(BSE::EdGrey, Region());
}

void BSE::DisplayGrid::PrintGridLines( Renderer &renderer) const{
    int numHorizontalLines = numRows_ + 1;
    int numVerticalLines = numCols_ + 1;
    float horizontalLineLength = colWidth_ * numCols_;
    float verticalLineLength = rowWidth_ * numRows_;
    PointF pos = position_;
    for( int i = 0; i < numHorizontalLines; ++i){
       // renderer.Display(BSE::Line(pos, PointF( pos.x_+ horizontalLineLength, pos.y_),1.0f ) );
        pos.y_ += rowWidth_;
    }
    pos = position_;
    for( int i = 0; i < numVerticalLines; ++i){
       // renderer.Display(BSE::Line(pos, PointF( pos.x_, pos.y_ + verticalLineLength),1.0f ) );
        pos.x_ += colWidth_;
    }
}

PointF BSE::DisplayGrid::Snap(const PointF& position) const{
    PointF newPosition( position );
    Snap( newPosition );
    return newPosition;
}

void BSE::DisplayGrid::Snap(PointF& position) const{
    float posX = position_.x_;
    float posY = position_.y_;
    //TODO: restrict by grid size
    while( posX + colWidth_ < position.x_ &&
           posX + colWidth_ < position_.x_ + (colWidth_* numCols_)) {
        posX += colWidth_;
    }
    while( posY + rowWidth_ < position.y_ &&
           posY +rowWidth_ < position_.y_ + (rowWidth_ * numRows_)){
        posY += rowWidth_;
    }
    position.x_ = posX;
    position.y_ = posY;
}
