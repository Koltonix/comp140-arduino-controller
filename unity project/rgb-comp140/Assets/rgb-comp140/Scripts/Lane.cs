using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

namespace comp140.data
{
    [Serializable]
    public class Lane
    {
        [Header("Lane Identifier")]
        public int laneIndex = 0;

        [Header("Lane Input")]
        public float encoderValue = 0.0f;

        [Header("Lane State")]
        public int score = 0;
        public float currentAngle = 0.0f;
        public float timeLeft = 0.0f;

        private const int maxNumOfColours = 3;
        public Color32 selectedColour = Color.black;
        public Color32[] colourOrder = new Color32[maxNumOfColours];

        [Header("UI Settings")]
        [SerializeField]
        private TextMeshProUGUI[] laneEncoderValue;
        [SerializeField]
        private TextMeshProUGUI[] laneTime;

        [SerializeField]
        private Image[] selectedColours;
        [SerializeField]
        private Image[] queuedColours;

        [Header("String Decoder")]
        [HideInInspector]
        private string lastValue;
        public string[] allValues;

        public Lane(int laneIndex)
        {
            this.laneIndex = laneIndex;
        }

        public void AssignStringsToValues(string[] allStrings)
        {
            score = Convert.ToInt32(allStrings[0]);
            laneIndex = Convert.ToInt32(allStrings[1]);
            currentAngle = float.Parse(allStrings[2]);
            encoderValue = Convert.ToInt32(allStrings[3]);
            timeLeft = float.Parse(allStrings[4]);

            selectedColour = allStrings[5].DecodeColourString();
            colourOrder[0] = allStrings[6].DecodeColourString();
            colourOrder[1] = allStrings[7].DecodeColourString();
            colourOrder[2] = allStrings[8].DecodeColourString();
        }
    }

}