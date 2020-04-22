using System;
using System.Collections.Generic;
using UnityEngine;

public static class ExtensionMethods
{
    public static Color32 DecodeColourString(this string colourInput)
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

    private static string lastValue;

    /// <0/0/60/0/0.00/255,0,0/0,0,255/255,255,0/0,255,255>
    public static string[] DecodeArduinoString(this string message)
    {
        List<string> allStrings = new List<string>();

        int index = 0;
        lastValue = "";

        for (int i = 0; i < message.Length; i++)
        {
            //Must start with the opening
            if (message[0] != '<') return null;
            if (message[i] == '<') continue;

            if (message[i] == '/' || message[i] == '>')
            {
                allStrings.Add(lastValue);

                lastValue = "";
                index++;
            }

            else lastValue += message[i];
        }

        return allStrings.ToArray();
    }
}