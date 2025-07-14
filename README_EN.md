This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gvector
Library for working with 2 measured vectors

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [use] (#usage)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id = "USAGE"> </A>

## Usage
### class gvector
### Constructor
`` `CPP
Float X = 0;
Float y = 0;

Contexpr Gvector ();
CONSTEXPR GVECTOR (Float X, Float Y);
`` `

### Factory
`` `CPP
// Create from the corner (single)
Static Gvector Fromangle (Float RAD);

// Create from polar coordinates
Static Gvector Frompolar (Float Rad, Float Mag);

// Create zero
Static Gvector fromzero ();
`` `

### static methods
`` `CPP
// from radian to degrees
Static Float Todeg (Float RAD);

// From degrees to radian
Static Float Torad (Float Deg);

// The shortest angle of rotation from From From to TO (Radiana)
Static Float Shortangle (Float from, Float To);

// The shortest angle of rotation from from from TO (degrees)
Static int Shortangledeg (Int From, Int to);

// angle between
Static Float AnglebetWeen (Constus Gvector & A, Constus Gvector & B);

// distance between square
Static Float Distsq (Conster & A, Constor & B);

// distance between
Static Float Dist (Conster & a, Constor & B);

// Scalar work (== 0 - perpendicular,> 0 in one direction, <0 in opposite)
Static Float Dot (Conster & A, Conster & B);

// Vector work (<0 - clock,> 0 against the sentry)
Static Float Cross (Conster & A, Conster & B);

// Vector projection on another vector
Static Gvcestor Project (Conster & A, Constor & B);

// Point Pocation P on line AB
Static Gvcestor ProjectPoint (COST GVECTOR & A, COST GVECTOR & B, COST GVECTOR & P);

// distance (perpendicular) from point P to line AB
Static Float Distoline (Conster & a, Constor & B, Conster & P);

// Fold
Static Gvector Add (Constor & V1, Constor & V2);
Static Gvector Add (Constor & V1, Float S);

// subtract
Static Gvcestor Sub (COST GVECTOR & V1, COST GVECTOR & V2);
Static Gvcestor Sub (Constor & V1, Float S);

// multiply
Static Gvector Mul (Constor & V1, Conster Gvector & V2);
Static Gvector Mul (Constor & V1, Float S);

// divide
Static Gvcestor Div (COST GVECTOR & V1, COST GVECTOR & V2);
Static Gvcestor Div (Conster & V1, Float S);
`` `

### Arithmetic
`` `CPP
// ================= porn ==================================================
GVECTOR & Add (Float V);
Gvector & Operator+= (Float V);
Gvector Operator+(Float V);

GVECTOR & Add (COST GVECTOR & V);
GVECTOR & Operator+= (COST GVECTOR & V);
GVECTOR Operator+(COST GVECTOR & V);

// ================= sub ==================================================
GVECTOR & SUB (Float V);
Gvector & Operator-= (Float V);
Gvector Operator- (Float V);

GVECTOR & Sub (COST GVECTOR & V);
GVECTOR & Operator-= (COST GVECTOR & V);
Gvector Operator- (COST GVECTOR & V);

Gvector Operator- ();

// ================= Mul =========================================
GVECTOR & MUL (Float V);
Gvector & Operator*= (Float V);
Gvector Operator*(Float V);

GVECTOR & MUL (COST GVECTOR & V);
GVECTOR & Operator*= (COST GVECTOR & V);
Gvector Operator*(COST GVECTOR & V);

// ================ s ==================================================
GVECTOR & DIV (Float V);
Gvector & Operator/= (Float V);
GVECTOR Operator/(Float V);

GVECTOR & DIV (COST GVECTOR & V);
GVECTOR & Operator/= (COST GVECTOR & V);
GVECTOR Operator/(COST GVECTOR & V);
`` `

### comparison
`` `CPP
// Checking equality, taking into account Epsilon
Bool Equals (Constor & V, Float Tolerance = 1e-6F);

Bool Operator == (COST GVECTOR & V);

Bool Operator! = (COST GVECTOR & V);

// check for zero length
Operator Bool ();
`` `

#### Get
`` `CPP
// Create a copy
Gvector Copy ();

// Length in the square
Float magsq ();

// length
Float mag ();

// Scalar work (== 0 - perpendicular,> 0 in one direction, <0 in opposite)
Float DOT (COST GVECTOR & V);

// Vector work (turn to v: <0 - clock,> 0 against the sentry)
Float Cross (Conster & V);

// Comparison in the direction with angular tolerance
Bool ISPArallelto (COST GVECTOR & V, FLOAT TOLOLANCE = 1E-6F);

// angle between
Float AnglebetWeen (Constus Gvector & V);

// Normal
Gvector normal ();

// Normalized copy
Gvector Normalized ();

// Production length on vector
Float ProjectMag (Constus Gvector & V);

// Vector projection on another vector
Gvector Project (COST GVECTOR & V);

// Proof of the point on the AB line
GVECTOR ProjectPoint (Conster & A, Constus Gvector & B);

// Distance (perpendicular) to line AB
Float DistToline (Conster & A, Constor & B);

// distance in the square
Float Distsq (Conster & V);

// distance to
Float Dist (Conster & V);

// The current angle between the vector and the axis X
Float Heading ();

// The current angle between the vector and the axis X
Float Headingdeg ();

// Check for zero or Epsilon
Bool Iszero (Float Epsilon = 1e-6F);
`` `

#### Modification
`` `CPP
// install
Inline Gvector & Set (Float X, Float Y);

// install in 0
GVECTOR & SETZERO ();

// turn onto the corner
GVECTOR & ROTATE (Float RAD);

// turn in the direction of the vector
GVECTOR & ROTATETO (COST GVECTOR & TARGET);

// turn by +90 °
GVECTOR & ROTATE90CCCW ();

// turn by -90 °
GVECTOR & ROTATE90CW ();

// turn on 180 (reflect along yourself)
GVECTOR & ROTATE180 ();

// Reflect on the axis x
GVECTOR & ReflectX ();

// Reflect on the axis Y
Gvector & Reflecty ();

// Reflect by normal (should be normalized)
GVECTOR & Reflect (COST GVECTOR & NORMAL);

// normalize
GVECTOR & NORMALIZE ();

// Set the length
GVECTOR & SETMAG (Float V);

// limit the length from above
GVECTOR & LIMIT (Float Mag);

// Limit the length in the range
GVECTOR & CLAMP (Float Minm, Float Maxm);

// Install the direction
GVECTOR & SETHEADING (FLOAT RAD);

// Install the direction
GVECTOR & SETHEADINGDEG (Int Deg);

// Interpolate the current vector to V, where t is the coefficient from 0.0 to 1.0.
GVECTOR & LERP (COST GVECTOR & V, FLOAT T);
`` `

## Examples
### Movement with a rebound
`` `CPP
int w = 200, h = 100;
GVECTOR POS (W / 2, H / 2);
GVECTOR VEL (3, 2);

VOID loop () {
POS += Vel;
if (pos.x> = w || pos.x <0) {
pos.x = constrain (pos.x, 0, w - 1);
Vel.reflecty ();
}
if (pos.y> = h || pos.y <0) {
pos.y = constrain (pos.y, 0, h - 1);
Vel.reflectx ();
}
DELAY (30);
}
`` `

### distance between points
`` `CPP
GVECTOR A (10, 20);
GVECTOR B (30, 40);
Gvector ab = b - a;
Float Dist = Ab.mag ();
`` `

<a ID = "Versions"> </a>

## versions
- V1.0

<a id = "Install"> </a>
## Installation
- The library can be found by the name ** gvector ** and installed through the library manager in:
- Arduino ide
- Arduino ide v2
- Platformio
- [download the library] (https://github.com/gyverlibs/gvector/archive/refs/heads/main.zip) .Zip archive for manual installation:
- unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
- unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
- unpack and put in *documents/arduino/libraries/ *
- (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
-read more detailed instructions for installing libraries[here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id = "Feedback"> </a>

## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code