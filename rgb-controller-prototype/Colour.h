class Colour
{
public:
	int r;
	int g;
	int b;

	Colour(int r, int g, int b);
	Colour();
};

Colour::Colour(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
};

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
};
