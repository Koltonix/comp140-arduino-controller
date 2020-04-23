//////////////////////////////////////////////////
// Christopher Robertson 2020.
// https://github.com/Koltonix
// MIT License Copyright (c) 2020
//////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using UnityEngine;


/// <summary>Stores all of the custom extension methods.</summary>
public static class ExtensionMethods
{
    /// <summary>Converts a string to a Color32.</summary>
    /// <param name="colourInput"></param>
    /// <returns>The string as a Color32.</returns>
    /// <remarks>The input should be the format of 'r,g,b'.</remarks>
    public static Color32 ToColour(this string colourInput)
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

    /// <summary>Decodes the Arduino Message and disconcatenate the strings</summary>
    /// <param name="message"></param>
    /// <returns>An string array of all of the values separated.</returns>
    /// <remarks>
    /// It should start and end with '<' and '>' and use '/' to separate values.
    /// <0/0/60/0/0.00/255,0,0/0,0,255/255,255,0/0,255,255/0> Example.
    /// </remarks>
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