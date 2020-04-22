using System;
using UnityEngine;

public static class ColourConverter
{
    public static Color32 DecodeColourString(string colourInput)
    {
        if (colourInput == null) return Color.black;

        string currentValue = "";
        int colourIndex = 0;
        int[] rgbValue = new int[3];

        for (int i = 0; i < colourInput.Length; i++)
        {
            if (colourInput == " ") continue;

            //Next RGB value
            if (colourInput[i] == ',' || i == colourInput.Length - 1)
            {
                if (i == colourInput.Length - 1) currentValue += colourInput[i];
                rgbValue[colourIndex] = Int32.Parse(currentValue);

                currentValue = "";
                colourIndex++;
            }

            else currentValue += colourInput[i];
        }

        return new Color32((byte)rgbValue[0], (byte)rgbValue[1], (byte)rgbValue[2], 255);
    }
}
