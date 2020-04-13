using System;
using System.IO.Ports;
using UnityEngine;

using comp140.data;
using comp140.interfaces;

namespace comp140.input
{
    public class ArduinoInput : MonoBehaviour, ILane
    {
        [Header("Arduino Settings")]
        [SerializeField]
        private int commPort;
        private SerialPort serial = null;

        [Header("Input Settings")]
        private const int numOfLanes = 2;
        private Lane[] lanes = new Lane[numOfLanes];

        private void Start()
        {
            ConnectToSerial();

            for (int i = 0; i < numOfLanes; i++)
            {
                lanes[i] = new Lane(i);
            }
        }

        private void Update()
        {
            for (int i = 0; i < numOfLanes; i++)
            {
                GetArduinoInput(i);
            }
        }

        private void ConnectToSerial()
        {
            serial = new SerialPort("\\\\.\\COM" + commPort, 9600);
            serial.ReadTimeout = 50;
            serial.Open();
        }

        private void GetArduinoInput(int laneIndex)
        {
            lanes[laneIndex].encoderValue = Convert.ToInt32(GetEncoderInputFromArduino("encoderValue" + laneIndex));
            lanes[laneIndex].timeLeft = float.Parse(GetEncoderInputFromArduino("timeLeft" + laneIndex));

            lanes[laneIndex].selectedColour = ColourConverter.DecodeColourString(GetEncoderInputFromArduino("selectedColour" + laneIndex));

            lanes[laneIndex].colourOrder[0] = ColourConverter.DecodeColourString(GetEncoderInputFromArduino("firstColour" + laneIndex));
            lanes[laneIndex].colourOrder[1] = ColourConverter.DecodeColourString(GetEncoderInputFromArduino("secondColour" + laneIndex));
            lanes[laneIndex].colourOrder[2] = ColourConverter.DecodeColourString(GetEncoderInputFromArduino("thirdColour" + laneIndex));
        }

        private string GetEncoderInputFromArduino(string identifier)
        {
            WriteToArduino(identifier);
            String value = ReadFromArduino(50);

            if (value != null)
            {
                return value;
            }

            return null;
        }

        private void WriteToArduino(string message)
        {
            serial.WriteLine(message);
            serial.BaseStream.Flush();
        }

        private string ReadFromArduino(int timeout = 0)
        {
            serial.ReadTimeout = timeout;

            try
            {
                return serial.ReadLine();
            }

            catch
            {
                return null;
            }
        }

        private void OnDestroy()
        {
            serial.Close();
        }

        #region ILane Interface Implementation
        public Lane GetLane(int index)
        {
            return lanes[index];
        }

        public Lane[] GetAllLanes()
        {
            return lanes;
        }
        #endregion
    }

}