using System;
using System.Collections.Generic;
using UnityEngine;

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
        public Color32 selectedColour = Color.black;
        public List<Color32> colourOrder = new List<Color32>(maxNumOfColours);
        private const int maxNumOfColours = 3;
        public float timeLeft = 0.0f;

        public Lane(int laneIndex)
        {
            this.laneIndex = laneIndex;
        }
    }

}