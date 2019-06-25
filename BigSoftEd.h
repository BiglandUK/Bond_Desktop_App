//BigSoftEd.h

#ifndef BIGSOFTED_H
#define BIGSOFTED_H

#include <string>
#include "Utility.h"
class Renderer;

namespace BSE{

// generic colour class
class Colour{
public:
    unsigned int _r,_g,_b,_a;

    Colour( unsigned int r=0, unsigned int g=0, unsigned int b=0, unsigned int a=255 );
};

// Input colours
static const BSE::Colour Error      = BSE::Colour(250, 50, 50);
static const BSE::Colour Input      = BSE::Colour( 30, 30,100);
static const BSE::Colour Inactive   = BSE::Colour(180,180,180);
// Text
static const BSE::Colour Normal     = BSE::Colour( 30, 30, 30);
static const BSE::Colour Mute       = BSE::Colour(180,180,180);
static const BSE::Colour Highlight  = BSE::Colour(200,200, 50);

static const BSE::Colour LightGrey  = BSE::Colour(231,231,231);
static const BSE::Colour EdGrey     = BSE::Colour(149,161,173);
static const BSE::Colour DarkGrey   = BSE::Colour( 70, 75, 81);
static const BSE::Colour Red        = BSE::Colour(217,115,115);
static const BSE::Colour Orange     = BSE::Colour(255,209, 71);
static const BSE::Colour Green      = BSE::Colour( 49,149, 49);
static const BSE::Colour Blue       = BSE::Colour( 44, 47,140);
static const BSE::Colour Purple     = BSE::Colour(150,50, 150);

// Fades between colours.
class ColourFader {
public:
    ColourFader( BSE::Colour& colour, double speed = 0.5 );

    void Update( const double time );
    void SetNewColour( const BSE::Colour& col );

    bool Finished() const;

private:
	void UpdateColour();

private:
    const double _speed;

protected:
    BSE::Colour& _target; // ref to object's colour
    BSE::Colour _to; // colour to change to
    BSE::Colour _from; // colour to change from
    double _tweener; // a value less than 1 means a fade is in progress

};

// Set text sizes.
enum TextSize{ XS=24, S=36, M=48, L=60, XL=72 };
// generic text class
class Text{
public:
    Text( std::string str ="",
          BSE::Colour = BSE::Normal,
          PointF pos = PointF(0.0f, 0.0f),
		  BSE::TextSize textSize = BSE::M );

	~Text();

    PointF GetPosition() const;
    void SetPosition( const PointF& pos );

    std::string GetString() const;
    void SetString( const std::string& str );

    BSE::TextSize GetSize() const;
    void SetSize( const BSE::TextSize size );

    BSE::Colour GetColour() const;
    BSE::Colour& GetColour();
    void SetColour( const Colour& col );

	void Display( Renderer &renderer );

private:
    std::string _str;
    PointF _pos;
    BSE::TextSize _size;
    BSE::Colour _colour;
};

// generic line class
class Line{
public:
    Line( const PointF &start = PointF(0.0f, 0.0f), const PointF &end = PointF(0.0f, 0.0f),
          const float thickness = 1.0f,
          BSE::Colour col = BSE::Normal );
    ~Line();

    PointF GetStartPosition() const;
    void SetStartPosition( const PointF& pos );

    PointF GetEndPosition() const;
    void SetEndPosition( const PointF& pos );

    float GetThickness() const;
    void SetThickness( const float thickness );

    BSE::Colour GetColour() const;
    BSE::Colour& GetColour();

    void SetColour( const BSE::Colour &col );

	void Update( double time );
	void Display( Renderer &renderer );

private:
    PointF _startPos, _endPos;
    float _thickness;
    BSE::Colour _colour;
};

/** Divides an area of the screen into a grid
 This is used to calculate print locations and control snap to grid.
 The grid is ZERO based.
 */
class DisplayGrid{
private:
    unsigned int numRows_, numCols_;
    float rowWidth_, colWidth_;
    PointF position_;

    struct Cell{
        unsigned int row_, col_;
    };

public:
    DisplayGrid( unsigned int rows, unsigned int cols, float rowWidth, float colWidth, const PointF& position );

    PointF PrintPosition( const int row, const int col) const; // returns print location for a specified cell
    void RowColFromPoint( const PointF &point, int &row, int& col ) const; // stores row and col positions for a supplied Point. records -1 if off grid
    /** CellsOverlap - utility that compares the location of two horizontal cell ranges and returns true if they overlap
    */
    bool CellsOverlap( const int row1, const int col1, const int size1,
                                    const int row2, const int col2, const int size2 ) const;

    void PrintGrid( Renderer &renderer ) const;
    void PrintGridInterior( Renderer &renderer )const;
    void PrintGridLines( Renderer &renderer) const;

    void AddRow( unsigned int num = 1 );
    void AddColumn( unsigned int num = 1 );
    void RemoveRow(); // removes last row - to a minimum of 1
    void RemoveColumn(); // removes last column - to a minimum of 1

    //Setters
    void SetRowWidth( const float width );
    void SetColumnWidth( const float width );
    void SetRows( const int rows );
    void SetColumns( const int cols );
    void SetPosition( const PointF& position );
    void SetPosition( const float posX, const float posY);

    //Getters
    unsigned int NumRows() const;
    unsigned int NumCols() const;
    float ColWidth() const;
    float RowWidth() const;
    PointF Position() const;
    RegionF Region() const;

    //Snap takes a location and returns/transforms to the corner of the grid cell it is in
    PointF Snap( const PointF& position ) const;
    void Snap( PointF& position ) const;

};

}; // end BSE namespace

#endif
