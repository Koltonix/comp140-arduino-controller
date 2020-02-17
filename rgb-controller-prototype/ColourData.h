#include "ColourData.cpp"

ColourData::ColourData(int _r, int _g, int _b)
{
	int rgb[3] = { _r, _g, _b };

	for (int i = 0; i < sizeof(rgb); i++)
	{
		if (rgb[i] > 255)
		{
			rgb[i] = 255;
			continue;
		}

		else if (rgb[i] < 0)
		{
			rgb[i] = 0;
			continue;
		}
	}

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
};