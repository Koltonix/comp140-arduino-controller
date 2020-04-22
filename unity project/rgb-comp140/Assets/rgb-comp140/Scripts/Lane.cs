//////////////////////////////////////////////////
// Christopher Robertson 2020.
// https://github.com/Koltonix
// MIT License Copyright (c) 2020
//////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

namespace comp140.data
{
    [Serializable]
    public class Lane : MonoBehaviour
    {
        [Header("Lane Identifier")]
        #region private int laneIndex;
        private int laneIndex = 0;
        public int LaneIndex
        {
            get { return laneIndex; }
            set
            {
                laneIndex = value;
            }
        }
        #endregion

        [Space]

        [Header("Lane Input")]
        #region private float encoderValue;
        private float encoderValue;
        public float EncoderValue
        {
            get { return encoderValue; }
            set
            {
                encoderValue = value;
                encoderValueText.text = encoderValue.ToString();
            }
        }

        #endregion
        [SerializeField]
        #region private int canInput;
        private bool canInput;
        public bool CanInput
        { 
            get { return canInput; }
            set
            {
                canInput = value;
                lostImage.SetActive(!canInput);
            }
        }
        #endregion
        [Space]

        [Header("Lane State")]
        #region private int score;
        private int score = 0;
        public int Score
        { 
            get { return score; }
            set
            {
                score = value;
                scoreText.text = "Score:\n" + score;
            }
        }
        #endregion
        #region private float currentAngle;
        private float currentAngle = 0.0f;
        public float CurrentAngle
        {
            get { return currentAngle; }
            set
            {
                currentAngle = value;
                currentAngleText.text = currentAngle.ToString();
            }
        }
        #endregion
        #region private float timeLeft;
        private float timeLeft = 0.0f;
        public float TimeLeft
        {
            get { return timeLeft; }
            set
            {
                timeLeft = value;
                timerText.text = timeLeft.ToString();
            }
        }
        #endregion

        public Color32 selectedColour = Color.black;
        private Color32[] colourOrder;
        [Space]

        [Header("String Decoder")]
        [HideInInspector]
        private string lastValue;
        public string[] allValues;
        [Space]

        [Header("UI Settings")]
        [SerializeField]
        private TextMeshProUGUI indexText;
        [SerializeField]
        private TextMeshProUGUI scoreText;
        [SerializeField]
        private TextMeshProUGUI currentAngleText;
        [SerializeField]
        private TextMeshProUGUI encoderValueText;
        [SerializeField]
        private TextMeshProUGUI timerText;

        [SerializeField]
        private Image[] laneColours;
        [SerializeField]
        private GameObject lostImage;

        public Lane(int laneIndex)
        {
            this.LaneIndex = laneIndex;
        }

        public void AssignStringsToValues(string[] allStrings)
        {
            if (allStrings != null)
            {
                Score = Convert.ToInt32(allStrings[0]);
                LaneIndex = Convert.ToInt32(allStrings[1]);
                CurrentAngle = float.Parse(allStrings[2]);
                EncoderValue = Convert.ToInt32(allStrings[3]);
                TimeLeft = float.Parse(allStrings[4]);

                selectedColour = allStrings[5].DecodeColourString();

                colourOrder = new Color32[3];
                colourOrder[0] = allStrings[6].DecodeColourString();
                colourOrder[1] = allStrings[7].DecodeColourString();
                colourOrder[2] = allStrings[8].DecodeColourString();

                int canInputInt = Convert.ToInt32(allStrings[9]);
                CanInput = Convert.ToBoolean(canInputInt);

                SetColourImages();
            }      
        }

        private void SetColourImages()
        {   
            for (int i = 0; i < laneColours.Length; i++)
            {
                if (i == 0) laneColours[0].color = selectedColour;
                else laneColours[i].color = colourOrder[i - 1];
            }
        }
    }

}